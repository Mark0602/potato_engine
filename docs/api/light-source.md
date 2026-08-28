# light_source

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `light.h`  
**Documented overloads:** 4

This page documents the engine-owned callables declared for `light_source`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Engine::lighting->set_time_of_day(20.0f);
Engine::lighting->set_shadow_strength(0.75f);
~~~

## Functions

### ~light_source

~~~cpp
light_source::~light_source()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### light_source

~~~cpp
light_source::light_source(const light_source &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Performs the light source operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### light_source

~~~cpp
light_source::light_source(Vec position={}, float radius=160.0f, Color color=Color::white(), float intensity=1.0f, float softness=0.35f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Performs the light source operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `Vec` | Value supplied for the position parameter. | — |
| `color` | `Color` | Value supplied for the color parameter. | `Color::white()` |


---

### operator=

~~~cpp
light_source & light_source::operator=(const light_source &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `light_source &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.



