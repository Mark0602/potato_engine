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

### ~Collision_Body

~~~cpp
virtual Physics::Collision_Body::~Collision_Body()
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Unregisters the body from its physics world.

**Parameters:** None.

### ~Physics_Engine

~~~cpp
Physics::Physics_Engine::~Physics_Engine()
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Detaches every registered body and clears simulation state.

**Parameters:** None.

### add_body

~~~cpp
void Physics::Physics_Engine::add_body(Collision_Body *body)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Registers a body with this world.

**Parameters**

- `body` (`Collision_Body *`): Borrowed pointer. Duplicate registration is ignored.

### alpha_threshold

~~~cpp
std::uint8_t Physics::Collision_Body::alpha_threshold() const
~~~

**Access:** public  **Returns:** ``std::uint8_t``  **Engine version:** Potato Engine 1.0.0

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### apply_force

~~~cpp
void Physics::Collision_Body::apply_force(const Vec &force)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Accumulates a continuous force for the next simulation step.

**Parameters**

- `force` (`const Vec &`): Force vector in world-space directions.

### apply_impulse

~~~cpp
void Physics::Collision_Body::apply_impulse(const Vec &impulse)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Immediately changes dynamic body velocity using an impulse.

**Parameters**

- `impulse` (`const Vec &`): Impulse vector applied to the body.

### auto_sleep

~~~cpp
bool Physics::Physics_Engine::auto_sleep() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Applies the requested state change to the target object or service. Validate target pointers and preconditions before invoking the operation.

**Parameters:** None.

### bodies

~~~cpp
const std::vector< Collision_Body * > & Physics::Physics_Engine::bodies() const
~~~

**Access:** public  **Returns:** `const std::vector< Collision_Body * > &`  **Engine version:** Potato Engine 1.0.0

Performs the bodies operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### body_type

~~~cpp
Body_Type Physics::Collision_Body::body_type() const
~~~

**Access:** public  **Returns:** `Body_Type`  **Engine version:** Potato Engine 1.0.0

Performs the body type operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### clear

~~~cpp
void Physics::Physics_Engine::clear()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Detaches every body and clears collisions and timestep state.

**Parameters:** None.

### clear_forces

~~~cpp
void Physics::Collision_Body::clear_forces()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Removes all forces waiting for the next simulation step.

**Parameters:** None.

### clear_local_bounds

~~~cpp
void Physics::Collision_Body::clear_local_bounds()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### Collision_Body

~~~cpp
Physics::Collision_Body::Collision_Body(const Collision_Body &)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Collision_Body value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Collision_Body &`): Value supplied for the  parameter.

### Collision_Body

~~~cpp
Physics::Collision_Body::Collision_Body(const Transform &transform, Collision_Shape shape=Collision_Shape::RECTANGLE, Body_Type type=Body_Type::STATIC)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a standalone collision body with its own Transform.

**Parameters**

- `transform` (`const Transform &`): Initial world-space transform copied into the body.
- `shape` (`Collision_Shape`): Collision shape used by narrow-phase checks. Default: `Collision_Shape::RECTANGLE`.
- `type` (`Body_Type`): Simulation type of the body. Default: `Body_Type::STATIC`.

### Collision_Body

~~~cpp
Physics::Collision_Body::Collision_Body(Object *owner, Collision_Shape shape=Collision_Shape::RECTANGLE, Body_Type type=Body_Type::STATIC)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a collision body attached to an Object.

**Parameters**

- `owner` (`Object *`): Borrowed Object pointer whose transform and texture are used.
- `shape` (`Collision_Shape`): Collision shape used by narrow-phase checks. Default: `Collision_Shape::RECTANGLE`.
- `type` (`Body_Type`): Simulation type of the body. Default: `Body_Type::STATIC`.

### collision_transform

~~~cpp
Transform Physics::Collision_Body::collision_transform() const
~~~

**Access:** public  **Returns:** `Transform`  **Engine version:** Potato Engine 1.0.0

Constructs a Collision_Body value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### collisions

~~~cpp
const std::vector< Collision > & Physics::Physics_Engine::collisions() const
~~~

**Access:** public  **Returns:** `const std::vector< Collision > &`  **Engine version:** Potato Engine 1.0.0

Performs the collisions operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### fixed_timestep

~~~cpp
float Physics::Physics_Engine::fixed_timestep() const
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Performs the fixed timestep operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### Gravitational_Object

~~~cpp
Physics::Gravitational_Object::Gravitational_Object(const Transform &transform, Collision_Shape shape=Collision_Shape::RECTANGLE, float mass=1.0f)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a standalone gravitational body.

**Parameters**

- `transform` (`const Transform &`): Initial world-space transform.
- `shape` (`Collision_Shape`): Collision shape used by the body. Default: `Collision_Shape::RECTANGLE`.
- `mass` (`float`): Body mass used for force and impulse calculations.

### Gravitational_Object

~~~cpp
Physics::Gravitational_Object::Gravitational_Object(Object *owner, Collision_Shape shape=Collision_Shape::RECTANGLE, float mass=1.0f)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a gravitational body attached to an Object.

**Parameters**

- `owner` (`Object *`): Borrowed Object pointer.
- `shape` (`Collision_Shape`): Collision shape used by the body. Default: `Collision_Shape::RECTANGLE`.
- `mass` (`float`): Body mass used for force and impulse calculations.

### gravity

~~~cpp
const Vec & Physics::Physics_Engine::gravity() const
~~~

**Access:** public  **Returns:** `const Vec &`  **Engine version:** Potato Engine 1.0.0

Constructs a Gravitational_Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### has_local_bounds

~~~cpp
bool Physics::Collision_Body::has_local_bounds() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### inverse_mass

~~~cpp
float Physics::Collision_Body::inverse_mass() const
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Performs the inverse mass operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### is_awake

~~~cpp
bool Physics::Collision_Body::is_awake() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### local_offset

~~~cpp
Vec Physics::Collision_Body::local_offset() const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Performs the local offset operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### local_size

~~~cpp
Vec Physics::Collision_Body::local_size() const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Performs the local size operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### local_transform

~~~cpp
const Transform & Physics::Collision_Body::local_transform() const
~~~

**Access:** public  **Returns:** `const Transform &`  **Engine version:** Potato Engine 1.0.0

Performs the local transform operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### make_mask_tag

~~~cpp
constexpr Mask_Tag Physics::make_mask_tag(std::uint8_t bit_index)
~~~

**Access:** public  **Returns:** `constexpr Mask_Tag`  **Engine version:** Potato Engine 1.0.0

Creates a single collision category bit.

**Parameters**

- `bit_index` (`std::uint8_t`): Bit index in the inclusive range [0, 63].

### masks_allow

~~~cpp
static bool Physics::Physics_Engine::masks_allow(const Collision_Body &a, const Collision_Body &b)
~~~

**Access:** private  **Storage:** static  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Creates or emits a new engine value using the supplied configuration. Determine ownership from the return type and the owning pool or service.

**Parameters**

- `a` (`const Collision_Body &`): Value supplied for the a parameter.
- `b` (`const Collision_Body &`): Value supplied for the b parameter.

### mass

~~~cpp
float Physics::Collision_Body::mass() const
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Performs the mass operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### operator bool

~~~cpp
Physics::Raycast_Hit::operator bool() const
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Implements the operator bool operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** None.

### operator=

~~~cpp
Collision_Body & Physics::Collision_Body::operator=(const Collision_Body &)=delete
~~~

**Access:** public  **Returns:** `Collision_Body &`  **Engine version:** Potato Engine 1.0.0

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const Collision_Body &`): Value supplied for the  parameter.

### owner

~~~cpp
Object * Physics::Collision_Body::owner() const
~~~

**Access:** public  **Returns:** `Object *`  **Engine version:** Potato Engine 1.0.0

Performs the owner operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### Physics_Engine

~~~cpp
Physics::Physics_Engine::Physics_Engine(Logger *logger=nullptr)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs an empty physics world.

**Parameters**

- `logger` (`Logger *`): Optional logger pointer. The world does not own it.

### previous_transform

~~~cpp
Transform Physics::Collision_Body::previous_transform() const
~~~

**Access:** public  **Returns:** `Transform`  **Engine version:** Potato Engine 1.0.0

Constructs a Physics_Engine value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### query_overlaps

~~~cpp
std::vector< Collision_Body * > Physics::Physics_Engine::query_overlaps(const Collision_Body &body, Mask_Tag mask=MASK_ALL) const
~~~

**Access:** public  **Returns:** `std::vector< Collision_Body * >`  **Engine version:** Potato Engine 1.0.0

Finds registered bodies overlapping the supplied body.

**Parameters**

- `body` (`const Collision_Body &`): Body used as the query shape. It need not be registered.
- `mask` (`Mask_Tag`): Collision categories included in the result. Default: `MASK_ALL`.

### raycast

~~~cpp
Raycast_Hit Physics::Physics_Engine::raycast(const Vec &origin, const Vec &direction, float max_distance, Mask_Tag mask=MASK_ALL, const Collision_Body *ignored_body=nullptr) const
~~~

**Access:** public  **Returns:** `Raycast_Hit`  **Engine version:** Potato Engine 1.0.0

Casts a ray through the physics world and returns the nearest hit.

**Parameters**

- `origin` (`const Vec &`): Ray start in world coordinates.
- `direction` (`const Vec &`): Ray direction; normalized internally.
- `max_distance` (`float`): Maximum ray length in logical world units.
- `mask` (`Mask_Tag`): Collision categories accepted by the query. Default: `MASK_ALL`.
- `ignored_body` (`const Collision_Body *`): Optional body that should never be returned.

### rebuild_static_grid

~~~cpp
void Physics::Physics_Engine::rebuild_static_grid()
~~~

**Access:** private  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs the query overlaps operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### remove_body

~~~cpp
void Physics::Physics_Engine::remove_body(Collision_Body *body)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Removes a body without destroying it.

**Parameters**

- `body` (`Collision_Body *`): Body pointer to remove.

### resolve

~~~cpp
void Physics::Physics_Engine::resolve(Collision &collision)
~~~

**Access:** private  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Applies positional correction, normal impulse and friction.

**Parameters**

- `collision` (`Collision &`): Value supplied for the collision parameter.

### set_alpha_threshold

~~~cpp
void Physics::Collision_Body::set_alpha_threshold(std::uint8_t threshold)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the minimum alpha value considered solid.

**Parameters**

- `threshold` (`std::uint8_t`): Alpha threshold in the inclusive range [0, 255].

### set_auto_sleep

~~~cpp
void Physics::Physics_Engine::set_auto_sleep(bool enabled)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

- `enabled` (`bool`): Value supplied for the enabled parameter.

### set_body_type

~~~cpp
void Physics::Collision_Body::set_body_type(Body_Type type)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Changes how the body participates in simulation.

**Parameters**

- `type` (`Body_Type`): New static, dynamic, or kinematic body type.

### set_collision_callback

~~~cpp
void Physics::Collision_Body::set_collision_callback(Collision_Callback callback)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the callback invoked for collision and trigger events.

**Parameters**

- `callback` (`Collision_Callback`): Function receiving collision information from this body's perspective.

### set_fixed_timestep

~~~cpp
void Physics::Physics_Engine::set_fixed_timestep(float seconds)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the fixed simulation step in seconds. Invalid values are ignored.

**Parameters**

- `seconds` (`float`): New fixed step duration in seconds.

### set_gravity

~~~cpp
void Physics::Physics_Engine::set_gravity(const Vec &gravity)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets world gravity in logical units per second squared.

**Parameters**

- `gravity` (`const Vec &`): New gravity vector.

### set_local_bounds

~~~cpp
void Physics::Collision_Body::set_local_bounds(Vec offset, Vec size)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `offset` (`Vec`): Value supplied for the offset parameter.
- `size` (`Vec`): Value supplied for the size parameter.

### set_local_transform

~~~cpp
void Physics::Collision_Body::set_local_transform(const Transform &transform)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `transform` (`const Transform &`): Value supplied for the transform parameter.

### set_mass

~~~cpp
void Physics::Collision_Body::set_mass(float mass)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets body mass. Values at or below zero are clamped to a safe minimum.

**Parameters**

- `mass` (`float`): New body mass.

### set_max_substeps

~~~cpp
void Physics::Physics_Engine::set_max_substeps(int count)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the maximum physics steps processed during one frame.

**Parameters**

- `count` (`int`): Maximum substep count, clamped to at least one.

### set_pixel_texture

~~~cpp
void Physics::Collision_Body::set_pixel_texture(Texture *texture)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Overrides the texture used for pixel-perfect collision.

**Parameters**

- `texture` (`Texture *`): Borrowed texture pointer. Passing nullptr uses the owner texture.

### set_shape

~~~cpp
void Physics::Collision_Body::set_shape(Collision_Shape shape)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Changes the collision shape used by future checks.

**Parameters**

- `shape` (`Collision_Shape`): New collision shape.

### set_sleep_settings

~~~cpp
void Physics::Physics_Engine::set_sleep_settings(float velocity_threshold, int stationary_steps)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `velocity_threshold` (`float`): Value supplied for the velocity_threshold parameter.
- `stationary_steps` (`int`): Value supplied for the stationary_steps parameter.

### set_spatial_cell_size

~~~cpp
void Physics::Physics_Engine::set_spatial_cell_size(float size)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the uniform-grid cell size used by broad-phase collision detection.

**Parameters**

- `size` (`float`): Cell width and height in world units. Non-positive values are ignored.

### shape

~~~cpp
Collision_Shape Physics::Collision_Body::shape() const
~~~

**Access:** public  **Returns:** `Collision_Shape`  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** None.

### sleep

~~~cpp
void Physics::Collision_Body::sleep()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### spatial_cell_size

~~~cpp
float Physics::Physics_Engine::spatial_cell_size() const
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Performs the spatial cell size operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### step

~~~cpp
void Physics::Physics_Engine::step(float delta_seconds)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs exactly one simulation step.

**Parameters**

- `delta_seconds` (`float`): Duration of this step in seconds.

### test_collision

~~~cpp
bool Physics::Physics_Engine::test_collision(Collision_Body &a, Collision_Body &b, Collision *result=nullptr) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Tests two bodies without advancing or resolving them.

**Parameters**

- `a` (`Collision_Body &`): First body.
- `b` (`Collision_Body &`): Second body.
- `result` (`Collision *`): Optional output collision information.

### texture

~~~cpp
Texture * Physics::Collision_Body::texture() const
~~~

**Access:** public  **Returns:** `Texture *`  **Engine version:** Potato Engine 1.0.0

Gets the texture used for pixel-perfect checks.

**Parameters:** None.

### transform

~~~cpp
const Transform & Physics::Collision_Body::transform() const
~~~

**Access:** public  **Returns:** `const Transform &`  **Engine version:** Potato Engine 1.0.0

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.

### transform

~~~cpp
Transform & Physics::Collision_Body::transform()
~~~

**Access:** public  **Returns:** `Transform &`  **Engine version:** Potato Engine 1.0.0

Performs the transform operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### update

~~~cpp
void Physics::Physics_Engine::update(float delta_seconds)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Advances the world using an accumulator and fixed timestep.

**Parameters**

- `delta_seconds` (`float`): Frame duration in seconds.

### wake

~~~cpp
void Physics::Collision_Body::wake()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Advances or processes the component for the current frame or time interval. Call it from the lifecycle phase expected by the owning service.

**Parameters:** None.

### Header usage example

~~~cpp
Physics::Collision_Body body;
body.set_mass(2.0f);
Engine::physics_engine->add_body(&body);
~~~

## tileset.h

### add

~~~cpp
void Tilemap_Registry::add(const std::string &name, Tilemap *tilemap)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.
- `tilemap` (`Tilemap *`): Value supplied for the tilemap parameter.

### add_index

~~~cpp
void Tileset_Group::add_index(int index)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Adds one tile id to the group.

**Parameters**

- `index` (`int`): Tile id to append.

### cell_index

~~~cpp
std::size_t Tilemap::cell_index(int column, int row) const
~~~

**Access:** private  **Returns:** ``std::size_t``  **Engine version:** Potato Engine 1.0.0

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

- `column` (`int`): Value supplied for the column parameter.
- `row` (`int`): Value supplied for the row parameter.

### cell_to_world

~~~cpp
Vec Tilemap::cell_to_world(int column, int row) const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Converts a cell's column and row indices to world coordinates.

**Parameters**

- `column` (`int`): Column index of the cell.
- `row` (`int`): Row index of the cell.

### clear

~~~cpp
void Tilemap::clear()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Transforms the supplied value into the requested representation. The source value is preserved unless a non-const reference appears in the signature.

**Parameters:** None.

### clear_indexes

~~~cpp
void Tileset_Group::clear_indexes()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Clears all tile ids from the group.

**Parameters:** None.

### create

~~~cpp
bool Tilemap::create(int width, int height, int empty_tile_id=-1, Vec origin={0.f, 0.f})
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Creates a new tilemap with the given dimensions and origin.

**Parameters**

- `width` (`int`): Number of columns in the tilemap.
- `height` (`int`): Number of rows in the tilemap.
- `empty_tile_id` (`int`): Tile id to use for empty cells. This is usually -1.
- `origin` (`Vec`): Top-left position of the tilemap in world coordinates.

### create_tile

~~~cpp
Tile Tileset::create_tile(int id, const Vec &position, bool collidable=false) const
~~~

**Access:** public  **Returns:** `Tile`  **Engine version:** Potato Engine 1.0.0

Creates a lightweight Tile using this tileset's texture.

**Parameters**

- `id` (`int`): Tile id/index inside the tileset.
- `position` (`const Vec &`): Top-left position for the tile.
- `collidable` (`bool`): Whether the tile should be considered collidable.

### draw

~~~cpp
void Tile::draw(SDL_Renderer *renderer, const Vec &size) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Draws the tile using its full texture.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `size` (`const Vec &`): Draw size in logical coordinates.

### draw

~~~cpp
void Tilemap::draw(SDL_Renderer *renderer, const class Camera *camera=nullptr) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

- `renderer` (`SDL_Renderer *`): Value supplied for the renderer parameter.
- `camera` (`const class Camera *`): Value supplied for the camera parameter.

### draw

~~~cpp
void Tileset::draw(SDL_Renderer *renderer, int index, const Vec &position, const Vec &size, bool skip_when_transparent=true) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Draws a tile id at a position using a custom draw size.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `index` (`int`): Tile id/index inside the tileset.
- `position` (`const Vec &`): Top-left draw position.
- `size` (`const Vec &`): Destination draw size.
- `skip_when_transparent` (`bool`): Value supplied for the skip_when_transparent parameter.

### draw

~~~cpp
void Tileset::draw(SDL_Renderer *renderer, int index, const Vec &position) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Draws a tile id at a position using the default tile size.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `index` (`int`): Tile id/index inside the tileset.
- `position` (`const Vec &`): Top-left draw position.

### draw_group

~~~cpp
void Tileset_Group::draw_group(SDL_Renderer *renderer, const Vec &position, int columns) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Draws the group wrapped into rows.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `position` (`const Vec &`): Top-left position of the first tile.
- `columns` (`int`): Number of columns before wrapping to the next row.

### draw_group

~~~cpp
void Tileset_Group::draw_group(SDL_Renderer *renderer, const Vec &position) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Draws the group in one horizontal row.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `position` (`const Vec &`): Top-left position of the first tile.

### draw_tile

~~~cpp
void Tileset::draw_tile(SDL_Renderer *renderer, const Tile &tile, const Vec &size) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Draws a Tile using the Tile id and position with a custom draw size.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `tile` (`const Tile &`): Tile data to draw.
- `size` (`const Vec &`): Destination draw size.

### draw_tile

~~~cpp
void Tileset::draw_tile(SDL_Renderer *renderer, const Tile &tile) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Draws a Tile using the Tile id and position.

**Parameters**

- `renderer` (`SDL_Renderer *`): SDL renderer used for drawing.
- `tile` (`const Tile &`): Tile data to draw.

### erase_tile

~~~cpp
bool Tilemap::erase_tile(int column, int row)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Erases a tile at the specified column and row, setting it to the empty tile id.

**Parameters**

- `column` (`int`): Column index of the tile to erase.
- `row` (`int`): Row index of the tile to erase.

### get

~~~cpp
Tilemap * Tilemap_Registry::get(const std::string &name)
~~~

**Access:** public  **Returns:** `Tilemap *`  **Engine version:** Potato Engine 1.0.0

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.

### get_cell_size

~~~cpp
Vec Tilemap::get_cell_size() const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_cell_texture

~~~cpp
Texture * Tilemap::get_cell_texture(int column, int row) const
~~~

**Access:** public  **Returns:** `Texture *`  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters**

- `column` (`int`): Value supplied for the column parameter.
- `row` (`int`): Value supplied for the row parameter.

### get_height

~~~cpp
int Tilemap::get_height() const
~~~

**Access:** public  **Returns:** ``int``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_id

~~~cpp
int Tile::get_id() const
~~~

**Access:** public  **Returns:** ``int``  **Engine version:** Potato Engine 1.0.0

Gets the numeric id of the tile.

**Parameters:** None.

### get_indexes

~~~cpp
std::vector< int > Tileset_Group::get_indexes() const
~~~

**Access:** public  **Returns:** ``std::vector< int >``  **Engine version:** Potato Engine 1.0.0

Gets all tile ids in the group.

**Parameters:** None.

### get_last_error

~~~cpp
const std::string & Tilemap::get_last_error() const
~~~

**Access:** public  **Returns:** ``const std::string &``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_origin

~~~cpp
Vec Tilemap::get_origin() const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_position

~~~cpp
Vec Tile::get_position() const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the top-left position of the tile.

**Parameters:** None.

### get_revision

~~~cpp
std::uint64_t Tilemap::get_revision() const
~~~

**Access:** public  **Returns:** ``std::uint64_t``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_source_path

~~~cpp
const std::string & Tilemap::get_source_path() const
~~~

**Access:** public  **Returns:** ``const std::string &``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_texture

~~~cpp
Texture * Tile::get_texture() const
~~~

**Access:** public  **Returns:** `Texture *`  **Engine version:** Potato Engine 1.0.0

Gets the texture assigned to the tile.

**Parameters:** None.

### get_texture

~~~cpp
Texture * Tileset::get_texture() const
~~~

**Access:** public  **Returns:** `Texture *`  **Engine version:** Potato Engine 1.0.0

Gets the texture atlas used by the tileset.

**Parameters:** None.

### get_tile

~~~cpp
int Tilemap::get_tile(int column, int row) const
~~~

**Access:** public  **Returns:** ``int``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters**

- `column` (`int`): Value supplied for the column parameter.
- `row` (`int`): Value supplied for the row parameter.

### get_tile_count

~~~cpp
std::size_t Tileset::get_tile_count() const
~~~

**Access:** public  **Returns:** ``std::size_t``  **Engine version:** Potato Engine 1.0.0

Gets the number of indexed tiles in the tileset.

**Parameters:** None.

### get_tile_rect

~~~cpp
const SDL_FRect * Tileset::get_tile_rect(int index) const
~~~

**Access:** public  **Returns:** ``const SDL_FRect *``  **Engine version:** Potato Engine 1.0.0

Gets the source rectangle for a tile id.

**Parameters**

- `index` (`int`): Tile id/index to query.

### get_tile_size

~~~cpp
Vec Tileset::get_tile_size() const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the size of a single tile.

**Parameters:** None.

### get_tile_texture

~~~cpp
Texture * Tileset::get_tile_texture(int index) const
~~~

**Access:** public  **Returns:** `Texture *`  **Engine version:** Potato Engine 1.0.0

Gets the texture used for a specific tile id.

**Parameters**

- `index` (`int`): Tile id/index inside the tileset.

### get_tileset

~~~cpp
const Tileset * Tilemap::get_tileset() const
~~~

**Access:** public  **Returns:** `const Tileset *`  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_tileset

~~~cpp
const Tileset * Tileset_Group::get_tileset() const
~~~

**Access:** public  **Returns:** `const Tileset *`  **Engine version:** Potato Engine 1.0.0

Gets the tileset used by the group.

**Parameters:** None.

### get_tileset

~~~cpp
Tileset * Tileset::get_tileset()
~~~

**Access:** public  **Returns:** `Tileset *`  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### get_tileset_size

~~~cpp
Vec Tileset::get_tileset_size() const
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the grid size of the tileset.

**Parameters:** None.

### get_width

~~~cpp
int Tilemap::get_width() const
~~~

**Access:** public  **Returns:** ``int``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

### init

~~~cpp
void Tileset::init(Texture *whole_texture, const Vec &tile_size, const Vec &tileset_size)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Initializes or reinitializes the tileset.

**Parameters**

- `whole_texture` (`Texture *`): Borrowed pointer to the full atlas texture.
- `tile_size` (`const Vec &`): Size of one tile in pixels/logical units.
- `tileset_size` (`const Vec &`): Number of tiles in the atlas as columns and rows.

### is_collidable

~~~cpp
bool Tile::is_collidable() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether this tile is collidable.

**Parameters:** None.

### is_valid_cell

~~~cpp
bool Tilemap::is_valid_cell(int column, int row) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks if the specified column and row are valid cell coordinates in the tilemap.

**Parameters**

- `column` (`int`): Column index to check.
- `row` (`int`): Row index to check.

### is_valid_index

~~~cpp
bool Tileset::is_valid_index(int index) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks if a tile id exists in the tileset.

**Parameters**

- `index` (`int`): Tile id/index to check.

### load_json

~~~cpp
bool Tilemap::load_json(const std::string &path)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Loads a tilemap from a JSON file.

**Parameters**

- `path` (`const std::string &`): File path to the JSON tilemap.

### load_tileset

~~~cpp
Tileset * Tileset::load_tileset(const std::string &path, Logger *logger=nullptr, SDL_ScaleMode scale_mode=SDL_SCALEMODE_PIXELART)
~~~

**Access:** public  **Returns:** `Tileset *`  **Engine version:** Potato Engine 1.0.0

Performs the init operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `path` (`const std::string &`): Value supplied for the path parameter.
- `logger` (`Logger *`): Value supplied for the logger parameter.
- `scale_mode` (`SDL_ScaleMode`): Value supplied for the scale_mode parameter.

### names

~~~cpp
std::vector< std::string > Tilemap_Registry::names()
~~~

**Access:** public  **Returns:** ``std::vector< std::string >``  **Engine version:** Potato Engine 1.0.0

Performs the names operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### rebuild_tile_rects

~~~cpp
void Tileset::rebuild_tile_rects()
~~~

**Access:** private  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Rebuilds the cached source rectangles from tile size and grid size.

**Parameters:** None.

### remove

~~~cpp
void Tilemap_Registry::remove(const std::string &name, Tilemap *tilemap=nullptr)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs the rebuild tile rects operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.
- `tilemap` (`Tilemap *`): Value supplied for the tilemap parameter.

### resize

~~~cpp
bool Tilemap::resize(int new_width, int new_height, int empty_tile_id=-1)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Resizes the tilemap to new dimensions, preserving existing tiles where possible.

**Parameters**

- `new_width` (`int`): New number of columns in the tilemap.
- `new_height` (`int`): New number of rows in the tilemap.
- `empty_tile_id` (`int`): Tile id to use for new empty cells. This is usually -1.

### save_json

~~~cpp
bool Tilemap::save_json(const std::string &path)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Saves the tilemap to a JSON file.

**Parameters**

- `path` (`const std::string &`): File path to save the tilemap.

### set_cell_size

~~~cpp
void Tilemap::set_cell_size(Vec cell_size)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs the resize operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `cell_size` (`Vec`): Value supplied for the cell_size parameter.

### set_cell_texture

~~~cpp
bool Tilemap::set_cell_texture(int column, int row, Texture *texture)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `column` (`int`): Value supplied for the column parameter.
- `row` (`int`): Value supplied for the row parameter.
- `texture` (`Texture *`): Value supplied for the texture parameter.

### set_collidable

~~~cpp
void Tile::set_collidable(bool collidable)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets whether this tile is collidable.

**Parameters**

- `collidable` (`bool`): New collision flag.

### set_id

~~~cpp
void Tile::set_id(int id)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the numeric id of the tile.

**Parameters**

- `id` (`int`): New tile id.

### set_indexes

~~~cpp
void Tileset_Group::set_indexes(const std::vector< int > &indexes)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets all tile ids in the group.

**Parameters**

- `indexes` (`const std::vector< int > &`): New tile id list.

### set_origin

~~~cpp
void Tilemap::set_origin(Vec origin)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `origin` (`Vec`): Value supplied for the origin parameter.

### set_position

~~~cpp
void Tile::set_position(const Vec &position)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the top-left position of the tile.

**Parameters**

- `position` (`const Vec &`): New tile position in logical coordinates.

### set_texture

~~~cpp
void Tile::set_texture(Texture *texture)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the texture assigned to the tile.

**Parameters**

- `texture` (`Texture *`): Borrowed pointer to the tile texture, or nullptr.

### set_texture

~~~cpp
void Tileset::set_texture(Texture *texture)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the texture atlas used by the tileset.

**Parameters**

- `texture` (`Texture *`): Borrowed pointer to the atlas texture, or nullptr.

### set_tile

~~~cpp
bool Tilemap::set_tile(int column, int row, int tile_id)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `column` (`int`): Value supplied for the column parameter.
- `row` (`int`): Value supplied for the row parameter.
- `tile_id` (`int`): Value supplied for the tile_id parameter.

### set_tile_size

~~~cpp
void Tileset::set_tile_size(const Vec &tile_size)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the size of a single tile and rebuilds the source rectangles.

**Parameters**

- `tile_size` (`const Vec &`): New tile size.

### set_tileset

~~~cpp
void Tilemap::set_tileset(const Tileset *tileset)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `tileset` (`const Tileset *`): Value supplied for the tileset parameter.

### set_tileset

~~~cpp
void Tileset_Group::set_tileset(const Tileset *tileset)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the tileset used by the group.

**Parameters**

- `tileset` (`const Tileset *`): Borrowed pointer to the tileset, or nullptr.

### set_tileset_size

~~~cpp
void Tileset::set_tileset_size(const Vec &tileset_size)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the grid size of the tileset and rebuilds the source rectangles.

**Parameters**

- `tileset_size` (`const Vec &`): New grid size as columns and rows.

### submit

~~~cpp
void Tilemap::submit(class Render_Pool &render_pool, uint8_t z_index=128, const class Camera *camera=nullptr, const Color &tint=Color::white(), bool camera_space=true, bool y_sort=true) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `render_pool` (`class Render_Pool &`): Value supplied for the render_pool parameter.
- `z_index` (`uint8_t`): Value supplied for the z_index parameter.
- `camera` (`const class Camera *`): Value supplied for the camera parameter.
- `tint` (`const Color &`): Value supplied for the tint parameter. Default: `Color::white()`.
- `camera_space` (`bool`): Value supplied for the camera_space parameter.
- `y_sort` (`bool`): Value supplied for the y_sort parameter.

### Tile

~~~cpp
Tile::Tile()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs an empty tile.

**Parameters:** None.

### Tile

~~~cpp
Tile::Tile(int id, const Vec &position, Texture *texture=nullptr, bool collidable=false)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a tile with an id, position, texture and collision flag.

**Parameters**

- `id` (`int`): Numeric tile id. For atlas tiles this is usually the tileset index.
- `position` (`const Vec &`): Top-left position of the tile in logical coordinates.
- `texture` (`Texture *`): Texture used by this tile. This is borrowed, not owned.
- `collidable` (`bool`): Whether this tile should block movement or collision checks.

### Tilemap

~~~cpp
Tilemap::Tilemap()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Tile value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### Tilemap

~~~cpp
Tilemap::Tilemap(const Tileset *tileset)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Tilemap value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `tileset` (`const Tileset *`): Value supplied for the tileset parameter.

### Tileset

~~~cpp
Tileset::Tileset()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs an empty tileset.

**Parameters:** None.

### Tileset

~~~cpp
Tileset::Tileset(Texture *whole_texture, const Vec &tile_size, const Vec &tileset_size)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a tileset from a texture atlas and grid information.

**Parameters**

- `whole_texture` (`Texture *`): Borrowed pointer to the full atlas texture.
- `tile_size` (`const Vec &`): Size of one tile in pixels/logical units.
- `tileset_size` (`const Vec &`): Number of tiles in the atlas as columns and rows.

### Tileset_Group

~~~cpp
Tileset_Group::Tileset_Group()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs an empty group.

**Parameters:** None.

### Tileset_Group

~~~cpp
Tileset_Group::Tileset_Group(const Tileset *tileset, const std::vector< int > &indexes)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a group for a tileset with explicit tile indexes.

**Parameters**

- `tileset` (`const Tileset *`): Borrowed pointer to the tileset used for drawing.
- `indexes` (`const std::vector< int > &`): Tile ids contained by this group.

### Tileset_Group

~~~cpp
Tileset_Group::Tileset_Group(const Tileset *tileset)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a group for a tileset with no explicit indexes.

**Parameters**

- `tileset` (`const Tileset *`): Borrowed pointer to the tileset used for drawing.

### valid_cell

~~~cpp
bool Tilemap::valid_cell(int column, int row) const
~~~

**Access:** private  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Constructs a Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `column` (`int`): Value supplied for the column parameter.
- `row` (`int`): Value supplied for the row parameter.

### world_to_cell

~~~cpp
bool Tilemap::world_to_cell(const Vec &world_position, int &out_column, int &out_row) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Converts world coordinates to cell indices in the tilemap.

**Parameters**

- `world_position` (`const Vec &`): World coordinates to convert.
- `out_column` (`int &`): Output parameter for the column index.
- `out_row` (`int &`): Output parameter for the row index.

### Header usage example

~~~cpp
Tilemap map;
map.load_json("assets/maps/level1.json");
map.set_tile({4, 3}, 7);
~~~









