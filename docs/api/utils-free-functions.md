# Utils free functions

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `utils.h`  
**Documented overloads:** 47

This page documents the engine-owned callables declared for `Utils free functions`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Vec direction = normalize(target - origin);
float separation = distance(origin, target);
~~~

## Functions

### abs

~~~cpp
Vec abs(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector with each component replaced by its absolute value.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### angle

~~~cpp
float angle(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Angle (radians) from point a to point b, measured from the positive X axis.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### angle_between

~~~cpp
float angle_between(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Unsigned angle between two direction vectors (radians).

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### angle_between_degrees

~~~cpp
float angle_between_degrees(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Unsigned angle between two vectors in degrees. See angle_between().

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### angle_between_radians

~~~cpp
float angle_between_radians(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Alias for angle_between() — returns the unsigned angle in radians.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### angle_between_signed

~~~cpp
float angle_between_signed(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Signed angle from a to b (radians). Positive = counter-clockwise.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### angle_between_signed_degrees

~~~cpp
float angle_between_signed_degrees(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Signed angle from a to b in degrees. See angle_between_signed().

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### angle_between_signed_radians

~~~cpp
float angle_between_signed_radians(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Alias for angle_between_signed() — returns the signed angle in radians.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### ceil

~~~cpp
Vec ceil(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector with each component rounded up to the nearest integer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### clamp

~~~cpp
float clamp(float value, float min, float max)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Clamps a float value between a minimum and maximum.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### clamp

~~~cpp
int clamp(int value, int min, int max)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Clamps an integer value between a minimum and maximum.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### clamp

~~~cpp
Vec clamp(const Vec &a, const Vec &min, const Vec &max)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Clamps each component of a between the corresponding components of min and max.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value to clamp. | — |
| `min` | `const Vec &` | Per-component minimum. | — |
| `max` | `const Vec &` | Per-component maximum. | — |


---

### convert_FRect_to_Vec

~~~cpp
Vec convert_FRect_to_Vec(const SDL_FRect &rect)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Extracts the top-left position {x, y} from an SDL_FRect as a Vec.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### convert_Vec_to_FRect

~~~cpp
SDL_FRect convert_Vec_to_FRect(const Vec &a, const Vec &size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_FRect`

Converts a position Vec and a size Vec into an SDL_FRect.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Top-left position. | — |
| `size` | `const Vec &` | Width and height. | — |


---

### cross

~~~cpp
float cross(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

2D cross product (scalar). Positive if b is counter-clockwise from a.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### distance

~~~cpp
float distance(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Calculates the distance between two Vec points.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The first Vec point. | — |
| `b` | `const Vec &` | The second Vec point. | — |


---

### distance_squared

~~~cpp
float distance_squared(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Calculates the squared distance between two Vec points.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The first Vec point. | — |
| `b` | `const Vec &` | The second Vec point. | — |


---

### dot

~~~cpp
float dot(const Vec &a, const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Dot product of two vectors. Positive = same direction, 0 = perpendicular, negative = opposite.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### floor

~~~cpp
Vec floor(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector with each component rounded down to the nearest integer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### fullscreen_window

~~~cpp
void fullscreen_window(SDL_Window *window)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the SDL window to fullscreen mode if it is valid.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_mouse_position

~~~cpp
static Vec get_mouse_position()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `Vec`

Gets the current mouse position in logical coordinates. This function retrieves the current mouse position in window coordinates and converts it to logical coordinates based on the current SDL renderer.

**Parameters:** None.

---

### get_window_bottom_center

~~~cpp
Vec get_window_bottom_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the bottom-center point of the window in logical coordinates as a Vec. This function calculates the bottom-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_bottom_left

~~~cpp
Vec get_window_bottom_left()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the top-right corner of the window in logical coordinates as a Vec. This function calculates the top-right corner of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_bottom_right

~~~cpp
Vec get_window_bottom_right()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the bottom-right corner of the window in logical coordinates as a Vec. This function calculates the bottom-right corner of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_center

~~~cpp
Vec get_window_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the center of the window in logical coordinates as a Vec. This function calculates the center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_left_center

~~~cpp
Vec get_window_left_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the left-center point of the window in logical coordinates as a Vec. This function calculates the left-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_right_center

~~~cpp
Vec get_window_right_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the right-center point of the window in logical coordinates as a Vec. This function calculates the right-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_size

~~~cpp
Vec get_window_size()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the window size in logical coordinates as a Vec. This function retrieves the current size of the SDL window and returns it as a Vec, where x is the width and y is the height.

**Parameters:** None.

---

### get_window_top_center

~~~cpp
Vec get_window_top_center()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the top-center point of the window in logical coordinates as a Vec. This function calculates the top-center point of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### get_window_top_left

~~~cpp
Vec get_window_top_left()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the top-left corner of the window in logical coordinates as a Vec. This function returns the top-left corner of the SDL window, which is always at (0, 0) in logical coordinates.

**Parameters:** None.

---

### get_window_top_right

~~~cpp
Vec get_window_top_right()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the bottom-left corner of the window in logical coordinates as a Vec. This function calculates the bottom-left corner of the SDL window based on its current size and returns it as a Vec.

**Parameters:** None.

---

### invert

~~~cpp
Vec invert(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector pointing in the opposite direction (-x, -y).

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### is_point_in_circle

~~~cpp
bool is_point_in_circle(const Vec &point, const Vec &circle_center, float radius)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Tests whether a point lies inside or on the boundary of a circle.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `point` | `const Vec &` | Point to test. | — |
| `circle_center` | `const Vec &` | Centre of the circle. | — |


---

### is_point_in_rect

~~~cpp
bool is_point_in_rect(const Vec &point, const Vec &rect_Vec, const SDL_FRect &rect)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Tests whether a point is inside an SDL_FRect offset by rect_Vec.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `point` | `const Vec &` | Point to test in logical coordinates. | — |
| `rect_Vec` | `const Vec &` | Top-left offset added to rect.x/y. | — |


---

### length

~~~cpp
float length(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Calculates the length (magnitude) of a Vec.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The Vec whose length is to be calculated. | — |


---

### length_squared

~~~cpp
float length_squared(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Calculates the squared length (magnitude) of a Vec.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The Vec whose squared length is to be calculated. | — |


---

### lerp

~~~cpp
Vec lerp(const Vec &a, const Vec &b, float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Linearly interpolates between two vectors.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Start value (t = 0). | — |
| `b` | `const Vec &` | End value (t = 1). | — |


---

### lerp_color

~~~cpp
void lerp_color(Color &color, const Color &target, float t)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Linearly interpolates between two colors.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `color` | `Color &` | The starting color, which will be modified to the interpolated value. | — |
| `target` | `const Color &` | The target color to interpolate towards. | — |


---

### maximize_window

~~~cpp
void maximize_window(SDL_Window *window)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Maximizes the SDL window if it is valid.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### nearly_equal

~~~cpp
bool nearly_equal(const Vec &a, const Vec &b, float epsilon=0.01f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if two Vec points are nearly equal within a given epsilon.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | The first Vec point. | — |
| `b` | `const Vec &` | The second Vec point. | — |


---

### normalize

~~~cpp
Vec normalize(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a unit vector in the same direction as a. Returns {0,0} if a is zero.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### os_cursor_visibility

~~~cpp
void os_cursor_visibility(bool visible, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Changes the visibility of the OS cursor.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Optional logger for debugging purposes. By default nullptr, which means no logging will occur. | — |


---

### perpendicular

~~~cpp
Vec perpendicular(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector perpendicular to a, rotated 90° counter-clockwise.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### reflect

~~~cpp
Vec reflect(const Vec &a, const Vec &normal)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Reflects vector a off a surface with the given unit normal.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Incoming direction vector. | — |
| `normal` | `const Vec &` | Unit normal of the surface. | — |


---

### rotate

~~~cpp
Vec rotate(const Vec &a, float angle)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Rotates vector a by angle degrees counter-clockwise.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Vector to rotate. | — |


---

### round

~~~cpp
Vec round(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns a vector with each component rounded to the nearest integer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### windowed_window

~~~cpp
void windowed_window(SDL_Window *window)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the SDL window to windowed mode if it is valid.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


