# Physics::Physics_Engine

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `physics.h`  
**Documented overloads:** 25

This page documents the engine-owned callables declared for `Physics::Physics_Engine`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Detailed workflow example

~~~cpp
Tilemap level;
if (!level.load_json("assets/maps/level01.json")) {
    Engine::logger->log(Log_Level::ERROR, "World", "Level could not be loaded");
    return;
}

Physics::Collision_Body player_body;
player_body.set_body_type(Physics::Body_Type::DYNAMIC);
player_body.set_shape(Physics::Collision_Shape::RECTANGLE);
player_body.set_mass(1.0f);
player_body.set_local_bounds({0.0f, 0.0f}, {24.0f, 32.0f});
Engine::physics_engine->add_body(&player_body);

player_body.apply_force({240.0f, 0.0f});
Engine::physics_engine->update(delta_seconds);
auto nearby = Engine::physics_engine->query_overlaps(player_body, Physics::MASK_ALL);
~~~

## Usage example

~~~cpp
Physics::Collision_Body body;
body.set_mass(2.0f);
Engine::physics_engine->add_body(&body);
~~~

## Functions

### ~Physics_Engine

~~~cpp
Physics::Physics_Engine::~Physics_Engine()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Detaches every registered body and clears simulation state.

**Parameters:** None.

---

### add_body

~~~cpp
void Physics::Physics_Engine::add_body(Collision_Body *body)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Registers a body with this world.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `body` | `Collision_Body *` | Borrowed pointer. Duplicate registration is ignored. | — |


---

### auto_sleep

~~~cpp
bool Physics::Physics_Engine::auto_sleep() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Applies the requested state change to the target object or service. Validate target pointers and preconditions before invoking the operation.

**Parameters:** None.

---

### bodies

~~~cpp
const std::vector< Collision_Body * > & Physics::Physics_Engine::bodies() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::vector< Collision_Body * > &`

Performs the bodies operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### clear

~~~cpp
void Physics::Physics_Engine::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Detaches every body and clears collisions and timestep state.

**Parameters:** None.

---

### collisions

~~~cpp
const std::vector< Collision > & Physics::Physics_Engine::collisions() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::vector< Collision > &`

Performs the collisions operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### fixed_timestep

~~~cpp
float Physics::Physics_Engine::fixed_timestep() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the fixed timestep operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### gravity

~~~cpp
const Vec & Physics::Physics_Engine::gravity() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Vec &`

Constructs a Gravitational_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### masks_allow

~~~cpp
static bool Physics::Physics_Engine::masks_allow(const Collision_Body &a, const Collision_Body &b)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Storage:** static · **Returns:** `bool`

Creates or emits a new engine value using the supplied configuration. Determine ownership from the return type and the owning pool or service.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `const Collision_Body &` | Value supplied for the a parameter. | — |
| `b` | `const Collision_Body &` | Value supplied for the b parameter. | — |


---

### Physics_Engine

~~~cpp
Physics::Physics_Engine::Physics_Engine(Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an empty physics world.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Optional logger pointer. The world does not own it. | — |


---

### query_overlaps

~~~cpp
std::vector< Collision_Body * > Physics::Physics_Engine::query_overlaps(const Collision_Body &body, Mask_Tag mask=MASK_ALL) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Collision_Body * >`

Finds registered bodies overlapping the supplied body.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `body` | `const Collision_Body &` | Body used as the query shape. It need not be registered. | — |
| `mask` | `Mask_Tag` | Collision categories included in the result. | `MASK_ALL` |


---

### raycast

~~~cpp
Raycast_Hit Physics::Physics_Engine::raycast(const Vec &origin, const Vec &direction, float max_distance, Mask_Tag mask=MASK_ALL, const Collision_Body *ignored_body=nullptr) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Raycast_Hit`

Casts a ray through the physics world and returns the nearest hit.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `origin` | `const Vec &` | Ray start in world coordinates. | — |
| `direction` | `const Vec &` | Ray direction; normalized internally. | — |
| `mask` | `Mask_Tag` | Collision categories accepted by the query. | `MASK_ALL` |
| `ignored_body` | `const Collision_Body *` | Optional body that should never be returned. | — |


---

### rebuild_static_grid

~~~cpp
void Physics::Physics_Engine::rebuild_static_grid()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Performs the query overlaps operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### remove_body

~~~cpp
void Physics::Physics_Engine::remove_body(Collision_Body *body)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes a body without destroying it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `body` | `Collision_Body *` | Body pointer to remove. | — |


---

### resolve

~~~cpp
void Physics::Physics_Engine::resolve(Collision &collision)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Applies positional correction, normal impulse and friction.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `collision` | `Collision &` | Value supplied for the collision parameter. | — |


---

### set_auto_sleep

~~~cpp
void Physics::Physics_Engine::set_auto_sleep(bool enabled)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_fixed_timestep

~~~cpp
void Physics::Physics_Engine::set_fixed_timestep(float seconds)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the fixed simulation step in seconds. Invalid values are ignored.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_gravity

~~~cpp
void Physics::Physics_Engine::set_gravity(const Vec &gravity)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets world gravity in logical units per second squared.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `gravity` | `const Vec &` | New gravity vector. | — |


---

### set_max_substeps

~~~cpp
void Physics::Physics_Engine::set_max_substeps(int count)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the maximum physics steps processed during one frame.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_sleep_settings

~~~cpp
void Physics::Physics_Engine::set_sleep_settings(float velocity_threshold, int stationary_steps)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_spatial_cell_size

~~~cpp
void Physics::Physics_Engine::set_spatial_cell_size(float size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the uniform-grid cell size used by broad-phase collision detection.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### spatial_cell_size

~~~cpp
float Physics::Physics_Engine::spatial_cell_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `float`

Performs the spatial cell size operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### step

~~~cpp
void Physics::Physics_Engine::step(float delta_seconds)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs exactly one simulation step.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### test_collision

~~~cpp
bool Physics::Physics_Engine::test_collision(Collision_Body &a, Collision_Body &b, Collision *result=nullptr) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Tests two bodies without advancing or resolving them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `a` | `Collision_Body &` | First body. | — |
| `b` | `Collision_Body &` | Second body. | — |
| `result` | `Collision *` | Optional output collision information. | — |


---

### update

~~~cpp
void Physics::Physics_Engine::update(float delta_seconds)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Advances the world using an accumulator and fixed timestep.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


