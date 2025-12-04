#include "potato-engine.h"
#include <iostream>


potato_engine::potato_engine()
    : window(nullptr), device(nullptr), renderer(nullptr), scripts_started(false) {
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
        "Potato Engine",
        800,
        600,
        0
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create GPU device
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
    const char* driver_name = SDL_GetGPUDeviceDriver(device);
    if (driver_name) {
        std::cout << "GPU Driver: " << driver_name << std::endl;
    }

    // Claim the window
    if (!SDL_ClaimWindowForGPUDevice(device, window)) {
        std::cerr << "Could not claim window for GPU device! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyGPUDevice(device);
        device = nullptr;
        SDL_DestroyWindow(window);
        window = nullptr;
        return false;
    }

    // Create renderer
    renderer = new potato_render(window, device);

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
