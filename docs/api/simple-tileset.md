# Simple_Tileset

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `loading_screen.h`  
**Documented overloads:** 22

This page documents the engine-owned callables declared for `Simple_Tileset`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Engine::loading_screen->enqueue_step("Load level", [] { load_level(); });
Engine::loading_screen->update(delta_seconds);
~~~

## Functions

### ~Simple_Tileset

~~~cpp
Simple_Tileset::~Simple_Tileset()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### advance_frame

~~~cpp
void Simple_Tileset::advance_frame()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.

---

### advance_frame_index

~~~cpp
void Simple_Tileset::advance_frame_index(std::size_t &frame_index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### columns

~~~cpp
std::size_t Simple_Tileset::columns() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Performs the columns operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### draw_current_frame

~~~cpp
void Simple_Tileset::draw_current_frame(SDL_Renderer *renderer, const Vec &pos, const Vec &size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Value supplied for the pos parameter. | — |
| `size` | `const Vec &` | Value supplied for the size parameter. | — |


---

### draw_current_frame

~~~cpp
void Simple_Tileset::draw_current_frame(SDL_Renderer *renderer, const Vec &pos) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Value supplied for the pos parameter. | — |


---

### draw_frame

~~~cpp
void Simple_Tileset::draw_frame(SDL_Renderer *renderer, const Vec &pos, std::size_t frame_index, const Vec &size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Value supplied for the pos parameter. | — |
| `size` | `const Vec &` | Value supplied for the size parameter. | — |


---

### draw_frame

~~~cpp
void Simple_Tileset::draw_frame(SDL_Renderer *renderer, const Vec &pos, std::size_t frame_index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Value supplied for the pos parameter. | — |


---

### frame_count

~~~cpp
std::size_t Simple_Tileset::frame_count() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Performs the frame count operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### free

~~~cpp
void Simple_Tileset::free()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### is_loaded

~~~cpp
bool Simple_Tileset::is_loaded() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### make_tileset

~~~cpp
bool Simple_Tileset::make_tileset(const std::string &path, SDL_Renderer *renderer, Logger *logger=nullptr, Vec frame_size={0, 0})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Creates or emits a new engine value using the supplied configuration. Determine ownership from the return type and the owning pool or service.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |
| `frame_size` | `Vec` | Value supplied for the frame_size parameter. | — |


---

### operator=

~~~cpp
Simple_Tileset & Simple_Tileset::operator=(const Simple_Tileset &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Simple_Tileset &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
Simple_Tileset & Simple_Tileset::operator=(Simple_Tileset &&other) noexcept
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Simple_Tileset &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `Simple_Tileset &&` | Value supplied for the other parameter. | — |


---

### reset_frame

~~~cpp
void Simple_Tileset::reset_frame()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Restores the component to its initial reusable state. Previously accumulated transient state is discarded.

**Parameters:** None.

---

### rows

~~~cpp
std::size_t Simple_Tileset::rows() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Performs the rows operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### set_frame_size

~~~cpp
void Simple_Tileset::set_frame_size(const Vec &new_frame_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_frame_size` | `const Vec &` | Value supplied for the new_frame_size parameter. | — |


---

### set_whole_size

~~~cpp
void Simple_Tileset::set_whole_size(const Vec &new_whole_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_whole_size` | `const Vec &` | Value supplied for the new_whole_size parameter. | — |


---

### Simple_Tileset

~~~cpp
Simple_Tileset::Simple_Tileset() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Simple_Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Simple_Tileset

~~~cpp
Simple_Tileset::Simple_Tileset(const Simple_Tileset &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Simple_Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Simple_Tileset

~~~cpp
Simple_Tileset::Simple_Tileset(const std::string &path, SDL_Renderer *renderer, Logger *logger=nullptr, Vec frame_size={0, 0})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Simple_Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |
| `frame_size` | `Vec` | Value supplied for the frame_size parameter. | — |


---

### Simple_Tileset

~~~cpp
Simple_Tileset::Simple_Tileset(Simple_Tileset &&other) noexcept
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Simple_Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `Simple_Tileset &&` | Value supplied for the other parameter. | — |



