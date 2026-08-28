# Ease

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `animations.h`  
**Documented overloads:** 7

This page documents the engine-owned callables declared for `Ease`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Anim fade;
fade.start(0.25f, 0.0f, 1.0f, Ease::out_quad,
    [&label](float alpha) { label.set_texture_opacity(alpha); });
fade.tick(delta_seconds);
~~~

## Functions

### in_out_quad

~~~cpp
float Ease::in_out_quad(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the in out quad operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### in_quad

~~~cpp
float Ease::in_quad(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the in quad operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### linear

~~~cpp
float Ease::linear(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the linear operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### out_back

~~~cpp
float Ease::out_back(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Easing function that creates a "back" effect, where the animation overshoots and then returns to the target value. This function is useful for creating animations that have a sense of elasticity or bounce.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### out_cubic

~~~cpp
float Ease::out_cubic(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Creates or emits a new engine value using the supplied configuration. Determine ownership from the return type and the owning pool or service.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### out_elastic

~~~cpp
float Ease::out_elastic(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Easing function that creates an "elastic" effect, where the animation oscillates before settling. This function is useful for creating animations that have a spring-like or bouncy behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### out_quad

~~~cpp
float Ease::out_quad(float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the out elastic operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


