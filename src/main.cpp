#include "main.h"

potato_engine engine;
bool running = false;
SDL_Event event;
Uint64 last_time = 0;
float delta_time = 0.0f;

int main(int argc, char* argv[]) {

    std::cout << "Starting Potato Engine..." << std::endl;
    if (!engine.initialize()) {
        return 1;
    }

    // Automatically register all scripts
    std::cout << "Registering scripts..." << std::endl;
    auto scripts = potato_script_registry::instance().create_all_scripts();
    for (auto* script : scripts) {
        engine.add_script(script);
    }

    running = true;
    last_time = SDL_GetPerformanceCounter();
    delta_time = 0.0f;

    std::cout << "Entering main loop..." << std::endl;

    while (running) {
        // Calculate delta time
        //std::cout << "Calculating delta time..." << std::endl;
        Uint64 current_time = SDL_GetPerformanceCounter();
        delta_time = (current_time - last_time) / (float)SDL_GetPerformanceFrequency();
        last_time = current_time;

        //std::cout << "Handling events..." << std::endl;
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            engine.handle_event(event);
        }

        //std::cout << "Updating scripts..." << std::endl;
        // Update scripts
        engine.update(delta_time);

        //std::cout << "Rendering..." << std::endl;
        // Render
        engine.render();
        engine.render_scripts();

        //std::cout << "Frame complete." << std::endl;
    }

    engine.shutdown();
    return 0;
}
