# Input, Audio, and Localization API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This file documents Potato Engine-owned callable names. Overloads share one entry. Constructors, destructors, operators, and declared helpers are included. Third-party APIs are excluded.

## input.h

- **acquire_block(...)** — Performs the acquire block operation defined by this header.
- **action_down(...)** — Performs the action down operation defined by this header.
- **action_pressed(...)** — Performs the action pressed operation defined by this header.
- **action_released(...)** — Performs the action released operation defined by this header.
- **axis(...)** — Performs the axis operation defined by this header.
- **axis_delta(...)** — Performs the axis delta operation defined by this header.
- **begin_frame(...)** — Performs the begin frame operation defined by this header.
- **bind_axis_gamepad_axis(...)** — Binds axis gamepad axis.
- **bind_axis_key(...)** — Binds axis key.
- **bind_gamepad_button(...)** — Binds gamepad button.
- **bind_key(...)** — Binds key.
- **bind_mouse_button(...)** — Binds mouse button.
- **clear_mouse_viewport(...)** — Clears the owned state or collection.
- **controller_at(...)** — Performs the controller at operation defined by this header.
- **controller_axis(...)** — Performs the controller axis operation defined by this header.
- **controller_button_down(...)** — Performs the controller button down operation defined by this header.
- **controller_button_pressed(...)** — Performs the controller button pressed operation defined by this header.
- **controller_button_released(...)** — Performs the controller button released operation defined by this header.
- **handle_event(...)** — Handles event.
- **init(...)** — Initializes the service or resource.
- **is_blocked(...)** — Reports whether blocked.
- **key_down(...)** — Performs the key down operation defined by this header.
- **key_pressed(...)** — Performs the key pressed operation defined by this header.
- **key_released(...)** — Performs the key released operation defined by this header.
- **mouse_button_down(...)** — Performs the mouse button down operation defined by this header.
- **mouse_button_pressed(...)** — Performs the mouse button pressed operation defined by this header.
- **mouse_button_released(...)** — Performs the mouse button released operation defined by this header.
- **mouse_delta(...)** — Performs the mouse delta operation defined by this header.
- **mouse_position(...)** — Performs the mouse position operation defined by this header.
- **mouse_scroll_delta(...)** — Performs the mouse scroll delta operation defined by this header.
- **quit_requested(...)** — Performs the quit requested operation defined by this header.
- **release_block(...)** — Performs the release block operation defined by this header.
- **set_mouse_viewport(...)** — Sets mouse viewport.
- **shutdown(...)** — Releases initialized engine resources.
- **update(...)** — Advances state for the current frame.
- **valid_gamepad_axis(...)** — Performs the valid gamepad axis operation defined by this header.
- **valid_gamepad_button(...)** — Performs the valid gamepad button operation defined by this header.
- **valid_mouse_button(...)** — Performs the valid mouse button operation defined by this header.
- **valid_scancode(...)** — Performs the valid scancode operation defined by this header.

### Example

~~~cpp
Input::bind_key("jump", SDL_SCANCODE_SPACE);
if (Input::action_pressed("jump")) player_jump();
~~~

## audio.h

- **~Audio(...)** — Releases resources owned by the instance.
- **~ITrack(...)** — Releases resources owned by the instance.
- **~Track_Pool(...)** — Releases resources owned by the instance.
- **Audio(...)** — Constructs a Audio instance.
- **create_new_default_track(...)** — Creates new default track.
- **create_new_dynamic_track(...)** — Creates new dynamic track.
- **detach_track(...)** — Performs the detach track operation defined by this header.
- **flush_tracks(...)** — Performs the flush tracks operation defined by this header.
- **force_pause(...)** — Performs the force pause operation defined by this header.
- **force_play(...)** — Performs the force play operation defined by this header.
- **force_resume(...)** — Performs the force resume operation defined by this header.
- **force_stop(...)** — Performs the force stop operation defined by this header.
- **get_default_track_count(...)** — Returns default track count.
- **get_duration(...)** — Returns duration.
- **get_dynamic_track_lifetime(...)** — Returns dynamic track lifetime.
- **get_free_track(...)** — Returns free track.
- **get_mixer(...)** — Returns mixer.
- **get_props(...)** — Returns props.
- **get_total_track_count(...)** — Returns total track count.
- **get_track(...)** — Returns track.
- **init(...)** — Initializes the service or resource.
- **is_loaded(...)** — Reports whether loaded.
- **is_playing(...)** — Reports whether playing.
- **ITrack(...)** — Constructs a ITrack instance.
- **load(...)** — Performs the load operation defined by this header.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **pause(...)** — Pauses playback.
- **play(...)** — Starts playback.
- **play_fnf(...)** — Starts playback.
- **release_track(...)** — Performs the release track operation defined by this header.
- **resolve_engine_defaults(...)** — Performs the resolve engine defaults operation defined by this header.
- **resume(...)** — Resumes a paused operation.
- **set_default_track_count(...)** — Sets default track count.
- **set_dynamic_track_lifetime(...)** — Sets dynamic track lifetime.
- **set_fps(...)** — Sets fps.
- **set_gain(...)** — Sets gain.
- **set_logger(...)** — Sets logger.
- **set_loop_count(...)** — Sets loop count.
- **set_master_gain(...)** — Sets master gain.
- **set_mixer(...)** — Sets mixer.
- **set_panning(...)** — Sets panning.
- **set_pitch(...)** — Sets pitch.
- **set_position(...)** — Sets position.
- **set_props(...)** — Sets props.
- **set_track_pool(...)** — Sets track pool.
- **shutdown(...)** — Releases initialized engine resources.
- **stop(...)** — Stops the operation or state.
- **Track_Pool(...)** — Constructs a Track_Pool instance.
- **unload(...)** — Performs the unload operation defined by this header.
- **update_track(...)** — Advances state for the current frame.

### Example

~~~cpp
Audio music;
music.load("assets/audio/theme.ogg");
music.set_loop_count(-1);
music.play();
~~~

## localization.h

- **~Localization(...)** — Releases resources owned by the instance.
- **clear(...)** — Clears the owned state or collection.
- **format(...)** — Formats a value for presentation.
- **get(...)** — Performs the get operation defined by this header.
- **has_key(...)** — Reports whether key.
- **has_tag(...)** — Reports whether tag.
- **load(...)** — Performs the load operation defined by this header.
- **Localization(...)** — Constructs a Localization instance.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **set_current_tag(...)** — Sets current tag.
- **set_fallback_tag(...)** — Sets fallback tag.
- **set_logger(...)** — Sets logger.

### Example

~~~cpp
Localization strings;
strings.load("en-US", "assets/locales/en-US.json");
std::string title = strings.get("menu.title");
~~~


