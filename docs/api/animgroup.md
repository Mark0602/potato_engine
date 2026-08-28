# AnimGroup

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `animations.h`  
**Documented overloads:** 3

This page documents the engine-owned callables declared for `AnimGroup`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Anim fade;
fade.start(0.25f, 0.0f, 1.0f, Ease::out_quad,
    [&label](float alpha) { label.set_texture_opacity(alpha); });
fade.tick(delta_seconds);
~~~

## Functions

### add

~~~cpp
void AnimGroup::add(Anim a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds an Anim to the group.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `Anim` | The Anim to add to the group. | — |


---

### is_running

~~~cpp
bool AnimGroup::is_running() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### tick

~~~cpp
void AnimGroup::tick(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Ticks all Anim objects in the group by the specified delta time. If all Anim objects have completed, the on_done callback will be invoked.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


