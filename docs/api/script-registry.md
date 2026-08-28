# script_registry

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `script-registry.h`  
**Documented overloads:** 4

This page documents the engine-owned callables declared for `script_registry`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
REGISTER_SCRIPT(PlayerScript);
~~~

## Functions

### create_all_scripts

~~~cpp
std::vector< script * > script_registry::create_all_scripts()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< script * >`

Creates all registered scripts and sorts them by execution_order(). Lower execution_order() values appear first. The caller takes ownership of the returned pointers.

**Parameters:** None.

---

### instance

~~~cpp
static script_registry & script_registry::instance()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Storage:** static · **Returns:** `script_registry &`

Performs the execution order operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### register_script

~~~cpp
void script_registry::register_script(script_factory factory)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Registers a factory function that creates one script instance. Called automatically by REGISTER_SCRIPT at startup.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `factory` | `script_factory` | A callable that returns a heap-allocated script*. | — |


---

### script_registry

~~~cpp
script_registry::script_registry() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** None.


