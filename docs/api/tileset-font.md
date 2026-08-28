# Tileset_Font

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `fonts.h`  
**Documented overloads:** 19

This page documents the engine-owned callables declared for `Tileset_Font`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
SDL_Font font;
font.load("assets/fonts/ui.ttf", 24);
font.draw(IFont_Props{});
~~~

## Functions

### ~Tileset_Font

~~~cpp
Tileset_Font::~Tileset_Font() override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### draw

~~~cpp
void Tileset_Font::draw(const IFont_Props &props) const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws text using a full properties object.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `props` | `const IFont_Props &` | Draw properties to use for this call. | — |


---

### draw

~~~cpp
void Tileset_Font::draw(SDL_Renderer *renderer, const std::string &text, const Vec &pos, const Color &color, float scale=1.0f) const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws text using direct arguments.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Top-left draw position. | — |
| `color` | `const Color &` | Text color and opacity. | — |


---

### get_char_map

~~~cpp
const std::string & Tileset_Font::get_char_map() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### get_size

~~~cpp
Vec Tileset_Font::get_size(const std::string &text) const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Measures text using this font.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_tile_size

~~~cpp
const Vec & Tileset_Font::get_tile_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Vec &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### is_loaded

~~~cpp
bool Tileset_Font::is_loaded() const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the font has a loaded backing resource.

**Parameters:** None.

---

### load

~~~cpp
bool Tileset_Font::load(const std::string &path, int size=16) override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Loads a font from disk.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_tileset_font

~~~cpp
bool Tileset_Font::load_tileset_font(const std::string &path, const Vec &tile_size, const std::string &char_map)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Loads a bitmap font atlas using Engine::renderer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile_size` | `const Vec &` | Size of one glyph tile. | — |


---

### load_tileset_font

~~~cpp
bool Tileset_Font::load_tileset_font(SDL_Renderer *renderer, const std::string &path, const Vec &tile_size, const std::string &char_map)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Loads a bitmap font atlas using an explicit renderer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile_size` | `const Vec &` | Size of one glyph tile. | — |


---

### operator=

~~~cpp
Tileset_Font & Tileset_Font::operator=(const Tileset_Font &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tileset_Font &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
Tileset_Font & Tileset_Font::operator=(Tileset_Font &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tileset_Font &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### pixel_art

~~~cpp
bool Tileset_Font::pixel_art() const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the pixel art operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### set_char_map

~~~cpp
void Tileset_Font::set_char_map(const std::string &new_map)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_tile_size

~~~cpp
void Tileset_Font::set_tile_size(const Vec &tile_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile_size` | `const Vec &` | Value supplied for the tile_size parameter. | — |


---

### Tileset_Font

~~~cpp
Tileset_Font::Tileset_Font() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Tileset_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Tileset_Font

~~~cpp
Tileset_Font::Tileset_Font(const Tileset_Font &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Tileset_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Tileset_Font

~~~cpp
Tileset_Font::Tileset_Font(Tileset_Font &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Tileset_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### unload

~~~cpp
void Tileset_Font::unload() override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Unloads all resources held by the font.

**Parameters:** None.


