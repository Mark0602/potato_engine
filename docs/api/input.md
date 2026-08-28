# Input

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `input.h`  
**Documented overloads:** 35

This page documents the engine-owned callables declared for `Input`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Detailed workflow example

~~~cpp
Input::bind_key("jump", SDL_SCANCODE_SPACE);
Input::bind_gamepad_button("jump", SDL_GAMEPAD_BUTTON_SOUTH);
Input::bind_axis_key("move_x", SDL_SCANCODE_A, -1.0f);
Input::bind_axis_key("move_x", SDL_SCANCODE_D, 1.0f);

if (!Input::is_blocked() && Input::action_pressed("jump")) {
    player_jump();
}
~~~

## Usage example

~~~cpp
Input::bind_key("jump", SDL_SCANCODE_SPACE);
if (Input::action_pressed("jump")) player_jump();
~~~

## Functions

### acquire_block

~~~cpp
bool Input::acquire_block(const void *owner)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the acquire block operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### action_down

~~~cpp
bool Input::action_down(const std::string &action_name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether an action is currently held.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### action_pressed

~~~cpp
bool Input::action_pressed(const std::string &action_name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether an action was pressed this frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### action_released

~~~cpp
bool Input::action_released(const std::string &action_name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether an action was released this frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### axis

~~~cpp
float Input::axis(const std::string &axis_name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Gets the current value of a named axis.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### axis_delta

~~~cpp
float Input::axis_delta(const std::string &axis_name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Gets how much a named axis changed since the previous frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### begin_frame

~~~cpp
void Input::begin_frame()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Starts a new input frame.

**Parameters:** None.

---

### bind_axis_gamepad_axis

~~~cpp
void Input::bind_axis_gamepad_axis(const std::string &axis_name, SDL_GamepadAxis axis, float scale=1.0f, float deadzone=0.15f, int gamepad_index=0)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Binds a gamepad analog axis to a named axis.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### bind_axis_key

~~~cpp
void Input::bind_axis_key(const std::string &axis_name, SDL_Scancode key, float scale)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Binds a keyboard key to a named analog axis.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### bind_gamepad_button

~~~cpp
void Input::bind_gamepad_button(const std::string &action_name, SDL_GamepadButton button, int gamepad_index=0)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Binds a gamepad button to a named digital action.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### bind_key

~~~cpp
void Input::bind_key(const std::string &action_name, SDL_Scancode key)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Binds a keyboard key to a named digital action.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### bind_mouse_button

~~~cpp
void Input::bind_mouse_button(const std::string &action_name, Uint8 button)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Binds an SDL mouse button to a named digital action.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### clear_mouse_viewport

~~~cpp
void Input::clear_mouse_viewport()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the action down operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### controller_axis

~~~cpp
float Input::controller_axis(SDL_GamepadAxis axis, int gamepad_index=0, float deadzone=0.15f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Reads a gamepad axis.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### controller_button_down

~~~cpp
bool Input::controller_button_down(SDL_GamepadButton button, int gamepad_index)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a gamepad button is held on a selected gamepad.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### controller_button_down

~~~cpp
bool Input::controller_button_down(SDL_GamepadButton button)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a gamepad button is held on gamepad 0.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### controller_button_pressed

~~~cpp
bool Input::controller_button_pressed(SDL_GamepadButton button, int gamepad_index=0)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a gamepad button was pressed this frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### controller_button_released

~~~cpp
bool Input::controller_button_released(SDL_GamepadButton button, int gamepad_index=0)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a gamepad button was released this frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### handle_event

~~~cpp
void Input::handle_event(const SDL_Event &event)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Feeds an SDL event into the input system.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### init

~~~cpp
void Input::init()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Initializes the input system and opens available gamepads.

**Parameters:** None.

---

### is_blocked

~~~cpp
bool Input::is_blocked()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Handles an engine lifecycle callback or input event. Override or call it only at the event-processing phase described by the owning type.

**Parameters:** None.

---

### key_down

~~~cpp
bool Input::key_down(SDL_Scancode key)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a keyboard key is currently held.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### key_pressed

~~~cpp
bool Input::key_pressed(SDL_Scancode key)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a keyboard key was pressed this frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### key_released

~~~cpp
bool Input::key_released(SDL_Scancode key)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a keyboard key was released this frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### mouse_button_down

~~~cpp
bool Input::mouse_button_down(Uint8 button)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a mouse button is currently held.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### mouse_button_pressed

~~~cpp
bool Input::mouse_button_pressed(Uint8 button)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a mouse button was pressed this frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### mouse_button_released

~~~cpp
bool Input::mouse_button_released(Uint8 button)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether a mouse button was released this frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### mouse_delta

~~~cpp
Vec Input::mouse_delta()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets relative mouse movement for the current frame.

**Parameters:** None.

---

### mouse_position

~~~cpp
Vec Input::mouse_position()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the current mouse position.

**Parameters:** None.

---

### mouse_scroll_delta

~~~cpp
Vec Input::mouse_scroll_delta()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets mouse wheel movement for the current frame.

**Parameters:** None.

---

### quit_requested

~~~cpp
bool Input::quit_requested()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether an SDL quit event was seen this frame.

**Parameters:** None.

---

### release_block

~~~cpp
void Input::release_block(const void *owner)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the key down operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_mouse_viewport

~~~cpp
void Input::set_mouse_viewport(const Vec &origin, const Vec &size, const Vec &logical_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `origin` | `const Vec &` | Value supplied for the origin parameter. | — |
| `size` | `const Vec &` | Value supplied for the size parameter. | — |
| `logical_size` | `const Vec &` | Value supplied for the logical_size parameter. | — |


---

### shutdown

~~~cpp
void Input::shutdown()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Releases gamepads and clears registered actions and axes.

**Parameters:** None.

---

### update

~~~cpp
void Input::update()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Refreshes keyboard, mouse, gamepad, action, and axis states.

**Parameters:** None.
