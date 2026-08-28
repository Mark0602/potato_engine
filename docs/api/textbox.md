# TextBox

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `label.h`  
**Documented overloads:** 24

This page documents the engine-owned callables declared for `TextBox`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Label score;
score.set_text("Score: 100");
score.set_color(Color::white());
~~~

## Functions

### ~TextBox

~~~cpp
TextBox::~TextBox() override
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.

---

### blur

~~~cpp
void TextBox::blur()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the blur operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### clear

~~~cpp
void TextBox::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### erase_next_character

~~~cpp
void TextBox::erase_next_character()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### erase_previous_character

~~~cpp
void TextBox::erase_previous_character()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### finish

~~~cpp
void TextBox::finish(SDL_Scancode release_scancode)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### focus

~~~cpp
bool TextBox::focus(bool clear_existing_text=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the focus operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_cursor_position

~~~cpp
std::size_t TextBox::get_cursor_position() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_max_length

~~~cpp
std::size_t TextBox::get_max_length() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_prefix

~~~cpp
const std::string & TextBox::get_prefix() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_value

~~~cpp
const std::string & TextBox::get_value() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### handle_event

~~~cpp
TextBox_Result TextBox::handle_event(const SDL_Event &event)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `TextBox_Result`

Handles an engine lifecycle callback or input event. Override or call it only at the event-processing phase described by the owning type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### insert_text

~~~cpp
void TextBox::insert_text(const std::string &text)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs the insert text operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### is_focused

~~~cpp
bool TextBox::is_focused() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### next_utf8_boundary

~~~cpp
static std::size_t TextBox::next_utf8_boundary(const std::string &text, std::size_t position)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Storage:** static · **Returns:** `std::size_t`

Constructs a Label value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
TextBox & TextBox::operator=(const TextBox &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `TextBox &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### previous_utf8_boundary

~~~cpp
static std::size_t TextBox::previous_utf8_boundary(const std::string &text, std::size_t position)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Storage:** static · **Returns:** `std::size_t`

Performs the previous utf8 boundary operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### refresh_display_text

~~~cpp
void TextBox::refresh_display_text()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs the refresh display text operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### set_max_length

~~~cpp
void TextBox::set_max_length(std::size_t maximum_bytes)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the resize to text operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_prefix

~~~cpp
void TextBox::set_prefix(const std::string &prefix)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_value

~~~cpp
void TextBox::set_value(const std::string &value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### single_line_text

~~~cpp
static std::string TextBox::single_line_text(std::string text)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Storage:** static · **Returns:** `std::string`

Performs the single line text operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### TextBox

~~~cpp
TextBox::TextBox(const TextBox &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a TextBox value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### TextBox

~~~cpp
TextBox::TextBox(const Transform &transform={}, IFont *font=nullptr, Object_Pool *object_pool=nullptr, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a TextBox value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `const Transform &` | Value supplied for the transform parameter. | — |
| `font` | `IFont *` | Value supplied for the font parameter. | — |
| `object_pool` | `Object_Pool *` | Value supplied for the object_pool parameter. | — |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |



