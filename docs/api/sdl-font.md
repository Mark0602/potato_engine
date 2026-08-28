# SDL_Font

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `fonts.h`  
**Documented overloads:** 14

This page documents the engine-owned callables declared for `SDL_Font`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
SDL_Font font;
font.load("assets/fonts/ui.ttf", 24);
font.draw(IFont_Props{});
~~~

## Functions

### ~SDL_Font

~~~cpp
SDL_Font::~SDL_Font() override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### draw

~~~cpp
void SDL_Font::draw(const IFont_Props &props) const override
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
void SDL_Font::draw(SDL_Renderer *renderer, const std::string &text, const Vec &pos, const Color &color, float scale=1.0f) const override
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

### get_size

~~~cpp
Vec SDL_Font::get_size(const std::string &text) const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Measures text using this font.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### is_loaded

~~~cpp
bool SDL_Font::is_loaded() const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the font has a loaded backing resource.

**Parameters:** None.

---

### load

~~~cpp
bool SDL_Font::load(const std::string &path, int size=16) override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Loads a font from disk.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
SDL_Font & SDL_Font::operator=(const SDL_Font &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_Font &`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
SDL_Font & SDL_Font::operator=(SDL_Font &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_Font &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### pixel_art

~~~cpp
bool SDL_Font::pixel_art() const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the pixel art operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### SDL_Font

~~~cpp
SDL_Font::SDL_Font() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a SDL_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### SDL_Font

~~~cpp
SDL_Font::SDL_Font(const SDL_Font &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a SDL_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### SDL_Font

~~~cpp
SDL_Font::SDL_Font(SDL_Font &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a SDL_Font value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_pixel_art

~~~cpp
void SDL_Font::set_pixel_art(bool enabled) override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### unload

~~~cpp
void SDL_Font::unload() override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Unloads all resources held by the font.

**Parameters:** None.


