# functionality_trigger

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `functionality_trigger.h`  
**Documented overloads:** 4

This page documents the engine-owned callables declared for `functionality_trigger`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Functionality_Trigger::register_source(owner, source);
Functionality_Trigger::unregister_sources(owner);
~~~

## Functions

### clear

~~~cpp
void functionality_trigger::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### evaluate

~~~cpp
bool functionality_trigger::evaluate(const std::string &trigger_id, const trigger_context &context={})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the evaluate operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `context` | `const trigger_context &` | Value supplied for the context parameter. | — |


---

### register_source

~~~cpp
bool functionality_trigger::register_source(const std::string &trigger_id, const void *owner, trigger_source source)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `source` | `trigger_source` | Value supplied for the source parameter. | — |


---

### unregister_sources

~~~cpp
void functionality_trigger::unregister_sources(const void *owner)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.



