# Tileset

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `tileset.h`  
**Documented overloads:** 21

This page documents the engine-owned callables declared for `Tileset`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Tilemap map;
map.load_json("assets/maps/level1.json");
map.set_tile(4, 3, 7);
~~~

## Functions

### create_tile

~~~cpp
Tile Tileset::create_tile(int id, const Vec &position, bool collidable=false) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tile`

Creates a lightweight Tile using this tileset's texture.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left position for the tile. | — |


---

### draw

~~~cpp
void Tileset::draw(SDL_Renderer *renderer, int index, const Vec &position, const Vec &size, bool skip_when_transparent=true) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws a tile id at a position using a custom draw size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left draw position. | — |
| `size` | `const Vec &` | Destination draw size. | — |


---

### draw

~~~cpp
void Tileset::draw(SDL_Renderer *renderer, int index, const Vec &position) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws a tile id at a position using the default tile size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec &` | Top-left draw position. | — |


---

### draw_tile

~~~cpp
void Tileset::draw_tile(SDL_Renderer *renderer, const Tile &tile, const Vec &size) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws a Tile using the Tile id and position with a custom draw size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile` | `const Tile &` | Tile data to draw. | — |
| `size` | `const Vec &` | Destination draw size. | — |


---

### draw_tile

~~~cpp
void Tileset::draw_tile(SDL_Renderer *renderer, const Tile &tile) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws a Tile using the Tile id and position.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile` | `const Tile &` | Tile data to draw. | — |


---

### get_texture

~~~cpp
Texture * Tileset::get_texture() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Gets the texture atlas used by the tileset.

**Parameters:** None.

---

### get_tile_count

~~~cpp
std::size_t Tileset::get_tile_count() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::size_t`

Gets the number of indexed tiles in the tileset.

**Parameters:** None.

---

### get_tile_rect

~~~cpp
const SDL_FRect * Tileset::get_tile_rect(int index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const SDL_FRect *`

Gets the source rectangle for a tile id.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_tile_size

~~~cpp
Vec Tileset::get_tile_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the size of a single tile.

**Parameters:** None.

---

### get_tile_texture

~~~cpp
Texture * Tileset::get_tile_texture(int index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Gets the texture used for a specific tile id.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_tileset

~~~cpp
Tileset * Tileset::get_tileset()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tileset *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_tileset_size

~~~cpp
Vec Tileset::get_tileset_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Gets the grid size of the tileset.

**Parameters:** None.

---

### init

~~~cpp
void Tileset::init(Texture *whole_texture, const Vec &tile_size, const Vec &tileset_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Initializes or reinitializes the tileset.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `whole_texture` | `Texture *` | Borrowed pointer to the full atlas texture. | — |
| `tile_size` | `const Vec &` | Size of one tile in pixels/logical units. | — |
| `tileset_size` | `const Vec &` | Number of tiles in the atlas as columns and rows. | — |


---

### is_valid_index

~~~cpp
bool Tileset::is_valid_index(int index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if a tile id exists in the tileset.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_tileset

~~~cpp
Tileset * Tileset::load_tileset(const std::string &path, Logger *logger=nullptr, SDL_ScaleMode scale_mode=SDL_SCALEMODE_PIXELART)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Tileset *`

Performs the init operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |


---

### rebuild_tile_rects

~~~cpp
void Tileset::rebuild_tile_rects()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Rebuilds the cached source rectangles from tile size and grid size.

**Parameters:** None.

---

### set_texture

~~~cpp
void Tileset::set_texture(Texture *texture)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the texture atlas used by the tileset.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Borrowed pointer to the atlas texture, or nullptr. | — |


---

### set_tile_size

~~~cpp
void Tileset::set_tile_size(const Vec &tile_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the size of a single tile and rebuilds the source rectangles.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tile_size` | `const Vec &` | New tile size. | — |


---

### set_tileset_size

~~~cpp
void Tileset::set_tileset_size(const Vec &tileset_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the grid size of the tileset and rebuilds the source rectangles.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset_size` | `const Vec &` | New grid size as columns and rows. | — |


---

### Tileset

~~~cpp
Tileset::Tileset() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an empty tileset.

**Parameters:** None.

---

### Tileset

~~~cpp
Tileset::Tileset(Texture *whole_texture, const Vec &tile_size, const Vec &tileset_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a tileset from a texture atlas and grid information.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `whole_texture` | `Texture *` | Borrowed pointer to the full atlas texture. | — |
| `tile_size` | `const Vec &` | Size of one tile in pixels/logical units. | — |
| `tileset_size` | `const Vec &` | Number of tiles in the atlas as columns and rows. | — |



