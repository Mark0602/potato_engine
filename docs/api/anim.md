# Anim

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `animations.h`  
**Documented overloads:** 4

This page documents the engine-owned callables declared for `Anim`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Anim fade;
fade.start(0.25f, 0.0f, 1.0f, Ease::out_quad,
    [&label](float alpha) { label.set_texture_opacity(alpha); });
fade.tick(delta_seconds);
~~~

## Functions

### is_running

~~~cpp
bool Anim::is_running() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### progress

~~~cpp
float Anim::progress() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the progress operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### start

~~~cpp
void Anim::start(float dur, float f, float t, std::function< float(float)> ease, std::function< void(float)> apply_fn, std::function< void()> done_fn=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### tick

~~~cpp
void Anim::tick(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


