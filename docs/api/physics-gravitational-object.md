# Physics::Gravitational_Object

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `physics.h`  
**Documented overloads:** 2

This page documents the engine-owned callables declared for `Physics::Gravitational_Object`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Physics::Collision_Body body;
body.set_mass(2.0f);
Engine::physics_engine->add_body(&body);
~~~

## Functions

### Gravitational_Object

~~~cpp
Physics::Gravitational_Object::Gravitational_Object(const Transform &transform, Collision_Shape shape=Collision_Shape::RECTANGLE, float mass=1.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a standalone gravitational body.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `const Transform &` | Initial world-space transform. | — |
| `shape` | `Collision_Shape` | Collision shape used by the body. | `Collision_Shape::RECTANGLE` |


---

### Gravitational_Object

~~~cpp
Physics::Gravitational_Object::Gravitational_Object(Object *owner, Collision_Shape shape=Collision_Shape::RECTANGLE, float mass=1.0f)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a gravitational body attached to an Object.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `owner` | `Object *` | Borrowed Object pointer. | — |
| `shape` | `Collision_Shape` | Collision shape used by the body. | `Collision_Shape::RECTANGLE` |


