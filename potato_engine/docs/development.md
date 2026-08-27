# Development workflow

## Source layout

| Path | Purpose |
| --- | --- |
| `engine.h`, `engine.cpp` | Application, SDL state, service handles, and frame loop |
| `src/*.h`, `src/*.cpp` | Reusable 2D systems and helpers |
| `src/modding/` | Generic mod manifests, manager, service, and AngelScript runtime |
| `assets/shaders/` | Lighting shader source and backend variants |
| `saves/templates/` | FlatBuffers save schema |
| `tests/` | Core unit/smoke tests and mod fixtures |
| `third_party/`, `flatbuffers/`, `src/include/` | Vendored dependencies and SDK files |
| `docs/` | English engine manual |

The project is an engine library, not a game. New engine code must not introduce domain-specific entities, content IDs, gameplay progression, application rules, or fixed asset paths beyond generic engine conventions.

## Add an engine feature

1. Put the focused public declaration in `src/<feature>.h` and implementation in `src/<feature>.cpp`.
2. Add implementation files explicitly to `POTATO_ENGINE_SOURCES`, or create a separate library when the feature should not force an engine dependency.
3. Include only directly required headers and use forward declarations where ownership permits.
4. Document ownership, units, coordinate space, thread requirements, failure values, and pointer invalidation.
5. Add an isolated test under `tests/` and register it with CTest.
6. Update the relevant English manual page and the coverage table in `docs/README.md`.

## Add a game script

Create a `.cpp` containing a `script` subclass and `REGISTER_SCRIPT`. It must be compiled into the final executable so its static registrar runs.

`new_script.bat` interactively writes a starter into `scripts/`. The current sandbox target globs `examples/*.cpp`, not `scripts/*.cpp`; therefore add the generated file to your game target or align the CMake source list. `CONFIGURE_DEPENDS` only helps for the directory actually listed by CMake.

Treat generated starter comments as scaffolding, not API documentation. Keep production behavior in game-owned modules outside `Potato::Engine`.

## Build configurations

`build.bat` creates a Debug MinGW build. For manual configuration:

```text
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++
cmake --build build --parallel
```

Useful options:

- `-DPOTATO_BUILD_SANDBOX=OFF` builds libraries/tests without `potato.exe`;
- `-DBUILD_TESTING=OFF` disables test executables.

The SDL paths in the root CMake file currently target `x86_64-w64-mingw32`. Supporting another platform/toolchain requires replacing the bundled import/runtime path configuration or consuming system/package-manager SDL targets.

## Tests

```text
ctest --test-dir build --output-on-failure
```

Current test targets:

- `engine_helpers_tests`: timer, animation, and scene-load helpers;
- `functionality_trigger_tests`: naming, context, OR behavior, and owner removal;
- `potato_modding_tests`: discovery, dependency ordering, side lifecycle, API/export callbacks, script compile/load, lookup, execution, and shutdown.

Add device/render integration tests separately when a real SDL window, audio device, or GPU is required; do not pretend those paths are covered by headless helper tests.

## Generated and runtime output

The build invokes `flatc` to generate the save schema header under `build/generated`. Do not hand-edit that header. Edit `saves/templates/save_game.fbs`, update version/migration behavior, and rebuild.

After changing `assets/shaders/day_night_light.frag.hlsl`, run `assets/shaders/compile.bat` to regenerate DXIL and SPIR-V. Keep the Metal source in sync as described by the shader README.

Build directories, compiler artifacts, executables, logs, game saves, settings, and local CMake presets are ignored by Git.

## Review checklist

- Public API and documentation are English and content-agnostic.
- Owned resources use RAII or have an explicit shutdown order; borrowed pointers are labelled and unregistered before destruction.
- Frame durations use seconds unless an API explicitly says milliseconds or frames.
- World-space and screen-space rendering are chosen intentionally.
- SDL/GPU resource creation stays on the main thread.
- New state has a defined scene-change and shutdown behavior.
- Failure paths return a useful value/error and leave services reusable or explicitly failed.
- Relevant tests build and pass, and documentation links/API names are checked.
