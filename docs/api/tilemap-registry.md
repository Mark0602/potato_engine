# Tilemap_Registry

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `tileset.h`  
**Documented overloads:** 4

This page documents the engine-owned callables declared for `Tilemap_Registry`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Tilemap map;
map.load_json("assets/maps/level1.json");
map.set_tile(4, 3, 7);
~~~

## Functions

### add

~~~cpp
void Tilemap_Registry::add(const std::string &name, Tilemap *tilemap)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tilemap` | `Tilemap *` | Value supplied for the tilemap parameter. | — |


---

### get

~~~cpp
Tilemap * Tilemap_Registry::get(const std::string &name)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tilemap *`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### names

~~~cpp
std::vector< std::string > Tilemap_Registry::names()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< std::string >`

Performs the names operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

---

### remove

~~~cpp
void Tilemap_Registry::remove(const std::string &name, Tilemap *tilemap=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the rebuild tile rects operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tilemap` | `Tilemap *` | Value supplied for the tilemap parameter. | — |



