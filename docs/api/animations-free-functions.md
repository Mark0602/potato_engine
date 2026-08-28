# Animations free functions

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `animations.h`  
**Documented overloads:** 4

This page documents the engine-owned callables declared for `Animations free functions`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Anim fade;
fade.start(0.25f, 0.0f, 1.0f, Ease::out_quad,
    [&label](float alpha) { label.set_texture_opacity(alpha); });
fade.tick(delta_seconds);
~~~

## Functions

### make_fade_in

~~~cpp
Anim make_fade_in(Object *obj, float dur, std::function< float(float)> ease=Ease::out_quad, std::function< void()> on_done=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Anim`

Creates an Anim that fades an object in. The object's opacity will be increased from 0 to 1 over the specified duration.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to animate. | — |


---

### make_fade_out

~~~cpp
Anim make_fade_out(Object *obj, float dur, std::function< float(float)> ease=Ease::in_quad, std::function< void()> on_done=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Anim`

Creates an Anim that fades an object out and hides it. The object's opacity will be reduced from 1 to 0 over the specified duration. After the animation completes, the object will be hidden and its opacity will be reset to 1.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to animate. | — |


---

### make_slide_in

~~~cpp
AnimGroup make_slide_in(Object *obj, Vec target_pos, Vec offset, float dur, std::function< float(float)> ease=Ease::out_back, std::function< void()> on_done=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `AnimGroup`

Creates an AnimGroup that slides an object into view and fades it in. The object will be moved from (target_pos + offset) to target_pos over the specified duration, and its opacity will be increased from 0 to 1. After the animation completes, the object will be fully visible and interactive.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to animate. | — |
| `target_pos` | `Vec` | The final position of the object after the slide-in animation. | — |
| `offset` | `Vec` | The offset to apply to the target position for the starting position of the slide-in effect. | — |


---

### make_slide_out

~~~cpp
AnimGroup make_slide_out(Object *obj, Vec offset, float dur, std::function< float(float)> ease=Ease::in_quad, std::function< void()> on_done=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `AnimGroup`

Creates an AnimGroup that slides an object out of view and fades it out. The object will be moved to (current position + offset) over the specified duration, and its opacity will be reduced to 0. After the animation completes, the object will be hidden.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to animate. | — |
| `offset` | `Vec` | The offset to apply to the object's current position for the slide-out effect. | — |


