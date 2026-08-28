# Transform

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `vec.h`  
**Documented overloads:** 12

This page documents the engine-owned callables declared for `Transform`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Vec velocity{120.0f, 0.0f};
Transform player{{32.0f, 48.0f}, {16.0f, 16.0f}};
player.pos += velocity * delta_seconds;
~~~

## Functions

### operator-

~~~cpp
Transform Transform::operator-(const Transform &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Transform &` | Value supplied for the other parameter. | — |


---

### operator-=

~~~cpp
Transform & Transform::operator-=(const Transform &other)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Implements the operator-= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Transform &` | Value supplied for the other parameter. | — |


---

### operator*

~~~cpp
Transform Transform::operator*(float scalar) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Implements the operator* operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator*=

~~~cpp
Transform & Transform::operator*=(float scalar)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Implements the operator* operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator/

~~~cpp
Transform Transform::operator/(float scalar) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Implements the operator/ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator/=

~~~cpp
Transform & Transform::operator/=(float scalar)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Implements the operator/ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator+

~~~cpp
Transform Transform::operator+(const Transform &other) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Implements the operator+ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Transform &` | Value supplied for the other parameter. | — |


---

### operator+=

~~~cpp
Transform & Transform::operator+=(const Transform &other)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Implements the operator+= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `other` | `const Transform &` | Value supplied for the other parameter. | — |


---

### Transform

~~~cpp
Transform::Transform() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Transform

~~~cpp
Transform::Transform(const Vec &pos, const Vec &size, const Vec &rotation)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform with given position, size, and rotation.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Position in 2D space. | — |
| `size` | `const Vec &` | Size in 2D space. | — |
| `rotation` | `const Vec &` | Rotation in 2D space. x is the angle in degrees, y is the SDL_FlipMode. | — |


---

### Transform

~~~cpp
Transform::Transform(const Vec &pos, const Vec &size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform with given position and size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Position in 2D space. | — |
| `size` | `const Vec &` | Size in 2D space. | — |


---

### Transform

~~~cpp
Transform::Transform(const Vec &pos)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform with given position.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `const Vec &` | Position in 2D space. | — |



