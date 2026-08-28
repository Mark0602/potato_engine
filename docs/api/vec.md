# Vec

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `vec.h`  
**Documented overloads:** 18

This page documents the engine-owned callables declared for `Vec`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Vec velocity{120.0f, 0.0f};
Transform player{{32.0f, 48.0f}, {16.0f, 16.0f}};
player.pos += velocity * delta_seconds;
~~~

## Functions

### operator-

~~~cpp
Vec Vec::operator-(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Implements the operator- operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### operator-=

~~~cpp
Vec & Vec::operator-=(const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Implements the operator-= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### operator!=

~~~cpp
bool Vec::operator!=(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator!= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### operator*

~~~cpp
Vec Vec::operator*(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Component-wise multiplication.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### operator*

~~~cpp
Vec Vec::operator*(float b) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Scalar multiplication.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator*=

~~~cpp
Vec & Vec::operator*=(const Vec &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Component-wise multiply-assign.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `b` | `const Vec &` | Value supplied for the b parameter. | — |


---

### operator*=

~~~cpp
Vec & Vec::operator*=(float b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Implements the operator*= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator/

~~~cpp
Vec Vec::operator/(float b) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Scalar division. Behaviour is undefined if b is zero.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator/=

~~~cpp
Vec & Vec::operator/=(float b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Implements the operator/= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator+

~~~cpp
Vec Vec::operator+(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Implements the operator+ operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### operator+=

~~~cpp
Vec & Vec::operator+=(const Vec &a)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec &`

Implements the operator+= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### operator<

~~~cpp
bool Vec::operator<(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

True only if both x and y are strictly less.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### operator<=

~~~cpp
bool Vec::operator<=(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator< operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### operator==

~~~cpp
bool Vec::operator==(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator== operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### operator>

~~~cpp
bool Vec::operator>(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

True only if both x and y are strictly greater.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### operator>=

~~~cpp
bool Vec::operator>=(const Vec &a) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Implements the operator> operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Vec &` | Value supplied for the a parameter. | — |


---

### Vec

~~~cpp
Vec::Vec() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Transform value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Vec

~~~cpp
Vec::Vec(float x, float y)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Vec with given x and y values.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.



