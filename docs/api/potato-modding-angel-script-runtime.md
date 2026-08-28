# potato::modding::angel_script_runtime

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `angel_script_runtime.h`  
**Documented overloads:** 15

This page documents the engine-owned callables declared for `potato::modding::angel_script_runtime`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
potato::modding::angel_script_runtime runtime;
runtime.initialize(log_sink);
runtime.set_line_budget(10000);
~~~

## Functions

### ~angel_script_runtime

~~~cpp
potato::modding::angel_script_runtime::~angel_script_runtime()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### angel_script_runtime

~~~cpp
potato::modding::angel_script_runtime::angel_script_runtime() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Performs the angel script runtime operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### angel_script_runtime

~~~cpp
potato::modding::angel_script_runtime::angel_script_runtime(const angel_script_runtime &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Performs the angel script runtime operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### build_mod

~~~cpp
bool potato::modding::angel_script_runtime::build_mod(const mod_manifest &manifest, const std::vector< std::filesystem::path > &script_paths, mod_side runtime_side, std::string *error=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `manifest` | `const mod_manifest &` | Value supplied for the manifest parameter. | — |
| `runtime_side` | `mod_side` | Value supplied for the runtime_side parameter. | — |


---

### engine

~~~cpp
asIScriptEngine * potato::modding::angel_script_runtime::engine() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `asIScriptEngine *`

Performs the engine operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### execute

~~~cpp
bool potato::modding::angel_script_runtime::execute(asIScriptFunction *function, const std::vector< void * > &object_arguments={}, std::string *error=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the execute operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### find_function

~~~cpp
asIScriptFunction * potato::modding::angel_script_runtime::find_function(const std::string &mod_id, mod_side runtime_side, const std::string &declaration) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `asIScriptFunction *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `runtime_side` | `mod_side` | Value supplied for the runtime_side parameter. | — |


---

### initialize

~~~cpp
bool potato::modding::angel_script_runtime::initialize(script_log_sink log_sink, std::string *error=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the initialize operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `log_sink` | `script_log_sink` | Value supplied for the log_sink parameter. | — |


---

### initialized

~~~cpp
bool potato::modding::angel_script_runtime::initialized() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### line_budget

~~~cpp
std::size_t potato::modding::angel_script_runtime::line_budget() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Performs the line budget operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### module_key

~~~cpp
static std::string potato::modding::angel_script_runtime::module_key(const std::string &mod_id, mod_side side)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Storage:** static · **Returns:** `std::string`

Performs the module key operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `side` | `mod_side` | Value supplied for the side parameter. | — |


---

### operator=

~~~cpp
angel_script_runtime & potato::modding::angel_script_runtime::operator=(const angel_script_runtime &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `angel_script_runtime &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_line_budget

~~~cpp
void potato::modding::angel_script_runtime::set_line_budget(std::size_t value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### shutdown

~~~cpp
void potato::modding::angel_script_runtime::shutdown()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

---

### write_log

~~~cpp
void potato::modding::angel_script_runtime::write_log(script_log_level level, const std::string &category, const std::string &message) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the write log operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `level` | `script_log_level` | Value supplied for the level parameter. | — |



