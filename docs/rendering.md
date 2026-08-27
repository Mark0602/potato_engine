# Rendering, textures, cameras, and lighting

## Renderer backends

`RendererBackend::CPU` creates a normal SDL renderer. `RendererBackend::GPU` creates an SDL GPU renderer and exposes both its SDL_Renderer-compatible interface and the borrowed `SDL_GPUDevice`. Select the backend through `config::game_config::renderer_backend` before constructing `Engine::Application`.

The rest of the 2D API uses `SDL_Renderer*` on both backends. Textures, fonts, geometry batching, objects, and draw commands therefore do not need separate CPU/GPU code. Use `Engine::using_gpu_renderer()` before accessing GPU-only facilities. `Texture::get_gpu_texture()` and `Engine::gpu_device` return `nullptr` on the CPU backend.

The renderer uses `SDL_LOGICAL_PRESENTATION_LETTERBOX`. Draw in the configured logical resolution; SDL scales the result and adds bars when the window aspect ratio differs.

## Textures

`Texture` is a non-copyable, movable RAII wrapper around `SDL_Texture`. It can load from a file or an existing `SDL_Surface`, defaults to pixel-art sampling, and records its source path and native size.

Key capabilities:

- full-texture, destination-sized, rotated, flipped, tinted, and source-region drawing;
- `SDL_SCALEMODE_PIXELART` or `SDL_SCALEMODE_LINEAR` filtering;
- opacity modulation;
- native SDL texture access and optional SDL_GPU texture access;
- a CPU alpha mask used by transparency queries and pixel-perfect physics;
- `is_fully_transparent()` and `is_region_transparent()` checks.

Prefer `Asset_Pool::load_texture()` for shared assets. Direct construction is appropriate for short-lived or self-contained resources such as loading artwork.

```cpp
Engine::asset_pool->load_texture("hero", "hero.png");
Texture* hero = Engine::asset_pool->get_texture("hero");

Object sprite({100.0f, 80.0f}, {32.0f, 32.0f}, {}, hero,
              Engine::object_pool, Engine::logger);
sprite.tint = Color::white();
sprite.z_index = 128;
```

With the default path enabled, the asset pool resolves texture paths below `assets/textures/`. Pass `false` as `use_default_path` for an explicit path.

## Draw commands and render pool

`Draw` describes either a texture command or a font command. It carries a `Transform`, optional source rectangle, tint, text scale, visibility, z-index, Y-sort metadata, and a `camera_space` flag.

Submit commands during `on_render()`:

```cpp
Draw command(texture, {{64.0f, 64.0f}, {16.0f, 16.0f}}, Color::white(), 128);
command.camera_space = true;
command.y_sort = true;
command.sort_y = 80.0f;
Engine::render_pool->submit(command);
```

`Render_Pool::flush()` performs a stable sort and clears the queue after drawing:

- higher `z_index` values draw first;
- lower `z_index` values draw later and therefore appear on top;
- at the same layer, fixed-order commands draw before the Y-sorted group;
- Y-sorted commands with smaller `sort_y` draw first, so lower feet appear in front;
- screen-space commands skip camera conversion and world lighting.

Commands borrow their texture/font pointers only for the current frame. Submit them again every frame. Objects in `Engine::object_pool` with `visible && auto_submit` generate their commands automatically after script `on_render()` calls.

Use `on_post_render()` for immediate overlays that must appear after the world queue and lighting pass. Immediate SDL drawing during normal `on_render()` can be covered by later queued commands.

## Source rectangles and atlases

Set `Object::source_rect` and `use_source_rect=true` to draw an atlas region. `Tileset`, `Tileset_Font`, `Simple_Tileset`, and `Tilemap` build on the same concept. Transparent atlas cells can be skipped through tileset transparency caching.

## Cameras

`Camera` stores a world position, logical viewport, zoom, rotation, optional movement bounds, follow behavior, and shake state. It converts points, sizes, and complete transforms in both directions and exposes `can_see()` for render culling.

```cpp
Camera* camera = Engine::camera_pool->main_camera();
camera->set_position({320.0f, 180.0f});
camera->set_zoom(2.0f);
camera->set_bounds({0.0f, 0.0f}, {4096.0f, 4096.0f});
camera->follow(player, 8.0f, dt);

Vec world_mouse = camera->screen_to_world(Input::mouse_position());
```

Camera position represents the world point at the center of the viewport. Zoom must be positive. The camera API expresses camera rotation in radians, while drawable `Transform::rotation.x` uses degrees.

`Camera_Pool` owns named cameras. `main_cam` is created automatically, receives the logical viewport size, is active initially, and cannot be removed. `create`, `get`, `set_active`, `remove`, and `clear` manage additional cameras.

## GPU day/night lighting

When `game_config::enable_shaders` is true, the application creates `Light_System`. The effect requires a usable GPU device and compiled shader assets. If initialization fails, normal rendering continues.

`light_source` is a soft point light that automatically registers with the current `Engine::lighting` service. It exposes position, color, radius, intensity, softness, enabled state, and a screen-space option. Keep no more than `Light_System::MAX_LIGHTS` (16) relevant to one pass.

```cpp
light_source lamp({300.0f, 200.0f}, 180.0f,
                  Color(255, 210, 140), 1.2f, 0.4f);

Engine::lighting->set_time_of_day(22.0f);
Engine::lighting->set_night_ambient(Color(64, 82, 145), 0.28f);
Engine::lighting->set_shadow_strength(0.8f);
Engine::lighting->set_day_length(600.0f);
Engine::lighting->set_auto_advance(true);
```

Time of day is expressed in hours. `get_night_amount()` reports the current day/night blend. During rendering, the application begins a world pass before script rendering, applies lighting only to camera-space commands, then ends the pass before `on_post_render()`.

Shader source and precompiled variants are described in [`assets/shaders/README.md`](../assets/shaders/README.md).

