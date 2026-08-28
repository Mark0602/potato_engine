# UI_Object

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `object.h`  
**Documented overloads:** 20

This page documents the engine-owned callables declared for `UI_Object`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Object* player = new Object({0.0f, 0.0f}, {32.0f, 32.0f});
player->name = "player";
player->add_tag("controllable");
Engine::object_pool->add(player);
~~~

## Functions

### configure_as_ui

~~~cpp
void UI_Object::configure_as_ui()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs the center on screen operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### get_font

~~~cpp
IFont * UI_Object::get_font() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `IFont *`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### is_interactive

~~~cpp
bool UI_Object::is_interactive() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

---

### on_click

~~~cpp
bool UI_Object::on_click(const Vec &mouse_pos) const override
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
bool UI_Object::on_hover(const Vec &mouse_pos) const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Returns true if mouse_pos is within the object's bounding box.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `mouse_pos` | `const Vec &` | Cursor position in logical coordinates. | — |


---

### operator=

~~~cpp
UI_Object & UI_Object::operator=(const UI_Object &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `UI_Object &`

Handles an engine lifecycle callback or input event. Override or call it only at the event-processing phase described by the owning type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_enabled

~~~cpp
void UI_Object::set_enabled(bool value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_font

~~~cpp
void UI_Object::set_font(IFont *font)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `font` | `IFont *` | Value supplied for the font parameter. | — |


---

### UI_Object

~~~cpp
UI_Object::UI_Object()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Performs the toggle visibility operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### UI_Object

~~~cpp
UI_Object::UI_Object()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### UI_Object

~~~cpp
UI_Object::UI_Object(const UI_Object &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### UI_Object

~~~cpp
UI_Object::UI_Object(const UI_Object &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### UI_Object

~~~cpp
UI_Object::UI_Object(float x, float y, float w, float h, float rx, float ry=0.0f, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### UI_Object

~~~cpp
UI_Object::UI_Object(float x, float y, float w, float h, float rx, float ry=0.0f, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### UI_Object

~~~cpp
UI_Object::UI_Object(float x, float y, float w, float h, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### UI_Object

~~~cpp
UI_Object::UI_Object(float x, float y, float w, float h, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### UI_Object

~~~cpp
UI_Object::UI_Object(Transform transform, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `Transform` | Value supplied for the transform parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### UI_Object

~~~cpp
UI_Object::UI_Object(Transform transform, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `Transform` | Value supplied for the transform parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### UI_Object

~~~cpp
UI_Object::UI_Object(Vec p, Vec s, Vec r={0.0f, 0.0f}, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `r` | `Vec` | Value supplied for the r parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |


---

### UI_Object

~~~cpp
UI_Object::UI_Object(Vec p, Vec s, Vec r={0.0f, 0.0f}, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a UI_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `r` | `Vec` | Value supplied for the r parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | — |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | — |
| `l` | `Logger *` | Value supplied for the l parameter. | — |



