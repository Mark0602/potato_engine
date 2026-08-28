# Color

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `color.h`  
**Documented overloads:** 46

This page documents the engine-owned callables declared for `Color`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Color tint = Color::from_hex_string("#FFAA33");
tint = tint.with_alpha(192);
~~~

## Functions

### black

~~~cpp
static const Color Color::black()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined black color (0, 0, 0, 255).

**Parameters:** None.

---

### blue

~~~cpp
static const Color Color::blue()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined blue color (0, 0, 255, 255).

**Parameters:** None.

---

### brown

~~~cpp
static const Color Color::brown()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined brown color (165, 42, 42, 255).

**Parameters:** None.

---

### Color

~~~cpp
Color::Color() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Color with specified red, green, blue, and alpha values.

**Parameters:** None.

---

### Color

~~~cpp
Color::Color(const SDL_Color &color)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Color from an SDL_Color.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Color

~~~cpp
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a=255)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Color with specified red, green, blue, and alpha values.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### cyan

~~~cpp
static const Color Color::cyan()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined cyan color (0, 255, 255, 255).

**Parameters:** None.

---

### dark_blue

~~~cpp
static const Color Color::dark_blue()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark blue color (0, 0, 139, 255).

**Parameters:** None.

---

### dark_cyan

~~~cpp
static const Color Color::dark_cyan()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark cyan color (0, 139, 139, 255).

**Parameters:** None.

---

### dark_gray

~~~cpp
static const Color Color::dark_gray()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark gray color (169, 169, 169, 255).

**Parameters:** None.

---

### dark_green

~~~cpp
static const Color Color::dark_green()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark green color (0, 100, 0, 255).

**Parameters:** None.

---

### dark_magenta

~~~cpp
static const Color Color::dark_magenta()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark magenta color (139, 0, 139, 255).

**Parameters:** None.

---

### dark_red

~~~cpp
static const Color Color::dark_red()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark red color (139, 0, 0, 255).

**Parameters:** None.

---

### dark_yellow

~~~cpp
static const Color Color::dark_yellow()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined dark yellow color (204, 204, 0, 255).

**Parameters:** None.

---

### from_hex

~~~cpp
static Color Color::from_hex(uint32_t hex)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `Color`

Creates a Color from a hexadecimal value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### from_hex_string

~~~cpp
static Color Color::from_hex_string(std::string hex_string)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `Color`

Creates a Color from a hexadecimal string.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### from_sdl_color

~~~cpp
static Color Color::from_sdl_color(const SDL_Color &color)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `Color`

Creates a Color from an SDL_Color.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### gray

~~~cpp
static const Color Color::gray()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined gray color (128, 128, 128, 255).

**Parameters:** None.

---

### green

~~~cpp
static const Color Color::green()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined green color (0, 255, 0, 255).

**Parameters:** None.

---

### light_blue

~~~cpp
static const Color Color::light_blue()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light blue color (173, 216, 230, 255).

**Parameters:** None.

---

### light_cyan

~~~cpp
static const Color Color::light_cyan()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light cyan color (224, 255, 255, 255).

**Parameters:** None.

---

### light_gray

~~~cpp
static const Color Color::light_gray()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light gray color (211, 211, 211, 255).

**Parameters:** None.

---

### light_green

~~~cpp
static const Color Color::light_green()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light green color (144, 238, 144, 255).

**Parameters:** None.

---

### light_magenta

~~~cpp
static const Color Color::light_magenta()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light magenta color (255, 182, 255, 255).

**Parameters:** None.

---

### light_red

~~~cpp
static const Color Color::light_red()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light red color (255, 182, 193, 255).

**Parameters:** None.

---

### light_yellow

~~~cpp
static const Color Color::light_yellow()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined light yellow color (255, 255, 224, 255).

**Parameters:** None.

---

### magenta

~~~cpp
static const Color Color::magenta()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined magenta color (255, 0, 255, 255).

**Parameters:** None.

---

### operator-

~~~cpp
Color Color::operator-(const Color &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Constructs a Vec value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |


---

### operator-=

~~~cpp
Color & Color::operator-=(const Color &other)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color &`

Implements the operator-= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |


---

### operator!=

~~~cpp
bool Color::operator!=(const Color &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator!= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |


---

### operator*

~~~cpp
Color Color::operator*(float scalar) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Implements the operator* operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator*=

~~~cpp
Color & Color::operator*=(float scalar)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color &`

Implements the operator*= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator/

~~~cpp
Color Color::operator/(float scalar) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Implements the operator/ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator/=

~~~cpp
Color & Color::operator/=(float scalar)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color &`

Implements the operator/= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator+

~~~cpp
Color Color::operator+(const Color &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Implements the operator+ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |


---

### operator+=

~~~cpp
Color & Color::operator+=(const Color &other)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color &`

Implements the operator+= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |


---

### operator==

~~~cpp
bool Color::operator==(const Color &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator== operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Color &` | Value supplied for the other parameter. | — |


---

### orange

~~~cpp
static const Color Color::orange()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined orange color (255, 165, 0, 255).

**Parameters:** None.

---

### pink

~~~cpp
static const Color Color::pink()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined pink color (255, 192, 203, 255).

**Parameters:** None.

---

### purple

~~~cpp
static const Color Color::purple()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined purple color (128, 0, 128, 255).

**Parameters:** None.

---

### red

~~~cpp
static const Color Color::red()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined red color (255, 0, 0, 255).

**Parameters:** None.

---

### to_sdl_color

~~~cpp
SDL_Color Color::to_sdl_color() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `SDL_Color`

Converts the Color to an SDL_Color.

**Parameters:** None.

---

### transparent

~~~cpp
static const Color Color::transparent()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined transparent color (0, 0, 0, 0).

**Parameters:** None.

---

### white

~~~cpp
static const Color Color::white()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined white color (255, 255, 255, 255).

**Parameters:** None.

---

### with_alpha

~~~cpp
Color Color::with_alpha(uint8_t alpha) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Color`

Creates a Color with specified alpha value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### yellow

~~~cpp
static const Color Color::yellow()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `const Color`

Predefined yellow color (255, 255, 0, 255).

**Parameters:** None.


