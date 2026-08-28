# Potato Engine API reference

**Engine version:** Potato Engine 1.0.0  
**Language:** C++  
**Documented overloads:** 983

Each engine class, struct, and namespace has its own documentation page. Free functions that do not belong to a type or namespace are grouped only by their declaration header. Third-party SDL, simdjson, FlatBuffers, and AngelScript APIs are excluded.

## Documentation by header

### `engine.h`

- [config](api/config.md) — 1 overload
- [Engine](api/engine.md) — 2 overloads
- [Engine::Application](api/engine-application.md) — 8 overloads
- [SDLstate](api/sdlstate.md) — 14 overloads

### `vec.h`

- [Transform](api/transform.md) — 12 overloads
- [Vec](api/vec.md) — 18 overloads

### `color.h`

- [Color](api/color.md) — 46 overloads

### `utils.h`

- [Utils free functions](api/utils-free-functions.md) — 47 overloads

### `debug.h`

- [Logger](api/logger.md) — 17 overloads

### `timer.h`

- [Timer](api/timer.md) — 9 overloads

### `prandom.h`

- [prandom](api/prandom.md) — 8 overloads

### `functionality_trigger.h`

- [functionality_trigger](api/functionality-trigger.md) — 4 overloads

### `game_console.h`

- [game_console](api/game-console.md) — 6 overloads

### `save_game.h`

- [Save_Game](api/save-game.md) — 7 overloads
- [Save_Pool](api/save-pool.md) — 7 overloads

### `render.h`

- [Draw](api/draw.md) — 5 overloads
- [GPU_Renderer](api/gpu-renderer.md) — 11 overloads
- [Render_Pool](api/render-pool.md) — 7 overloads

### `texture.h`

- [Texture](api/texture.md) — 35 overloads

### `fonts.h`

- [IFont](api/ifont.md) — 11 overloads
- [SDL_Font](api/sdl-font.md) — 14 overloads
- [Tileset_Font](api/tileset-font.md) — 19 overloads

### `camera.h`

- [Camera](api/camera.md) — 24 overloads
- [Camera_Pool](api/camera-pool.md) — 15 overloads

### `light.h`

- [light_source](api/light-source.md) — 4 overloads
- [Light_System](api/light-system.md) — 22 overloads
- [Light_System::Float4](api/light-system-float4.md) — 5 overloads

### `asset_pool.h`

- [Asset_Pool](api/asset-pool.md) — 45 overloads

### `loading_screen.h`

- [Loading_Screen](api/loading-screen.md) — 26 overloads
- [Simple_Tileset](api/simple-tileset.md) — 22 overloads

### `animations.h`

- [Anim](api/anim.md) — 4 overloads
- [Animations free functions](api/animations-free-functions.md) — 4 overloads
- [AnimGroup](api/animgroup.md) — 3 overloads
- [Ease](api/ease.md) — 7 overloads
- [StaggeredSlideIn](api/staggeredslidein.md) — 4 overloads

### `object.h`

- [Button](api/button.md) — 3 overloads
- [Object](api/object.md) — 34 overloads
- [Object_Pool](api/object-pool.md) — 7 overloads
- [Progress_Bar](api/progress-bar.md) — 4 overloads
- [Slider](api/slider.md) — 7 overloads
- [Toggle](api/toggle.md) — 5 overloads
- [UI_Object](api/ui-object.md) — 20 overloads
- [UI_Value](api/ui-value.md) — 6 overloads

### `entity.h`

- [Entity](api/entity.md) — 12 overloads

### `particle.h`

- [Particle](api/particle.md) — 4 overloads
- [Particle_Emitter](api/particle-emitter.md) — 7 overloads

### `label.h`

- [Label](api/label.md) — 21 overloads
- [TextBox](api/textbox.md) — 24 overloads

### `scene.h`

- [SceneManager](api/scenemanager.md) — 18 overloads

### `script-base.h`

- [script](api/script.md) — 9 overloads

### `script-registry.h`

- [script_registry](api/script-registry.md) — 4 overloads

### `input.h`

- [Input](api/input.md) — 35 overloads
- [Input::detail](api/input-detail.md) — 7 overloads

### `audio.h`

- [Audio](api/audio.md) — 35 overloads
- [ITrack](api/itrack.md) — 7 overloads
- [Track_Pool](api/track-pool.md) — 26 overloads

### `localization.h`

- [Localization](api/localization.md) — 16 overloads

### `physics.h`

- [Physics](api/physics.md) — 1 overload
- [Physics free functions](api/physics-free-functions.md) — 1 overload
- [Physics::Collision_Body](api/physics-collision-body.md) — 35 overloads
- [Physics::Gravitational_Object](api/physics-gravitational-object.md) — 2 overloads
- [Physics::Physics_Engine](api/physics-physics-engine.md) — 25 overloads

### `tileset.h`

- [Tile](api/tile.md) — 11 overloads
- [Tilemap](api/tilemap.md) — 30 overloads
- [Tilemap_Registry](api/tilemap-registry.md) — 4 overloads
- [Tileset](api/tileset.md) — 21 overloads
- [Tileset_Group](api/tileset-group.md) — 11 overloads

### `mod_manifest.h`

- [potato::modding::mod_manager](api/potato-modding-mod-manager.md) — 12 overloads

### `angel_script_runtime.h`

- [potato::modding::angel_script_runtime](api/potato-modding-angel-script-runtime.md) — 15 overloads

### `mod_service.h`

- [potato::modding::mod_service](api/potato-modding-mod-service.md) — 11 overloads

## Reading an entry

Every overload includes its exact C++ signature, engine version, access level, return type, description, and parameter information. Unnamed C++ parameters are identified explicitly and remain visible in the signature.

