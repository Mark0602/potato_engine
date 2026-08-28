# Physics

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `physics.h`  
**Documented overloads:** 1

This page documents the engine-owned callables declared for `Physics`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Physics::Collision_Body body;
body.set_mass(2.0f);
Engine::physics_engine->add_body(&body);
~~~

## Functions

### make_mask_tag

~~~cpp
constexpr Mask_Tag Physics::make_mask_tag(std::uint8_t bit_index)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `constexpr Mask_Tag`

Creates a single collision category bit.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


