# Object_Pool

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `object.h`  
**Documented overloads:** 7

This page documents the engine-owned callables declared for `Object_Pool`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Object* player = new Object({0.0f, 0.0f}, {32.0f, 32.0f});
player->name = "player";
player->add_tag("controllable");
Engine::object_pool->add(player);
~~~

## Functions

### add

~~~cpp
void Object_Pool::add(Object *obj)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds an object to the pool.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to add. | — |


---

### find_all_by_tag

~~~cpp
std::vector< Object * > Object_Pool::find_all_by_tag(const std::string &tag) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Object * >`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### find_by_name

~~~cpp
Object * Object_Pool::find_by_name(const std::string &name) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Object *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### find_by_tag

~~~cpp
Object * Object_Pool::find_by_tag(const std::string &tag) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Object *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_all

~~~cpp
std::vector< Object * > Object_Pool::get_all() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< Object * >`

Returns a vector of all objects in the pool.

**Parameters:** None.

---

### Object_Pool

~~~cpp
Object_Pool::Object_Pool() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Object value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### remove

~~~cpp
void Object_Pool::remove(Object *obj)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes an object from the pool.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `obj` | `Object *` | Pointer to the Object to remove. | — |



