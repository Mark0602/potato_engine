# Engine

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `engine.h`  
**Documented overloads:** 2

This page documents the engine-owned callables declared for `Engine`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
config::game_config cfg;
cfg.title = "Potato Demo";
Engine::Application app(cfg);
if (!app.initialize()) return 1;
return app.run();
~~~

## Functions

### quit

~~~cpp
void Engine::quit()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the quit operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### using_gpu_renderer

~~~cpp
bool Engine::using_gpu_renderer()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the using gpu renderer operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

