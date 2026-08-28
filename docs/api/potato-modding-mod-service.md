# potato::modding::mod_service

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `mod_service.h`  
**Documented overloads:** 11

This page documents the engine-owned callables declared for `potato::modding::mod_service`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Detailed workflow example

~~~cpp
potato::modding::mod_service_config config;
config.mods_path = "mods";
config.game_api_version = "1.0.0";
config.script_line_budget = 10000;

potato::modding::mod_service mods;
std::string error;
if (!mods.discover(config, &error)) {
    logger.log(Log_Level::ERROR, "Mods", error);
    return;
}

bool started = mods.start_scripts(
    potato::modding::mod_side::client,
    log_sink,
    register_script_api,
    register_mod_exports,
    &error
);
if (!started) logger.log(Log_Level::ERROR, "Mods", error);
~~~

## Usage example

~~~cpp
potato::modding::mod_service service;
service.discover(config);
~~~

## Functions

### config

~~~cpp
const mod_service_config & potato::modding::mod_service::config() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const mod_service_config &`

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### discover

~~~cpp
bool potato::modding::mod_service::discover(const mod_service_config &config, std::string *error=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `config` | `const mod_service_config &` | Value supplied for the config parameter. | — |


---

### discovered

~~~cpp
bool potato::modding::mod_service::discovered() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### failed

~~~cpp
bool potato::modding::mod_service::failed() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### manager

~~~cpp
const mod_manager & potato::modding::mod_service::manager() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const mod_manager &`

Performs the manager operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### runtime_side

~~~cpp
mod_side potato::modding::mod_service::runtime_side() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `mod_side`

Performs the runtime side operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### script_runtime

~~~cpp
angel_script_runtime & potato::modding::mod_service::script_runtime()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `angel_script_runtime &`

Performs the script runtime operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### script_runtime

~~~cpp
const angel_script_runtime & potato::modding::mod_service::script_runtime() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const angel_script_runtime &`

Performs the script runtime operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### scripts_started

~~~cpp
bool potato::modding::mod_service::scripts_started() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the scripts started operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### shutdown_scripts

~~~cpp
void potato::modding::mod_service::shutdown_scripts()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

---

### start_scripts

~~~cpp
bool potato::modding::mod_service::start_scripts(mod_side runtime_side, script_log_sink log_sink, script_api_registrar register_script_api, mod_export_registrar register_mod_exports, std::string *error=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `runtime_side` | `mod_side` | Value supplied for the runtime_side parameter. | — |
| `log_sink` | `script_log_sink` | Value supplied for the log_sink parameter. | — |
| `register_script_api` | `script_api_registrar` | Value supplied for the register_script_api parameter. | — |
| `register_mod_exports` | `mod_export_registrar` | Value supplied for the register_mod_exports parameter. | — |



