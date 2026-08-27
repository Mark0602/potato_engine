# Physics and Tilemaps API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This reference lists every engine-owned function overload declared in the covered headers. Signatures preserve parameter types, names, default values, qualifiers, and namespaces from the source. Access labels identify members that are not part of the public calling surface.

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

## physics.h

---

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

Constructs a Collision_Body value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

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

Constructs a Collision_Body value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

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

### make_mask_tag

~~~cpp
constexpr Mask_Tag Physics::make_mask_tag(std::uint8_t bit_index)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `constexpr Mask_Tag`

Creates a single collision category bit.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

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

### operator bool

~~~cpp
Physics::Raycast_Hit::operator bool() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Implements the operator bool operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

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

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.

---

### transform

~~~cpp
Transform & Physics::Collision_Body::transform()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Transform &`

Performs the transform operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

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

---

### Header usage example

~~~cpp
Physics::Collision_Body body;
body.set_mass(2.0f);
Engine::physics_engine->add_body(&body);
~~~

## tileset.h

---

### add

~~~cpp
void Tilemap_Registry::add(const std::string &name, Tilemap *tilemap)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

This overload performs the operation identified by its signature. Review its parameter and return metadata below, and call it only in the lifecycle phase required by the owning component.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tilemap` | `Tilemap *` | Value supplied for the tilemap parameter. | — |

---

### add_index

~~~cpp
void Tileset_Group::add_index(int index)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds one tile id to the group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### cell_index

~~~cpp
std::size_t Tilemap::cell_index(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `std::size_t`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### cell_to_world

~~~cpp
Vec Tilemap::cell_to_world(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Converts a cell's column and row indices to world coordinates.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### clear

~~~cpp
void Tilemap::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Transforms the supplied value into the requested representation. The source value is preserved unless a non-const reference appears in the signature.

**Parameters:** None.

---

### clear_indexes

~~~cpp
void Tileset_Group::clear_indexes()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Clears all tile ids from the group.

**Parameters:** None.

---

### create

~~~cpp
bool Tilemap::create(int width, int height, int empty_tile_id=-1, Vec origin={0.f, 0.f})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Creates a new tilemap with the given dimensions and origin.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `origin` | `Vec` | Top-left position of the tilemap in world coordinates. | — |

---

### create_tile

~~~cpp
Tile Tileset::create_tile(int id, const Vec &position, bool collidable=false) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tile`

Creates a lightweight Tile using this tileset's texture.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left position for the tile. | — |

---

### draw

~~~cpp
void Tile::draw(SDL_Renderer *renderer, const Vec &size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the tile using its full texture.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `size` | `const Vec &` | Draw size in logical coordinates. | — |

---

### draw

~~~cpp
void Tilemap::draw(SDL_Renderer *renderer, const class Camera *camera=nullptr) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `camera` | `const class Camera *` | Value supplied for the camera parameter. | — |

---

### draw

~~~cpp
void Tileset::draw(SDL_Renderer *renderer, int index, const Vec &position, const Vec &size, bool skip_when_transparent=true) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws a tile id at a position using a custom draw size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left draw position. | — |
| `size` | `const Vec &` | Destination draw size. | — |

---

### draw

~~~cpp
void Tileset::draw(SDL_Renderer *renderer, int index, const Vec &position) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws a tile id at a position using the default tile size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left draw position. | — |

---

### draw_group

~~~cpp
void Tileset_Group::draw_group(SDL_Renderer *renderer, const Vec &position, int columns) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the group wrapped into rows.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left position of the first tile. | — |

---

### draw_group

~~~cpp
void Tileset_Group::draw_group(SDL_Renderer *renderer, const Vec &position) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the group in one horizontal row.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left position of the first tile. | — |

---

### draw_tile

~~~cpp
void Tileset::draw_tile(SDL_Renderer *renderer, const Tile &tile, const Vec &size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws a Tile using the Tile id and position with a custom draw size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile` | `const Tile &` | Tile data to draw. | — |
| `size` | `const Vec &` | Destination draw size. | — |

---

### draw_tile

~~~cpp
void Tileset::draw_tile(SDL_Renderer *renderer, const Tile &tile) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws a Tile using the Tile id and position.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile` | `const Tile &` | Tile data to draw. | — |

---

### erase_tile

~~~cpp
bool Tilemap::erase_tile(int column, int row)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Erases a tile at the specified column and row, setting it to the empty tile id.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### get

~~~cpp
Tilemap * Tilemap_Registry::get(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tilemap *`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### get_cell_size

~~~cpp
Vec Tilemap::get_cell_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_cell_texture

~~~cpp
Texture * Tilemap::get_cell_texture(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### get_height

~~~cpp
int Tilemap::get_height() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_id

~~~cpp
int Tile::get_id() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Gets the numeric id of the tile.

**Parameters:** None.

---

### get_indexes

~~~cpp
std::vector< int > Tileset_Group::get_indexes() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< int >`

Gets all tile ids in the group.

**Parameters:** None.

---

### get_last_error

~~~cpp
const std::string & Tilemap::get_last_error() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_origin

~~~cpp
Vec Tilemap::get_origin() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_position

~~~cpp
Vec Tile::get_position() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the top-left position of the tile.

**Parameters:** None.

---

### get_revision

~~~cpp
std::uint64_t Tilemap::get_revision() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::uint64_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_source_path

~~~cpp
const std::string & Tilemap::get_source_path() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_texture

~~~cpp
Texture * Tile::get_texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Gets the texture assigned to the tile.

**Parameters:** None.

---

### get_texture

~~~cpp
Texture * Tileset::get_texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Gets the texture atlas used by the tileset.

**Parameters:** None.

---

### get_tile

~~~cpp
int Tilemap::get_tile(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### get_tile_count

~~~cpp
std::size_t Tileset::get_tile_count() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Gets the number of indexed tiles in the tileset.

**Parameters:** None.

---

### get_tile_rect

~~~cpp
const SDL_FRect * Tileset::get_tile_rect(int index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const SDL_FRect *`

Gets the source rectangle for a tile id.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### get_tile_size

~~~cpp
Vec Tileset::get_tile_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the size of a single tile.

**Parameters:** None.

---

### get_tile_texture

~~~cpp
Texture * Tileset::get_tile_texture(int index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Gets the texture used for a specific tile id.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### get_tileset

~~~cpp
const Tileset * Tilemap::get_tileset() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Tileset *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_tileset

~~~cpp
const Tileset * Tileset_Group::get_tileset() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Tileset *`

Gets the tileset used by the group.

**Parameters:** None.

---

### get_tileset

~~~cpp
Tileset * Tileset::get_tileset()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tileset *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_tileset_size

~~~cpp
Vec Tileset::get_tileset_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the grid size of the tileset.

**Parameters:** None.

---

### get_width

~~~cpp
int Tilemap::get_width() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### init

~~~cpp
void Tileset::init(Texture *whole_texture, const Vec &tile_size, const Vec &tileset_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Initializes or reinitializes the tileset.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `whole_texture` | `Texture *` | Borrowed pointer to the full atlas texture. | — |
| `tile_size` | `const Vec &` | Size of one tile in pixels/logical units. | — |
| `tileset_size` | `const Vec &` | Number of tiles in the atlas as columns and rows. | — |

---

### is_collidable

~~~cpp
bool Tile::is_collidable() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether this tile is collidable.

**Parameters:** None.

---

### is_valid_cell

~~~cpp
bool Tilemap::is_valid_cell(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the specified column and row are valid cell coordinates in the tilemap.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### is_valid_index

~~~cpp
bool Tileset::is_valid_index(int index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if a tile id exists in the tileset.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### load_json

~~~cpp
bool Tilemap::load_json(const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Loads a tilemap from a JSON file.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### load_tileset

~~~cpp
Tileset * Tileset::load_tileset(const std::string &path, Logger *logger=nullptr, SDL_ScaleMode scale_mode=SDL_SCALEMODE_PIXELART)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tileset *`

Performs the init operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |

---

### names

~~~cpp
std::vector< std::string > Tilemap_Registry::names()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< std::string >`

Performs the names operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### rebuild_tile_rects

~~~cpp
void Tileset::rebuild_tile_rects()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Rebuilds the cached source rectangles from tile size and grid size.

**Parameters:** None.

---

### remove

~~~cpp
void Tilemap_Registry::remove(const std::string &name, Tilemap *tilemap=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the rebuild tile rects operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tilemap` | `Tilemap *` | Value supplied for the tilemap parameter. | — |

---

### resize

~~~cpp
bool Tilemap::resize(int new_width, int new_height, int empty_tile_id=-1)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Resizes the tilemap to new dimensions, preserving existing tiles where possible.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### save_json

~~~cpp
bool Tilemap::save_json(const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Saves the tilemap to a JSON file.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### set_cell_size

~~~cpp
void Tilemap::set_cell_size(Vec cell_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the resize operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `cell_size` | `Vec` | Value supplied for the cell_size parameter. | — |

---

### set_cell_texture

~~~cpp
bool Tilemap::set_cell_texture(int column, int row, Texture *texture)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Value supplied for the texture parameter. | — |

---

### set_collidable

~~~cpp
void Tile::set_collidable(bool collidable)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets whether this tile is collidable.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### set_id

~~~cpp
void Tile::set_id(int id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the numeric id of the tile.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### set_indexes

~~~cpp
void Tileset_Group::set_indexes(const std::vector< int > &indexes)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets all tile ids in the group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### set_origin

~~~cpp
void Tilemap::set_origin(Vec origin)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `origin` | `Vec` | Value supplied for the origin parameter. | — |

---

### set_position

~~~cpp
void Tile::set_position(const Vec &position)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the top-left position of the tile.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | New tile position in logical coordinates. | — |

---

### set_texture

~~~cpp
void Tile::set_texture(Texture *texture)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the texture assigned to the tile.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Borrowed pointer to the tile texture, or nullptr. | — |

---

### set_texture

~~~cpp
void Tileset::set_texture(Texture *texture)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the texture atlas used by the tileset.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Borrowed pointer to the atlas texture, or nullptr. | — |

---

### set_tile

~~~cpp
bool Tilemap::set_tile(int column, int row, int tile_id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### set_tile_size

~~~cpp
void Tileset::set_tile_size(const Vec &tile_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the size of a single tile and rebuilds the source rectangles.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile_size` | `const Vec &` | New tile size. | — |

---

### set_tileset

~~~cpp
void Tilemap::set_tileset(const Tileset *tileset)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Value supplied for the tileset parameter. | — |

---

### set_tileset

~~~cpp
void Tileset_Group::set_tileset(const Tileset *tileset)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the tileset used by the group.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Borrowed pointer to the tileset, or nullptr. | — |

---

### set_tileset_size

~~~cpp
void Tileset::set_tileset_size(const Vec &tileset_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the grid size of the tileset and rebuilds the source rectangles.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset_size` | `const Vec &` | New grid size as columns and rows. | — |

---

### submit

~~~cpp
void Tilemap::submit(class Render_Pool &render_pool, uint8_t z_index=128, const class Camera *camera=nullptr, const Color &tint=Color::white(), bool camera_space=true, bool y_sort=true) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `render_pool` | `class Render_Pool &` | Value supplied for the render_pool parameter. | — |
| `camera` | `const class Camera *` | Value supplied for the camera parameter. | — |
| `tint` | `const Color &` | Value supplied for the tint parameter. | `Color::white()` |

---

### Tile

~~~cpp
Tile::Tile() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an empty tile.

**Parameters:** None.

---

### Tile

~~~cpp
Tile::Tile(int id, const Vec &position, Texture *texture=nullptr, bool collidable=false)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a tile with an id, position, texture and collision flag.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left position of the tile in logical coordinates. | — |
| `texture` | `Texture *` | Texture used by this tile. This is borrowed, not owned. | — |

---

### Tilemap

~~~cpp
Tilemap::Tilemap() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Tile value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Tilemap

~~~cpp
Tilemap::Tilemap(const Tileset *tileset)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Tilemap value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Value supplied for the tileset parameter. | — |

---

### Tileset

~~~cpp
Tileset::Tileset() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an empty tileset.

**Parameters:** None.

---

### Tileset

~~~cpp
Tileset::Tileset(Texture *whole_texture, const Vec &tile_size, const Vec &tileset_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a tileset from a texture atlas and grid information.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `whole_texture` | `Texture *` | Borrowed pointer to the full atlas texture. | — |
| `tile_size` | `const Vec &` | Size of one tile in pixels/logical units. | — |
| `tileset_size` | `const Vec &` | Number of tiles in the atlas as columns and rows. | — |

---

### Tileset_Group

~~~cpp
Tileset_Group::Tileset_Group() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an empty group.

**Parameters:** None.

---

### Tileset_Group

~~~cpp
Tileset_Group::Tileset_Group(const Tileset *tileset, const std::vector< int > &indexes)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a group for a tileset with explicit tile indexes.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Borrowed pointer to the tileset used for drawing. | — |

---

### Tileset_Group

~~~cpp
Tileset_Group::Tileset_Group(const Tileset *tileset)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a group for a tileset with no explicit indexes.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Borrowed pointer to the tileset used for drawing. | — |

---

### valid_cell

~~~cpp
bool Tilemap::valid_cell(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `bool`

Constructs a Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.

---

### world_to_cell

~~~cpp
bool Tilemap::world_to_cell(const Vec &world_position, int &out_column, int &out_row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Converts world coordinates to cell indices in the tilemap.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `world_position` | `const Vec &` | World coordinates to convert. | — |

---

### Header usage example

~~~cpp
Tilemap map;
map.load_json("assets/maps/level1.json");
map.set_tile(4, 3, 7);
~~~







