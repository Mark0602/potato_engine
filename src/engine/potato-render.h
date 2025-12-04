#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>

class potato_render {
public:
    potato_render(SDL_Window* window, SDL_GPUDevice* device);
    ~potato_render();

    void render();

private:
    SDL_Window* window;
    SDL_GPUDevice* device;
};
