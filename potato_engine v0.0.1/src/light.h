#ifndef LIGHT_H
#define LIGHT_H

#include <SDL3/SDL.h>

#include <array>
#include <cstddef>
#include <vector>

#include "color.h"
#include "vec.h"

class Camera;
class Logger;
class Light_System;

/** A soft 2D point light that automatically registers with Engine::lighting. */
class light_source {
public:
    explicit light_source(
        Vec position = {},
        float radius = 160.0f,
        Color color = Color::white(),
        float intensity = 1.0f,
        float softness = 0.35f
    );
    ~light_source();

    light_source(const light_source&) = delete;
    light_source& operator=(const light_source&) = delete;

    Vec position{};
    Color color = Color::white();
    float radius = 160.0f;
    float intensity = 1.0f;
    float softness = 0.35f;
    bool enabled = true;
    bool screen_space = false;

private:
    friend class Light_System;
    Light_System* registered_system = nullptr;
};

/** Packs light_source values into an SDL_GPU fragment-shader uniform block. */
class Light_System {
public:
    static constexpr std::size_t MAX_LIGHTS = 16;

    Light_System() = default;
    ~Light_System() { shutdown(); }

    Light_System(const Light_System&) = delete;
    Light_System& operator=(const Light_System&) = delete;

    bool init(SDL_Renderer* renderer, SDL_GPUDevice* device, Logger* logger = nullptr);
    void shutdown();

    void update(float delta_time);
    bool begin_world_pass(const Camera* camera);
    void set_active(bool active, SDL_ScaleMode scale_mode = SDL_SCALEMODE_LINEAR);
    void end_world_pass();

    void register_light(light_source* light);
    void unregister_light(light_source* light);

    void set_time_of_day(float hour);
    float get_time_of_day() const { return time_of_day; }
    float get_night_amount() const;

    void set_auto_advance(bool enabled) { auto_advance = enabled; }
    bool is_auto_advance_enabled() const { return auto_advance; }
    void set_day_length(float seconds);
    void set_night_ambient(Color color, float strength);
    void set_shadow_strength(float strength);

    bool is_ready() const { return render_state != nullptr; }
    std::size_t light_count() const { return lights.size(); }

private:
    struct alignas(16) Float4 {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        Float4() = default;
        Float4(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w) {}

        Float4(const Vec& vec, float z = 0.0f, float w = 0.0f)
            : x(vec.x), y(vec.y), z(z), w(w) {}
        
        Float4(const Color& color, float w = 1.0f)
            : x(static_cast<float>(color.r) / 255.0f),
              y(static_cast<float>(color.g) / 255.0f),
              z(static_cast<float>(color.b) / 255.0f), w(w) {}
        
        Float4(const Vec4& vec)
            : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    };

    struct alignas(16) GPU_Uniforms {
        Float4 viewport{}; // output width, output height, light count, shadow strength
        Float4 ambient{};  // night RGB, night ambient strength
        Float4 cycle{};    // night amount, logical width, logical height, pixel-art flag
        std::array<Float4, MAX_LIGHTS> light_position_radius{};
        std::array<Float4, MAX_LIGHTS> light_color_softness{};
    };

    SDL_Renderer* renderer = nullptr;
    SDL_GPUDevice* device = nullptr;
    SDL_GPUShader* fragment_shader = nullptr;
    SDL_GPURenderState* render_state = nullptr;
    SDL_GPURenderState* pixelart_render_state = nullptr;
    SDL_GPURenderState* active_render_state = nullptr;
    Logger* logger = nullptr;
    std::vector<light_source*> lights;

    float time_of_day = 12.0f;
    float sunrise = 6.0f;
    float sunset = 19.0f;
    float transition_hours = 1.0f;
    float day_length_seconds = 600.0f;
    float night_ambient_strength = 0.28f;
    float shadow_strength = 0.80f;
    Color night_ambient = {64, 82, 145, 255};
    bool auto_advance = false;
    bool world_pass_started = false;
    bool state_active = false;
};

#endif
