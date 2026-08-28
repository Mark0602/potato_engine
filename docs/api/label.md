# Label

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `label.h`  
**Documented overloads:** 21

This page documents the engine-owned callables declared for `Label`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Label score;
score.set_text("Score: 100");
score.set_color(Color::white());
~~~

## Functions

### clear_shadow

~~~cpp
void Label::clear_shadow()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### draw

~~~cpp
void Label::draw(SDL_Renderer *renderer) override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the label immediately with the assigned font.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_color

~~~cpp
Color Label::get_color() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Gets the label color.

**Parameters:** None.

---

### get_font

~~~cpp
IFont * Label::get_font() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `IFont *`

Gets the currently assigned font.

**Parameters:** None.

---

### get_scale

~~~cpp
float Label::get_scale() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Gets the draw scale used by the font.

**Parameters:** None.

---

### get_text

~~~cpp
const std::string & Label::get_text() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Gets the current text of the label.

**Parameters:** None.

---

### Label

~~~cpp
Label::Label() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Label

~~~cpp
Label::Label(const Label &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Label

~~~cpp
Label::Label(const Transform &transform, const std::string &text, IFont *font=nullptr, Logger *logger=nullptr, Object_Pool *object_pool=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label object with no assigned font.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `const Transform &` | Transform data inherited from Object. | — |
| `font` | `IFont *` | Value supplied for the font parameter. | — |
| `logger` | `Logger *` | Optional logger for debug output. | — |
| `object_pool` | `Object_Pool *` | Optional pool used for automatic rendering. | — |


---

### Label

~~~cpp
Label::Label(const Vec &pos, const Vec &size, const Vec &rot, const std::string &text, const std::string &font_name, Logger *logger=nullptr, Object_Pool *object_pool=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label object and resolves its font from Engine::asset_pool.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | The top-left position of the label in logical coordinates. | — |
| `size` | `const Vec &` | The width and height of the label in logical pixels. | — |
| `rot` | `const Vec &` | Rotation data inherited from Object. | — |
| `logger` | `Logger *` | Optional logger for debug output. | — |
| `object_pool` | `Object_Pool *` | Optional pool used for automatic rendering. | — |


---

### Label

~~~cpp
Label::Label(const Vec &pos, const Vec &size, const Vec &rot, const std::string &text, IFont *font, Logger *logger=nullptr, Object_Pool *object_pool=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label object with a borrowed font pointer.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | The top-left position of the label in logical coordinates. | — |
| `size` | `const Vec &` | The width and height of the label in logical pixels. | — |
| `rot` | `const Vec &` | Rotation data inherited from Object. | — |
| `font` | `IFont *` | Borrowed IFont pointer. Ownership stays with Asset_Pool or the caller. | — |
| `logger` | `Logger *` | Optional logger for debug output. | — |
| `object_pool` | `Object_Pool *` | Optional pool used for automatic rendering. | — |


---

### Label

~~~cpp
Label::Label(const Vec &pos, const Vec &size, const Vec &rot, const std::string &text, Logger *logger=nullptr, Object_Pool *object_pool=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Label object with no assigned font.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | The top-left position of the label in logical coordinates. | — |
| `size` | `const Vec &` | The width and height of the label in logical pixels. | — |
| `rot` | `const Vec &` | Rotation data inherited from Object. | — |
| `logger` | `Logger *` | Optional logger for debug output. | — |
| `object_pool` | `Object_Pool *` | Optional pool used for automatic rendering. | — |


---

### make_draw_command

~~~cpp
Draw Label::make_draw_command() const override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Draw`

Creates a font draw command for Render_Pool.

**Parameters:** None.

---

### resize_to_text

~~~cpp
Vec Label::resize_to_text()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Updates the Object size from the current font and text.

**Parameters:** None.

---

### set_color

~~~cpp
void Label::set_color(const Color &new_color)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the label color.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_color` | `const Color &` | New text color and opacity. | — |


---

### set_font

~~~cpp
void Label::set_font(IFont *new_font)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the borrowed font pointer used for rendering.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_font` | `IFont *` | Borrowed IFont pointer. Ownership stays with the caller. | — |


---

### set_font_from_asset_pool

~~~cpp
bool Label::set_font_from_asset_pool(const std::string &font_name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Resolves and sets the font from Engine::asset_pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_scale

~~~cpp
void Label::set_scale(float new_scale)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the draw scale used by the font.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_shadow

~~~cpp
void Label::set_shadow(const Vec &offset, const Color &color)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Enables a simple drop shadow rendered immediately behind the text.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `offset` | `const Vec &` | Shadow offset in logical pixels. | — |
| `color` | `const Color &` | Shadow color; its alpha is multiplied by the label opacity. | — |


---

### set_text

~~~cpp
void Label::set_text(const std::string &new_text)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the text of the label.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### submit_draw_commands

~~~cpp
void Label::submit_draw_commands(Render_Pool &render_pool) override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `render_pool` | `Render_Pool &` | Value supplied for the render_pool parameter. | — |



