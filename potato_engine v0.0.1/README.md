# Potato Engine

Potato Engine is a reusable, content-agnostic C++17 2D engine built on SDL3. It provides an application loop and a set of independent engine helpers without any game-specific rules or content.

The engine includes:

- CPU and SDL_GPU-backed 2D rendering with logical resolution, cameras, draw ordering, Y sorting, texture regions, and optional lighting;
- objects, object-attached scripts, labels, text input, buttons, sliders, toggles, and progress bars;
- keyboard, mouse, hot-pluggable gamepad, named action, and analog axis input;
- fixed-step 2D physics with masks, triggers, forces, impulses, sleeping, broad-phase acceleration, overlap queries, raycasts, and pixel-alpha collision;
- scenes, deferred transitions, responsive loading tasks, assets, fonts, audio, localization, tilemaps, animation, particles, timers, saves, logging, and console helpers;
- generic mod discovery and a sandboxed AngelScript runtime;
- a generic named functionality-trigger registry for combining independent Boolean sources.

## Build and run

On Windows, install CMake 3.24+ and a MinGW `g++` compiler, then run:

```text
build.bat
run.bat
```

The executable is written to `build/potato.exe`. The sandbox accepts `--gpu`, `--cpu`, `--console`, and `--help`.

To run the tests:

```text
ctest --test-dir build --output-on-failure
```

## Minimal application

```cpp
#include "engine.h"

int main() {
    config::game_config game;
    game.title = "My Potato Game";
    game.logical_width = 1280;
    game.logical_height = 720;
    game.renderer_backend = RendererBackend::GPU;

    Engine::Application application(game);
    return application.run();
}
```

Game behavior is implemented with `script` subclasses and registered with `REGISTER_SCRIPT`. Applications linking the engine as a library must compile their own script translation units into their executable.

## CMake targets

| Target | Purpose |
| --- | --- |
| `Potato::Engine` | Application lifecycle and all reusable 2D engine systems. |
| `Potato::Modding` | Manifest discovery, dependency ordering, content lookup, and AngelScript runtime. |
| `Potato::FunctionalityTrigger` | Named, multi-source Boolean trigger registry. |
| `Potato::Json` | Shared simdjson implementation. |
| `Potato::AngelScript` | Statically linked AngelScript VM. |
| `potato_sandbox` | Minimal executable, emitted as `potato.exe`. |

## Documentation

Start with the [documentation index](docs/README.md).

- [Getting started and configuration](docs/getting-started.md)
- [Architecture, lifecycle, and ownership](docs/architecture.md)
- [Rendering, textures, cameras, and lighting](docs/rendering.md)
- [Objects, UI, text, and scripts](docs/objects-ui-scripts.md)
- [Input](docs/input.md)
- [Physics](docs/physics.md)
- [Assets, fonts, audio, and localization](docs/assets-audio-localization.md)
- [Scenes and loading](docs/scenes-loading.md)
- [Tilemaps](docs/tilemaps.md)
- [Animation, particles, and timers](docs/animation-particles-timers.md)
- [Saving, utilities, logging, and triggers](docs/helpers-saving.md)
- [Modding and AngelScript](docs/modding.md)
- [Development workflow](docs/development.md)
