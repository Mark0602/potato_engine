# What is Potato Engine

Potato Engine is a 2D game engine or game framework made with C++, it is designed specifically for games made by me, but feel free to use it. The engine is completely open-source. You can find everything in the /src folder, and change it according to the needs of your game, and I am planning to keep it this way. Potato Engine is not meant to be a full fledged AAA engine, it suits developers working on indie 2D pixel art games (tho 3D might come in the far future, I'm not sure yet). As stated, feel free to use it, change the systems how it works in your own ways, and if you release a game with it the only thing I ask for is credit. 
Updates are planned to happen as frequently as possible but as an university student time is not something I have. Also updates usually come by porting features back from my WIP games to the native engine. A small editor already exists, but not yet moved to the native engine. Please keep in mind the engine will always prioritize creating objects and scripts from a code. If you have suggestions or ideas feel free to let me know

### Disclaimer
Most of the documentation is still AI written as I did not manage to find the time to write all of it, but it will be hand rewritten in the near future. That said expect some unlogical arrangement, some logical flaws and weird language. Support is appriciated.

# Potato Engine documentation

This manual documents the reusable engine as it exists in the current source tree. All project-owned documentation is written in English. Third-party documentation under `flatbuffers`, `third_party`, and bundled SDL directories belongs to those dependencies.


## Manual

The complete callable catalog for **Potato Engine 1.0.0** starts at [API reference](docs/api-reference.md).

| Area | Document | Covered features |
| --- | --- | --- |
| Setup | [Getting started](docs/getting-started.md) | Requirements, build, run, CMake targets, application creation, configuration, tests |
| API Reference | [API Reference](docs/api-reference.md) | A detailed description of every function and class found in the API  |
| Core | [Architecture](docs/architecture.md) | Lifecycle, frame order, services, coordinates, ownership, shutdown |
| Graphics | [Rendering](docs/rendering.md) | Backends, logical presentation, textures, draw queue, cameras, lighting, fonts at render time |
| Gameplay structure | [Objects, UI, and scripts](docs/objects-ui-scripts.md) | Objects, pools, tags, components, lifecycle scripts, UI widgets, labels, text boxes, entity sample |
| Hierarchies | [Object hierarchy](docs/object-hierarchy.md) | Parent/child relationships, local and world transforms, reparenting, lifetime, rendering, physics, and saving |
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
