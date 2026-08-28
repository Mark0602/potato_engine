# Engine::Application

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `engine.h`  
**Documented overloads:** 8

This page documents the engine-owned callables declared for `Engine::Application`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Detailed workflow example

~~~cpp
config::game_config config;
config.title = "Potato Adventure";
config.renderer_backend = RendererBackend::CPU;

Engine::Application application(config);
if (!application.initialize()) {
    return 1;
}

Logger session_log;
session_log.init("logs/session.log");
session_log.log(Log_Level::INFO, "Bootstrap", "Application initialized");

Vec spawn{64.0f, 96.0f};
Vec target{320.0f, 180.0f};
Vec direction = normalize(target - spawn);
Timer autosave;
autosave.start(30.0f);

return application.run();
~~~

## Usage example

~~~cpp
config::game_config cfg;
cfg.title = "Potato Demo";
Engine::Application app(cfg);
if (!app.initialize()) return 1;
return app.run();
~~~

## Functions

### ~Application

~~~cpp
Engine::Application::~Application()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### Application

~~~cpp
Engine::Application::Application(config::game_config config={})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Application value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `config` | `config::game_config` | Value supplied for the config parameter. | — |


---

### Application

~~~cpp
Engine::Application::Application(const Application &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Application value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### initialize

~~~cpp
bool Engine::Application::initialize()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the initialize operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### is_initialized

~~~cpp
bool Engine::Application::is_initialized() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### operator=

~~~cpp
Application & Engine::Application::operator=(const Application &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Application &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### run

~~~cpp
int Engine::Application::run()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Performs the run operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### shutdown

~~~cpp
void Engine::Application::shutdown()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.


