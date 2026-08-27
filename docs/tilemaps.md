# Tiles and tilemaps

## Tile

`Tile` is lightweight data, not an `Object`. It stores an integer ID, world position, borrowed texture, and collidable flag. It can draw a full single-tile texture directly. The collidable flag is metadata; it does not automatically create physics bodies.

## Tileset

`Tileset` borrows a complete texture atlas plus a tile size and grid dimensions. It indexes cells row-major from zero and caches source rectangles and transparency information.

```cpp
Texture* atlas = Engine::asset_pool->get_texture("terrain");
Tileset terrain(atlas, {16.0f, 16.0f}, {8.0f, 8.0f});

terrain.draw(Engine::renderer, 5, {128.0f, 96.0f});
Tile tile = terrain.create_tile(5, {128.0f, 96.0f}, true);
```

The API can validate IDs, return their `SDL_FRect`, create `Tile` values, draw with default/custom size, and change the atlas/grid dimensions. The custom-size draw can skip fully transparent cells. `load_tileset(path)` creates and returns a dynamically allocated `Tileset`; prefer explicit texture/tileset ownership in new code so lifetime is unambiguous.

`Tileset_Group` stores a borrowed tileset and a reusable list of tile IDs. It draws them in one row or wraps them to a requested column count.

## Tilemap

`Tilemap` stores a rectangular grid of tile IDs. `EMPTY_TILE_ID` is `-1`. It borrows an optional tileset and may override individual cells with borrowed `Texture*` values.

Core operations include:

- `create`, `resize`, `clear`, `get_tile`, `set_tile`, and `erase_tile`;
- `get_cell_texture` and `set_cell_texture`;
- origin and fallback cell-size control;
- `cell_to_world`, `world_to_cell`, and coordinate validation;
- a monotonic revision value for change detection;
- `load_json`, `save_json`, source path, and last-error reporting;
- immediate `draw` or queued/batched `submit`.

`submit` accepts z-index, optional camera, tint, camera-space selection, and Y sorting. The tilemap builds geometry batches for atlas cells and submits texture overrides as appropriate. Use queued submission when integrating with normal object ordering and lighting.

## JSON format

```json
{
  "width": 4,
  "height": 3,
  "origin": [32, 48],
  "tileset_path": "assets/textures/terrain.png",
  "tiles": [
    [0, 1, 2, -1],
    [8, 9, 10, -1],
    [-1, -1, -1, -1]
  ]
}
```

Width and height must be positive integers matching the row count and row widths. Tile IDs must be `-1` or non-negative integers. `origin` is optional and defaults to zero. `tileset_path` is currently parsed for compatibility and written by `save_json`, but loading does not create or assign a `Tileset`; the caller must provide one separately.

Per-cell texture overrides are runtime-only and are not serialized by `save_json`.

## Registry

`Tilemap_Registry` is a non-owning, named process-wide registry for tools and systems that need to discover layers. `add(name, pointer)`, `get(name)`, `remove(name, optional_pointer)`, and `names()` manage entries. Removing or clearing a tilemap does not destroy it. Unregister every map before its lifetime ends.

