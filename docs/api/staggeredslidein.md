# StaggeredSlideIn

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `animations.h`  
**Documented overloads:** 4

This page documents the engine-owned callables declared for `StaggeredSlideIn`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

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
void StaggeredSlideIn::add(Object *obj, Vec target_pos, Vec offset, float dur, float delay, std::function< float(float)> ease=Ease::out_back)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Value supplied for the obj parameter. | — |
| `target_pos` | `Vec` | Value supplied for the target_pos parameter. | — |
| `offset` | `Vec` | Value supplied for the offset parameter. | — |


---

### is_running

~~~cpp
bool StaggeredSlideIn::is_running() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### start

~~~cpp
void StaggeredSlideIn::start()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

---

### tick

~~~cpp
void StaggeredSlideIn::tick(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


