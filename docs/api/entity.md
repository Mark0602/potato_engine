# Entity

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `entity.h`  
**Documented overloads:** 12

This page documents the engine-owned callables declared for `Entity`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Entity enemy;
enemy.set_pos({240.0f, 120.0f});
enemy.activate();
~~~

## Functions

### ~Entity

~~~cpp
Entity::~Entity()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### activate

~~~cpp
void Entity::activate()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Activates the entity, allowing it to be updated and rendered.

**Parameters:** None.

---

### deactivate

~~~cpp
void Entity::deactivate()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Deactivates the entity, preventing it from being updated or rendered.

**Parameters:** None.

---

### Entity

~~~cpp
Entity::Entity() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

---

### Entity

~~~cpp
Entity::Entity(Transform t, Texture *tex=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Entity value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `t` | `Transform` | Value supplied for the t parameter. | — |
| `tex` | `Texture *` | Value supplied for the tex parameter. | `nullptr` |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | `nullptr` |
| `l` | `Logger *` | Value supplied for the l parameter. | `nullptr` |


---

### Entity

~~~cpp
Entity::Entity(Vec p, Vec s, Vec r={0.0f, 0.0f}, Texture *t=nullptr, Object_Pool *objp=nullptr, Logger *l=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Entity value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `p` | `Vec` | Value supplied for the p parameter. | — |
| `s` | `Vec` | Value supplied for the s parameter. | — |
| `r` | `Vec` | Value supplied for the r parameter. | — |
| `t` | `Texture *` | Value supplied for the t parameter. | `nullptr` |
| `objp` | `Object_Pool *` | Value supplied for the objp parameter. | `nullptr` |
| `l` | `Logger *` | Value supplied for the l parameter. | `nullptr` |


---

### free

~~~cpp
void Entity::free()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Frees the entity's resources and marks it as inactive. This method should be called when the entity is no longer needed to avoid memory leaks.

**Parameters:** None.

---

### get_pos

~~~cpp
Vec Entity::get_pos() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the position of the entity.

**Parameters:** None.

---

### get_texture

~~~cpp
Texture * Entity::get_texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Gets the size of the entity.

**Parameters:** None.

---

### is_alive

~~~cpp
bool Entity::is_alive() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the entity is alive based on its health and lifetime.

**Parameters:** None.

---

### set_pos

~~~cpp
void Entity::set_pos(const Vec &new_pos)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the position of the entity.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_pos` | `constVec &` | The new position to set for the entity. | — |


---

### set_texture

~~~cpp
void Entity::set_texture(Texture *new_texture)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the texture of the entity.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `new_texture` | `Texture *` | Pointer to the new texture to set for the entity. | — |



