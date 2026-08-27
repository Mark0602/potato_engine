# Potato Engine documentation

This manual documents the reusable engine as it exists in the current source tree. All project-owned documentation is written in English. Third-party documentation under `flatbuffers`, `third_party`, and bundled SDL directories belongs to those dependencies.

## Manual

| Area | Document | Covered features |
| --- | --- | --- |
| Setup | [Getting started](docs/getting-started.md) | Requirements, build, run, CMake targets, application creation, configuration, tests |
| Core | [Architecture](docs/architecture.md) | Lifecycle, frame order, services, coordinates, ownership, shutdown |
| Graphics | [Rendering](docs/rendering.md) | Backends, logical presentation, textures, draw queue, cameras, lighting, fonts at render time |
| Gameplay structure | [Objects, UI, and scripts](docs/objects-ui-scripts.md) | Objects, pools, tags, components, lifecycle scripts, UI widgets, labels, text boxes, entity sample |
| Devices | [Input](docs/input.md) | Keyboard, mouse, controller, actions, axes, blocking, embedded viewports |
| Simulation | [Physics](docs/physics.md) | Bodies, shapes, masks, dynamics, callbacks, queries, raycasts, pixel collision |
| Content services | [Assets, audio, and localization](docs/assets-audio-localization.md) | Asset cache, textures, fonts, audio tracks/groups, localized strings and textures |
| Flow | [Scenes and loading](docs/scenes-loading.md) | Scene IDs/names, deferred transitions, load queues, custom artwork, failure behavior |
| Worlds | [Tilemaps](docs/tilemaps.md) | Tiles, atlases, groups, JSON maps, batching, editing helpers, registry |
| Effects | [Animation, particles, and timers](docs/animation-particles-timers.md) | Easing, value animation, groups, object transitions, emitters, timers |
| General helpers | [Saving and helpers](docs/helpers-saving.md) | FlatBuffer snapshots, math, color, random, logger, console, triggers |
| Extension | [Modding](docs/modding.md) | Manifests, ordering, sides, hashes, content, exports, AngelScript sandbox |
| Maintenance | [Development](docs/development.md) | Layout, adding code, CMake, tests, generated files, contribution rules |

## Public headers

`engine.h` contains the application entry point, renderer selection, configuration structures, and process-wide service handles. Feature types live in focused headers under `src/`; include the header for each feature you use. `engine.h` is not an umbrella header for all helpers.

The engine deliberately has no game-domain API. A game supplies its own entities, rules, assets, scene content, save extensions, and mod adapter on top of these primitives.

