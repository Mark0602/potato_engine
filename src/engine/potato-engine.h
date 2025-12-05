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
    char window_title[256] = "Potato Engine";

    bool initialize();
    void update(float delta_time);
    void handle_event(const SDL_Event& event);
    void render();
    void render_scripts();
    void shutdown();

    void add_script(potato_script* script);

    SDL_Window* get_window() const { return window; }
    SDL_GPUDevice* get_device() const { return device; }

private:
    SDL_Window* window;
    SDL_GPUDevice* device;
    potato_render* renderer;
    std::vector<potato_script*> scripts;
    bool scripts_started;
};
