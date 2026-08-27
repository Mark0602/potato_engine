#include "light.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>

#include "camera.h"
#include "debug.h"
#include "engine.h"

namespace {

float smoothstep(float edge0, float edge1, float value) {
    if (edge0 == edge1) return value < edge0 ? 0.0f : 1.0f;
    const float t = std::clamp((value - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

float color_channel(std::uint8_t value) {
    return static_cast<float>(value) / 255.0f;
}

} // namespace

light_source::light_source(Vec position, float radius, Color color, float intensity, float softness)
    : position(position), color(color), radius(radius), intensity(intensity), softness(softness) {
    if (Engine::lighting) Engine::lighting->register_light(this);
}

light_source::~light_source() {
    if (registered_system) registered_system->unregister_light(this);
}

bool Light_System::init(SDL_Renderer* new_renderer, SDL_GPUDevice* new_device, Logger* new_logger) {
    shutdown();
    renderer = new_renderer;
    device = new_device;
    logger = new_logger;

    // GPU-only enhancement; light_source remains valid on the legacy backend.
    if (!renderer || !device) return true;

    const char* driver = SDL_GetGPUDeviceDriver(device);
    const char* shader_path = nullptr;
    const char* entrypoint = "main";
    SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;

    if (driver && std::strcmp(driver, "direct3d12") == 0) {
        shader_path = "assets/shaders/day_night_light.frag.dxil";
        format = SDL_GPU_SHADERFORMAT_DXIL;
    } else if (driver && std::strcmp(driver, "vulkan") == 0) {
        shader_path = "assets/shaders/day_night_light.frag.spv";
        format = SDL_GPU_SHADERFORMAT_SPIRV;
    } else if (driver && std::strcmp(driver, "metal") == 0) {
        shader_path = "assets/shaders/day_night_light.frag.msl";
        entrypoint = "main0";
        format = SDL_GPU_SHADERFORMAT_MSL;
    } else {
        if (logger) logger->log(Log_Level::WARNING, "Lighting", "No day-night shader for the active SDL_GPU driver.");
        return true;
    }

    std::size_t code_size = 0;
    void* shader_code = SDL_LoadFile(shader_path, &code_size);
    if (!shader_code || code_size == 0) {
        if (logger) logger->log(Log_Level::ERROR, "Lighting", "Failed to load shader '" + std::string(shader_path) + "': " + SDL_GetError());
        if (shader_code) SDL_free(shader_code);
        return false;
    }

    SDL_GPUShaderCreateInfo shader_info{};
    shader_info.code_size = code_size;
    shader_info.code = static_cast<const Uint8*>(shader_code);
    shader_info.entrypoint = entrypoint;
    shader_info.format = format;
    shader_info.stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
    shader_info.num_samplers = 1;
    shader_info.num_uniform_buffers = 1;

    fragment_shader = SDL_CreateGPUShader(device, &shader_info);
    SDL_free(shader_code);
    if (!fragment_shader) {
        if (logger) logger->log(Log_Level::ERROR, "Lighting", "Failed to create SDL_GPU lighting shader: " + std::string(SDL_GetError()));
        return false;
    }

    SDL_GPURenderStateCreateInfo state_info{};
    state_info.fragment_shader = fragment_shader;
    render_state = SDL_CreateGPURenderState(renderer, &state_info);
    if (!render_state) {
        if (logger) logger->log(Log_Level::ERROR, "Lighting", "Failed to create GPU render state: " + std::string(SDL_GetError()));
        SDL_ReleaseGPUShader(device, fragment_shader);
        fragment_shader = nullptr;
        return false;
    }
    pixelart_render_state = SDL_CreateGPURenderState(renderer, &state_info);
    if (!pixelart_render_state) {
        if (logger) logger->log(Log_Level::ERROR, "Lighting", "Failed to create pixel-art GPU render state: " + std::string(SDL_GetError()));
        SDL_DestroyGPURenderState(render_state);
        render_state = nullptr;
        SDL_ReleaseGPUShader(device, fragment_shader);
        fragment_shader = nullptr;
        return false;
    }

    if (logger) logger->log(Log_Level::INFO, "Lighting", "Loaded day-night shader for " + std::string(driver));
    return true;
}

void Light_System::shutdown() {
    if (active_render_state && renderer) SDL_SetGPURenderState(renderer, nullptr);
    state_active = false;
    active_render_state = nullptr;
    world_pass_started = false;
    if (pixelart_render_state) {
        SDL_DestroyGPURenderState(pixelart_render_state);
        pixelart_render_state = nullptr;
    }
    if (render_state) {
        SDL_DestroyGPURenderState(render_state);
        render_state = nullptr;
    }
    if (fragment_shader && device) {
        SDL_ReleaseGPUShader(device, fragment_shader);
        fragment_shader = nullptr;
    }
    for (light_source* light : lights) {
        if (light && light->registered_system == this) light->registered_system = nullptr;
    }
    lights.clear();
    renderer = nullptr;
    device = nullptr;
    logger = nullptr;
}

void Light_System::register_light(light_source* light) {
    if (!light) return;
    if (light->registered_system && light->registered_system != this)
        light->registered_system->unregister_light(light);
    if (std::find(lights.begin(), lights.end(), light) == lights.end()) lights.push_back(light);
    light->registered_system = this;
}

void Light_System::unregister_light(light_source* light) {
    if (!light) return;
    lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
    if (light->registered_system == this) light->registered_system = nullptr;
}

void Light_System::set_time_of_day(float hour) {
    time_of_day = std::fmod(hour, 24.0f);
    if (time_of_day < 0.0f) time_of_day += 24.0f;
}

void Light_System::set_day_length(float seconds) {
    day_length_seconds = std::max(1.0f, seconds);
}

void Light_System::set_night_ambient(Color color, float strength) {
    night_ambient = color;
    night_ambient_strength = std::clamp(strength, 0.0f, 1.0f);
}

void Light_System::set_shadow_strength(float strength) {
    shadow_strength = std::clamp(strength, 0.0f, 1.0f);
}

void Light_System::update(float delta_time) {
    if (auto_advance && day_length_seconds > 0.0f)
        set_time_of_day(time_of_day + delta_time * (24.0f / day_length_seconds));
}

float Light_System::get_night_amount() const {
    const float dawn = smoothstep(sunrise - transition_hours, sunrise + transition_hours, time_of_day);
    const float dusk = smoothstep(sunset - transition_hours, sunset + transition_hours, time_of_day);
    return 1.0f - dawn * (1.0f - dusk);
}

bool Light_System::begin_world_pass(const Camera* camera) {
    world_pass_started = false;
    if (!render_state || !renderer) return false;

    int output_width = static_cast<int>(Engine::logical_width);
    int output_height = static_cast<int>(Engine::logical_height);
    SDL_GetCurrentRenderOutputSize(renderer, &output_width, &output_height);
    output_width = std::max(1, output_width);
    output_height = std::max(1, output_height);

    GPU_Uniforms uniforms{};
    uniforms.viewport = {static_cast<float>(output_width), static_cast<float>(output_height), 0.0f, shadow_strength};
    uniforms.ambient = {
        color_channel(night_ambient.r), color_channel(night_ambient.g),
        color_channel(night_ambient.b), night_ambient_strength
    };
    uniforms.cycle = {
        get_night_amount(),
        static_cast<float>(std::max<std::uint16_t>(1, Engine::logical_width)),
        static_cast<float>(std::max<std::uint16_t>(1, Engine::logical_height)), 0.0f
    };

    std::size_t written = 0;
    for (const light_source* light : lights) {
        if (!light || !light->enabled || light->radius <= 0.0f || light->intensity <= 0.0f) continue;
        if (written >= MAX_LIGHTS) break;
        Vec screen_position = light->position;
        float screen_radius = light->radius;
        if (!light->screen_space && camera) {
            screen_position = camera->world_to_screen(light->position);
            screen_radius *= camera->get_zoom();
        }
        uniforms.light_position_radius[written] = {
            screen_position.x, screen_position.y, screen_radius, light->intensity
        };
        uniforms.light_color_softness[written] = {
            color_channel(light->color.r), color_channel(light->color.g),
            color_channel(light->color.b), std::clamp(light->softness, 0.001f, 0.999f)
        };
        ++written;
    }
    uniforms.viewport.z = static_cast<float>(written);

    if (!SDL_SetGPURenderStateFragmentUniforms(render_state, 0, &uniforms, sizeof(uniforms))) {
        if (logger) logger->log(Log_Level::ERROR, "Lighting", "Failed to update lighting uniforms: " + std::string(SDL_GetError()));
        return false;
    }

    // SDL's PIXELART sampler is linear by design: its built-in fragment shader
    // adjusts the UVs before sampling. A custom render state replaces that
    // shader, so keep a second state which performs the same UV correction.
    GPU_Uniforms pixelart_uniforms = uniforms;
    pixelart_uniforms.cycle.w = 1.0f;
    if (!SDL_SetGPURenderStateFragmentUniforms(
            pixelart_render_state, 0, &pixelart_uniforms, sizeof(pixelart_uniforms))) {
        if (logger) logger->log(Log_Level::ERROR, "Lighting", "Failed to update pixel-art lighting uniforms: " + std::string(SDL_GetError()));
        return false;
    }
    world_pass_started = true;
    set_active(true);
    return state_active;
}

void Light_System::set_active(bool active, SDL_ScaleMode scale_mode) {
    if (!world_pass_started || !renderer || !render_state || !pixelart_render_state) return;
    SDL_GPURenderState* desired_state = nullptr;
    if (active) {
        desired_state = scale_mode == SDL_SCALEMODE_PIXELART
            ? pixelart_render_state
            : render_state;
    }
    if (active_render_state == desired_state) return;
    if (SDL_SetGPURenderState(renderer, desired_state)) {
        active_render_state = desired_state;
        state_active = desired_state != nullptr;
    } else if (logger) {
        logger->log(Log_Level::ERROR, "Lighting", "Failed to switch GPU lighting state: " + std::string(SDL_GetError()));
    }
}

void Light_System::end_world_pass() {
    set_active(false);
    world_pass_started = false;
}
