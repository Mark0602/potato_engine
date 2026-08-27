# Modding API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This reference lists every engine-owned function overload declared in the covered headers. Signatures preserve parameter types, names, default values, qualifiers, and namespaces from the source. Access labels identify members that are not part of the public calling surface.

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

## mod_manifest.h

### applies_to

~~~cpp
static bool potato::modding::mod_manager::applies_to(mod_side declared_side, mod_side runtime_side)
~~~

**Access:** public  **Storage:** static  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the applies to operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `declared_side` (`mod_side`): Value supplied for the declared_side parameter.
- `runtime_side` (`mod_side`): Value supplied for the runtime_side parameter.

### canonical_name

~~~cpp
static std::string potato::modding::mod_manager::canonical_name(const std::string &value)
~~~

**Access:** public  **Storage:** static  **Returns:** ``std::string``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `value` (`const std::string &`): Value supplied for the value parameter.

### content_paths

~~~cpp
std::vector< std::filesystem::path > potato::modding::mod_manager::content_paths(const std::string &group, mod_side runtime_side) const
~~~

**Access:** public  **Returns:** ``std::vector< std::filesystem::path >``  **Engine version:** Potato Engine 1.0.0

Performs the content paths operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `group` (`const std::string &`): Value supplied for the group parameter.
- `runtime_side` (`mod_side`): Value supplied for the runtime_side parameter.

### discover

~~~cpp
bool potato::modding::mod_manager::discover(const std::filesystem::path &mods_path, const std::string &expected_game_api_version, std::string *error=nullptr)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

- `mods_path` (`const std::filesystem::path &`): Value supplied for the mods_path parameter.
- `expected_game_api_version` (`const std::string &`): Value supplied for the expected_game_api_version parameter.
- `error` (`std::string *`): Value supplied for the error parameter.

### empty

~~~cpp
bool potato::modding::mod_manager::empty() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### exports

~~~cpp
const std::vector< mod_export > * potato::modding::mod_manager::exports(const mod_manifest &manifest, const std::string &group) const
~~~

**Access:** public  **Returns:** `const std::vector< mod_export > *`  **Engine version:** Potato Engine 1.0.0

Performs the exports operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `manifest` (`const mod_manifest &`): Value supplied for the manifest parameter.
- `group` (`const std::string &`): Value supplied for the group parameter.

### is_snake_case

~~~cpp
static bool potato::modding::mod_manager::is_snake_case(const std::string &value)
~~~

**Access:** public  **Storage:** static  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `value` (`const std::string &`): Value supplied for the value parameter.

### mods

~~~cpp
const std::vector< mod_manifest > & potato::modding::mod_manager::mods() const
~~~

**Access:** public  **Returns:** `const std::vector< mod_manifest > &`  **Engine version:** Potato Engine 1.0.0

Performs the mods operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### qualified_id

~~~cpp
static std::string potato::modding::mod_manager::qualified_id(const std::string &mod_id, const std::string &local_id)
~~~

**Access:** public  **Storage:** static  **Returns:** ``std::string``  **Engine version:** Potato Engine 1.0.0

Performs the qualified id operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `mod_id` (`const std::string &`): Value supplied for the mod_id parameter.
- `local_id` (`const std::string &`): Value supplied for the local_id parameter.

### root_path

~~~cpp
const std::filesystem::path & potato::modding::mod_manager::root_path() const
~~~

**Access:** public  **Returns:** ``const std::filesystem::path &``  **Engine version:** Potato Engine 1.0.0

Performs the root path operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### script_paths

~~~cpp
std::vector< std::filesystem::path > potato::modding::mod_manager::script_paths(const mod_manifest &manifest, mod_side runtime_side) const
~~~

**Access:** public  **Returns:** ``std::vector< std::filesystem::path >``  **Engine version:** Potato Engine 1.0.0

Performs the script paths operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `manifest` (`const mod_manifest &`): Value supplied for the manifest parameter.
- `runtime_side` (`mod_side`): Value supplied for the runtime_side parameter.

### shared_mod_hash

~~~cpp
std::string potato::modding::mod_manager::shared_mod_hash() const
~~~

**Access:** public  **Returns:** ``std::string``  **Engine version:** Potato Engine 1.0.0

Performs the shared mod hash operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### Header usage example

~~~cpp
potato::modding::mod_manager mods;
mods.discover("mods", "1.0.0");
~~~

## angel_script_runtime.h

### ~angel_script_runtime

~~~cpp
potato::modding::angel_script_runtime::~angel_script_runtime()
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### angel_script_runtime

~~~cpp
potato::modding::angel_script_runtime::angel_script_runtime()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Performs the angel script runtime operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### angel_script_runtime

~~~cpp
potato::modding::angel_script_runtime::angel_script_runtime(const angel_script_runtime &)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Performs the angel script runtime operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `` (`const angel_script_runtime &`): Value supplied for the  parameter.

### build_mod

~~~cpp
bool potato::modding::angel_script_runtime::build_mod(const mod_manifest &manifest, const std::vector< std::filesystem::path > &script_paths, mod_side runtime_side, std::string *error=nullptr)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

- `manifest` (`const mod_manifest &`): Value supplied for the manifest parameter.
- `script_paths` (`const std::vector< std::filesystem::path > &`): Value supplied for the script_paths parameter.
- `runtime_side` (`mod_side`): Value supplied for the runtime_side parameter.
- `error` (`std::string *`): Value supplied for the error parameter.

### engine

~~~cpp
asIScriptEngine * potato::modding::angel_script_runtime::engine() const
~~~

**Access:** public  **Returns:** ``asIScriptEngine *``  **Engine version:** Potato Engine 1.0.0

Performs the engine operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### execute

~~~cpp
bool potato::modding::angel_script_runtime::execute(asIScriptFunction *function, const std::vector< void * > &object_arguments={}, std::string *error=nullptr)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the execute operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `function` (`asIScriptFunction *`): Value supplied for the function parameter.
- `object_arguments` (`const std::vector< void * > &`): Value supplied for the object_arguments parameter.
- `error` (`std::string *`): Value supplied for the error parameter.

### find_function

~~~cpp
asIScriptFunction * potato::modding::angel_script_runtime::find_function(const std::string &mod_id, mod_side runtime_side, const std::string &declaration) const
~~~

**Access:** public  **Returns:** ``asIScriptFunction *``  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters**

- `mod_id` (`const std::string &`): Value supplied for the mod_id parameter.
- `runtime_side` (`mod_side`): Value supplied for the runtime_side parameter.
- `declaration` (`const std::string &`): Value supplied for the declaration parameter.

### initialize

~~~cpp
bool potato::modding::angel_script_runtime::initialize(script_log_sink log_sink, std::string *error=nullptr)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the initialize operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `log_sink` (`script_log_sink`): Value supplied for the log_sink parameter.
- `error` (`std::string *`): Value supplied for the error parameter.

### initialized

~~~cpp
bool potato::modding::angel_script_runtime::initialized() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### line_budget

~~~cpp
std::size_t potato::modding::angel_script_runtime::line_budget() const
~~~

**Access:** public  **Returns:** ``std::size_t``  **Engine version:** Potato Engine 1.0.0

Performs the line budget operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### module_key

~~~cpp
static std::string potato::modding::angel_script_runtime::module_key(const std::string &mod_id, mod_side side)
~~~

**Access:** private  **Storage:** static  **Returns:** ``std::string``  **Engine version:** Potato Engine 1.0.0

Performs the module key operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `mod_id` (`const std::string &`): Value supplied for the mod_id parameter.
- `side` (`mod_side`): Value supplied for the side parameter.

### operator=

~~~cpp
angel_script_runtime & potato::modding::angel_script_runtime::operator=(const angel_script_runtime &)=delete
~~~

**Access:** public  **Returns:** `angel_script_runtime &`  **Engine version:** Potato Engine 1.0.0

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const angel_script_runtime &`): Value supplied for the  parameter.

### set_line_budget

~~~cpp
void potato::modding::angel_script_runtime::set_line_budget(std::size_t value)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `value` (`std::size_t`): Value supplied for the value parameter.

### shutdown

~~~cpp
void potato::modding::angel_script_runtime::shutdown()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### write_log

~~~cpp
void potato::modding::angel_script_runtime::write_log(script_log_level level, const std::string &category, const std::string &message) const
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs the write log operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `level` (`script_log_level`): Value supplied for the level parameter.
- `category` (`const std::string &`): Value supplied for the category parameter.
- `message` (`const std::string &`): Value supplied for the message parameter.

### Header usage example

~~~cpp
potato::modding::angel_script_runtime runtime;
runtime.initialize(log_sink);
runtime.set_line_budget(10000);
~~~

## mod_service.h

### config

~~~cpp
const mod_service_config & potato::modding::mod_service::config() const
~~~

**Access:** public  **Returns:** `const mod_service_config &`  **Engine version:** Potato Engine 1.0.0

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### discover

~~~cpp
bool potato::modding::mod_service::discover(const mod_service_config &config, std::string *error=nullptr)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

- `config` (`const mod_service_config &`): Value supplied for the config parameter.
- `error` (`std::string *`): Value supplied for the error parameter.

### discovered

~~~cpp
bool potato::modding::mod_service::discovered() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### failed

~~~cpp
bool potato::modding::mod_service::failed() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

### manager

~~~cpp
const mod_manager & potato::modding::mod_service::manager() const
~~~

**Access:** public  **Returns:** `const mod_manager &`  **Engine version:** Potato Engine 1.0.0

Performs the manager operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### runtime_side

~~~cpp
mod_side potato::modding::mod_service::runtime_side() const
~~~

**Access:** public  **Returns:** `mod_side`  **Engine version:** Potato Engine 1.0.0

Performs the runtime side operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### script_runtime

~~~cpp
angel_script_runtime & potato::modding::mod_service::script_runtime()
~~~

**Access:** public  **Returns:** `angel_script_runtime &`  **Engine version:** Potato Engine 1.0.0

Performs the script runtime operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### script_runtime

~~~cpp
const angel_script_runtime & potato::modding::mod_service::script_runtime() const
~~~

**Access:** public  **Returns:** `const angel_script_runtime &`  **Engine version:** Potato Engine 1.0.0

Performs the script runtime operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### scripts_started

~~~cpp
bool potato::modding::mod_service::scripts_started() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the scripts started operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### shutdown_scripts

~~~cpp
void potato::modding::mod_service::shutdown_scripts()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### start_scripts

~~~cpp
bool potato::modding::mod_service::start_scripts(mod_side runtime_side, script_log_sink log_sink, script_api_registrar register_script_api, mod_export_registrar register_mod_exports, std::string *error=nullptr)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters**

- `runtime_side` (`mod_side`): Value supplied for the runtime_side parameter.
- `log_sink` (`script_log_sink`): Value supplied for the log_sink parameter.
- `register_script_api` (`script_api_registrar`): Value supplied for the register_script_api parameter.
- `register_mod_exports` (`mod_export_registrar`): Value supplied for the register_mod_exports parameter.
- `error` (`std::string *`): Value supplied for the error parameter.

### Header usage example

~~~cpp
potato::modding::mod_service service;
service.discover(config);
~~~









