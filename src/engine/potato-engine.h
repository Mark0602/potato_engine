#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include <vector>
#include "potato-render.h"
#include "potato-script-base.h"


// =============================================================================
// POTATO ENGINE CLASS
// =============================================================================

class potato_engine {
public:
    potato_engine();
    ~potato_engine();

    int window_w = 800;
    int window_h = 600;
    const char* window_title = "Potato Engine";

    bool initialize();
    void update(float delta_time);
    void handle_event(const SDL_Event& event);
    void render();
    void render_scripts();
    void shutdown();

    void add_script(potato_script* script);

    SDL_Window* get_window() const { return window; }
    SDL_GPUDevice* get_device() const { return device; }

    potato_render_mode get_render_mode() const { return render_mode; }
    void set_render_mode(potato_render_mode mode) { render_mode = mode; }

    void draw_vertex_buffer(potato_vertex_buffer* vertex_buffer, size_t vertex_count);

    void set_title(const char* title) { window_title = title; SDL_SetWindowTitle(window, title); }

private:
    SDL_Window* window;
    SDL_GPUDevice* device;
    potato_render* renderer;
    potato_render_mode render_mode = RENDER_MODE_VERTEX;
    std::vector<potato_script*> scripts;
    bool scripts_started;
};
