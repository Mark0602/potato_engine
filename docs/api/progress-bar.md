# Progress_Bar

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `object.h`  
**Documented overloads:** 4

This page documents the engine-owned callables declared for `Progress_Bar`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Object* player = new Object({0.0f, 0.0f}, {32.0f, 32.0f});
player->name = "player";
player->add_tag("controllable");
Engine::object_pool->add(player);
~~~

## Functions

### fill_transform

~~~cpp
Transform Progress_Bar::fill_transform() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### Progress_Bar

~~~cpp
Progress_Bar::Progress_Bar()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Performs the position update operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### Progress_Bar

~~~cpp
Progress_Bar::Progress_Bar(float x, float y, float w, float h, float minimum=0.0f, float maximum=1.0f, float initial_value=0.0f, UI_Orientation direction=UI_Orientation::Horizontal, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Progress_Bar value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `direction` | `UI_Orientation` | Value supplied for the direction parameter. | `UI_Orientation::Horizontal` |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### Progress_Bar

~~~cpp
Progress_Bar::Progress_Bar(Vec p, Vec s, float minimum=0.0f, float maximum=1.0f, float initial_value=0.0f, UI_Orientation direction=UI_Orientation::Horizontal, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Progress_Bar value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `direction` | `UI_Orientation` | Value supplied for the direction parameter. | `UI_Orientation::Horizontal` |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


