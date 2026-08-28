# config

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `engine.h`  
**Documented overloads:** 1

This page documents the engine-owned callables declared for `config`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
config::game_config cfg;
cfg.title = "Potato Demo";
Engine::Application app(cfg);
if (!app.initialize()) return 1;
return app.run();
~~~

## Functions

### load_config

~~~cpp
static bool config::load_config(const std::string &path, project_config &pconf, game_config &gconf, settings &settings)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pconf` | `project_config &` | Value supplied for the pconf parameter. | — |
| `gconf` | `game_config &` | Value supplied for the gconf parameter. | — |
| `settings` | `settings &` | Value supplied for the settings parameter. | — |


