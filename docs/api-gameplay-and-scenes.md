# Gameplay and Scenes API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This file documents Potato Engine-owned callable names. Overloads share one entry. Constructors, destructors, operators, and declared helpers are included. Third-party APIs are excluded.

## animations.h

- **add(...)** — Performs the add operation defined by this header.
- **in_out_quad(...)** — Performs the in out quad operation defined by this header.
- **in_quad(...)** — Performs the in quad operation defined by this header.
- **is_running(...)** — Reports whether running.
- **linear(...)** — Performs the linear operation defined by this header.
- **make_fade_in(...)** — Creates fade in.
- **make_fade_out(...)** — Creates fade out.
- **make_slide_in(...)** — Creates slide in.
- **make_slide_out(...)** — Creates slide out.
- **out_back(...)** — Performs the out back operation defined by this header.
- **out_cubic(...)** — Performs the out cubic operation defined by this header.
- **out_elastic(...)** — Performs the out elastic operation defined by this header.
- **out_quad(...)** — Performs the out quad operation defined by this header.
- **progress(...)** — Performs the progress operation defined by this header.
- **start(...)** — Starts the operation or state.
- **tick(...)** — Advances time-dependent state.

### Example

~~~cpp
Animation<float> fade(0.0f, 1.0f, 0.25f, Ease::out_quad);
fade.start();
fade.tick(delta_seconds);
~~~

## object.h

- **~Object(...)** — Releases resources owned by the instance.
- **add(...)** — Performs the add operation defined by this header.
- **add_tag(...)** — Adds tag.
- **attach_script(...)** — Performs the attach script operation defined by this header.
- **Button(...)** — Constructs a Button instance.
- **center_on_screen(...)** — Performs the center on screen operation defined by this header.
- **configure_as_ui(...)** — Performs the configure as ui operation defined by this header.
- **detach_script(...)** — Performs the detach script operation defined by this header.
- **draw(...)** — Draws or submits visual output.
- **fill_transform(...)** — Performs the fill transform operation defined by this header.
- **find_by_name(...)** — Finds by name.
- **find_by_tag(...)** — Finds by tag.
- **free(...)** — Performs the free operation defined by this header.
- **get_font(...)** — Returns font.
- **get_object_pool(...)** — Returns object pool.
- **get_transform(...)** — Returns transform.
- **has_tag(...)** — Reports whether tag.
- **hide(...)** — Performs the hide operation defined by this header.
- **is_interactive(...)** — Reports whether interactive.
- **make_draw_command(...)** — Creates draw command.
- **normalized_value(...)** — Performs the normalized value operation defined by this header.
- **Object(...)** — Constructs a Object instance.
- **Object_Pool(...)** — Constructs a Object_Pool instance.
- **on_click(...)** — Performs the on click operation defined by this header.
- **on_hover(...)** — Performs the on hover operation defined by this header.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **position_update(...)** — Performs the position update operation defined by this header.
- **Progress_Bar(...)** — Constructs a Progress_Bar instance.
- **register_with_pool(...)** — Registers with pool.
- **remove(...)** — Performs the remove operation defined by this header.
- **remove_tag(...)** — Removes tag.
- **rotation_update(...)** — Performs the rotation update operation defined by this header.
- **scale_centered(...)** — Performs the scale centered operation defined by this header.
- **scale_centered_condition(...)** — Performs the scale centered condition operation defined by this header.
- **set_checked(...)** — Sets checked.
- **set_enabled(...)** — Sets enabled.
- **set_font(...)** — Sets font.
- **set_input_transparent(...)** — Sets input transparent.
- **set_logger(...)** — Sets logger.
- **set_object_pool(...)** — Sets object pool.
- **set_range(...)** — Sets range.
- **set_step(...)** — Sets step.
- **set_texture(...)** — Sets texture.
- **set_texture_opacity(...)** — Sets texture opacity.
- **set_transform(...)** — Sets transform.
- **set_value(...)** — Sets value.
- **show(...)** — Performs the show operation defined by this header.
- **size_update(...)** — Performs the size update operation defined by this header.
- **Slider(...)** — Constructs a Slider instance.
- **submit_draw_commands(...)** — Performs the submit draw commands operation defined by this header.
- **thumb_center(...)** — Performs the thumb center operation defined by this header.
- **thumb_transform(...)** — Performs the thumb transform operation defined by this header.
- **Toggle(...)** — Constructs a Toggle instance.
- **toggle_at(...)** — Performs the toggle at operation defined by this header.
- **toggle_visibility(...)** — Performs the toggle visibility operation defined by this header.
- **UI_Object(...)** — Constructs a UI_Object instance.
- **UI_Value(...)** — Constructs a UI_Value instance.
- **update_from_pointer(...)** — Advances state for the current frame.
- **value_at(...)** — Performs the value at operation defined by this header.

### Example

~~~cpp
Object* player = new Object("player");
player->add_tag("controllable");
Engine::object_pool->add(player);
~~~

## entity.h

- **~Entity(...)** — Releases resources owned by the instance.
- **activate(...)** — Performs the activate operation defined by this header.
- **deactivate(...)** — Performs the deactivate operation defined by this header.
- **Entity(...)** — Constructs a Entity instance.
- **free(...)** — Performs the free operation defined by this header.
- **get_pos(...)** — Returns pos.
- **get_texture(...)** — Returns texture.
- **is_alive(...)** — Reports whether alive.
- **Object(...)** — Constructs a Object instance.
- **set_pos(...)** — Sets pos.
- **set_texture(...)** — Sets texture.

### Example

~~~cpp
Entity enemy;
enemy.set_pos({240.0f, 120.0f});
enemy.activate();
~~~

## particle.h

- **~Particle_Emitter(...)** — Releases resources owned by the instance.
- **draw(...)** — Draws or submits visual output.
- **free(...)** — Performs the free operation defined by this header.
- **is_alive(...)** — Reports whether alive.
- **Particle(...)** — Constructs a Particle instance.
- **Particle_Emitter(...)** — Constructs a Particle_Emitter instance.
- **spawn_particle(...)** — Performs the spawn particle operation defined by this header.
- **update(...)** — Advances state for the current frame.

### Example

~~~cpp
Particle_Emitter emitter;
emitter.spawn_particle();
emitter.update(delta_seconds);
~~~

## label.h

- **~TextBox(...)** — Releases resources owned by the instance.
- **blur(...)** — Performs the blur operation defined by this header.
- **clear(...)** — Clears the owned state or collection.
- **clear_shadow(...)** — Clears the owned state or collection.
- **draw(...)** — Draws or submits visual output.
- **erase_next_character(...)** — Performs the erase next character operation defined by this header.
- **erase_previous_character(...)** — Performs the erase previous character operation defined by this header.
- **finish(...)** — Performs the finish operation defined by this header.
- **focus(...)** — Performs the focus operation defined by this header.
- **get_color(...)** — Returns color.
- **get_cursor_position(...)** — Returns cursor position.
- **get_font(...)** — Returns font.
- **get_max_length(...)** — Returns max length.
- **get_scale(...)** — Returns scale.
- **handle_event(...)** — Handles event.
- **insert_text(...)** — Performs the insert text operation defined by this header.
- **is_focused(...)** — Reports whether focused.
- **Label(...)** — Constructs a Label instance.
- **make_draw_command(...)** — Creates draw command.
- **next_utf8_boundary(...)** — Performs the next utf8 boundary operation defined by this header.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **previous_utf8_boundary(...)** — Performs the previous utf8 boundary operation defined by this header.
- **refresh_display_text(...)** — Performs the refresh display text operation defined by this header.
- **resize_to_text(...)** — Performs the resize to text operation defined by this header.
- **set_color(...)** — Sets color.
- **set_font(...)** — Sets font.
- **set_font_from_asset_pool(...)** — Sets font from asset pool.
- **set_max_length(...)** — Sets max length.
- **set_prefix(...)** — Sets prefix.
- **set_scale(...)** — Sets scale.
- **set_shadow(...)** — Sets shadow.
- **set_text(...)** — Sets text.
- **set_value(...)** — Sets value.
- **single_line_text(...)** — Performs the single line text operation defined by this header.
- **submit_draw_commands(...)** — Performs the submit draw commands operation defined by this header.
- **TextBox(...)** — Constructs a TextBox instance.

### Example

~~~cpp
Label score;
score.set_text("Score: 100");
score.set_color(Color::white());
~~~

## scene.h

- **action(...)** — Performs the action operation defined by this header.
- **cancel_scene_request(...)** — Performs the cancel scene request operation defined by this header.
- **complete_transition(...)** — Performs the complete transition operation defined by this header.
- **consume_scene_request(...)** — Performs the consume scene request operation defined by this header.
- **current_scene(...)** — Performs the current scene operation defined by this header.
- **enqueue_load_step(...)** — Performs the enqueue load step operation defined by this header.
- **enqueue_load_task(...)** — Performs the enqueue load task operation defined by this header.
- **has_scene_request(...)** — Reports whether scene request.
- **instance(...)** — Performs the instance operation defined by this header.
- **register_scene(...)** — Registers scene.
- **request_scene(...)** — Requests scene.
- **requested_scene(...)** — Performs the requested scene operation defined by this header.
- **scene_name(...)** — Performs the scene name operation defined by this header.
- **SceneManager(...)** — Constructs a SceneManager instance.
- **set_scene(...)** — Sets scene.
- **take_load_tasks(...)** — Performs the take load tasks operation defined by this header.

### Example

~~~cpp
SceneManager::instance().register_scene(1, "menu");
SceneManager::instance().request_scene(1);
~~~

## script-base.h

- **~script(...)** — Releases resources owned by the instance.
- **execution_order(...)** — Performs the execution order operation defined by this header.
- **on_destroy(...)** — Performs the on destroy operation defined by this header.
- **on_event(...)** — Performs the on event operation defined by this header.
- **on_post_render(...)** — Performs the on post render operation defined by this header.
- **on_render(...)** — Performs the on render operation defined by this header.
- **on_start(...)** — Performs the on start operation defined by this header.
- **on_update(...)** — Performs the on update operation defined by this header.
- **scene_id(...)** — Performs the scene id operation defined by this header.

### Example

~~~cpp
class PlayerScript : public script {
public:
    void on_update() override { /* gameplay */ }
};
~~~

## script-registry.h

- **execution_order(...)** — Performs the execution order operation defined by this header.
- **instance(...)** — Performs the instance operation defined by this header.
- **register_script(...)** — Registers script.
- **scene_id(...)** — Performs the scene id operation defined by this header.
- **script_registry(...)** — Performs the script registry operation defined by this header.

### Example

~~~cpp
REGISTER_SCRIPT(PlayerScript, 1, 0);
~~~


