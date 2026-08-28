# Texture

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `texture.h`  
**Documented overloads:** 35

This page documents the engine-owned callables declared for `Texture`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Texture texture;
texture.load("assets/player.png");
texture.draw({{100, 100}, texture.get_size()});
~~~

## Functions

### ~Texture

~~~cpp
virtual Texture::~Texture()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Frees the underlying SDL_Texture.

**Parameters:** None.

---

### draw

~~~cpp
void Texture::draw(SDL_Renderer *renderer, const SDL_FRect *src, const SDL_FRect *dst) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws a sub-region of the texture into a destination rectangle.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### draw

~~~cpp
void Texture::draw(SDL_Renderer *renderer, const Vec &pos, const Vec &size, const Vec &rotation) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the texture at pos scaled to size and rotated by rotation.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Top-left position in logical coordinates. | — |
| `size` | `const Vec &` | Desired draw size (width, height). | — |
| `rotation` | `const Vec &` | Rotation angle in degrees (clockwise). | — |


---

### draw

~~~cpp
void Texture::draw(SDL_Renderer *renderer, const Vec &pos, const Vec &size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the texture at pos scaled to size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Top-left position in logical coordinates. | — |
| `size` | `const Vec &` | Desired draw size (width, height). | — |


---

### draw

~~~cpp
void Texture::draw(SDL_Renderer *renderer, const Vec &pos) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the texture at pos using its native size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Top-left position in logical coordinates. | — |


---

### draw_ex

~~~cpp
void Texture::draw_ex(SDL_Renderer *renderer, const SDL_FRect *source, const Transform &transform, const Color &tint) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the size operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `const Transform &` | Value supplied for the transform parameter. | — |
| `tint` | `const Color &` | Value supplied for the tint parameter. | — |


---

### draw_ex

~~~cpp
void Texture::draw_ex(SDL_Renderer *renderer, const Transform &transform, const Color &tint) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the texture with a Transform and Color tint.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `const Transform &` | Transform containing position, size, and rotation. | — |
| `tint` | `const Color &` | Color tint to apply. | — |


---

### draw_ex

~~~cpp
void Texture::draw_ex(SDL_Renderer *renderer, const Vec &pos, const Vec &size, double angle, const Vec *center, SDL_FlipMode flip) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the texture with rotation and/or flip.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Top-left position in logical coordinates. | — |
| `size` | `const Vec &` | Desired draw size. | — |
| `center` | `const Vec *` | Rotation center relative to pos, or nullptr for the texture centre. | — |


---

### free

~~~cpp
void Texture::free()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Destroys the SDL_Texture and resets internal state.

**Parameters:** None.

---

### get_gpu_texture

~~~cpp
SDL_GPUTexture * Texture::get_gpu_texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_GPUTexture *`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### get_height

~~~cpp
float Texture::get_height() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_path

~~~cpp
std::string Texture::get_path() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::string`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_scale_mode

~~~cpp
SDL_ScaleMode Texture::get_scale_mode() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_ScaleMode`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_sdl_texture

~~~cpp
SDL_Texture * Texture::get_sdl_texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_Texture *`

Returns the underlying SDL_Texture pointer.

**Parameters:** None.

---

### get_SDL_Texture

~~~cpp
SDL_Texture * Texture::get_SDL_Texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_Texture *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_size

~~~cpp
Vec Texture::get_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_texture_path

~~~cpp
std::string Texture::get_texture_path() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::string`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_width

~~~cpp
float Texture::get_width() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### has_alpha_mask

~~~cpp
bool Texture::has_alpha_mask() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### is_fully_transparent

~~~cpp
bool Texture::is_fully_transparent() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the texture is fully transparent (all pixels have alpha = 0).

**Parameters:** None.

---

### is_gpu_backed

~~~cpp
bool Texture::is_gpu_backed() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### is_loaded

~~~cpp
bool Texture::is_loaded() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### is_pixel_opaque

~~~cpp
bool Texture::is_pixel_opaque(int x, int y, uint8_t alpha_threshold=1) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### is_region_transparent

~~~cpp
bool Texture::is_region_transparent(const SDL_FRect &region, uint8_t alpha_threshold=1) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if a rectangular region of the texture is fully transparent.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load

~~~cpp
bool Texture::load(SDL_Renderer *renderer, const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

(Re)loads the texture from a file path.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_from_surface

~~~cpp
bool Texture::load_from_surface(SDL_Renderer *renderer, SDL_Surface *surface)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

(Re)loads the texture from an SDL_Surface.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
Texture & Texture::operator=(const Texture &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture &`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
Texture & Texture::operator=(Texture &&other) noexcept
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `Texture &&` | Value supplied for the other parameter. | — |


---

### set_scale_mode

~~~cpp
void Texture::set_scale_mode(SDL_ScaleMode scale_mode)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Changes the scale mode (texture filtering).

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_texture_opacity

~~~cpp
void Texture::set_texture_opacity(float alpha)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Changes the opacity of the texture.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Texture

~~~cpp
Texture::Texture() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** None.

---

### Texture

~~~cpp
Texture::Texture(const Texture &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Texture value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Texture

~~~cpp
Texture::Texture(SDL_Renderer *renderer, const std::string &path, Logger *logger=nullptr, SDL_ScaleMode scale_mode=SDL_SCALEMODE_PIXELART)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Loads a texture from a file.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Optional logger; pass nullptr to suppress log output. | — |


---

### Texture

~~~cpp
Texture::Texture(SDL_Renderer *renderer, SDL_Surface *surface, Logger *logger=nullptr, SDL_ScaleMode scale_mode=SDL_SCALEMODE_PIXELART)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Creates a texture from an existing SDL_Surface.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Optional logger. | — |


---

### Texture

~~~cpp
Texture::Texture(Texture &&other) noexcept
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Texture value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `Texture &&` | Value supplied for the other parameter. | — |



