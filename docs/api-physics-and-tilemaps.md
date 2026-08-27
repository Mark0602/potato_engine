# Physics and Tilemaps API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This file documents Potato Engine-owned callable names. Overloads share one entry. Constructors, destructors, operators, and declared helpers are included. Third-party APIs are excluded.

## physics.h

- **~Collision_Body(...)** — Releases resources owned by the instance.
- **~Physics_Engine(...)** — Releases resources owned by the instance.
- **add_body(...)** — Adds body.
- **alpha_threshold(...)** — Performs the alpha threshold operation defined by this header.
- **apply_force(...)** — Applies force.
- **apply_impulse(...)** — Applies impulse.
- **auto_sleep(...)** — Performs the auto sleep operation defined by this header.
- **body_type(...)** — Performs the body type operation defined by this header.
- **bool(...)** — Converts the value to Boolean state.
- **clear(...)** — Clears the owned state or collection.
- **clear_forces(...)** — Clears the owned state or collection.
- **clear_local_bounds(...)** — Clears the owned state or collection.
- **Collision_Body(...)** — Constructs a Collision_Body instance.
- **collision_transform(...)** — Performs the collision transform operation defined by this header.
- **fixed_timestep(...)** — Performs the fixed timestep operation defined by this header.
- **Gravitational_Object(...)** — Constructs a Gravitational_Object instance.
- **has_local_bounds(...)** — Reports whether local bounds.
- **inverse_mass(...)** — Performs the inverse mass operation defined by this header.
- **is_awake(...)** — Reports whether awake.
- **local_offset(...)** — Performs the local offset operation defined by this header.
- **local_size(...)** — Performs the local size operation defined by this header.
- **make_mask_tag(...)** — Creates mask tag.
- **masks_allow(...)** — Performs the masks allow operation defined by this header.
- **mass(...)** — Performs the mass operation defined by this header.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **owner(...)** — Performs the owner operation defined by this header.
- **Physics_Engine(...)** — Constructs a Physics_Engine instance.
- **previous_transform(...)** — Performs the previous transform operation defined by this header.
- **raycast(...)** — Performs the raycast operation defined by this header.
- **rebuild_static_grid(...)** — Performs the rebuild static grid operation defined by this header.
- **remove_body(...)** — Removes body.
- **resolve(...)** — Performs the resolve operation defined by this header.
- **set_alpha_threshold(...)** — Sets alpha threshold.
- **set_auto_sleep(...)** — Sets auto sleep.
- **set_body_type(...)** — Sets body type.
- **set_collision_callback(...)** — Sets collision callback.
- **set_fixed_timestep(...)** — Sets fixed timestep.
- **set_gravity(...)** — Sets gravity.
- **set_local_bounds(...)** — Sets local bounds.
- **set_local_transform(...)** — Sets local transform.
- **set_mass(...)** — Sets mass.
- **set_max_substeps(...)** — Sets max substeps.
- **set_pixel_texture(...)** — Sets pixel texture.
- **set_shape(...)** — Sets shape.
- **set_sleep_settings(...)** — Sets sleep settings.
- **set_spatial_cell_size(...)** — Sets spatial cell size.
- **shape(...)** — Performs the shape operation defined by this header.
- **sleep(...)** — Performs the sleep operation defined by this header.
- **spatial_cell_size(...)** — Performs the spatial cell size operation defined by this header.
- **step(...)** — Performs the step operation defined by this header.
- **test_collision(...)** — Performs the test collision operation defined by this header.
- **texture(...)** — Performs the texture operation defined by this header.
- **transform(...)** — Performs the transform operation defined by this header.
- **update(...)** — Advances state for the current frame.
- **wake(...)** — Performs the wake operation defined by this header.

### Example

~~~cpp
Physics::Collision_Body body;
body.set_mass(2.0f);
Engine::physics_engine->add_body(&body);
~~~

## tileset.h

- **add(...)** — Performs the add operation defined by this header.
- **add_index(...)** — Adds index.
- **cell_index(...)** — Performs the cell index operation defined by this header.
- **cell_to_world(...)** — Performs the cell to world operation defined by this header.
- **clear(...)** — Clears the owned state or collection.
- **clear_indexes(...)** — Clears the owned state or collection.
- **create_tile(...)** — Creates tile.
- **draw(...)** — Draws or submits visual output.
- **draw_group(...)** — Draws or submits visual output.
- **draw_tile(...)** — Draws or submits visual output.
- **erase_tile(...)** — Performs the erase tile operation defined by this header.
- **get(...)** — Performs the get operation defined by this header.
- **get_cell_size(...)** — Returns cell size.
- **get_cell_texture(...)** — Returns cell texture.
- **get_height(...)** — Returns height.
- **get_id(...)** — Returns id.
- **get_indexes(...)** — Returns indexes.
- **get_origin(...)** — Returns origin.
- **get_position(...)** — Returns position.
- **get_revision(...)** — Returns revision.
- **get_texture(...)** — Returns texture.
- **get_tile(...)** — Returns tile.
- **get_tile_count(...)** — Returns tile count.
- **get_tile_size(...)** — Returns tile size.
- **get_tile_texture(...)** — Returns tile texture.
- **get_tileset(...)** — Returns tileset.
- **get_tileset_size(...)** — Returns tileset size.
- **get_width(...)** — Returns width.
- **init(...)** — Initializes the service or resource.
- **is_collidable(...)** — Reports whether collidable.
- **is_valid_cell(...)** — Reports whether valid cell.
- **is_valid_index(...)** — Reports whether valid index.
- **load_json(...)** — Loads json.
- **load_tileset(...)** — Loads tileset.
- **names(...)** — Performs the names operation defined by this header.
- **rebuild_tile_rects(...)** — Performs the rebuild tile rects operation defined by this header.
- **remove(...)** — Performs the remove operation defined by this header.
- **resize(...)** — Performs the resize operation defined by this header.
- **save_json(...)** — Saves json.
- **set_cell_size(...)** — Sets cell size.
- **set_cell_texture(...)** — Sets cell texture.
- **set_collidable(...)** — Sets collidable.
- **set_id(...)** — Sets id.
- **set_indexes(...)** — Sets indexes.
- **set_origin(...)** — Sets origin.
- **set_position(...)** — Sets position.
- **set_texture(...)** — Sets texture.
- **set_tile(...)** — Sets tile.
- **set_tile_size(...)** — Sets tile size.
- **set_tileset(...)** — Sets tileset.
- **set_tileset_size(...)** — Sets tileset size.
- **submit(...)** — Performs the submit operation defined by this header.
- **Tile(...)** — Constructs a Tile instance.
- **Tilemap(...)** — Constructs a Tilemap instance.
- **Tileset(...)** — Constructs a Tileset instance.
- **Tileset_Group(...)** — Constructs a Tileset_Group instance.
- **valid_cell(...)** — Performs the valid cell operation defined by this header.
- **world_to_cell(...)** — Performs the world to cell operation defined by this header.

### Example

~~~cpp
Tilemap map;
map.load_json("assets/maps/level1.json");
map.set_tile({4, 3}, 7);
~~~


