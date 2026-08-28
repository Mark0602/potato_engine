# Tilemap

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `tileset.h`  
**Documented overloads:** 30

This page documents the engine-owned callables declared for `Tilemap`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Tilemap map;
map.load_json("assets/maps/level1.json");
map.set_tile(4, 3, 7);
~~~

## Functions

### cell_index

~~~cpp
std::size_t Tilemap::cell_index(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `std::size_t`

Adds or registers data with the owning engine service. The caller must keep borrowed objects valid for as long as the receiving service uses them.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### cell_to_world

~~~cpp
Vec Tilemap::cell_to_world(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Converts a cell's column and row indices to world coordinates.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### clear

~~~cpp
void Tilemap::clear()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Transforms the supplied value into the requested representation. The source value is preserved unless a non-const reference appears in the signature.

**Parameters:** None.

---

### create

~~~cpp
bool Tilemap::create(int width, int height, int empty_tile_id=-1, Vec origin={0.f, 0.f})
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Creates a new tilemap with the given dimensions and origin.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `origin` | `Vec` | Top-left position of the tilemap in world coordinates. | — |


---

### draw

~~~cpp
void Tilemap::draw(SDL_Renderer *renderer, const class Camera *camera=nullptr) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `camera` | `const class Camera *` | Value supplied for the camera parameter. | — |


---

### erase_tile

~~~cpp
bool Tilemap::erase_tile(int column, int row)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Erases a tile at the specified column and row, setting it to the empty tile id.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_cell_size

~~~cpp
Vec Tilemap::get_cell_size() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_cell_texture

~~~cpp
Texture * Tilemap::get_cell_texture(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Texture *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_height

~~~cpp
int Tilemap::get_height() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_last_error

~~~cpp
const std::string & Tilemap::get_last_error() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_origin

~~~cpp
Vec Tilemap::get_origin() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Vec`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_revision

~~~cpp
std::uint64_t Tilemap::get_revision() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `std::uint64_t`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_source_path

~~~cpp
const std::string & Tilemap::get_source_path() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const std::string &`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_tile

~~~cpp
int Tilemap::get_tile(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_tileset

~~~cpp
const Tileset * Tilemap::get_tileset() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `const Tileset *`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### get_width

~~~cpp
int Tilemap::get_width() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `int`

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters:** None.

---

### is_valid_cell

~~~cpp
bool Tilemap::is_valid_cell(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the specified column and row are valid cell coordinates in the tilemap.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### load_json

~~~cpp
bool Tilemap::load_json(const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Loads a tilemap from a JSON file.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### resize

~~~cpp
bool Tilemap::resize(int new_width, int new_height, int empty_tile_id=-1)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Resizes the tilemap to new dimensions, preserving existing tiles where possible.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### save_json

~~~cpp
bool Tilemap::save_json(const std::string &path)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Saves the tilemap to a JSON file.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_cell_size

~~~cpp
void Tilemap::set_cell_size(Vec cell_size)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs the resize operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `cell_size` | `Vec` | Value supplied for the cell_size parameter. | — |


---

### set_cell_texture

~~~cpp
bool Tilemap::set_cell_texture(int column, int row, Texture *texture)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `texture` | `Texture *` | Value supplied for the texture parameter. | — |


---

### set_origin

~~~cpp
void Tilemap::set_origin(Vec origin)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `origin` | `Vec` | Value supplied for the origin parameter. | — |


---

### set_tile

~~~cpp
bool Tilemap::set_tile(int column, int row, int tile_id)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_tileset

~~~cpp
void Tilemap::set_tileset(const Tileset *tileset)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Value supplied for the tileset parameter. | — |


---

### submit

~~~cpp
void Tilemap::submit(class Render_Pool &render_pool, uint8_t z_index=128, const class Camera *camera=nullptr, const Color &tint=Color::white(), bool camera_space=true, bool y_sort=true) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `render_pool` | `class Render_Pool &` | Value supplied for the render_pool parameter. | — |
| `camera` | `const class Camera *` | Value supplied for the camera parameter. | — |
| `tint` | `const Color &` | Value supplied for the tint parameter. | `Color::white()` |


---

### Tilemap

~~~cpp
Tilemap::Tilemap() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Tile value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Tilemap

~~~cpp
Tilemap::Tilemap(const Tileset *tileset)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Tilemap value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `tileset` | `const Tileset *` | Value supplied for the tileset parameter. | — |


---

### valid_cell

~~~cpp
bool Tilemap::valid_cell(int column, int row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `bool`

Constructs a Tileset value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### world_to_cell

~~~cpp
bool Tilemap::world_to_cell(const Vec &world_position, int &out_column, int &out_row) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Converts world coordinates to cell indices in the tilemap.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `world_position` | `const Vec &` | World coordinates to convert. | — |



