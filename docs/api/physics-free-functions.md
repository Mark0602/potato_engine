# Physics free functions

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `physics.h`  
**Documented overloads:** 1

This page documents the engine-owned callables declared for `Physics free functions`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Physics::Collision_Body body;
body.set_mass(2.0f);
Engine::physics_engine->add_body(&body);
~~~

## Functions

### operator bool

~~~cpp
Physics::Raycast_Hit::operator bool() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Implements the operator bool operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** None.

