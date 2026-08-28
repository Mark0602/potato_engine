# IFont

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `fonts.h`  
**Documented overloads:** 11

This page documents the engine-owned callables declared for `IFont`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
SDL_Font font;
font.load("assets/fonts/ui.ttf", 24);
font.draw(IFont_Props{});
~~~

## Functions

### ~IFont

~~~cpp
virtual IFont::~IFont() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Frees implementation-specific font resources.

**Parameters:** None.

---

### draw

~~~cpp
virtual void IFont::draw(const IFont_Props &props) const =0
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
virtual void IFont::draw(SDL_Renderer *renderer, const std::string &text, const Vec &pos, const Color &color, float scale=1.0f) const =0
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

### get_props

~~~cpp
virtual IFont_Props * IFont::get_props() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `IFont_Props *`

Gets the retained draw properties pointer.

**Parameters:** None.

---

### get_size

~~~cpp
virtual Vec IFont::get_size(const std::string &text) const =0
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Measures text using this font.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### is_loaded

~~~cpp
virtual bool IFont::is_loaded() const =0
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the font has a loaded backing resource.

**Parameters:** None.

---

### load

~~~cpp
virtual bool IFont::load(const std::string &path, int size=16)=0
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Loads a font from disk.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### pixel_art

~~~cpp
virtual bool IFont::pixel_art() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the pixel art operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### set_pixel_art

~~~cpp
virtual void IFont::set_pixel_art(bool enabled)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_props

~~~cpp
virtual void IFont::set_props(IFont_Props *new_props)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the retained draw properties pointer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_props` | `IFont_Props *` | Borrowed pointer; ownership stays with the caller. | — |


---

### unload

~~~cpp
virtual void IFont::unload()=0
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Unloads all resources held by the font.

**Parameters:** None.


