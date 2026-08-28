# Slider

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `object.h`  
**Documented overloads:** 7

This page documents the engine-owned callables declared for `Slider`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Object* player = new Object({0.0f, 0.0f}, {32.0f, 32.0f});
player->name = "player";
player->add_tag("controllable");
Engine::object_pool->add(player);
~~~

## Functions

### Slider

~~~cpp
Slider::Slider()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

---

### Slider

~~~cpp
Slider::Slider(float x, float y, float w, float h, float minimum=0.0f, float maximum=1.0f, float initial_value=0.0f, UI_Orientation direction=UI_Orientation::Horizontal, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr, float value_step=0.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Slider value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `direction` | `UI_Orientation` | Value supplied for the direction parameter. | `UI_Orientation::Horizontal` |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### Slider

~~~cpp
Slider::Slider(Vec p, Vec s, float minimum=0.0f, float maximum=1.0f, float initial_value=0.0f, UI_Orientation direction=UI_Orientation::Horizontal, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr, float value_step=0.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Slider value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `direction` | `UI_Orientation` | Value supplied for the direction parameter. | `UI_Orientation::Horizontal` |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### thumb_center

~~~cpp
Vec Slider::thumb_center() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** None.

---

### thumb_transform

~~~cpp
Transform Slider::thumb_transform(Vec thumb_size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Performs the thumb transform operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `thumb_size` | `Vec` | Value supplied for the thumb_size parameter. | — |


---

### update_from_pointer

~~~cpp
bool Slider::update_from_pointer(const Vec &pointer_pos)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pointer_pos` | `const Vec &` | Value supplied for the pointer_pos parameter. | — |


---

### value_at

~~~cpp
float Slider::value_at(const Vec &pointer_pos) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the value at operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pointer_pos` | `const Vec &` | Value supplied for the pointer_pos parameter. | — |


