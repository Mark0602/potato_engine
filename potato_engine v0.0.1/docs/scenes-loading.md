# Scenes and loading

## Scene manager

`SceneManager` is a process-wide singleton. Scenes are numeric IDs with optional unique human-readable names. The default active ID is `0`.

```cpp
auto* scenes = Engine::scene_manager;
scenes->register_scene(0, "menu");
scenes->register_scene(1, "gameplay");
```

`current_scene`, `current_scene_name`, and `scene_name(id)` expose state. Scripts with `SCRIPT_SCENE(id)` are active only when the ID matches; `SCRIPT_SCENE(-1)` scripts are global.

## Immediate and deferred changes

`set_scene(id/name)` changes the active ID immediately and is mainly a low-level compatibility API. The application notices the change and starts a transition on the next transition-processing point.

Prefer `request_scene(id/name)` for a user-visible transition:

```cpp
Engine::scene_manager->request_scene("gameplay");
```

The request is rejected when the ID is invalid, already active, already requested, or already transitioning. The application consumes the request, starts the loading overlay, runs queued work and not-yet-started scripts for the target scene, then activates the scene. Each globally registered script's `on_start()` runs at most once across scene visits.

Only one request is stored. A newer request may be queued after an earlier transition completes; use `cancel_scene_request()` to clear a request that has not started.

## Scene load work

Queue work before requesting the target:

```cpp
scenes->enqueue_load_task(
    1,
    "Loading save",
    [] { load_save_data(); },
    2.0f
);
scenes->request_scene(1);
```

`enqueue_load_task` wraps an atomic `void()` action. It runs on the main thread and cannot be interrupted by the frame budget. Split long work with `enqueue_load_step`; its callback runs at most once per loading frame and returns `true` only when complete:

```cpp
scenes->enqueue_load_step(
    1,
    "Building chunks",
    [next = std::size_t{0}]() mutable {
        build_chunk(next++);
        return next == chunk_count();
    }
);
```

Tasks are one-shot and removed when that scene transition takes them. Positive weights control progress-bar contribution; invalid/small weights are clamped to a safe minimum.

## Loading screen

`Loading_Screen` is a main-thread queue and overlay. `begin(title, completion)` clears unfinished old tasks. `enqueue`, `enqueue_step`, `update`, `render`, and `cancel` support direct non-scene loading operations.

The overlay presents at least one frame before executing the first task. Atomic tasks are processed within a default 4 ms budget after work starts, but one slow atomic callback may exceed that budget. Incremental steps always yield after one call.

The state API exposes `active`, `failed`, `error`, `progress`, `title`, `current_task`, `pending_task_count`, and configurable `frame_budget_ms`.

Exceptions thrown by a task are caught, logged as failure, and clear the queue without invoking the completion callback. The application exits with `-1` when its active loading screen fails.

SDL window, renderer, texture, font, and other graphics resource creation should remain on the main thread. CPU-only file reading or decoding may use worker threads only if game code safely transfers the result back into a main-thread step.

## Artwork and fallback

Without assets, the overlay draws a built-in background, spinner, and progress bar. Custom artwork can be owned independently of the normal asset pool:

```cpp
Engine::loading_screen->load_artwork(
    "assets/loading/background.png",
    "assets/loading/spinner.png",
    {16.0f, 16.0f}
);
```

A positive icon frame size treats the icon as a row-major sprite sheet and advances frames. Without it, the full icon texture rotates. Missing artwork falls back safely.

`set_artwork(background, icon)` accepts borrowed textures; they must outlive the loading operation. `Simple_Tileset` is the smaller RAII atlas helper used by this path and is available for other minimal frame-sheet uses.

