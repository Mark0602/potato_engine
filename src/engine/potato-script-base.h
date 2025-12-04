#pragma once

#include <SDL3/SDL.h>

class potato_script {
public:
    virtual ~potato_script() = default;

    // Called once when the script is first initialized
    virtual void on_start() {}

    // Called every frame before rendering
    virtual void on_update(float delta_time) {}

    // Called during the render phase (useful for custom rendering/debug drawing)
    virtual void on_render() {}

    // Called when an SDL event occurs
    virtual void on_event(const SDL_Event& event) {}

    // Called once when the script is being destroyed
    virtual void on_destroy() {}
};
