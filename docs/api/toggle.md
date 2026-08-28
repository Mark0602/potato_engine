# Toggle

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `object.h`  
**Documented overloads:** 5

This page documents the engine-owned callables declared for `Toggle`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Object* player = new Object({0.0f, 0.0f}, {32.0f, 32.0f});
player->name = "player";
player->add_tag("controllable");
Engine::object_pool->add(player);
~~~

## Functions

### set_checked

~~~cpp
void Toggle::set_checked(bool value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the rotation update operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Toggle

~~~cpp
Toggle::Toggle()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Toggle value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Toggle

~~~cpp
Toggle::Toggle(float x, float y, float w, float h, bool initial_state=false, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Toggle value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### Toggle

~~~cpp
Toggle::Toggle(Vec p, Vec s, bool initial_state=false, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Toggle value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### toggle_at

~~~cpp
bool Toggle::toggle_at(const Vec &pointer_pos)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the toggle at operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pointer_pos` | `const Vec &` | Value supplied for the pointer_pos parameter. | — |


