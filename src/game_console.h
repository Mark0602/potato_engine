#ifndef GAME_CONSOLE_H
#define GAME_CONSOLE_H

#include <SDL3/SDL_events.h>

namespace game_console {
    bool is_console_visible();
    bool show_console();
    void hide_console();
    void toggle_console();

    /** Handles the global F1/grave console shortcut. */
    bool handle_event(const SDL_Event& event);

    bool is_supported();
}

#endif
