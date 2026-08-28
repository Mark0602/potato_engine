# Button

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `object.h`  
**Documented overloads:** 3

This page documents the engine-owned callables declared for `Button`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Object* player = new Object({0.0f, 0.0f}, {32.0f, 32.0f});
player->name = "player";
player->add_tag("controllable");
Engine::object_pool->add(player);
~~~

## Functions

### Button

~~~cpp
Button::Button() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** None.

---

### on_click

~~~cpp
bool Button::on_click(const Vec &mouse_pos) const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Returns true if mouse_pos is within the object's bounding box (alias for on_hover).

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `mouse_pos` | `const Vec &` | Cursor position in logical coordinates. | — |


---

### on_hover

~~~cpp
bool Button::on_hover(const Vec &mouse_pos) const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Returns true if mouse_pos is within the object's bounding box.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `mouse_pos` | `const Vec &` | Cursor position in logical coordinates. | — |



