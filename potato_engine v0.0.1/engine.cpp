#include "engine.h"

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <utility>

#include "src/asset_pool.h"
#include "src/audio.h"
#include "src/camera.h"
#include "src/debug.h"
#include "src/game_console.h"
#include "src/input.h"
#include "src/light.h"
#include "src/loading_screen.h"
#include "src/object.h"
#include "src/physics.h"
#include "src/render.h"
#include "src/save_game.h"
#include "src/scene.h"
#include "src/script-base.h"
#include "src/script-registry.h"

SDLstate::SDLstate(
    std::string title,
    std::uint16_t window_width,
    std::uint16_t window_height,
    std::uint16_t logical_width,
    std::uint16_t logical_height
)
    : title_(title.empty() ? "Potato Engine" : std::move(title)),
      width_(window_width),
      height_(window_height),
      logical_width_(logical_width),
      logical_height_(logical_height) {}

SDLstate::~SDLstate() {
    clearup();
}

void SDLstate::clearup() {
    if (gpu_renderer_) {
        gpu_renderer_->shutdown();
        delete gpu_renderer_;
        gpu_renderer_ = nullptr;
    } else if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    renderer = nullptr;
    gpu_device = nullptr;

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if (sdl_initialized_) {
        SDL_Quit();
        sdl_initialized_ = false;
    }
}

bool SDLstate::initiate(RendererBackend backend) {
    if (window && renderer) return true;

    renderer_backend_ = backend;
    run = true;
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD)) {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Potato Engine",
            "Failed to initialize SDL3.",
            nullptr
        );
        return false;
    }
    sdl_initialized_ = true;

    window = SDL_CreateWindow(
        title_.c_str(), width_, height_, SDL_WINDOW_RESIZABLE
    );
    if (!window) {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Potato Engine",
            SDL_GetError(),
            nullptr
        );
        return false;
    }

    if (renderer_backend_ == RendererBackend::GPU) {
        gpu_renderer_ = new GPU_Renderer();
        if (gpu_renderer_->init(window)) {
            renderer = gpu_renderer_->renderer();
            gpu_device = gpu_renderer_->device();
        }
    } else {
        renderer = SDL_CreateRenderer(window, nullptr);
    }

    if (!renderer) {
        const std::string error = std::string("Failed to initialize the ") +
            (renderer_backend_ == RendererBackend::GPU ? "SDL_GPU" : "SDL") +
            " renderer: " + SDL_GetError();
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR, "Potato Engine", error.c_str(), nullptr
        );
        return false;
    }

    if (!SDL_SetRenderLogicalPresentation(
            renderer,
            logical_width_,
            logical_height_,
            SDL_LOGICAL_PRESENTATION_LETTERBOX
        )) {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Potato Engine",
            SDL_GetError(),
            nullptr
        );
        return false;
    }
    return true;
}

bool SDLstate::begin_frame() {
    if (gpu_renderer_) return gpu_renderer_->begin_frame();
    if (!renderer) return false;
    return SDL_SetRenderDrawColor(renderer, 12, 18, 28, 255) &&
           SDL_RenderClear(renderer);
}

void SDLstate::present() {
    if (gpu_renderer_) gpu_renderer_->end_frame();
    else if (renderer) SDL_RenderPresent(renderer);
}

namespace Engine {

class Application::Implementation final {
public:
    explicit Implementation(config::game_config application_config)
        : config(std::move(application_config)),
          state(
              config.title,
              config.window_width,
              config.window_height,
              config.logical_width,
              config.logical_height
          ) {}

    bool initialize() {
        if (initialized) return true;
        if (config.show_console) game_console::show_console();

        if (!state.initiate(config.renderer_backend)) return false;
        initialized = true;

        if (!MIX_Init()) {
            std::cerr << "Failed to initialize SDL_mixer: "
                      << SDL_GetError() << '\n';
            shutdown();
            return false;
        }
        mixer_initialized = true;

        if (!TTF_Init()) {
            std::cerr << "Failed to initialize SDL_ttf: "
                      << SDL_GetError() << '\n';
            shutdown();
            return false;
        }
        ttf_initialized = true;

        mixer = MIX_CreateMixerDevice(
            SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr
        );
        if (!mixer) {
            std::cerr << "Failed to create the audio mixer: "
                      << SDL_GetError() << '\n';
            shutdown();
            return false;
        }

        context = &state;
        renderer = state.renderer;
        gpu_device = state.gpu_device;
        renderer_backend = state.get_renderer_backend();
        window = state.window;
        logical_width = state.getlogicalwidth();
        logical_height = state.getlogicalheight();

        logger = new Logger();
        logger->init(config.log_path);
        logger->flood_logging(false);
        render_pool = new Render_Pool(renderer);
        scene_manager = &SceneManager::instance();
        object_pool = new Object_Pool();
        physics_engine = new Physics::Physics_Engine(logger);
        save_pool = new Save_Pool();
        camera_pool = new Camera_Pool();
        camera_pool->main_camera()->set_viewport({
            static_cast<float>(logical_width),
            static_cast<float>(logical_height)
        });
        track_pool = new Track_Pool(mixer, config.audio_tracks, logger);
        asset_pool = new Asset_Pool(renderer, logger);
        loading_screen = new Loading_Screen(renderer, logger);
        if (config.enable_shaders) {
            lighting = new Light_System();
            if (!lighting->init(renderer, gpu_device, logger)) {
                logger->log(
                    Log_Level::WARNING,
                    "Lighting",
                    "Lighting initialization failed; continuing without the effect."
                );
            }
        }

        Input::init();
        input_initialized = true;
        scripts = script_registry::instance().create_all_scripts();
        last_scene = scene_manager->current_scene();

        loading_screen->begin("Starting Potato Engine");
        for (script* registered_script : scripts) {
            if (!is_active(registered_script)) continue;
            loading_screen->enqueue("Starting script", [this, registered_script]() {
                registered_script->on_start();
                started_scripts.insert(registered_script);
            });
        }

        logger->log(
            Log_Level::INFO,
            "Engine",
            std::string("Potato Engine initialized with ") +
                (using_gpu_renderer() ? "SDL_GPU" : "SDL") + " rendering."
        );
        return true;
    }

    int run() {
        if (!initialize()) return -1;

        Uint64 last_tick = SDL_GetTicksNS();
        float frame_timer = 0.0f;
        int frame_counter = 0;

        while (state.run) {
            const Uint64 frame_start = SDL_GetTicksNS();
            const float frame_delta = std::min(
                static_cast<float>(frame_start - last_tick) / 1000000000.0f,
                0.1f
            );
            last_tick = frame_start;

            Input::begin_frame();
            process_scene_transition();

            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                Input::handle_event(event);
                game_console::handle_event(event);

                if (event.type == SDL_EVENT_QUIT ||
                    event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                    quit();
                }

                if (!loading_screen->active()) {
                    for (script* registered_script : scripts) {
                        if (is_active(registered_script)) {
                            registered_script->on_event(event);
                        }
                    }
                    for (script* attached_script : object_scripts) {
                        if (is_active(attached_script)) {
                            attached_script->on_event(event);
                        }
                    }
                }
            }

            Input::update();
            if (loading_screen->active()) {
                loading_screen->update(frame_delta);
                if (loading_screen->failed()) {
                    exit_code = -1;
                    quit();
                }
            } else {
                update_scripts(frame_delta);
                if (physics_engine) physics_engine->update(frame_delta);
                if (track_pool) track_pool->flush_tracks(frame_delta);
                if (lighting) lighting->update(frame_delta);
                process_scene_transition();
            }

            state.begin_frame();
            if (loading_screen->active()) {
                loading_screen->render(frame_delta);
            } else if (!loading_screen->failed()) {
                render_scripts();
            }
            state.present();

            delta_time = static_cast<int>(frame_delta * 1000.0f);
            fps = frame_delta > 0.0f ? 1.0f / frame_delta : 0.0f;
            frame_timer += frame_delta;
            ++frame_counter;
            if (frame_timer >= 1.0f) {
                avg_fps = static_cast<float>(frame_counter) / frame_timer;
                frame_timer = 0.0f;
                frame_counter = 0;
            }

            pace_frame(frame_start);
        }

        return exit_code;
    }

    void shutdown() {
        if (!initialized) return;

        for (script* registered_script : scripts) {
            registered_script->on_destroy();
            delete registered_script;
        }
        scripts.clear();
        started_scripts.clear();

        while (!object_scripts.empty()) {
            script* attached_script = object_scripts.back();
            object_scripts.pop_back();
            attached_script->on_destroy();
            delete attached_script;
        }

        delete loading_screen;
        loading_screen = nullptr;
        delete lighting;
        lighting = nullptr;
        delete asset_pool;
        asset_pool = nullptr;
        delete track_pool;
        track_pool = nullptr;
        delete physics_engine;
        physics_engine = nullptr;
        delete render_pool;
        render_pool = nullptr;
        delete save_pool;
        save_pool = nullptr;
        delete camera_pool;
        camera_pool = nullptr;
        delete object_pool;
        object_pool = nullptr;
        scene_manager = nullptr;

        if (input_initialized) {
            Input::shutdown();
            input_initialized = false;
        }

        if (mixer) {
            MIX_DestroyMixer(mixer);
            mixer = nullptr;
        }
        if (ttf_initialized) {
            TTF_Quit();
            ttf_initialized = false;
        }
        if (mixer_initialized) {
            MIX_Quit();
            mixer_initialized = false;
        }

        if (logger) {
            logger->log(Log_Level::INFO, "Engine", "Potato Engine stopped.");
            logger->finalize_log();
            logger->close();
            delete logger;
            logger = nullptr;
        }

        context = nullptr;
        renderer = nullptr;
        gpu_device = nullptr;
        window = nullptr;
        logical_width = 0;
        logical_height = 0;
        delta_time = 0;
        fps = 0.0f;
        avg_fps = 0.0f;
        initialized = false;
    }

    bool is_initialized() const { return initialized; }

private:
    bool is_active(const script* candidate) const {
        return candidate && scene_manager &&
            (candidate->scene_id() == -1 ||
             candidate->scene_id() == scene_manager->current_scene());
    }

    void begin_scene_transition(int target_scene) {
        const std::string& name = scene_manager->scene_name(target_scene);
        loading_screen->begin(
            name.empty() ? "Loading scene" : "Loading " + name,
            [this, target_scene]() {
                scene_manager->complete_transition(target_scene);
                last_scene = target_scene;
            }
        );

        for (SceneManager::Load_Task& task :
             scene_manager->take_load_tasks(target_scene)) {
            loading_screen->enqueue_step(
                task.label, std::move(task.step), task.weight
            );
        }

        for (script* registered_script : scripts) {
            if (registered_script->scene_id() != target_scene ||
                started_scripts.find(registered_script) !=
                    started_scripts.end()) {
                continue;
            }
            loading_screen->enqueue("Starting scene script", [this, registered_script]() {
                registered_script->on_start();
                started_scripts.insert(registered_script);
            });
        }
    }

    void process_scene_transition() {
        if (!loading_screen || loading_screen->active() || !scene_manager) return;

        int target_scene = -1;
        if (scene_manager->consume_scene_request(target_scene)) {
            begin_scene_transition(target_scene);
            return;
        }
        if (scene_manager->current_scene() != last_scene) {
            begin_scene_transition(scene_manager->current_scene());
        }
    }

    void update_scripts(float frame_delta) {
        for (script* registered_script : scripts) {
            if (is_active(registered_script)) {
                registered_script->on_update(frame_delta);
            }
        }
        for (script* attached_script : object_scripts) {
            if (is_active(attached_script)) {
                attached_script->on_update(frame_delta);
            }
        }
    }

    void render_scripts() {
        if (lighting) {
            lighting->begin_world_pass(camera_pool->active_camera());
        }

        for (script* registered_script : scripts) {
            if (is_active(registered_script)) registered_script->on_render();
        }
        for (script* attached_script : object_scripts) {
            if (is_active(attached_script)) attached_script->on_render();
        }
        for (Object* object : object_pool->get_all()) {
            if (object && object->visible && object->auto_submit) {
                object->submit_draw_commands(*render_pool);
            }
        }
        render_pool->flush();
        if (lighting) lighting->end_world_pass();

        for (script* registered_script : scripts) {
            if (is_active(registered_script)) {
                registered_script->on_post_render();
            }
        }
        for (script* attached_script : object_scripts) {
            if (is_active(attached_script)) {
                attached_script->on_post_render();
            }
        }
    }

    void pace_frame(Uint64 frame_start) const {
        const bool focused = window &&
            (SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS) != 0;
        const int frame_limit = focused
            ? settings.target_fps
            : settings.background_fps;
        if (frame_limit <= 0) return;

        const Uint64 target_duration =
            1000000000ull / static_cast<Uint64>(frame_limit);
        const Uint64 elapsed = SDL_GetTicksNS() - frame_start;
        if (elapsed < target_duration) {
            SDL_DelayPrecise(target_duration - elapsed);
        }
    }

    config::game_config config;
    config::settings settings;
    SDLstate state;
    MIX_Mixer* mixer = nullptr;
    std::vector<script*> scripts;
    std::unordered_set<script*> started_scripts;
    int last_scene = 0;
    int exit_code = 0;
    bool initialized = false;
    bool mixer_initialized = false;
    bool ttf_initialized = false;
    bool input_initialized = false;
};

Application::Application(config::game_config config)
    : implementation_(
          std::make_unique<Implementation>(std::move(config))
      ) {}

Application::~Application() {
    shutdown();
}

bool Application::initialize() {
    return implementation_->initialize();
}

int Application::run() {
    return implementation_->run();
}

void Application::shutdown() {
    if (implementation_) implementation_->shutdown();
}

bool Application::is_initialized() const {
    return implementation_ && implementation_->is_initialized();
}

} // namespace Engine
