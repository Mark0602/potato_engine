# Save_Pool

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `save_game.h`  
**Documented overloads:** 7

This page documents the engine-owned callables declared for `Save_Pool`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Save_Game::save_current("saves/slot1.bin");
Save_Game::load_and_apply("saves/slot1.bin");
~~~

## Functions

### add

~~~cpp
void Save_Pool::add(Object *object)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `object` | `Object *` | Value supplied for the object parameter. | — |


---

### capture_snapshot

~~~cpp
Save_Game::Snapshot Save_Pool::capture_snapshot() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Save_Game::Snapshot`

Serializes or captures the requested engine state. The destination and success reporting behavior follow the parameters and return type shown below.

**Parameters:** None.

---

### clear

~~~cpp
void Save_Pool::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### contains

~~~cpp
bool Save_Pool::contains(const Object *object) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Performs the contains operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `object` | `const Object *` | Value supplied for the object parameter. | — |


---

### empty

~~~cpp
bool Save_Pool::empty() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### get_all

~~~cpp
std::vector< Object * > Save_Pool::get_all() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Object * >`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### remove

~~~cpp
void Save_Pool::remove(Object *object)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `object` | `Object *` | Value supplied for the object parameter. | — |



