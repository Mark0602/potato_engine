# Physics

Potato Engine provides a lightweight 2D fixed-step physics and collision system in `namespace Physics`. It is designed for logical-pixel worlds and borrows game objects rather than owning them.

## Bodies and shapes

`Collision_Body` can attach to an `Object` and use its transform/texture, or own a standalone transform. Attached bodies obtain collision geometry from `Object::get_world_transform()`, so static, dynamic, and kinematic objects can participate while parented. Physics movement and penetration correction are applied in world space and converted back into the object's parent-local transform. It automatically registers with `Engine::physics_engine` when that service is available and unregisters on destruction.

For compatibility, `Collision_Body::transform()` still returns a mutable reference to the owner's local `transform` (or the standalone body's world transform). Use `collision_transform()` for the effective world-space geometry, and use `Object::set_world_transform()` when manually teleporting a parented owner.

Supported shapes are:

- `RECTANGLE`: axis-aligned bounds;
- `CIRCLE`: the smaller transform dimension is the diameter;
- `OVAL`: half the transform size supplies ellipse radii;
- `PIXEL_PERFECT`: source alpha-mask collision, with rectangle fallback when no mask is available.

Body types are `STATIC`, `DYNAMIC`, and `KINEMATIC`. Static bodies never move. Dynamic bodies receive forces, gravity, impulses, damping, and collision response. Kinematic bodies move by velocity but ignore forces and impulses.

`Gravitational_Object` is a convenience dynamic body with `gravity_scale=1`.

## Local colliders

An attached body normally uses its owner's full world transform. `set_local_transform()` or `set_local_bounds(offset, size)` defines a collider relative to that object without changing visual geometry. Collider offset and angle follow the owner's world rotation; collider size remains unscaled. `clear_local_bounds()` restores the full owner transform.

## Dynamics

Public body state includes velocity, gravity scale, restitution, friction, linear damping, enabled/trigger flags, category masks, broad-phase padding, and awake state. Use `set_mass`, `apply_force`, `apply_impulse`, `clear_forces`, `wake`, and `sleep` for simulation control.

For pixel collision, use `set_pixel_texture()` to override the owner's texture and `set_alpha_threshold()` to define solid pixels. Rotation is considered by oval and pixel point tests; rectangle response intentionally remains axis-aligned.

## Collision filtering

`Mask_Tag` is a 64-bit bitmask. `make_mask_tag(0..63)` creates one category bit. A pair is accepted only when each body's `collision_mask` accepts the other body's `mask_tag`.

```cpp
constexpr Physics::Mask_Tag PLAYER = Physics::make_mask_tag(0);
constexpr Physics::Mask_Tag WORLD  = Physics::make_mask_tag(1);

Physics::Gravitational_Object player_body(player_object);
player_body.mask_tag = PLAYER;
player_body.collision_mask = WORLD;

Physics::Collision_Body wall(
    wall_object,
    Physics::Collision_Shape::RECTANGLE,
    Physics::Body_Type::STATIC
);
wall.mask_tag = WORLD;
wall.collision_mask = PLAYER;
```

Use `MASK_NONE`, `MASK_DEFAULT`, and `MASK_ALL` for standard cases. A body may combine category bits with bitwise OR.

## Triggers and callbacks

Set `is_trigger=true` to report overlap without physical response. `set_collision_callback()` receives a `Collision` from that body's perspective, containing borrowed body pointers, approximate point, normal, and penetration. Callbacks can occur for physical collisions and triggers during a step; avoid destroying bodies from inside a callback unless you have audited iterator safety.

The world also exposes `collisions()` for results from the most recent simulation step.

## Simulation settings

`Physics_Engine::update(frame_seconds)` accumulates time and processes fixed steps. Defaults are 120 Hz, at most eight substeps per frame, downward gravity `{0, 980}`, and a 64-unit uniform-grid cell size.

Tune with:

- `set_gravity`;
- `set_fixed_timestep`;
- `set_max_substeps`;
- `set_spatial_cell_size`;
- `set_auto_sleep` and `set_sleep_settings`.

The uniform grid caches static geometry and reduces broad-phase pairs. Choose a cell size near the typical collider size. `active_collision_range` adds broad-phase padding for bodies that need nearby collision candidates. Automatic sleep keeps stationary non-static bodies collidable while stopping them as active simulation sources.

## Queries

`test_collision(a, b, result)` checks two shapes without stepping or resolving them. `query_overlaps(body, mask)` returns all registered overlapping bodies accepted by a category mask.

`raycast(origin, direction, max_distance, mask, ignored_body)` normalizes the direction and returns the nearest `Raycast_Hit`:

```cpp
const auto hit = Engine::physics_engine->raycast(
    origin, aim_direction, 500.0f, WORLD, &player_body
);
if (hit) {
    Object* object = hit.body->owner();
}
```

Query results and body owner pointers are borrowed. They remain valid only while the corresponding bodies/objects remain alive.

## Manual worlds

`Physics_Engine::add_body`, `remove_body`, `step`, and `clear` allow isolated or custom-loop worlds. Moving a body to a different world detaches it from the old one. Destroy the bodies before the world, or let the world destructor detach them.
