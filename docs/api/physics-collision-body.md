# Physics::Collision_Body

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `physics.h`  
**Documented overloads:** 35

This page documents the engine-owned callables declared for `Physics::Collision_Body`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Physics::Collision_Body body;
body.set_mass(2.0f);
Engine::physics_engine->add_body(&body);
~~~

## Functions

### ~Collision_Body

~~~cpp
virtual Physics::Collision_Body::~Collision_Body()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Unregisters the body from its physics world.

**Parameters:** None.

---

### alpha_threshold

~~~cpp
std::uint8_t Physics::Collision_Body::alpha_threshold() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::uint8_t`

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### apply_force

~~~cpp
void Physics::Collision_Body::apply_force(const Vec &force)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Accumulates a continuous force for the next simulation step.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `force` | `const Vec &` | Force vector in world-space directions. | — |


---

### apply_impulse

~~~cpp
void Physics::Collision_Body::apply_impulse(const Vec &impulse)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Immediately changes dynamic body velocity using an impulse.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `impulse` | `const Vec &` | Impulse vector applied to the body. | — |


---

### body_type

~~~cpp
Body_Type Physics::Collision_Body::body_type() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Body_Type`

Performs the body type operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### clear_forces

~~~cpp
void Physics::Collision_Body::clear_forces()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes all forces waiting for the next simulation step.

**Parameters:** None.

---

### clear_local_bounds

~~~cpp
void Physics::Collision_Body::clear_local_bounds()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### Collision_Body

~~~cpp
Physics::Collision_Body::Collision_Body(const Collision_Body &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Copy construction is disabled because a body has registration state and a borrowed owner relationship.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Collision_Body

~~~cpp
Physics::Collision_Body::Collision_Body(const Transform &transform, Collision_Shape shape=Collision_Shape::RECTANGLE, Body_Type type=Body_Type::STATIC)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a standalone collision body with its own Transform.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `const Transform &` | Initial world-space transform copied into the body. | — |
| `shape` | `Collision_Shape` | Collision shape used by narrow-phase checks. | `Collision_Shape::RECTANGLE` |
| `type` | `Body_Type` | Simulation type of the body. | `Body_Type::STATIC` |


---

### Collision_Body

~~~cpp
Physics::Collision_Body::Collision_Body(Object *owner, Collision_Shape shape=Collision_Shape::RECTANGLE, Body_Type type=Body_Type::STATIC)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a collision body attached to an Object.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `owner` | `Object *` | Borrowed Object pointer whose transform and texture are used. | — |
| `shape` | `Collision_Shape` | Collision shape used by narrow-phase checks. | `Collision_Shape::RECTANGLE` |
| `type` | `Body_Type` | Simulation type of the body. | `Body_Type::STATIC` |


---

### collision_transform

~~~cpp
Transform Physics::Collision_Body::collision_transform() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Returns the effective world-space collision transform, including the owner's parent hierarchy and optional local collider transform.

**Parameters:** None.

---

### has_local_bounds

~~~cpp
bool Physics::Collision_Body::has_local_bounds() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### inverse_mass

~~~cpp
float Physics::Collision_Body::inverse_mass() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the inverse mass operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### is_awake

~~~cpp
bool Physics::Collision_Body::is_awake() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### local_offset

~~~cpp
Vec Physics::Collision_Body::local_offset() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Performs the local offset operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### local_size

~~~cpp
Vec Physics::Collision_Body::local_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Performs the local size operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### local_transform

~~~cpp
const Transform & Physics::Collision_Body::local_transform() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Transform &`

Performs the local transform operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### mass

~~~cpp
float Physics::Collision_Body::mass() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the mass operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### operator=

~~~cpp
Collision_Body & Physics::Collision_Body::operator=(const Collision_Body &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Collision_Body &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### owner

~~~cpp
Object * Physics::Collision_Body::owner() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Object *`

Performs the owner operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### previous_transform

~~~cpp
Transform Physics::Collision_Body::previous_transform() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform`

Constructs a Physics_Engine value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### set_alpha_threshold

~~~cpp
void Physics::Collision_Body::set_alpha_threshold(std::uint8_t threshold)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the minimum alpha value considered solid.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_body_type

~~~cpp
void Physics::Collision_Body::set_body_type(Body_Type type)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Changes how the body participates in simulation.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `type` | `Body_Type` | New static, dynamic, or kinematic body type. | — |


---

### set_collision_callback

~~~cpp
void Physics::Collision_Body::set_collision_callback(Collision_Callback callback)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the callback invoked for collision and trigger events.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `callback` | `Collision_Callback` | Function receiving collision information from this body's perspective. | — |


---

### set_local_bounds

~~~cpp
void Physics::Collision_Body::set_local_bounds(Vec offset, Vec size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `offset` | `Vec` | Value supplied for the offset parameter. | — |
| `size` | `Vec` | Value supplied for the size parameter. | — |


---

### set_local_transform

~~~cpp
void Physics::Collision_Body::set_local_transform(const Transform &transform)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `transform` | `const Transform &` | Value supplied for the transform parameter. | — |


---

### set_mass

~~~cpp
void Physics::Collision_Body::set_mass(float mass)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets body mass. Values at or below zero are clamped to a safe minimum.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_pixel_texture

~~~cpp
void Physics::Collision_Body::set_pixel_texture(Texture *texture)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Overrides the texture used for pixel-perfect collision.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Borrowed texture pointer. Passing nullptr uses the owner texture. | — |


---

### set_shape

~~~cpp
void Physics::Collision_Body::set_shape(Collision_Shape shape)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Changes the collision shape used by future checks.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `shape` | `Collision_Shape` | New collision shape. | — |


---

### shape

~~~cpp
Collision_Shape Physics::Collision_Body::shape() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Collision_Shape`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** None.

---

### sleep

~~~cpp
void Physics::Collision_Body::sleep()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

---

### texture

~~~cpp
Texture * Physics::Collision_Body::texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Gets the texture used for pixel-perfect checks.

**Parameters:** None.

---

### transform

~~~cpp
const Transform & Physics::Collision_Body::transform() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Transform &`

Returns the owner's local transform when attached, or the standalone body's world transform. Use `collision_transform()` for effective world-space geometry.

**Parameters:** None.

---

### transform

~~~cpp
Transform & Physics::Collision_Body::transform()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Returns a mutable reference to the owner's local transform when attached, or the standalone body's world transform. For world-space teleports of a parented owner, use `Object::set_world_transform()`.

**Parameters:** None.

---

### wake

~~~cpp
void Physics::Collision_Body::wake()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.
