# potato::modding::mod_manager

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `mod_manifest.h`  
**Documented overloads:** 12

This page documents the engine-owned callables declared for `potato::modding::mod_manager`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
potato::modding::mod_manager mods;
mods.discover("mods", "1.0.0");
~~~

## Functions

### applies_to

~~~cpp
static bool potato::modding::mod_manager::applies_to(mod_side declared_side, mod_side runtime_side)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `bool`

Performs the applies to operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `declared_side` | `mod_side` | Value supplied for the declared_side parameter. | — |
| `runtime_side` | `mod_side` | Value supplied for the runtime_side parameter. | — |


---

### canonical_name

~~~cpp
static std::string potato::modding::mod_manager::canonical_name(const std::string &value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `std::string`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### content_paths

~~~cpp
std::vector< std::filesystem::path > potato::modding::mod_manager::content_paths(const std::string &group, mod_side runtime_side) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< std::filesystem::path >`

Performs the content paths operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `runtime_side` | `mod_side` | Value supplied for the runtime_side parameter. | — |


---

### discover

~~~cpp
bool potato::modding::mod_manager::discover(const std::filesystem::path &mods_path, const std::string &expected_game_api_version, std::string *error=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### empty

~~~cpp
bool potato::modding::mod_manager::empty() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### exports

~~~cpp
const std::vector< mod_export > * potato::modding::mod_manager::exports(const mod_manifest &manifest, const std::string &group) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::vector< mod_export > *`

Performs the exports operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `manifest` | `const mod_manifest &` | Value supplied for the manifest parameter. | — |


---

### is_snake_case

~~~cpp
static bool potato::modding::mod_manager::is_snake_case(const std::string &value)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### mods

~~~cpp
const std::vector< mod_manifest > & potato::modding::mod_manager::mods() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::vector< mod_manifest > &`

Performs the mods operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### qualified_id

~~~cpp
static std::string potato::modding::mod_manager::qualified_id(const std::string &mod_id, const std::string &local_id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `std::string`

Performs the qualified id operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### root_path

~~~cpp
const std::filesystem::path & potato::modding::mod_manager::root_path() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::filesystem::path &`

Performs the root path operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### script_paths

~~~cpp
std::vector< std::filesystem::path > potato::modding::mod_manager::script_paths(const mod_manifest &manifest, mod_side runtime_side) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< std::filesystem::path >`

Performs the script paths operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `manifest` | `const mod_manifest &` | Value supplied for the manifest parameter. | — |
| `runtime_side` | `mod_side` | Value supplied for the runtime_side parameter. | — |


---

### shared_mod_hash

~~~cpp
std::string potato::modding::mod_manager::shared_mod_hash() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::string`

Performs the shared mod hash operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

