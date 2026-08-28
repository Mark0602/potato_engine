# Camera

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `camera.h`  
**Documented overloads:** 24

This page documents the engine-owned callables declared for `Camera`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Camera* camera = Engine::camera_pool->create("gameplay");
camera->set_position({320.0f, 180.0f});
camera->set_zoom(2.0f);
~~~

## Functions

### apply_bounds

~~~cpp
void Camera::apply_bounds()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Applies the requested state change to the target object or service. Validate target pointers and preconditions before invoking the operation.

**Parameters:** None.

---

### Camera

~~~cpp
Camera::Camera() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Default constructor for the Camera class.

**Parameters:** None.

---

### can_see

~~~cpp
bool Camera::can_see(const Transform &world_transform) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Returns true when a world-space transform overlaps the camera view. This is used by the render pipeline to skip objects outside the visible area.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `world_transform` | `const Transform &` | Value supplied for the world_transform parameter. | — |


---

### clear_bounds

~~~cpp
void Camera::clear_bounds()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Clears any bounds set for the camera, allowing it to move freely.

**Parameters:** None.

---

### follow

~~~cpp
void Camera::follow(Object *target, float smoothing, float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Makes the camera follow a target object with optional smoothing.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `target` | `Object *` | Pointer to the Object to follow. | — |


---

### get_position

~~~cpp
Vec Camera::get_position() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the current position of the camera in world coordinates.

**Parameters:** None.

---

### get_rotation

~~~cpp
float Camera::get_rotation() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Gets the current rotation of the camera in radians.

**Parameters:** None.

---

### get_viewport

~~~cpp
Vec Camera::get_viewport() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the viewport size in logical screen pixels.

**Parameters:** None.

---

### get_zoom

~~~cpp
float Camera::get_zoom() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Gets the current zoom level of the camera.

**Parameters:** None.

---

### move

~~~cpp
void Camera::move(Vec delta)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the camera by a specified delta in world coordinates.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `delta` | `Vec` | A Vec representing the change in position for the camera. | — |


---

### reset

~~~cpp
void Camera::reset()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Resets the camera to its default state: position at (0,0), zoom level of 1, and no rotation. This function is useful for resetting the camera after a scene change or when you want to return to a default view.

**Parameters:** None.

---

### screen_size_to_world

~~~cpp
Vec Camera::screen_size_to_world(Vec screen_size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Converts a size from screen coordinates to world coordinates.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `screen_size` | `Vec` | A Vec representing the size in screen coordinates. | — |


---

### screen_to_world

~~~cpp
Transform Camera::screen_to_world(const Transform &screen_transform) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Converts a full screen transform back into world-space. Useful when placing objects from mouse or UI coordinates.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `screen_transform` | `const Transform &` | Value supplied for the screen_transform parameter. | — |


---

### screen_to_world

~~~cpp
Vec Camera::screen_to_world(Vec screen_pos) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Converts a position from screen coordinates to world coordinates.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `screen_pos` | `Vec` | A Vec representing the position in screen coordinates. | — |


---

### set_bounds

~~~cpp
void Camera::set_bounds(Vec min, Vec max)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the bounds for the camera's position.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `min` | `Vec` | A Vec representing the minimum bounds (top-left corner). | — |
| `max` | `Vec` | A Vec representing the maximum bounds (bottom-right corner). | — |


---

### set_position

~~~cpp
void Camera::set_position(Vec position)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the position of the camera in world coordinates.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `Vec` | A Vec representing the new position of the camera. | — |


---

### set_rotation

~~~cpp
void Camera::set_rotation(float rotation)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the rotation of the camera in radians.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_viewport

~~~cpp
void Camera::set_viewport(float width, float height)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the viewport dimensions for the camera.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_viewport

~~~cpp
void Camera::set_viewport(Vec size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the viewport dimensions for the camera using a Vec.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `size` | `Vec` | A Vec where x is the width and y is the height of the viewport in pixels. | — |


---

### set_zoom

~~~cpp
void Camera::set_zoom(float zoom)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the zoom level of the camera.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### shake

~~~cpp
void Camera::shake(float intensity, float duration)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Shakes the camera for a specified duration and intensity.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### world_size_to_screen

~~~cpp
Vec Camera::world_size_to_screen(Vec world_size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Converts a size from world coordinates to screen coordinates.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `world_size` | `Vec` | A Vec representing the size in world coordinates. | — |


---

### world_to_screen

~~~cpp
Transform Camera::world_to_screen(const Transform &world_transform) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Converts a full world transform into screen-space. The position is offset by the camera and the size is scaled by zoom.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `world_transform` | `const Transform &` | Value supplied for the world_transform parameter. | — |


---

### world_to_screen

~~~cpp
Vec Camera::world_to_screen(Vec world_pos) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Converts a position from world coordinates to screen coordinates.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `world_pos` | `Vec` | A Vec representing the position in world coordinates. | — |



