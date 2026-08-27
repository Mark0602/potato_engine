# Graphics and Assets API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This file documents Potato Engine-owned callable names. Overloads share one entry. Constructors, destructors, operators, and declared helpers are included. Third-party APIs are excluded.

## render.h

- **~GPU_Renderer(...)** — Releases resources owned by the instance.
- **~Render_Pool(...)** — Releases resources owned by the instance.
- **begin_frame(...)** — Performs the begin frame operation defined by this header.
- **clear(...)** — Clears the owned state or collection.
- **device(...)** — Performs the device operation defined by this header.
- **Draw(...)** — Constructs a Draw instance.
- **empty(...)** — Performs the empty operation defined by this header.
- **end_frame(...)** — Performs the end frame operation defined by this header.
- **flush(...)** — Performs the flush operation defined by this header.
- **GPU_Renderer(...)** — Constructs a GPU_Renderer instance.
- **init(...)** — Initializes the service or resource.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **Render_Pool(...)** — Constructs a Render_Pool instance.
- **renderer(...)** — Performs the renderer operation defined by this header.
- **shutdown(...)** — Releases initialized engine resources.
- **size(...)** — Performs the size operation defined by this header.
- **submit(...)** — Performs the submit operation defined by this header.

### Example

~~~cpp
Draw command;
command.transform = {{100.0f, 80.0f}, {32.0f, 32.0f}};
Engine::render_pool->submit(command);
~~~

## texture.h

- **~Texture(...)** — Releases resources owned by the instance.
- **draw(...)** — Draws or submits visual output.
- **draw_ex(...)** — Draws or submits visual output.
- **free(...)** — Performs the free operation defined by this header.
- **get_gpu_texture(...)** — Returns gpu texture.
- **get_height(...)** — Returns height.
- **get_path(...)** — Returns path.
- **get_scale_mode(...)** — Returns scale mode.
- **get_SDL_Texture(...)** — Returns SDL Texture.
- **get_size(...)** — Returns size.
- **get_texture_path(...)** — Returns texture path.
- **get_width(...)** — Returns width.
- **has_alpha_mask(...)** — Reports whether alpha mask.
- **is_fully_transparent(...)** — Reports whether fully transparent.
- **is_gpu_backed(...)** — Reports whether gpu backed.
- **is_loaded(...)** — Reports whether loaded.
- **is_pixel_opaque(...)** — Reports whether pixel opaque.
- **is_region_transparent(...)** — Reports whether region transparent.
- **load(...)** — Performs the load operation defined by this header.
- **load_from_surface(...)** — Loads from surface.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **set_scale_mode(...)** — Sets scale mode.
- **set_texture_opacity(...)** — Sets texture opacity.
- **Texture(...)** — Constructs a Texture instance.

### Example

~~~cpp
Texture texture;
texture.load("assets/player.png");
texture.draw({{100, 100}, texture.get_size()});
~~~

## fonts.h

- **~IFont(...)** — Releases resources owned by the instance.
- **~SDL_Font(...)** — Releases resources owned by the instance.
- **~Tileset_Font(...)** — Releases resources owned by the instance.
- **draw(...)** — Draws or submits visual output.
- **get_props(...)** — Returns props.
- **get_size(...)** — Returns size.
- **is_loaded(...)** — Reports whether loaded.
- **load(...)** — Performs the load operation defined by this header.
- **load_tileset_font(...)** — Loads tileset font.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **pixel_art(...)** — Performs the pixel art operation defined by this header.
- **SDL_Font(...)** — Constructs a SDL_Font instance.
- **set_char_map(...)** — Sets char map.
- **set_pixel_art(...)** — Sets pixel art.
- **set_props(...)** — Sets props.
- **set_tile_size(...)** — Sets tile size.
- **Tileset_Font(...)** — Constructs a Tileset_Font instance.
- **unload(...)** — Performs the unload operation defined by this header.

### Example

~~~cpp
SDL_Font font;
font.load("assets/fonts/ui.ttf", 24);
font.draw(IFont_Props{});
~~~

## camera.h

- **~Camera_Pool(...)** — Releases resources owned by the instance.
- **active_camera(...)** — Performs the active camera operation defined by this header.
- **apply_bounds(...)** — Applies bounds.
- **Camera(...)** — Constructs a Camera instance.
- **Camera_Pool(...)** — Constructs a Camera_Pool instance.
- **can_see(...)** — Reports whether see.
- **clear(...)** — Clears the owned state or collection.
- **clear_bounds(...)** — Clears the owned state or collection.
- **create(...)** — Performs the create operation defined by this header.
- **follow(...)** — Performs the follow operation defined by this header.
- **get(...)** — Performs the get operation defined by this header.
- **get_position(...)** — Returns position.
- **get_rotation(...)** — Returns rotation.
- **get_viewport(...)** — Returns viewport.
- **get_zoom(...)** — Returns zoom.
- **main_camera(...)** — Performs the main camera operation defined by this header.
- **move(...)** — Performs the move operation defined by this header.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **remove(...)** — Performs the remove operation defined by this header.
- **reset(...)** — Performs the reset operation defined by this header.
- **screen_size_to_world(...)** — Performs the screen size to world operation defined by this header.
- **screen_to_world(...)** — Performs the screen to world operation defined by this header.
- **set_active(...)** — Sets active.
- **set_bounds(...)** — Sets bounds.
- **set_position(...)** — Sets position.
- **set_rotation(...)** — Sets rotation.
- **set_viewport(...)** — Sets viewport.
- **set_zoom(...)** — Sets zoom.
- **shake(...)** — Performs the shake operation defined by this header.
- **size(...)** — Performs the size operation defined by this header.
- **world_size_to_screen(...)** — Performs the world size to screen operation defined by this header.
- **world_to_screen(...)** — Performs the world to screen operation defined by this header.

### Example

~~~cpp
Camera* camera = Engine::camera_pool->create("gameplay");
camera->set_position({320.0f, 180.0f});
camera->set_zoom(2.0f);
~~~

## light.h

- **~light_source(...)** — Releases resources owned by the instance.
- **~Light_System(...)** — Releases resources owned by the instance.
- **begin_world_pass(...)** — Performs the begin world pass operation defined by this header.
- **end_world_pass(...)** — Performs the end world pass operation defined by this header.
- **Float4(...)** — Constructs a Float4 instance.
- **get_night_amount(...)** — Returns night amount.
- **get_time_of_day(...)** — Returns time of day.
- **init(...)** — Initializes the service or resource.
- **is_auto_advance_enabled(...)** — Reports whether auto advance enabled.
- **is_ready(...)** — Reports whether ready.
- **light_count(...)** — Performs the light count operation defined by this header.
- **light_source(...)** — Performs the light source operation defined by this header.
- **Light_System(...)** — Constructs a Light_System instance.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **register_light(...)** — Registers light.
- **set_active(...)** — Sets active.
- **set_auto_advance(...)** — Sets auto advance.
- **set_day_length(...)** — Sets day length.
- **set_night_ambient(...)** — Sets night ambient.
- **set_shadow_strength(...)** — Sets shadow strength.
- **set_time_of_day(...)** — Sets time of day.
- **shutdown(...)** — Releases initialized engine resources.
- **unregister_light(...)** — Unregisters light.
- **update(...)** — Advances state for the current frame.

### Example

~~~cpp
Engine::lighting->set_time_of_day(20.0f);
Engine::lighting->set_shadow_strength(0.75f);
~~~

## asset_pool.h

- **~Asset_Pool(...)** — Releases resources owned by the instance.
- **activate_localized_texture(...)** — Performs the activate localized texture operation defined by this header.
- **add_audio_to_group(...)** — Adds audio to group.
- **Asset_Pool(...)** — Constructs a Asset_Pool instance.
- **clear(...)** — Clears the owned state or collection.
- **format_text(...)** — Formats a value for presentation.
- **get_audio(...)** — Returns audio.
- **get_font(...)** — Returns font.
- **get_text(...)** — Returns text.
- **get_texture(...)** — Returns texture.
- **has_audio(...)** — Reports whether audio.
- **has_audio_group(...)** — Reports whether audio group.
- **has_font(...)** — Reports whether font.
- **has_texture(...)** — Reports whether texture.
- **load_audio(...)** — Loads audio.
- **load_locale(...)** — Loads locale.
- **load_locales_from_directory(...)** — Loads locales from directory.
- **load_sdl_font(...)** — Loads sdl font.
- **load_texture(...)** — Loads texture.
- **load_tileset_font(...)** — Loads tileset font.
- **localization(...)** — Performs the localization operation defined by this header.
- **pause_audio_group(...)** — Pauses playback.
- **play_audio_group(...)** — Starts playback.
- **play_audio_group_shuffled(...)** — Starts playback.
- **remove_audio_from_all_groups(...)** — Removes audio from all groups.
- **remove_audio_from_group(...)** — Removes audio from group.
- **resume_audio_group(...)** — Resumes a paused operation.
- **set_audio_group_gain(...)** — Sets audio group gain.
- **set_audio_group_loop_count(...)** — Sets audio group loop count.
- **set_audio_group_pitch(...)** — Sets audio group pitch.
- **set_audio_group_props(...)** — Sets audio group props.
- **set_locale(...)** — Sets locale.
- **set_logger(...)** — Sets logger.
- **set_renderer(...)** — Sets renderer.
- **stop_audio_group(...)** — Stops the operation or state.
- **unload_audio(...)** — Unloads audio.
- **unload_font(...)** — Unloads font.
- **unload_texture(...)** — Unloads texture.

### Example

~~~cpp
Engine::asset_pool->load_texture("player", "player.png");
Texture* player = Engine::asset_pool->get_texture("player");
~~~

## loading_screen.h

- **~Loading_Screen(...)** — Releases resources owned by the instance.
- **~Simple_Tileset(...)** — Releases resources owned by the instance.
- **active(...)** — Performs the active operation defined by this header.
- **advance_frame(...)** — Performs the advance frame operation defined by this header.
- **advance_frame_index(...)** — Performs the advance frame index operation defined by this header.
- **cancel(...)** — Performs the cancel operation defined by this header.
- **columns(...)** — Performs the columns operation defined by this header.
- **draw_current_frame(...)** — Draws or submits visual output.
- **draw_fallback_background(...)** — Draws or submits visual output.
- **draw_frame(...)** — Draws or submits visual output.
- **draw_progress_bar(...)** — Draws or submits visual output.
- **draw_spinner(...)** — Draws or submits visual output.
- **enqueue(...)** — Performs the enqueue operation defined by this header.
- **enqueue_step(...)** — Performs the enqueue step operation defined by this header.
- **fail(...)** — Performs the fail operation defined by this header.
- **failed(...)** — Performs the failed operation defined by this header.
- **finish(...)** — Performs the finish operation defined by this header.
- **frame_budget_ms(...)** — Performs the frame budget ms operation defined by this header.
- **frame_count(...)** — Performs the frame count operation defined by this header.
- **free(...)** — Performs the free operation defined by this header.
- **is_loaded(...)** — Reports whether loaded.
- **Loading_Screen(...)** — Constructs a Loading_Screen instance.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **pending_task_count(...)** — Performs the pending task count operation defined by this header.
- **progress(...)** — Performs the progress operation defined by this header.
- **render(...)** — Performs the render operation defined by this header.
- **reset_frame(...)** — Performs the reset frame operation defined by this header.
- **rows(...)** — Performs the rows operation defined by this header.
- **set_artwork(...)** — Sets artwork.
- **set_frame_budget_ms(...)** — Sets frame budget ms.
- **set_frame_size(...)** — Sets frame size.
- **set_whole_size(...)** — Sets whole size.
- **Simple_Tileset(...)** — Constructs a Simple_Tileset instance.
- **update(...)** — Advances state for the current frame.

### Example

~~~cpp
Engine::loading_screen->enqueue_step("Load level", [] { load_level(); });
Engine::loading_screen->update();
~~~


