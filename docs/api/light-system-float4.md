# Light_System::Float4

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `light.h`  
**Documented overloads:** 5

This page documents the engine-owned callables declared for `Light_System::Float4`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Engine::lighting->set_time_of_day(20.0f);
Engine::lighting->set_shadow_strength(0.75f);
~~~

## Functions

### Float4

~~~cpp
Light_System::Float4::Float4() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Float4

~~~cpp
Light_System::Float4::Float4(const Color &color, float w=1.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `color` | `const Color &` | Value supplied for the color parameter. | — |


---

### Float4

~~~cpp
Light_System::Float4::Float4(const Vec &vec, float z=0.0f, float w=0.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `vec` | `const Vec &` | Value supplied for the vec parameter. | — |


---

### Float4

~~~cpp
Light_System::Float4::Float4(const Vec4 &vec)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `vec` | `const Vec4 &` | Value supplied for the vec parameter. | — |


---

### Float4

~~~cpp
Light_System::Float4::Float4(float x, float y, float z, float w)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Float4 value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.



