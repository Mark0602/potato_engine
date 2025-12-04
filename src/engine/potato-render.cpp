#include "potato-render.h"

potato_render::potato_render(SDL_Window* window, SDL_GPUDevice* device)
    : window(window), device(device) {
}

potato_render::~potato_render() {
}

void potato_render::render() {
    // Acquire command buffer
    SDL_GPUCommandBuffer* cmdbuf = SDL_AcquireGPUCommandBuffer(device);
    if (cmdbuf == nullptr) {
        return;
    }

    // Acquire swapchain texture
    SDL_GPUTexture* swapchain_texture;
    if (!SDL_AcquireGPUSwapchainTexture(cmdbuf, window, &swapchain_texture, nullptr, nullptr)) {
        SDL_SubmitGPUCommandBuffer(cmdbuf);
        return;
    }

    if (swapchain_texture != nullptr) {
        // Set up color target
        SDL_GPUColorTargetInfo color_target = {};
        color_target.texture = swapchain_texture;
        color_target.clear_color = {0.0f, 0.0f, 0.0f, 1.0f};
        color_target.load_op = SDL_GPU_LOADOP_CLEAR;
        color_target.store_op = SDL_GPU_STOREOP_STORE;

        // Begin render pass
        SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(
            cmdbuf,
            &color_target,
            1,
            nullptr
        );

        // End render pass
        SDL_EndGPURenderPass(render_pass);
    }

    // Submit command buffer
    SDL_SubmitGPUCommandBuffer(cmdbuf);
}
