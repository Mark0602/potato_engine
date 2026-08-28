# Input::detail

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `input.h`  
**Documented overloads:** 7

This page documents the engine-owned callables declared for `Input::detail`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Functions

### controller_at

~~~cpp
Controller_State * Input::detail::controller_at(int index)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Controller_State *`

Performs the controller at operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### find_action

~~~cpp
const Action * Input::detail::find_action(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Action *`

Performs the controller axis operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### find_axis

~~~cpp
const Axis_Action * Input::detail::find_axis(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Axis_Action *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### valid_gamepad_axis

~~~cpp
bool Input::detail::valid_gamepad_axis(SDL_GamepadAxis axis)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### valid_gamepad_button

~~~cpp
bool Input::detail::valid_gamepad_button(SDL_GamepadButton button)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### valid_mouse_button

~~~cpp
bool Input::detail::valid_mouse_button(Uint8 button)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### valid_scancode

~~~cpp
bool Input::detail::valid_scancode(SDL_Scancode key)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


