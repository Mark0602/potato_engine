# Tile

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `tileset.h`  
**Documented overloads:** 11

This page documents the engine-owned callables declared for `Tile`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Tilemap map;
map.load_json("assets/maps/level1.json");
map.set_tile(4, 3, 7);
~~~

## Functions

### draw

~~~cpp
void Tile::draw(SDL_Renderer *renderer, const Vec &size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the tile using its full texture.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `size` | `const Vec &` | Draw size in logical coordinates. | — |


---

### get_id

~~~cpp
int Tile::get_id() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Gets the numeric id of the tile.

**Parameters:** None.

---

### get_position

~~~cpp
Vec Tile::get_position() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the top-left position of the tile.

**Parameters:** None.

---

### get_texture

~~~cpp
Texture * Tile::get_texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Gets the texture assigned to the tile.

**Parameters:** None.

---

### is_collidable

~~~cpp
bool Tile::is_collidable() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks whether this tile is collidable.

**Parameters:** None.

---

### set_collidable

~~~cpp
void Tile::set_collidable(bool collidable)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets whether this tile is collidable.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_id

~~~cpp
void Tile::set_id(int id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the numeric id of the tile.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_position

~~~cpp
void Tile::set_position(const Vec &position)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the top-left position of the tile.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | New tile position in logical coordinates. | — |


---

### set_texture

~~~cpp
void Tile::set_texture(Texture *texture)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the texture assigned to the tile.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Borrowed pointer to the tile texture, or nullptr. | — |


---

### Tile

~~~cpp
Tile::Tile() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an empty tile.

**Parameters:** None.

---

### Tile

~~~cpp
Tile::Tile(int id, const Vec &position, Texture *texture=nullptr, bool collidable=false)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a tile with an id, position, texture and collision flag.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left position of the tile in logical coordinates. | — |
| `texture` | `Texture *` | Texture used by this tile. This is borrowed, not owned. | — |



