# Tileset_Group

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `tileset.h`  
**Documented overloads:** 11

This page documents the engine-owned callables declared for `Tileset_Group`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Tilemap map;
map.load_json("assets/maps/level1.json");
map.set_tile(4, 3, 7);
~~~

## Functions

### add_index

~~~cpp
void Tileset_Group::add_index(int index)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Adds one tile id to the group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### clear_indexes

~~~cpp
void Tileset_Group::clear_indexes()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Clears all tile ids from the group.

**Parameters:** None.

---

### draw_group

~~~cpp
void Tileset_Group::draw_group(SDL_Renderer *renderer, const Vec &position, int columns) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the group wrapped into rows.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left position of the first tile. | — |


---

### draw_group

~~~cpp
void Tileset_Group::draw_group(SDL_Renderer *renderer, const Vec &position) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the group in one horizontal row.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left position of the first tile. | — |


---

### get_indexes

~~~cpp
std::vector< int > Tileset_Group::get_indexes() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::vector< int >`

Gets all tile ids in the group.

**Parameters:** None.

---

### get_tileset

~~~cpp
const Tileset * Tileset_Group::get_tileset() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Tileset *`

Gets the tileset used by the group.

**Parameters:** None.

---

### set_indexes

~~~cpp
void Tileset_Group::set_indexes(const std::vector< int > &indexes)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets all tile ids in the group.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_tileset

~~~cpp
void Tileset_Group::set_tileset(const Tileset *tileset)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the tileset used by the group.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Borrowed pointer to the tileset, or nullptr. | — |


---

### Tileset_Group

~~~cpp
Tileset_Group::Tileset_Group() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an empty group.

**Parameters:** None.

---

### Tileset_Group

~~~cpp
Tileset_Group::Tileset_Group(const Tileset *tileset, const std::vector< int > &indexes)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a group for a tileset with explicit tile indexes.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Borrowed pointer to the tileset used for drawing. | — |


---

### Tileset_Group

~~~cpp
Tileset_Group::Tileset_Group(const Tileset *tileset)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a group for a tileset with no explicit indexes.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Borrowed pointer to the tileset used for drawing. | — |



