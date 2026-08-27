# Input

The `Input` namespace tracks current and previous frame state for keyboards, mouse buttons, and opened SDL gamepads. `Engine::Application` initializes it, forwards SDL events, updates it before scripts, and shuts it down automatically.

## Named actions

Digital actions combine any number of keyboard keys, mouse buttons, and gamepad buttons. The action is down when any binding is down.

```cpp
Input::bind_key("confirm", SDL_SCANCODE_RETURN);
Input::bind_mouse_button("confirm", SDL_BUTTON_LEFT);
Input::bind_gamepad_button("confirm", SDL_GAMEPAD_BUTTON_SOUTH);

if (Input::action_pressed("confirm")) { /* one frame */ }
if (Input::action_down("confirm")) { /* held */ }
if (Input::action_released("confirm")) { /* one frame */ }
```

Register bindings during startup. Reusing an action name adds another binding.

## Named axes

Axes sum all binding contributions and clamp the result to `[-1, 1]`. Keyboard keys supply fixed scaled values; gamepad axes supply normalized analog values with deadzone filtering.

```cpp
Input::bind_axis_key("move_x", SDL_SCANCODE_A, -1.0f);
Input::bind_axis_key("move_x", SDL_SCANCODE_D, 1.0f);
Input::bind_axis_gamepad_axis(
    "move_x", SDL_GAMEPAD_AXIS_LEFTX, 1.0f, 0.15f, 0
);

const float x = Input::axis("move_x");
const float change = Input::axis_delta("move_x");
```

## Raw queries

The direct APIs mirror the same frame transitions:

- `key_pressed`, `key_down`, `key_released` use SDL scancodes;
- `mouse_button_pressed`, `mouse_button_down`, `mouse_button_released` use SDL button IDs;
- `controller_button_pressed`, `controller_button_down`, and `controller_button_released` accept an optional opened-gamepad index;
- `controller_axis` reads a normalized axis with a configurable deadzone;
- `mouse_position`, `mouse_delta`, and `mouse_scroll_delta` expose logical cursor data;
- `quit_requested` reports whether the current frame received an SDL quit event.

Gamepads are opened during initialization and updated for hotplug/remap events. An invalid device index or enum yields a neutral result.

## Mouse coordinates and embedded viewports

When a renderer is available, the normal cursor position is converted into SDL logical presentation coordinates. For a game displayed inside a host UI, call:

```cpp
Input::set_mouse_viewport(host_origin, host_size, game_logical_size);
```

The input system then maps window mouse input from that rectangle into the supplied logical size. `clear_mouse_viewport()` restores normal renderer-based conversion. All sizes must be positive for the mapping to activate.

## Exclusive blocking

`Input::acquire_block(owner)` gives a non-null identity token exclusive control. A different owner cannot acquire it until `release_block(owner)` is called. While blocked, gameplay-facing queries return false, zero, or an empty vector. `mouse_position()` remains available so the owning UI can continue placing the cursor.

`TextBox` uses this facility while focused. Custom modal UI should use a stable owner address and release it on every close/destruction path.

## Manual lifecycle

Only custom application loops should call `init`, `begin_frame`, `handle_event`, `update`, and `shutdown` directly. The required order is begin frame, feed every polled event, then update once before gameplay queries.

