# Objects, UI, text, and scripts

## Object

`Object` is the base renderable value. It contains a name, string tags, borrowed texture, optional atlas source rectangle, transform, tint, visibility, input behavior, draw ordering, camera-space selection, Y sorting, optional pool registration, and one attached script.

Constructing with an `Object_Pool*` registers the object. The pool is a borrowed registry used for lookup and automatic submission; it does not delete objects. Object destruction removes the pointer from its pool.

Common operations include:

- `add_tag`, `remove_tag`, and `has_tag`;
- transform setters and position/size/rotation updates;
- `on_hover` and `on_click` bounding-box hit tests;
- `hide`, `show`, `toggle_visibility`, and input transparency;
- centered scaling helpers and texture opacity;
- `make_draw_command` and `submit_draw_commands` extension points;
- `attach_script` and `detach_script`.

`free()` releases object state and is protected against repeated calls. A texture pointer is generally borrowed from the asset pool; do not delete it through the object. `Object_Pool::find_by_name`, `find_by_tag`, `find_all_by_tag`, and `get_all` return borrowed pointers.

## Script lifecycle

Derive from `script` and override only the callbacks you need:

| Callback | Timing |
| --- | --- |
| `on_start()` | Once when the script first becomes part of an active startup/scene load, or immediately for an attached script |
| `on_event(event)` | For every SDL event while active and not loading |
| `on_update(dt)` | Once per active gameplay frame, with seconds |
| `on_render()` | Before automatic object submission and render-pool flush |
| `on_post_render()` | After world drawing and lighting; intended for overlays |
| `on_destroy()` | Before the engine or owning object deletes the script |

`SCRIPT_ORDER(n)` controls stable execution order; lower values run first. `SCRIPT_SCENE(id)` limits a script to a scene, while `-1` makes it global. `REGISTER_SCRIPT(Type)` registers a factory during static initialization.

```cpp
#include "engine.h"
#include "src/object.h"
#include "src/script-registry.h"

class pulse_script final : public script {
    SCRIPT_ORDER(10)
    SCRIPT_SCENE(1)

public:
    void on_update(float dt) override {
        if (owner) owner->transform.rotation.x += 45.0f * dt;
    }
};

REGISTER_SCRIPT(pulse_script)
```

Globally registered scripts are owned by `Application`. `Object::attach_script(new pulse_script())` transfers ownership to the object, sets `script::owner`, registers the script for frame callbacks, and calls `on_start()` immediately. `detach_script()` calls `on_destroy()`, unregisters, and deletes it. Use a distinct script instance per object.

## UI objects and widgets

`UI_Object` configures fixed screen space (`camera_space=false`) and the top UI layer (`z_index=0`). It adds an `enabled` state: disabled controls can remain visible but are not interactive. It can also hold a borrowed font pointer.

The built-in widgets are intentionally logic and geometry primitives rather than a layout framework:

- `Button` provides enabled-aware hover/click hit testing;
- `UI_Value` owns a clamped range, optional step snapping, current value, and normalized value;
- `Slider` maps a pointer position to a horizontal or bottom-to-top vertical value and computes thumb geometry;
- `Toggle` stores `checked` and toggles only when a pointer hits it;
- `Progress_Bar` computes a fill transform from its normalized value and orientation.

The inherited texture represents the base/track. Draw a separate thumb, checked marker, or fill object using the returned geometry.

```cpp
Slider volume({40.0f, 40.0f}, {200.0f, 16.0f},
              0.0f, 1.0f, 0.8f,
              UI_Orientation::Horizontal,
              track_texture, Engine::object_pool);

if (Input::mouse_button_down(SDL_BUTTON_LEFT)) {
    volume.update_from_pointer(Input::mouse_position());
}
Transform thumb = volume.thumb_transform({12.0f, 24.0f});
```

## Labels and fonts

`Label` derives from `Object`, but submits a font draw command rather than a texture command. It supports text, borrowed `IFont`, color/tint, scale, size-to-text, and an optional offset shadow. A font may be assigned directly or resolved by name through `Engine::asset_pool`.

Labels participate in the same z-index, camera-space, visibility, and automatic-submission rules as objects. Set `camera_space=false` for UI labels.

## TextBox

`TextBox` is a single-line UTF-8 text editor rendered as a label. It supports focus/blur, value, prefix, byte limit, cursor movement, backspace/delete, submission with Enter, and cancellation with Escape.

The engine does not route events to a text box automatically. Forward raw events from an active script:

```cpp
void on_event(const SDL_Event& event) override {
    const TextBox_Result result = text_box.handle_event(event);
    if (result == TextBox_Result::SUBMITTED) {
        consume(text_box.get_value());
    }
}
```

While focused, the text box acquires Input's global block. Gameplay-facing key, mouse-button, controller, action, axis, delta, and wheel queries return neutral values until focus ends. The terminating key is swallowed through key release to prevent it from leaking into gameplay.

## Entity sample

`Entity` is a small example subclass of `Object` with `health`, `lifetime`, `active`, activation helpers, and texture access. It is not a required gameplay model. Games should define their own entity/component types rather than treating this sample as engine policy.

