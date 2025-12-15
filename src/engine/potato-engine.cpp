#include "potato-engine.h"
#include "potato-structures.h"
#include "potato-render.h"
#include <iostream>


// =============================================================================
// CONSTRUCTOR & DESTRUCTOR
// =============================================================================
potato_engine::potato_engine()
    : window(nullptr), device(nullptr), renderer(nullptr), scripts_started(false), render_mode(RENDER_MODE_VERTEX) {
}

potato_engine::~potato_engine() {
    shutdown();
}

bool potato_engine::initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        window_title,
        window_w,
        window_h,
        0
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create GPU device
    std::cout << "Creating GPU device..." << std::endl;
    device = SDL_CreateGPUDevice(
        SDL_GPU_SHADERFORMAT_SPIRV,
        true,
        nullptr
    );

    if (device == nullptr) {
        std::cerr << "GPU device could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        window = nullptr;
        return false;
    }

    // Get GPU driver info
    std::cout << "Retrieving GPU driver info..." << std::endl;
    const char* driver_name = SDL_GetGPUDeviceDriver(device);
    if (driver_name) {
        std::cout << "GPU Driver: " << driver_name << std::endl;
    }

    // Claim the window
    std::cout << "Claiming window for GPU device..." << std::endl;
    if (!SDL_ClaimWindowForGPUDevice(device, window)) {
        std::cerr << "Could not claim window for GPU device! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyGPUDevice(device);
        device = nullptr;
        SDL_DestroyWindow(window);
        window = nullptr;
        return false;
    }

    SDL_Renderer* sdl_renderer = nullptr;
    //std::cout << "Creating SDL Renderer if in BASIC mode..." << std::endl;
    // Create SDL Renderer
    /*if (get_render_mode() == RENDER_MODE_BASIC) {
        std::cerr << "Renderer set to BASIC mode!" << std::endl;
        sdl_renderer = SDL_CreateRenderer(window, nullptr);
    }

    if (get_render_mode() == RENDER_MODE_VERTEX) {
        std::cerr << "Renderer set to VErtEX/GPU mode!" << std::endl;
        sdl_renderer = SDL_CreateRenderer(window, nullptr);
    }

    std::cout << "Checking SDL Renderer creation..." << std::endl;
    if (sdl_renderer == nullptr && get_render_mode() == RENDER_MODE_BASIC) {
        std::cerr << "SDL Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_ReleaseWindowFromGPUDevice(device, window);
        SDL_DestroyGPUDevice(device);
        device = nullptr;
        SDL_DestroyWindow(window);
        window = nullptr;
        return false;
    }*/

    sdl_renderer = SDL_CreateRenderer(window, nullptr);

    std::cout << "Creating potato renderer..." << std::endl;
    // Create renderer
    renderer = new potato_render(window, device, sdl_renderer);

    return true;
}



void potato_engine::add_script(potato_script* script) {
    scripts.push_back(script);
    if (scripts_started) {
        script->on_start();
    }
}
void potato_engine::shutdown() {
    // Destroy all scripts
    for (auto* script : scripts) {
        script->on_destroy();
        delete script;
    }
    scripts.clear();

    if (renderer) {
        delete renderer;
        renderer = nullptr;
    }

    if (device) {
        if (window) {
            SDL_ReleaseWindowFromGPUDevice(device, window);
        }
        SDL_DestroyGPUDevice(device);
        device = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

void potato_engine::update(float delta_time) {
    // Start scripts on first update
    if (!scripts_started) {
        for (auto* script : scripts) {
            script->on_start();
        }
        scripts_started = true;
    }

    // Update all scripts
    for (auto* script : scripts) {
        script->on_update(delta_time);
    }
}

void potato_engine::handle_event(const SDL_Event& event) {
    for (auto* script : scripts) {
        script->on_event(event);
    }
}

void potato_engine::draw_vertex_buffer(potato_vertex_buffer* vertex_buffer, size_t vertex_count) {
    if (renderer && vertex_buffer) {
        // Beállítjuk a vertex count-ot
        vertex_buffer->set_vertex_count(vertex_count);
        // Egyszerűen hozzáadjuk a renderer vertex buffer listájához
        renderer->queue_vertex_buffers(vertex_buffer);
    }
}

void potato_engine::render() {
    if (renderer) {
        renderer->render();
    }
}

void potato_engine::render_scripts() {
    for (auto* script : scripts) {
        script->on_render();
    }
}