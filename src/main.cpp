#include <SDL3/SDL.h>
#include "engine/potato-engine.h"
#include "engine/potato-script-registry.h"
#include "potato-structures.h"
#include "engine/potato-texture.h"
#include "engine/potato-gameobject.h"

int main(int argc, char* argv[]) {
    potato_engine engine;

    if (!engine.initialize()) {
        return 1;
    }

    // Automatically register all scripts
    auto scripts = potato_script_registry::instance().create_all_scripts();
    for (auto* script : scripts) {
        engine.add_script(script);
    }

    bool running = true;
    SDL_Event event;
    Uint64 last_time = SDL_GetPerformanceCounter();
    float delta_time = 0.0f;

    while (running) {
        // Calculate delta time
        Uint64 current_time = SDL_GetPerformanceCounter();
        delta_time = (current_time - last_time) / (float)SDL_GetPerformanceFrequency();
        last_time = current_time;

        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            engine.handle_event(event);
        }

        // Update scripts
        engine.update(delta_time);

        // Render
        engine.render();
        engine.render_scripts();
    }

    engine.shutdown();
    return 0;
}
