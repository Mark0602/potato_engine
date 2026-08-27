#ifndef INPUT_H
#define INPUT_H

#include <SDL3/SDL.h>
#include "vec.h"
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

namespace Input {
    /**
     * @brief Identifies the physical device family that produced an input.
     *
     * Useful for UI prompts, debug overlays, or future rebinding screens where
     * the game needs to display whether an action came from keyboard, mouse,
     * or controller input.
     */
    enum class Input_Device {
        KEYBOARD,
        MOUSE,
        CONTROLLER
    };

    /**
     * @brief Describes the concrete SDL input source used by an input binding.
     *
     * Digital actions usually use `Keyboard_Key`, `Mouse_Button`, or
     * `Gamepad_Button`. Analog axes can use `Keyboard_Key` with a scale
     * value or `Gamepad_Axis` for real analog input.
     */
    enum class Input_Source_Type {
        Keyboard_Key,
        Mouse_Button,
        Gamepad_Button,
        Gamepad_Axis
    };

    /**
     * @brief Stores keyboard state for the current and previous frame.
     *
     * `previous` is copied from `current` in `begin_frame()`, then `current`
     * is refreshed in `update()`. This makes pressed/released queries possible.
     */
    struct Keyboard_State {
        bool current[SDL_SCANCODE_COUNT]{};
        bool previous[SDL_SCANCODE_COUNT]{};
    };

    /**
     * @brief Stores mouse buttons, position, movement, and wheel delta.
     *
     * Mouse buttons use SDL button ids: `SDL_BUTTON_LEFT` is 1,
     * `SDL_BUTTON_RIGHT` is 3, etc. `delta` and `scroll_wheel` are accumulated
     * from SDL events during the current frame and reset by `begin_frame()`.
     * `position` is stored in SDL logical render coordinates when a renderer
     * is available.
     */
    struct Mouse_State {
        bool current[6]{};
        bool previous[6]{};
        Vec  position{};
        Vec  delta{};
        Vec  scroll_wheel{};
    };

    /**
     * @brief Stores input state for one opened SDL gamepad.
     *
     * The `controller` pointer is owned by the input system and closed in
     * `shutdown()`. Buttons store current/previous frame state; axes are
     * normalized to the range `[-1, 1]`.
     */
    struct Controller_State {
        SDL_Gamepad* controller = nullptr;
        bool current[SDL_GAMEPAD_BUTTON_COUNT]{};
        bool previous[SDL_GAMEPAD_BUTTON_COUNT]{};
        Vec  left_stick{};
        Vec  right_stick{};
        float axes[SDL_GAMEPAD_AXIS_COUNT]{};
    };

    /**
     * @brief Current and previous state for a named digital action.
     *
     * Used by actions such as `"jump"`, `"click"`, `"pause"`, or `"save"`.
     */
    struct Action_state {
        bool current = false;
        bool previous = false;
    };

    /**
     * @brief Current and previous value for a named analog action.
     *
     * Used by axes such as `"move_x"`, `"move_y"`, `"aim_x"`, or `"zoom"`.
     */
    struct Axis_state {
        float current = 0.0f;
        float previous = 0.0f;
    };

    /**
     * @brief Connects a concrete physical input to an action or axis.
     *
     * Only the fields relevant to `type` are used. For axes, `scale` can flip
     * or weight the value. For gamepad axes, `deadzone` filters stick drift.
     *
     * Example:
     * ```cpp
     * // Created internally by bind_axis_key("move_x", SDL_SCANCODE_A, -1.0f)
     * // This means the A key contributes -1 to the "move_x" axis.
     * ```
     */
    struct Input_Binding {
        Input_Source_Type type = Input_Source_Type::Keyboard_Key;

        SDL_Scancode key = SDL_SCANCODE_UNKNOWN;
        Uint8 mouse_button = 0;

        int gamepad_index = 0;
        SDL_GamepadButton gamepad_button = SDL_GAMEPAD_BUTTON_INVALID;
        SDL_GamepadAxis gamepad_axis = SDL_GAMEPAD_AXIS_INVALID;

        float scale = 1.0f;
        float deadzone = 0.15f;
    };

    /**
     * @brief A named digital action with one or more input bindings.
     *
     * The action is considered down when any of its bindings are down.
     * Use this for commands like jump, shoot, interact, save, or pause.
     */
    struct Action {
        std::string name;
        Action_state state{};
        std::vector<Input_Binding> bindings{};
    };

    /**
     * @brief A named analog axis with one or more input bindings.
     *
     * All binding values are summed and clamped to `[-1, 1]`, so keyboard
     * pairs and gamepad sticks can drive the same gameplay axis.
     */
    struct Axis_Action {
        std::string name;
        float current = 0.0f;
        float previous = 0.0f;
        std::vector<Input_Binding> bindings;
    };

    namespace detail {
        inline Keyboard_State keyboard;
        inline Mouse_State mouse;
        inline std::vector<Controller_State> controllers;
        inline std::vector<Action> actions;
        inline std::vector<Axis_Action> axes;
        inline bool quit_flag = false;
        inline const void* blocking_owner = nullptr;
        inline bool mouse_viewport_enabled = false;
        inline Vec mouse_viewport_origin{};
        inline Vec mouse_viewport_size{};
        inline Vec mouse_viewport_logical_size{};

        inline bool valid_scancode(SDL_Scancode key) {
            return key >= 0 && key < SDL_SCANCODE_COUNT;
        }

        inline bool valid_mouse_button(Uint8 button) {
            return button > 0 && button < 6;
        }

        inline bool valid_gamepad_button(SDL_GamepadButton button) {
            return button >= 0 && button < SDL_GAMEPAD_BUTTON_COUNT;
        }

        inline bool valid_gamepad_axis(SDL_GamepadAxis axis) {
            return axis >= 0 && axis < SDL_GAMEPAD_AXIS_COUNT;
        }

        inline const Action* find_action(const std::string& name) {
            auto it = std::find_if(actions.begin(), actions.end(), [&](const Action& action) {
                return action.name == name;
            });
            return it != actions.end() ? &*it : nullptr;
        }

        inline const Axis_Action* find_axis(const std::string& name) {
            auto it = std::find_if(axes.begin(), axes.end(), [&](const Axis_Action& axis) {
                return axis.name == name;
            });
            return it != axes.end() ? &*it : nullptr;
        }

        inline Controller_State* controller_at(int index) {
            if (index < 0 || index >= static_cast<int>(controllers.size())) {
                return nullptr;
            }
            return &controllers[index];
        }
    }

    /**
     * @brief Initializes the input system and opens available gamepads.
     *
     * Call once after SDL has been initialized. `main.cpp` already does this.
     */
    void init();
    /**
     * @brief Starts a new input frame.
     *
     * Copies current states into previous states and clears frame-local data
     * like mouse delta, mouse wheel delta, and quit requests.
     */
    void begin_frame();
    /**
     * @brief Feeds an SDL event into the input system.
     *
     * Call this for every event returned by `SDL_PollEvent()`. It tracks
     * relative mouse motion, mouse wheel movement, quit requests, and gamepad
     * hotplug/remap events.
     *
     * @param event SDL event to process.
     */
    void handle_event(const SDL_Event& event);
    /**
     * @brief Refreshes keyboard, mouse, gamepad, action, and axis states.
     *
     * Call once after event polling and before scripts update. `main.cpp`
     * already does this, so scripts can safely query `Input::...` in
     * `on_update()`.
     */
    void update();
    /**
     * @brief Releases gamepads and clears registered actions and axes.
     *
     * Call once before SDL shutdown. `main.cpp` already does this.
     */
    void shutdown();

    /**
     * Gives one UI owner exclusive access to raw SDL input events. While an
     * owner holds the block, gameplay-facing Input queries return neutral
     * values. The owner must release the block when it loses focus.
     */
    inline bool acquire_block(const void* owner) {
        if (!owner || (detail::blocking_owner && detail::blocking_owner != owner)) {
            return false;
        }
        detail::blocking_owner = owner;
        return true;
    }

    inline void release_block(const void* owner) {
        if (detail::blocking_owner == owner) detail::blocking_owner = nullptr;
    }

    inline bool is_blocked() {
        return detail::blocking_owner != nullptr;
    }

    /** Maps window mouse input into an embedded game viewport. */
    inline void set_mouse_viewport(const Vec& origin, const Vec& size, const Vec& logical_size) {
        detail::mouse_viewport_enabled = size.x > 0.f && size.y > 0.f &&
                                         logical_size.x > 0.f && logical_size.y > 0.f;
        detail::mouse_viewport_origin = origin;
        detail::mouse_viewport_size = size;
        detail::mouse_viewport_logical_size = logical_size;
    }

    inline void clear_mouse_viewport() {
        detail::mouse_viewport_enabled = false;
    }

    /**
     * @brief Binds a keyboard key to a named digital action.
     *
     * @param action_name Name of the action, e.g. `"jump"`.
     * @param key SDL scancode to bind.
     *
     * Example:
     * ```cpp
     * Input::bind_key("jump", SDL_SCANCODE_SPACE);
     * if (Input::action_pressed("jump")) {
     *     // jump once
     * }
     * ```
     */
    void bind_key(const std::string& action_name, SDL_Scancode key);
    /**
     * @brief Binds an SDL mouse button to a named digital action.
     *
     * @param action_name Name of the action.
     * @param button SDL mouse button id, e.g. `SDL_BUTTON_LEFT`.
     */
    void bind_mouse_button(const std::string& action_name, Uint8 button);
    /**
     * @brief Binds a gamepad button to a named digital action.
     *
     * @param action_name Name of the action.
     * @param button SDL gamepad button, e.g. `SDL_GAMEPAD_BUTTON_SOUTH`.
     * @param gamepad_index Index of the opened gamepad. Defaults to 0.
     */
    void bind_gamepad_button(const std::string& action_name, SDL_GamepadButton button, int gamepad_index = 0);
    /**
     * @brief Binds a keyboard key to a named analog axis.
     *
     * Use `scale = -1.0f` and `scale = 1.0f` to build keyboard movement axes.
     *
     * @param axis_name Name of the axis, e.g. `"move_x"`.
     * @param key SDL scancode to bind.
     * @param scale Axis contribution while the key is held.
     *
     * Example:
     * ```cpp
     * Input::bind_axis_key("move_x", SDL_SCANCODE_A, -1.0f);
     * Input::bind_axis_key("move_x", SDL_SCANCODE_D,  1.0f);
     * float x = Input::axis("move_x");
     * ```
     */
    void bind_axis_key(const std::string& axis_name, SDL_Scancode key, float scale);
    /**
     * @brief Binds a gamepad analog axis to a named axis.
     *
     * @param axis_name Name of the axis.
     * @param axis SDL gamepad axis, e.g. `SDL_GAMEPAD_AXIS_LEFTX`.
     * @param scale Multiplier applied to the raw axis value.
     * @param deadzone Values below this magnitude become 0.
     * @param gamepad_index Index of the opened gamepad. Defaults to 0.
     */
    void bind_axis_gamepad_axis(
        const std::string& axis_name,
        SDL_GamepadAxis axis,
        float scale = 1.0f,
        float deadzone = 0.15f,
        int gamepad_index = 0
    );

    /**
     * @brief Checks whether an action was pressed this frame.
     *
     * @param action_name Name passed to a bind function.
     * @return `true` only on the frame the action changes from up to down.
     */
    inline bool action_pressed(const std::string& action_name) {
        if (is_blocked()) return false;
        const Action* action = detail::find_action(action_name);
        return action && action->state.current && !action->state.previous;
    }
    /**
     * @brief Checks whether an action was released this frame.
     *
     * @param action_name Name passed to a bind function.
     * @return `true` only on the frame the action changes from down to up.
     */
    inline bool action_released(const std::string& action_name) {
        if (is_blocked()) return false;
        const Action* action = detail::find_action(action_name);
        return action && !action->state.current && action->state.previous;
    }
    /**
     * @brief Checks whether an action is currently held.
     *
     * @param action_name Name passed to a bind function.
     * @return `true` while any binding for the action is down.
     */
    inline bool action_down(const std::string& action_name) {
        if (is_blocked()) return false;
        const Action* action = detail::find_action(action_name);
        return action && action->state.current;
    }
    /**
     * @brief Gets the current value of a named axis.
     *
     * @param axis_name Name passed to an axis bind function.
     * @return Axis value clamped to `[-1, 1]`.
     */
    inline float axis(const std::string& axis_name) {
        if (is_blocked()) return 0.0f;
        const Axis_Action* axis_action = detail::find_axis(axis_name);
        return axis_action ? axis_action->current : 0.0f;
    }
    /**
     * @brief Gets how much a named axis changed since the previous frame.
     *
     * @param axis_name Name passed to an axis bind function.
     * @return `current - previous`.
     */
    inline float axis_delta(const std::string& axis_name) {
        if (is_blocked()) return 0.0f;
        const Axis_Action* axis_action = detail::find_axis(axis_name);
        return axis_action ? axis_action->current - axis_action->previous : 0.0f;
    }

    /**
     * @brief Checks whether a keyboard key was pressed this frame.
     *
     * @param key SDL scancode.
     * @return `true` only on the transition from up to down.
     */
    inline bool key_pressed(SDL_Scancode key) {
        if (is_blocked()) return false;
        return detail::valid_scancode(key) && detail::keyboard.current[key] && !detail::keyboard.previous[key];
    }


    /**
     * @brief Checks whether a keyboard key was released this frame.
     *
     * @param key SDL scancode.
     * @return `true` only on the transition from down to up.
     */
    inline bool key_released(SDL_Scancode key) {
        if (is_blocked()) return false;
        return detail::valid_scancode(key) && !detail::keyboard.current[key] && detail::keyboard.previous[key];
    }
    /**
     * @brief Checks whether a keyboard key is currently held.
     *
     * @param key SDL scancode.
     * @return `true` while the key is down.
     */
    inline bool key_down(SDL_Scancode key) {
        if (is_blocked()) return false;
        return detail::valid_scancode(key) && detail::keyboard.current[key];
    }

    /**
     * @brief Checks whether a mouse button was pressed this frame.
     *
     * @param button SDL mouse button id, e.g. `SDL_BUTTON_LEFT`.
     * @return `true` only on the transition from up to down.
     */
    inline bool mouse_button_pressed(Uint8 button) {
        if (is_blocked()) return false;
        return detail::valid_mouse_button(button) && detail::mouse.current[button] && !detail::mouse.previous[button];
    }
    /**
     * @brief Checks whether a mouse button was released this frame.
     *
     * @param button SDL mouse button id.
     * @return `true` only on the transition from down to up.
     */
    inline bool mouse_button_released(Uint8 button) {
        if (is_blocked()) return false;
        return detail::valid_mouse_button(button) && !detail::mouse.current[button] && detail::mouse.previous[button];
    }
    /**
     * @brief Checks whether a mouse button is currently held.
     *
     * @param button SDL mouse button id.
     * @return `true` while the button is down.
     */
    inline bool mouse_button_down(Uint8 button) {
        if (is_blocked()) return false;
        return detail::valid_mouse_button(button) && detail::mouse.current[button];
    }

    /**
     * @brief Checks whether a gamepad button was pressed this frame.
     *
     * @param button SDL gamepad button.
     * @param gamepad_index Index of the opened gamepad. Defaults to 0.
     * @return `true` only on the transition from up to down.
     */
    inline bool controller_button_pressed(SDL_GamepadButton button, int gamepad_index = 0) {
        if (is_blocked()) return false;
        Controller_State* controller = detail::controller_at(gamepad_index);
        return controller && detail::valid_gamepad_button(button) && controller->current[button] && !controller->previous[button];
    }
    /**
     * @brief Checks whether a gamepad button was released this frame.
     *
     * @param button SDL gamepad button.
     * @param gamepad_index Index of the opened gamepad. Defaults to 0.
     * @return `true` only on the transition from down to up.
     */
    inline bool controller_button_released(SDL_GamepadButton button, int gamepad_index = 0) {
        if (is_blocked()) return false;
        Controller_State* controller = detail::controller_at(gamepad_index);
        return controller && detail::valid_gamepad_button(button) && !controller->current[button] && controller->previous[button];
    }
    /**
     * @brief Checks whether a gamepad button is held on a selected gamepad.
     *
     * @param button SDL gamepad button.
     * @param gamepad_index Index of the opened gamepad.
     * @return `true` while the button is down.
     */
    inline bool controller_button_down(SDL_GamepadButton button, int gamepad_index) {
        if (is_blocked()) return false;
        Controller_State* controller = detail::controller_at(gamepad_index);
        return controller && detail::valid_gamepad_button(button) && controller->current[button];
    }
    /**
     * @brief Checks whether a gamepad button is held on gamepad 0.
     *
     * @param button SDL gamepad button.
     * @return `true` while the button is down.
     */
    inline bool controller_button_down(SDL_GamepadButton button) {
        return controller_button_down(button, 0);
    }
    /**
     * @brief Reads a gamepad axis.
     *
     * @param axis SDL gamepad axis.
     * @param gamepad_index Index of the opened gamepad. Defaults to 0.
     * @param deadzone Values below this magnitude become 0.
     * @return Axis value in `[-1, 1]`, or 0 if unavailable/inside deadzone.
     */
    inline float controller_axis(SDL_GamepadAxis axis, int gamepad_index = 0, float deadzone = 0.15f) {
        if (is_blocked()) return 0.0f;
        Controller_State* controller = detail::controller_at(gamepad_index);
        if (!controller || !detail::valid_gamepad_axis(axis)) {
            return 0.0f;
        }

        float value = controller->axes[axis];
        return std::fabs(value) < deadzone ? 0.0f : value;
    }
    
    /**
     * @brief Gets the current mouse position.
     *
     * @return Mouse position in SDL logical render coordinates when possible.
     */
    inline Vec mouse_position() {
        return detail::mouse.position;
    }
    /**
     * @brief Gets relative mouse movement for the current frame.
     *
     * @return Accumulated motion from SDL mouse motion events since `begin_frame()`.
     */
    inline Vec mouse_delta() {
        if (is_blocked()) return {};
        return detail::mouse.delta;
    }
    /**
     * @brief Gets mouse wheel movement for the current frame.
     *
     * @return Accumulated wheel movement since `begin_frame()`.
     */
    inline Vec mouse_scroll_delta() {
        if (is_blocked()) return {};
        return detail::mouse.scroll_wheel;
    }
    /**
     * @brief Checks whether an SDL quit event was seen this frame.
     *
     * @return `true` if `SDL_EVENT_QUIT` was passed to `handle_event()`.
     */
    inline bool quit_requested() {
        return detail::quit_flag;
    }
}

#endif
