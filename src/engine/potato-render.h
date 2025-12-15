#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>
#include "potato-structures.h"
#include "potato-vertex-buffer.h"

class potato_render {
public:
    potato_render(SDL_Window* window, SDL_GPUDevice* device, SDL_Renderer* renderer);
    ~potato_render();

    void render();

    void queue_vertex_buffers(potato_vertex_buffer* vb) {
        if (!vb || vb->get_vertex_count() == 0) return;
        vertex_buffers.push_back(vb);
    }

    void set_pipeline(SDL_GPUGraphicsPipeline* new_pipeline) { pipeline = new_pipeline; }
    SDL_GPUGraphicsPipeline* get_pipeline() const { return pipeline; }

    bool init_default_pipeline();
    void destroy_pipelines();

private:
    SDL_Renderer* renderer;
    SDL_Window *window;
    SDL_GPUDevice* device;
    
    SDL_GPUGraphicsPipeline* default_color_pipeline = nullptr;

    std::vector<potato_vertex_buffer*> vertex_buffers;
    SDL_GPUGraphicsPipeline* pipeline;
};
