#include "input.h"

#include "engine.h"
#include <algorithm>
#include <cmath>

namespace {
    using namespace Input::detail;

    float normalize_axis(Sint16 value, float deadzone) {
        float normalized = value >= 0
            ? static_cast<float>(value) / 32767.0f
            : static_cast<float>(value) / 32768.0f;

        if (std::fabs(normalized) < deadzone) {
            return 0.0f;
        }

        return std::clamp(normalized, -1.0f, 1.0f);
    }

    Input::Action& find_or_create_action(const std::string& name) {
        auto it = std::find_if(actions.begin(), actions.end(), [&](const Input::Action& action) {
            return action.name == name;
        });

        if (it != actions.end()) {
            return *it;
        }

        actions.push_back(Input::Action{name});
        return actions.back();
    }

    Input::Axis_Action& find_or_create_axis(const std::string& name) {
        auto it = std::find_if(axes.begin(), axes.end(), [&](const Input::Axis_Action& axis) {
            return axis.name == name;
        });

        if (it != axes.end()) {
            return *it;
        }

        axes.push_back(Input::Axis_Action{name});
        return axes.back();
    }

    void close_controllers() {
        for (auto& controller : controllers) {
            if (controller.controller) {
                SDL_CloseGamepad(controller.controller);
                controller.controller = nullptr;
            }
        }
        controllers.clear();
    }

    void refresh_controllers() {
        close_controllers();

        int count = 0;
        SDL_JoystickID* ids = SDL_GetGamepads(&count);
        if (!ids) {
            return;
        }

        controllers.reserve(count);
        for (int i = 0; i < count; ++i) {
            SDL_Gamepad* gamepad = SDL_OpenGamepad(ids[i]);
            if (gamepad) {
                Input::Controller_State state;
                state.controller = gamepad;
                controllers.push_back(state);
            }
        }

        SDL_free(ids);
    }

    void bind_default_actions() {
        if (!actions.empty() || !axes.empty()) {
            return;
        }

        Input::bind_mouse_button("primary", SDL_BUTTON_LEFT);
        Input::bind_key("primary", SDL_SCANCODE_SPACE);
        Input::bind_key("primary", SDL_SCANCODE_RETURN);
        Input::bind_gamepad_button("primary", SDL_GAMEPAD_BUTTON_SOUTH);

        Input::bind_mouse_button("mouse_primary", SDL_BUTTON_LEFT);

        Input::bind_key("ui_accept", SDL_SCANCODE_SPACE);
        Input::bind_key("ui_accept", SDL_SCANCODE_RETURN);
        Input::bind_gamepad_button("ui_accept", SDL_GAMEPAD_BUTTON_SOUTH);

        Input::bind_key("ui_cancel", SDL_SCANCODE_ESCAPE);
        Input::bind_gamepad_button("ui_cancel", SDL_GAMEPAD_BUTTON_EAST);

        Input::bind_key("ui_up", SDL_SCANCODE_W);
        Input::bind_key("ui_up", SDL_SCANCODE_UP);
        Input::bind_gamepad_button("ui_up", SDL_GAMEPAD_BUTTON_DPAD_UP);

        Input::bind_key("ui_down", SDL_SCANCODE_S);
        Input::bind_key("ui_down", SDL_SCANCODE_DOWN);
        Input::bind_gamepad_button("ui_down", SDL_GAMEPAD_BUTTON_DPAD_DOWN);

        Input::bind_axis_key("move_x", SDL_SCANCODE_A, -1.0f);
        Input::bind_axis_key("move_x", SDL_SCANCODE_LEFT, -1.0f);
        Input::bind_axis_key("move_x", SDL_SCANCODE_D, 1.0f);
        Input::bind_axis_key("move_x", SDL_SCANCODE_RIGHT, 1.0f);
        Input::bind_axis_gamepad_axis("move_x", SDL_GAMEPAD_AXIS_LEFTX);

        Input::bind_axis_key("move_y", SDL_SCANCODE_W, -1.0f);
        Input::bind_axis_key("move_y", SDL_SCANCODE_UP, -1.0f);
        Input::bind_axis_key("move_y", SDL_SCANCODE_S, 1.0f);
        Input::bind_axis_key("move_y", SDL_SCANCODE_DOWN, 1.0f);
        Input::bind_axis_gamepad_axis("move_y", SDL_GAMEPAD_AXIS_LEFTY);
    }

    bool binding_down(const Input::Input_Binding& binding) {
        switch (binding.type) {
            case Input::Input_Source_Type::Keyboard_Key:
                return Input::key_down(binding.key);
            case Input::Input_Source_Type::Mouse_Button:
                return Input::mouse_button_down(binding.mouse_button);
            case Input::Input_Source_Type::Gamepad_Button:
                return Input::controller_button_down(binding.gamepad_button, binding.gamepad_index);
            case Input::Input_Source_Type::Gamepad_Axis:
                return std::fabs(Input::controller_axis(binding.gamepad_axis, binding.gamepad_index, binding.deadzone)) > 0.0f;
        }

        return false;
    }

    float binding_axis_value(const Input::Input_Binding& binding) {
        switch (binding.type) {
            case Input::Input_Source_Type::Keyboard_Key:
                return Input::key_down(binding.key) ? binding.scale : 0.0f;
            case Input::Input_Source_Type::Mouse_Button:
                return Input::mouse_button_down(binding.mouse_button) ? binding.scale : 0.0f;
            case Input::Input_Source_Type::Gamepad_Button:
                return Input::controller_button_down(binding.gamepad_button, binding.gamepad_index) ? binding.scale : 0.0f;
            case Input::Input_Source_Type::Gamepad_Axis:
                return Input::controller_axis(binding.gamepad_axis, binding.gamepad_index, binding.deadzone) * binding.scale;
        }

        return 0.0f;
    }
}

namespace Input {
    using namespace detail;

    void init() {
        blocking_owner = nullptr;
        refresh_controllers();
        bind_default_actions();
        update();
        for (int i = 0; i < SDL_SCANCODE_COUNT; ++i) {
            keyboard.previous[i] = keyboard.current[i];
        }
        for (int i = 0; i < 6; ++i) {
            mouse.previous[i] = mouse.current[i];
        }
        for (auto& controller : controllers) {
            for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; ++i) {
                controller.previous[i] = controller.current[i];
            }
        }
    }

    void begin_frame() {
        for (int i = 0; i < SDL_SCANCODE_COUNT; ++i) {
            keyboard.previous[i] = keyboard.current[i];
        }
        for (int i = 0; i < 6; ++i) {
            mouse.previous[i] = mouse.current[i];
        }
        for (auto& controller : controllers) {
            for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; ++i) {
                controller.previous[i] = controller.current[i];
            }
        }

        mouse.delta = {};
        mouse.scroll_wheel = {};
        quit_flag = false;
    }

    void handle_event(const SDL_Event& event) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                quit_flag = true;
                break;
            case SDL_EVENT_MOUSE_MOTION:
                mouse.delta.x += event.motion.xrel;
                mouse.delta.y += event.motion.yrel;
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                mouse.scroll_wheel.x += event.wheel.x;
                mouse.scroll_wheel.y += event.wheel.y;
                break;
            case SDL_EVENT_GAMEPAD_ADDED:
            case SDL_EVENT_GAMEPAD_REMOVED:
            case SDL_EVENT_GAMEPAD_REMAPPED:
                refresh_controllers();
                break;
            default:
                break;
        }
    }

    void update() {
        int key_count = 0;
        const bool* keys = SDL_GetKeyboardState(&key_count);
        int count = std::min(key_count, static_cast<int>(SDL_SCANCODE_COUNT));
        for (int i = 0; i < count; ++i) {
            keyboard.current[i] = keys[i];
        }

        float mouse_x = 0.0f;
        float mouse_y = 0.0f;
        SDL_MouseButtonFlags mouse_mask = SDL_GetMouseState(&mouse_x, &mouse_y);
        if (mouse_viewport_enabled) {
            const bool inside = mouse_x >= mouse_viewport_origin.x &&
                                mouse_y >= mouse_viewport_origin.y &&
                                mouse_x < mouse_viewport_origin.x + mouse_viewport_size.x &&
                                mouse_y < mouse_viewport_origin.y + mouse_viewport_size.y;
            const float scale_x = mouse_viewport_logical_size.x / mouse_viewport_size.x;
            const float scale_y = mouse_viewport_logical_size.y / mouse_viewport_size.y;
            mouse.position = {
                (mouse_x - mouse_viewport_origin.x) * scale_x,
                (mouse_y - mouse_viewport_origin.y) * scale_y
            };
            mouse.delta.x *= scale_x;
            mouse.delta.y *= scale_y;
            if (!inside) {
                mouse_mask = 0;
                mouse.delta = {};
            }
        } else if (Engine::renderer) {
            SDL_RenderCoordinatesFromWindow(Engine::renderer, mouse_x, mouse_y, &mouse.position.x, &mouse.position.y);
        } else {
            mouse.position = {mouse_x, mouse_y};
        }
        for (Uint8 button = 1; button < 6; ++button) {
            mouse.current[button] = (mouse_mask & SDL_BUTTON_MASK(button)) != 0;
        }

        SDL_UpdateGamepads();
        for (auto& controller : controllers) {
            if (!controller.controller) continue;

            for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; ++i) {
                controller.current[i] = SDL_GetGamepadButton(controller.controller, static_cast<SDL_GamepadButton>(i));
            }
            for (int i = 0; i < SDL_GAMEPAD_AXIS_COUNT; ++i) {
                controller.axes[i] = normalize_axis(
                    SDL_GetGamepadAxis(controller.controller, static_cast<SDL_GamepadAxis>(i)),
                    0.0f
                );
            }
            controller.left_stick = {
                controller.axes[SDL_GAMEPAD_AXIS_LEFTX],
                controller.axes[SDL_GAMEPAD_AXIS_LEFTY]
            };
            controller.right_stick = {
                controller.axes[SDL_GAMEPAD_AXIS_RIGHTX],
                controller.axes[SDL_GAMEPAD_AXIS_RIGHTY]
            };
        }

        for (auto& action : actions) {
            action.state.previous = action.state.current;
            action.state.current = false;
            for (const auto& binding : action.bindings) {
                if (binding_down(binding)) {
                    action.state.current = true;
                    break;
                }
            }
        }

        for (auto& axis_action : axes) {
            axis_action.previous = axis_action.current;
            axis_action.current = 0.0f;
            for (const auto& binding : axis_action.bindings) {
                axis_action.current += binding_axis_value(binding);
            }
        axis_action.current = std::clamp(axis_action.current, -1.0f, 1.0f);
        }
    }

    void shutdown() {
        blocking_owner = nullptr;
        close_controllers();
        actions.clear();
        axes.clear();
    }

    void bind_key(const std::string& action_name, SDL_Scancode key) {
        if (!valid_scancode(key)) return;
        auto& action = find_or_create_action(action_name);
        Input_Binding binding;
        binding.type = Input_Source_Type::Keyboard_Key;
        binding.key = key;
        action.bindings.push_back(binding);
    }

    void bind_mouse_button(const std::string& action_name, Uint8 button) {
        if (!valid_mouse_button(button)) return;
        auto& action = find_or_create_action(action_name);
        Input_Binding binding;
        binding.type = Input_Source_Type::Mouse_Button;
        binding.mouse_button = button;
        action.bindings.push_back(binding);
    }

    void bind_gamepad_button(const std::string& action_name, SDL_GamepadButton button, int gamepad_index) {
        if (!valid_gamepad_button(button)) return;
        auto& action = find_or_create_action(action_name);
        Input_Binding binding;
        binding.type = Input_Source_Type::Gamepad_Button;
        binding.gamepad_button = button;
        binding.gamepad_index = gamepad_index;
        action.bindings.push_back(binding);
    }

    void bind_axis_key(const std::string& axis_name, SDL_Scancode key, float scale) {
        if (!valid_scancode(key)) return;
        auto& axis_action = find_or_create_axis(axis_name);
        Input_Binding binding;
        binding.type = Input_Source_Type::Keyboard_Key;
        binding.key = key;
        binding.scale = scale;
        axis_action.bindings.push_back(binding);
    }

    void bind_axis_gamepad_axis(
        const std::string& axis_name,
        SDL_GamepadAxis axis,
        float scale,
        float deadzone,
        int gamepad_index
    ) {
        if (!valid_gamepad_axis(axis)) return;
        auto& axis_action = find_or_create_axis(axis_name);
        Input_Binding binding;
        binding.type = Input_Source_Type::Gamepad_Axis;
        binding.gamepad_axis = axis;
        binding.scale = scale;
        binding.deadzone = deadzone;
        binding.gamepad_index = gamepad_index;
        axis_action.bindings.push_back(binding);
    }

}
