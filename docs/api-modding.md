# Modding API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This file documents Potato Engine-owned callable names. Overloads share one entry. Constructors, destructors, operators, and declared helpers are included. Third-party APIs are excluded.

## mod_manifest.h

- **applies_to(...)** — Performs the applies to operation defined by this header.
- **canonical_name(...)** — Performs the canonical name operation defined by this header.
- **content_paths(...)** — Performs the content paths operation defined by this header.
- **discover(...)** — Performs the discover operation defined by this header.
- **empty(...)** — Performs the empty operation defined by this header.
- **is_snake_case(...)** — Reports whether snake case.
- **qualified_id(...)** — Performs the qualified id operation defined by this header.
- **script_paths(...)** — Performs the script paths operation defined by this header.
- **shared_mod_hash(...)** — Performs the shared mod hash operation defined by this header.

### Example

~~~cpp
potato::modding::mod_manager mods;
mods.discover("mods", "1.0.0");
~~~

## angel_script_runtime.h

- **~angel_script_runtime(...)** — Releases resources owned by the instance.
- **angel_script_runtime(...)** — Performs the angel script runtime operation defined by this header.
- **build_mod(...)** — Performs the build mod operation defined by this header.
- **engine(...)** — Performs the engine operation defined by this header.
- **find_function(...)** — Finds function.
- **initialize(...)** — Initializes the service or resource.
- **initialized(...)** — Initializes the service or resource.
- **line_budget(...)** — Performs the line budget operation defined by this header.
- **module_key(...)** — Performs the module key operation defined by this header.
- **operator=(...)** — Replaces this object with another value; the declaration may disable copying.
- **set_line_budget(...)** — Sets line budget.
- **shutdown(...)** — Releases initialized engine resources.
- **write_log(...)** — Performs the write log operation defined by this header.

### Example

~~~cpp
potato::modding::angel_script_runtime runtime;
runtime.initialize(log_sink);
runtime.set_line_budget(10000);
~~~

## mod_service.h

- **discover(...)** — Performs the discover operation defined by this header.
- **discovered(...)** — Performs the discovered operation defined by this header.
- **failed(...)** — Performs the failed operation defined by this header.
- **runtime_side(...)** — Performs the runtime side operation defined by this header.
- **script_runtime(...)** — Performs the script runtime operation defined by this header.
- **scripts_started(...)** — Performs the scripts started operation defined by this header.
- **shutdown_scripts(...)** — Releases initialized engine resources.
- **start_scripts(...)** — Starts the operation or state.

### Example

~~~cpp
potato::modding::mod_service service;
service.discover(config);
~~~


