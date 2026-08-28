# Save_Game

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `save_game.h`  
**Documented overloads:** 7

This page documents the engine-owned callables declared for `Save_Game`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Save_Game::save_current("saves/slot1.bin");
Save_Game::load_and_apply("saves/slot1.bin");
~~~

## Functions

### apply_snapshot

~~~cpp
bool Save_Game::apply_snapshot(const Snapshot &snapshot)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Applies the requested state change to the target object or service. Validate target pointers and preconditions before invoking the operation.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `snapshot` | `const Snapshot &` | Value supplied for the snapshot parameter. | — |


---

### capture_current

~~~cpp
Snapshot Save_Game::capture_current()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Snapshot`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters:** None.

---

### capture_object

~~~cpp
Object_State Save_Game::capture_object(const Object &object)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Object_State`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `object` | `const Object &` | Value supplied for the object parameter. | — |


---

### load_and_apply

~~~cpp
bool Save_Game::load_and_apply(const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_snapshot

~~~cpp
bool Save_Game::load_snapshot(const std::string &path, Snapshot &out_snapshot)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Reads, validates, or prepares the requested resource from the supplied input. Use the return value or error output to detect a failed operation before using the result.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `out_snapshot` | `Snapshot &` | Value supplied for the out_snapshot parameter. | — |


---

### save_current

~~~cpp
bool Save_Game::save_current(const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### save_snapshot

~~~cpp
bool Save_Game::save_snapshot(const Snapshot &snapshot, const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `snapshot` | `const Snapshot &` | Value supplied for the snapshot parameter. | — |


