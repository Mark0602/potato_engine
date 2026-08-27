#ifndef POTATO_ENGINE_H
#define POTATO_ENGINE_H

#include <SDL3/SDL.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <iostream>


#include "src/simdjson.h"

class Asset_Pool;
class Camera_Pool;
class GPU_Renderer;
class Light_System;
class Loading_Screen;
class Logger;
class Object_Pool;
class Render_Pool;
class Save_Pool;
class SceneManager;
class Track_Pool;
class script;
namespace Physics { class Physics_Engine; }

enum class RendererBackend : std::uint8_t {
    CPU,
    GPU
};

/** Owns the SDL window and the selected renderer backend. */
class SDLstate final {
public:
    SDLstate(
        std::string title = "Potato Engine",
        std::uint16_t window_width = 1280,
        std::uint16_t window_height = 720,
        std::uint16_t logical_width = 1280,
        std::uint16_t logical_height = 720
    );
    ~SDLstate();

    SDLstate(const SDLstate&) = delete;
    SDLstate& operator=(const SDLstate&) = delete;

    bool initiate(RendererBackend backend = RendererBackend::CPU);
    void clearup();
    bool begin_frame();
    void present();

    std::uint16_t getwindowwidth() const { return width_; }
    std::uint16_t getwindowheight() const { return height_; }
    std::uint16_t getlogicalwidth() const { return logical_width_; }
    std::uint16_t getlogicalheight() const { return logical_height_; }
    RendererBackend get_renderer_backend() const { return renderer_backend_; }
    bool is_gpu_renderer() const {
        return renderer_backend_ == RendererBackend::GPU;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_GPUDevice* gpu_device = nullptr;
    bool run = true;

private:
    std::string title_;
    std::uint16_t width_;
    std::uint16_t height_;
    std::uint16_t logical_width_;
    std::uint16_t logical_height_;
    RendererBackend renderer_backend_ = RendererBackend::CPU;
    GPU_Renderer* gpu_renderer_ = nullptr;
    bool sdl_initialized_ = false;
};

namespace config {
    struct project_config {
        std::string name = "My Game made with Potato Engine";
        std::string version = "0.0.1";
        std::string company = "Random Studio";
    };

    struct game_config {
        std::string title = "My Game made with Potato Engine";
        std::string version = "0.0.1";
        std::string log_path = "logs/latest.log";
        uint16_t window_width = 1280; 
        uint16_t logical_width = 1280;
        uint16_t window_height = 720;
        uint16_t logical_height = 720;
        RendererBackend renderer_backend = RendererBackend::CPU;
        uint8_t audio_tracks = 8;
        bool enable_shaders = true;
        bool show_console = false;
    };

    struct settings {
        uint32_t target_fps = 60;
        uint32_t background_fps = 20;
        bool fullscreen = false;
        bool vsync = false;
    };

    inline static bool load_config(const std::string& path, project_config& pconf, game_config& gconf, settings& settings) {

        simdjson::ondemand::parser parser;
        simdjson::padded_string json;

        auto error = simdjson::padded_string::load(path).get(json);
        if (error) {
            std::cerr << "Failed to load config: "
                    << simdjson::error_message(error)
                    << '\n';
            return false;
        }

        auto document = parser.iterate(json);

        auto project = document["project"].get_object();
        auto game = document["game"].get_object();
        auto dimensions = game["dimensions"].get_object();
        auto window = dimensions["window"].get_object();
        auto logical = dimensions["logical"].get_object();
        auto settings_obj = document["settings"].get_object();

        std::string_view name;
        if (!project["name"].get_string().get(name)) pconf.name = name;
        std::string_view pversion;
        if (!project["version"].get_string().get(pversion)) pconf.version = pversion;
        std::string_view company;
        if (!project["company"].get_string().get(company)) pconf.company = company;

        std::string_view title;
        if (!game["title"].get_string().get(title)) gconf.title = title;
        std::string_view gversion;
        if (!game["version"].get_string().get(gversion)) gconf.version = gversion;
        std::string_view log_path;
        if (!game["default log path"].get_string().get(log_path)) gconf.log_path = log_path;
        
        uint32_t window_w;
        if (!window["width"].get_uint32().get(window_w)) {
            if (window_w <= UINT16_MAX) gconf.window_width = static_cast<uint16_t>(window_w);
        }
        uint32_t window_h;
        if (!window["height"].get_uint32().get(window_h)) {
            if (window_h <= UINT16_MAX) gconf.window_height = static_cast<uint16_t>(window_h);
        }
        uint32_t logical_w;
        if (!logical["width"].get_uint32().get(logical_w)) {
            if (logical_w <= UINT16_MAX) gconf.logical_width = static_cast<uint16_t>(logical_w);
        }
        uint32_t logical_h;
        if (!logical["height"].get_uint32().get(logical_h)) {
            if (logical_h <= UINT16_MAX) gconf.logical_height = static_cast<uint16_t>(logical_h);
        }
        std::string_view backend_text;
        if(!game["renderer backend"].get_string().get(backend_text)) {
            if (backend_text == "GPU") gconf.renderer_backend = RendererBackend::GPU;
            else if (backend_text == "CPU") gconf.renderer_backend = RendererBackend::CPU;
        }
        uint32_t default_audio_tracks;
        if(!game["default audio tracks"].get_uint32().get(default_audio_tracks)) {
            if (default_audio_tracks <= UINT8_MAX) gconf.audio_tracks = static_cast<uint8_t>(default_audio_tracks);
        }
        bool en_shaders;
        if(!game["enable shaders"].get_bool().get(en_shaders)) gconf.enable_shaders = en_shaders;
        bool show_console;
        if(!game["show console on start"].get_bool().get(show_console)) gconf.show_console = show_console;
        
        uint32_t target_fps;
        if(!settings_obj["target fps"].get_uint32().get(target_fps)) settings.target_fps = target_fps;
        uint32_t background_fps;
        if(!settings_obj["background fps"].get_uint32().get(background_fps)) settings.background_fps = background_fps;
        bool fullscreen;
        if(!settings_obj["fullscreen"].get_bool().get(fullscreen)) settings.fullscreen = fullscreen;
        bool vsync;
        if(!settings_obj["vsync"].get_bool().get(vsync)) settings.vsync = vsync;
        
        return true;
    }
}

namespace Engine {

/** Configuration for the reusable Potato Engine application loop. */


/**
 * Owns engine services, registered scripts and the frame loop.
 *
 * A game can link `Potato::Engine`, register scripts with `REGISTER_SCRIPT`,
 * then create this class from its small executable entry point.
 */
class Application final {
public:
    explicit Application(config::game_config config = {});
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    bool initialize();
    int run();
    void shutdown();
    bool is_initialized() const;

private:
    class Implementation;
    std::unique_ptr<Implementation> implementation_;
};

// Borrowed process-wide service pointers. Application sets and clears these.
inline Light_System* lighting = nullptr;
inline SDLstate* context = nullptr;
inline SDL_Renderer* renderer = nullptr;
inline SDL_GPUDevice* gpu_device = nullptr;
inline RendererBackend renderer_backend = RendererBackend::CPU;
inline SDL_Window* window = nullptr;
inline std::uint16_t logical_width = 0;
inline std::uint16_t logical_height = 0;
inline Render_Pool* render_pool = nullptr;
inline Logger* logger = nullptr;
inline SceneManager* scene_manager = nullptr;
inline Loading_Screen* loading_screen = nullptr;
inline int delta_time = 0;
inline float fps = 0.0f;
inline float avg_fps = 0.0f;
inline Object_Pool* object_pool = nullptr;
inline Save_Pool* save_pool = nullptr;
inline Camera_Pool* camera_pool = nullptr;
inline Asset_Pool* asset_pool = nullptr;
inline Track_Pool* track_pool = nullptr;
inline Physics::Physics_Engine* physics_engine = nullptr;
inline float master_gain = 1.0f;
inline std::vector<script*> object_scripts = {};

inline bool using_gpu_renderer() {
    return renderer_backend == RendererBackend::GPU;
}

inline void quit() {
    if (context) context->run = false;
}

} // namespace Engine

#endif // POTATO_ENGINE_H
