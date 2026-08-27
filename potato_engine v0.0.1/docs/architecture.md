# Architecture and lifecycle

## Library layers

`Potato::Engine` owns the runtime-facing SDL systems. `Potato::Modding` and `Potato::FunctionalityTrigger` are independent static libraries: neither requires a particular game. `Potato::Json`, `Potato::AngelScript`, and FlatBuffers support those public layers.

`Engine::Application` is the normal entry point. Internally it owns `SDLstate`, creates the engine services, creates registered scripts, runs frames, and destroys everything in a controlled order. Copying `Application` and `SDLstate` is disabled.

## Initialization order

`Application::initialize()` performs these operations:

1. optionally opens the native console;
2. initializes SDL video, audio, and gamepad subsystems;
3. creates a resizable window and either an SDL 2D renderer or an SDL_GPU-backed renderer;
4. enables letterboxed logical presentation;
5. initializes SDL_mixer and SDL_ttf and opens the default playback device;
6. creates the logger, render pool, scene manager, object pool, physics world, save pool, camera pool, track pool, asset pool, loading screen, and optional lighting system;
7. initializes input and instantiates every registered script in execution order;
8. displays a startup loading screen and queues `on_start()` for scripts active in the initial scene.

If lighting initialization fails, the engine logs a warning and continues without the effect. Failures in required SDL, mixer, font, or loading operations end the application with an error.

## Frame order

Each frame follows this order:

1. calculate seconds since the previous frame and clamp the value to 0.1 seconds;
2. call `Input::begin_frame()` and start any pending scene transition;
3. poll SDL events, feed input and console handlers, then dispatch `on_event()` to active scripts when no loading screen is active;
4. call `Input::update()`;
5. while loading, advance the loading queue; otherwise run `on_update()`, fixed-step physics, audio-track maintenance, lighting time, and any newly requested scene transition;
6. clear the frame;
7. draw the loading overlay, or render active scripts and automatically submitted objects;
8. flush the render pool, finish the lighting world pass, then call `on_post_render()` for overlays;
9. present, update `Engine::delta_time`, `fps`, and `avg_fps`, and apply frame pacing.

Gameplay simulation and normal rendering pause while loading. SDL events, the window, loading animation, and input-state maintenance continue.

## Engine service handles

After initialization, the `Engine` namespace exposes borrowed process-wide pointers:

| Handle | Service |
| --- | --- |
| `context`, `window`, `renderer`, `gpu_device` | SDL runtime and native rendering handles |
| `render_pool` | Per-frame sorted draw queue |
| `logger` | Thread-safe file and console logger |
| `scene_manager`, `loading_screen` | Scene and transition services |
| `object_pool`, `save_pool` | Borrowed object registries |
| `camera_pool` | Owned named cameras and active camera |
| `asset_pool`, `track_pool` | Asset cache and audio playback tracks |
| `physics_engine`, `lighting` | Simulation and optional GPU lighting |

Additional values include `renderer_backend`, `logical_width`, `logical_height`, `delta_time` in milliseconds, instantaneous `fps`, one-second `avg_fps`, global `master_gain`, and the borrowed `object_scripts` list. `Engine::using_gpu_renderer()` reports the selected backend and `Engine::quit()` stops the loop.

These are non-owning conveniences. Never delete them, cache them beyond application shutdown, or use them before initialization. `Application::shutdown()` clears every handle.

## Coordinate conventions

The window has a physical size and the renderer has a logical size. SDL letterboxes and scales the logical canvas into the window. Engine objects, cameras, physics, tilemaps, and most input positions use logical units.

`Transform::pos` is the top-left point and `Transform::size` is width/height. `Transform::rotation.x` is an angle in degrees for rendering; `rotation.y` carries an `SDL_FlipMode`-compatible numeric value. Camera rotation is documented by the camera API as radians. Keep that unit difference explicit.

`Object::camera_space=true` means the active camera transforms and culls the draw. UI objects set it to `false`.

## Ownership rules

- `Application` owns engine services and globally registered script instances.
- `Asset_Pool` owns textures, fonts, and audio through `std::unique_ptr`; returned pointers are borrowed.
- `Camera_Pool` owns cameras; `main_cam` always exists.
- `Object_Pool`, `Save_Pool`, `Physics_Engine`, `Render_Pool`, tilemap registry, and light registration store borrowed pointers or commands. They do not own the referenced game objects.
- `Object` owns an attached `script` after `attach_script()` and deletes it in `detach_script()` or destruction.
- `Texture` owns its SDL texture. `light_source` and `Collision_Body` self-register and unregister with the current engine service.
- A `Draw` command borrows its texture/font only until that frame's `Render_Pool::flush()`.

Destroy game objects, bodies, lights, and borrowed references before destroying the services they use. Prefer RAII game objects whose lifetime is nested inside the application lifetime.

## Shutdown order

Registered scripts receive `on_destroy()` and are deleted first, followed by remaining attached scripts. Loading, lighting, assets, audio tracks, physics, rendering, saves, cameras, and objects are then released. Input, mixer, TTF, the logger, SDL renderer/window, and SDL itself are shut down last.

Calling `shutdown()` more than once is safe at the application level.
