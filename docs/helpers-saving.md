# Saving and general helpers

## Object snapshots

`Save_Game` serializes a generic FlatBuffers snapshot. The generated format has the file identifier `CCSV` and current schema version `2`.

A snapshot contains scene ID/name and object states. Each object state stores:

- name;
- position, size, and rotation;
- texture source path;
- visibility and input transparency;
- automatic-submission state;
- z-index and tint.

`Save_Game::capture_current()` captures objects in `Engine::save_pool` when that pool is non-empty; otherwise it captures every object in `Engine::object_pool`. `save_current`, `save_snapshot`, `load_snapshot`, `apply_snapshot`, and `load_and_apply` provide the complete binary workflow.

```cpp
Engine::save_pool->add(player);
Engine::save_pool->add(camera_target);

Save_Game::save_current("saves/games/slot_1.sav");
Save_Game::load_and_apply("saves/games/slot_1.sav");
```

`Save_Pool` is a non-owning selection registry with add/remove/contains/clear/get/capture operations. Remove pointers before their objects are destroyed.

### Restore behavior and limits

Applying a snapshot updates existing objects; it does not create them. Named states match `Object::name`. For old/unnamed layouts, positional fallback is used only when the current object count exactly matches the snapshot count. An object is applied at most once.

The current apply path restores world transform, visibility, input flags, auto-submit, z-index, and tint, then immediately calls `SceneManager::set_scene(snapshot.scene_id)`. Capturing a parented object stores its composed world transform; applying it converts that value into the target object's current parent space. Parent pointers and hierarchy structure are not serialized. Although texture paths and scene names are serialized, `apply_snapshot()` does not load/assign textures or resolve scenes by name. It also does not restore tags, scripts, physics, audio, custom entity state, tilemaps, or game rules. Extend or wrap the snapshot workflow for game-specific state.

`load_snapshot()` verifies FlatBuffer structure but does not currently reject an unfamiliar version. Consumers adding schema evolution should inspect `Snapshot::version` before applying.

## Vectors and transforms

`Vec` is a 2D float vector with component-wise arithmetic/comparison and scalar multiply/divide. Comparisons such as `<` require both components to satisfy the relation.

`Transform` groups `pos`, `size`, and `rotation`; its arithmetic changes position and size while preserving the left operand's rotation. `rotate_vector`, `compose_transform`, and `relative_transform` support object hierarchy conversion. Composition inherits position, angle, and flip flags but deliberately does not scale `size`. `Vec3` supports audio positioning and `Vec4` supports packed four-component data.

`utils.h` provides:

- distance, length, squared variants, normalization, dot/cross, and approximate equality;
- unsigned/signed angles in radians/degrees;
- vector interpolation, component/scalar clamping, reflection, rotation, inversion, absolute/floor/ceil/round, and perpendicular vectors;
- point-in-rectangle/circle tests and SDL rectangle conversions;
- logical mouse/window position helpers, cursor visibility, window maximize/fullscreen/windowed helpers;
- color interpolation;
- `Direction`, `Axis`, and `PI`.

The free helper names `abs`, `floor`, `ceil`, `round`, and `clamp` are in the global namespace; qualify standard-library alternatives where overload resolution could be ambiguous.

## Color

`Color` stores 8-bit RGBA, converts to/from `SDL_Color`, parses numeric or string hex (`RRGGBB` or `RRGGBBAA`), changes alpha, and supports saturating component arithmetic with scalar multiply/divide. Static constructors provide common named colors such as white, black, red, transparent, and light/dark variants.

## Random

`prandom` owns a process-wide `std::mt19937` seeded by `std::random_device`. It provides inclusive integral ranges, weighted ranges, uniform vector choices, weighted choices, and weighted index selection. Invalid ranges, empty choices, mismatched weights, negative/non-finite weights, or all-zero weights throw `std::runtime_error`.

The API currently exposes no deterministic seed setter. Tests or deterministic simulations that require reproducibility should use their own generator or explicitly seed `prandom::engine()`.

## Logging

`Logger` is a mutex-protected file and console logger with `DEBUG`, `INFO`, `WARNING`, `ERROR`, and `CRITICAL` levels. It supports minimum severity, elapsed-time formatting, optional frame indices, flood-debug suppression, whole-log retrieval, and timestamped finalization.

The application initializes `Engine::logger` at `game_config::log_path`, disables flood logging, and finalizes the file on shutdown. Direct users should call `init`, then `finalize_log` and `close`.

## Debug console

`game_console` can show, hide, toggle, and report a native debug console. The application forwards events so F1 or the grave key toggles it. On Windows it allocates/reconnects UTF-8 standard streams; on unsupported platforms `is_supported()` is false and operations are no-ops. Set `game_config::show_console` or use `--console` to open it at startup.

## Functionality triggers

`Potato::FunctionalityTrigger` combines independent Boolean sources under a lowercase `snake_case` ID. Sources registered for the same ID are OR-ed. The `owner` pointer is an identity token only and is never dereferenced.

```cpp
int input_owner;
functionality_trigger::trigger_context context;
context.actor_id = 42;
context.action_id = "use";
functionality_trigger::register_source(
    "activate_action",
    &input_owner,
    [](const functionality_trigger::trigger_context& context) {
        return context.action_id == "use" &&
               Input::action_pressed("use");
    }
);

const bool active = functionality_trigger::evaluate("activate_action", context);
```

`trigger_context` carries actor, subject, action, instance, and target data. Sources may ignore fields they do not need. `unregister_sources(owner)` removes all entries for one owner and `clear()` resets the registry. Ensure the captured data in every source outlives its registration.
