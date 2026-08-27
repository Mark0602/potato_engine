# Getting started

## Requirements

The checked-in build is configured for 64-bit Windows with MinGW import libraries. You need:

- CMake 3.24 or newer;
- a MinGW `g++` compiler on `PATH`;
- a C++17-capable toolchain.

SDL3, SDL3_image, SDL3_ttf, and SDL3_mixer headers, import libraries, and runtime DLLs are bundled in the repository. FlatBuffers and AngelScript are built from the checked-in sources.

## Build

The convenience command configures a Debug build and compiles every enabled target:

```text
build.bat
```

Equivalent commands:

```text
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++
cmake --build build --parallel
```

Set `POTATO_BUILD_SANDBOX=OFF` when consuming only the libraries:

```text
cmake -S . -B build -G "MinGW Makefiles" -DPOTATO_BUILD_SANDBOX=OFF
```

`BUILD_TESTING` is provided by CTest and defaults to enabled. The build generates `save_game_generated.h` from `saves/templates/save_game.fbs`, then copies the SDL runtime DLLs next to `potato.exe` when the sandbox target is built.

## Run

```text
run.bat
run.bat --gpu
run.bat --cpu --console
```

`run.bat` always builds first. The sandbox command-line parser also accepts `--fps=N` and `--background-fps=N`, but the current `Engine::Application` constructor accepts only `config::game_config`; those parsed values are not forwarded and the application currently uses its internal 60/20 FPS defaults.

## Create an application

```cpp
#include "engine.h"

int main() {
    config::game_config game;
    game.title = "Example";
    game.log_path = "logs/latest.log";
    game.window_width = 1280;
    game.window_height = 720;
    game.logical_width = 640;
    game.logical_height = 360;
    game.renderer_backend = RendererBackend::CPU;
    game.audio_tracks = 8;
    game.enable_shaders = true;
    game.show_console = false;

    Engine::Application app(game);
    return app.run();
}
```

`run()` initializes the services, owns the frame loop, shuts down through the destructor, and returns `-1` after an initialization or loading failure. You may call `initialize()`, `is_initialized()`, and `shutdown()` explicitly when embedding the lifecycle.

## Register behavior

```cpp
#include "engine.h"
#include "src/input.h"
#include "src/script-registry.h"

class movement_script final : public script {
    SCRIPT_ORDER(0)
    SCRIPT_SCENE(-1)

public:
    void on_start() override {
        Input::bind_axis_key("move_x", SDL_SCANCODE_A, -1.0f);
        Input::bind_axis_key("move_x", SDL_SCANCODE_D, 1.0f);
    }

    void on_update(float dt) override {
        (void)dt;
        const float movement = Input::axis("move_x");
        (void)movement;
    }
};

REGISTER_SCRIPT(movement_script)
```

Registration happens during static initialization. The executable must compile the `.cpp` file containing `REGISTER_SCRIPT`; merely placing a file in the repository does not register it. The sandbox CMake target currently discovers `examples/*.cpp`, while `new_script.bat` writes into `scripts/`, so add generated script files to your target or adjust the source glob before relying on the helper.

## Configuration JSON

`config::load_config(path, project, game, settings)` reads the following structure:

```json
{
  "project": {
    "name": "Example",
    "version": "1.0.0",
    "company": "Example Studio"
  },
  "game": {
    "title": "Example",
    "version": "1.0.0",
    "default log path": "logs/latest.log",
    "dimensions": {
      "window": { "width": 1280, "height": 720 },
      "logical": { "width": 640, "height": 360 }
    },
    "renderer backend": "GPU",
    "default audio tracks": 8,
    "enable shaders": true,
    "show console on start": false
  },
  "settings": {
    "target fps": 60,
    "background fps": 20,
    "fullscreen": false,
    "vsync": false
  }
}
```

The loader preserves defaults for missing or invalid optional values. It does not run automatically: the current sandbox does not call it, and `Application` does not accept `config::project_config` or a caller-provided `config::settings`. Load and apply the supported `game_config` fields in your entry point if you want file-driven setup.

## Link the libraries

For an in-tree consumer:

```cmake
add_subdirectory(path/to/potato-engine)
add_executable(my_game main.cpp game_script.cpp)
target_link_libraries(my_game PRIVATE Potato::Engine)
```

Link `Potato::Modding` and `Potato::FunctionalityTrigger` only when those independent libraries are needed.

## Tests

```text
ctest --test-dir build --output-on-failure
```

The current suite covers the timer/animation/scene helpers, the generic trigger registry, and mod discovery plus AngelScript lifecycle. Rendering, input devices, audio hardware, and GPU lighting are not exercised by these headless tests.

