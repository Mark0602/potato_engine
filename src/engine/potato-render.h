#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>


class potato_render {
public:
    potato_render(SDL_Window* window, SDL_GPUDevice* device, SDL_Renderer* renderer);
    ~potato_render();


    void render();

    void set_render_mode(potato_render_mode mode) { render_mode = mode; }
    potato_render_mode get_render_mode() const { return render_mode; }

private:
    SDL_Renderer* renderer;
    SDL_Window *window;
    SDL_GPUDevice* device;
    potato_render_mode render_mode;
};
