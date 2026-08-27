#ifndef TILESET_H
#define TILESET_H

#include <SDL3/SDL.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "texture.h"
#include "vec.h"

/**
 * @brief Lightweight tile data used by tile maps and tilesets.
 *
 * A Tile is intentionally not an Object. It only stores the minimum data needed
 * to identify and place a tile: a numeric id, a world position, an optional
 * texture pointer, and whether the tile should be considered collidable.
 */
class Tile {
public:
    /**
     * @brief Constructs an empty tile.
     */
    Tile() = default;

    /**
     * @brief Constructs a tile with an id, position, texture and collision flag.
     * @param id Numeric tile id. For atlas tiles this is usually the tileset index.
     * @param position Top-left position of the tile in logical coordinates.
     * @param texture Texture used by this tile. This is borrowed, not owned.
     * @param collidable Whether this tile should block movement or collision checks.
     */
    Tile(int id, const Vec& position, Texture* texture = nullptr, bool collidable = false);

    /**
     * @brief Gets the numeric id of the tile.
     * @return The tile id.
     */
    int get_id() const { return m_id; }

    /**
     * @brief Sets the numeric id of the tile.
     * @param id New tile id.
     */
    void set_id(int id) { m_id = id; }

    /**
     * @brief Gets the top-left position of the tile.
     * @return The tile position in logical coordinates.
     */
    Vec get_position() const { return m_position; }

    /**
     * @brief Sets the top-left position of the tile.
     * @param position New tile position in logical coordinates.
     */
    void set_position(const Vec& position) { m_position = position; }

    /**
     * @brief Gets the texture assigned to the tile.
     * @return Borrowed pointer to the tile texture, or nullptr.
     */
    Texture* get_texture() const { return m_texture; }

    /**
     * @brief Sets the texture assigned to the tile.
     * @param texture Borrowed pointer to the tile texture, or nullptr.
     */
    void set_texture(Texture* texture) { m_texture = texture; }

    /**
     * @brief Checks whether this tile is collidable.
     * @return True if the tile should be considered collidable.
     */
    bool is_collidable() const { return m_collidable; }

    /**
     * @brief Sets whether this tile is collidable.
     * @param collidable New collision flag.
     */
    void set_collidable(bool collidable) { m_collidable = collidable; }

    /**
     * @brief Draws the tile using its full texture.
     * @param renderer SDL renderer used for drawing.
     * @param size Draw size in logical coordinates.
     *
     * This is useful when the tile texture is already a single-tile texture.
     * For atlas-based drawing, prefer Tileset::draw_tile().
     */
    void draw(SDL_Renderer* renderer, const Vec& size) const;

private:
    int m_id = -1;
    Vec m_position = {0.0f, 0.0f};
    Texture* m_texture = nullptr;
    bool m_collidable = false;
};

/**
 * @brief Manages drawing tile ids from a larger tileset texture.
 *
 * Tileset treats the source texture as a complete grid of equal-sized tiles.
 * Tile ids are generated from left to right, top to bottom, starting at 0.
 * The Tileset does not own the texture; it only borrows it.
 */
class Tileset {
public:
    /**
     * @brief Constructs an empty tileset.
     */
    Tileset() = default;

    /**
     * @brief Constructs a tileset from a texture atlas and grid information.
     * @param whole_texture Borrowed pointer to the full atlas texture.
     * @param tile_size Size of one tile in pixels/logical units.
     * @param tileset_size Number of tiles in the atlas as columns and rows.
     */
    Tileset(Texture* whole_texture, const Vec& tile_size, const Vec& tileset_size);

    /**
     * @brief Initializes or reinitializes the tileset.
     * @param whole_texture Borrowed pointer to the full atlas texture.
     * @param tile_size Size of one tile in pixels/logical units.
     * @param tileset_size Number of tiles in the atlas as columns and rows.
     */
    void init(Texture* whole_texture, const Vec& tile_size, const Vec& tileset_size);

    /**
     * @brief Gets the texture atlas used by the tileset.
     * @return Borrowed pointer to the atlas texture, or nullptr.
     */
    Texture* get_texture() const { return m_whole_texture; }

    /**
     * @brief Sets the texture atlas used by the tileset.
     * @param texture Borrowed pointer to the atlas texture, or nullptr.
     */
    void set_texture(Texture* texture) { m_whole_texture = texture; }

    /**
     * @brief Gets the size of a single tile.
     * @return Tile size as width and height.
     */
    Vec get_tile_size() const { return m_tile_size; }

    /**
     * @brief Sets the size of a single tile and rebuilds the source rectangles.
     * @param tile_size New tile size.
     */
    void set_tile_size(const Vec& tile_size);

    /**
     * @brief Gets the grid size of the tileset.
     * @return Tileset size as columns and rows.
     */
    Vec get_tileset_size() const { return m_tileset_size; }

    /**
     * @brief Sets the grid size of the tileset and rebuilds the source rectangles.
     * @param tileset_size New grid size as columns and rows.
     */
    void set_tileset_size(const Vec& tileset_size);

    /**
     * @brief Gets the number of indexed tiles in the tileset.
     * @return Total number of source rectangles.
     */
    std::size_t get_tile_count() const { return m_tile_rects.size(); }

    /**
     * @brief Checks if a tile id exists in the tileset.
     * @param index Tile id/index to check.
     * @return True if the index is inside the generated tile range.
     */
    bool is_valid_index(int index) const;

    /**
     * @brief Gets the source rectangle for a tile id.
     * @param index Tile id/index to query.
     * @return Pointer to the source rectangle, or nullptr if the index is invalid.
     */
    const SDL_FRect* get_tile_rect(int index) const;

    /**
     * @brief Creates a lightweight Tile using this tileset's texture.
     * @param id Tile id/index inside the tileset.
     * @param position Top-left position for the tile.
     * @param collidable Whether the tile should be considered collidable.
     * @return A Tile data object. It is not registered with any object pool.
     */
    Tile create_tile(int id, const Vec& position, bool collidable = false) const;

    /**
     * @brief Draws a tile id at a position using the default tile size.
     * @param renderer SDL renderer used for drawing.
     * @param index Tile id/index inside the tileset.
     * @param position Top-left draw position.
     */
    void draw(SDL_Renderer* renderer, int index, const Vec& position) const;

    /**
     * @brief Draws a tile id at a position using a custom draw size.
     * @param renderer SDL renderer used for drawing.
     * @param index Tile id/index inside the tileset.
     * @param position Top-left draw position.
     * @param size Destination draw size.
     */
    void draw(SDL_Renderer* renderer, int index, const Vec& position, const Vec& size, bool skip_when_transparent = true) const;

    /**
     * @brief Draws a Tile using the Tile id and position.
     * @param renderer SDL renderer used for drawing.
     * @param tile Tile data to draw.
     */
    void draw_tile(SDL_Renderer* renderer, const Tile& tile) const;

    /**
     * @brief Draws a Tile using the Tile id and position with a custom draw size.
     * @param renderer SDL renderer used for drawing.
     * @param tile Tile data to draw.
     * @param size Destination draw size.
     */
    void draw_tile(SDL_Renderer* renderer, const Tile& tile, const Vec& size) const;

    /**
     * @brief Gets the texture used for a specific tile id.
     * @param index Tile id/index inside the tileset.
     * @return Borrowed pointer to the atlas texture, or nullptr if the index is invalid
     */
    Texture* get_tile_texture(int index) const {
        if (!is_valid_index(index)) {
            return nullptr;
        }
        return m_whole_texture;
    }

    Tileset* get_tileset() { return this; }

    Tileset* load_tileset(const std::string& path, Logger* logger = nullptr, SDL_ScaleMode scale_mode = SDL_SCALEMODE_PIXELART);

private:
    Texture* m_whole_texture = nullptr;
    Vec m_tile_size = {0.0f, 0.0f};
    Vec m_tileset_size = {0.0f, 0.0f};
    std::vector<SDL_FRect> m_tile_rects;
    std::vector<bool> m_transparent_flags;
    
    //Texture* m_whole_texture = nullptr;
    //Vec m_tile_size = {0.0f, 0.0f};
    //Vec m_tileset_size = {0.0f, 0.0f};
    //bool m_skip_when_transparent = false;

    /**
     * @brief Rebuilds the cached source rectangles from tile size and grid size.
     */
    void rebuild_tile_rects();
};

/**
 * @brief Stores a reusable group of tile ids from one tileset.
 *
 * Tileset_Group is useful for drawing several adjacent tile ids, for example
 * when previewing a multi-tile decoration or grouping animation frames.
 */
class Tileset_Group {
public:
    /**
     * @brief Constructs an empty group.
     */
    Tileset_Group() = default;

    /**
     * @brief Constructs a group for a tileset with no explicit indexes.
     * @param tileset Borrowed pointer to the tileset used for drawing.
     */
    explicit Tileset_Group(const Tileset* tileset);

    /**
     * @brief Constructs a group for a tileset with explicit tile indexes.
     * @param tileset Borrowed pointer to the tileset used for drawing.
     * @param indexes Tile ids contained by this group.
     */
    Tileset_Group(const Tileset* tileset, const std::vector<int>& indexes);

    /**
     * @brief Gets all tile ids in the group.
     * @return Copy of the tile id list.
     */
    std::vector<int> get_indexes() const { return m_indexes; }

    /**
     * @brief Sets all tile ids in the group.
     * @param indexes New tile id list.
     */
    void set_indexes(const std::vector<int>& indexes) { m_indexes = indexes; }

    /**
     * @brief Adds one tile id to the group.
     * @param index Tile id to append.
     */
    void add_index(int index) { m_indexes.push_back(index); }

    /**
     * @brief Clears all tile ids from the group.
     */
    void clear_indexes() { m_indexes.clear(); }

    /**
     * @brief Gets the tileset used by the group.
     * @return Borrowed pointer to the tileset, or nullptr.
     */
    const Tileset* get_tileset() const { return m_tileset; }

    /**
     * @brief Sets the tileset used by the group.
     * @param tileset Borrowed pointer to the tileset, or nullptr.
     */
    void set_tileset(const Tileset* tileset) { m_tileset = tileset; }

    /**
     * @brief Draws the group in one horizontal row.
     * @param renderer SDL renderer used for drawing.
     * @param position Top-left position of the first tile.
     */
    void draw_group(SDL_Renderer* renderer, const Vec& position) const;

    /**
     * @brief Draws the group wrapped into rows.
     * @param renderer SDL renderer used for drawing.
     * @param position Top-left position of the first tile.
     * @param columns Number of columns before wrapping to the next row.
     */
    void draw_group(SDL_Renderer* renderer, const Vec& position, int columns) const;

private:
    const Tileset* m_tileset = nullptr;
    std::vector<int> m_indexes;
};

class Tilemap {
public:
    static constexpr int EMPTY_TILE_ID = -1;

    Tilemap() = default;
    explicit Tilemap(const Tileset* tileset) : m_tileset(tileset) {}

    void set_tileset(const Tileset* tileset) { m_tileset = tileset; }
    const Tileset* get_tileset() const { return m_tileset; }

    /**
     * @brief Loads a tilemap from a JSON file.
     * @param path File path to the JSON tilemap.
     * @return True if the tilemap was successfully loaded, false otherwise.
     */
    bool load_json(const std::string& path);

    /** Draws all non-empty cells. Pass the active camera for world-space rendering. */
    void draw(SDL_Renderer* renderer, const class Camera* camera = nullptr) const;

    /** Queues all non-empty atlas or texture-override cells for rendering. */
    void submit(class Render_Pool& render_pool, uint8_t z_index = 128,
                const class Camera* camera = nullptr,
                const Color& tint = Color::white(),
                bool camera_space = true,
                bool y_sort = true) const;

    int get_width() const { return m_width; }
    int get_height() const { return m_height; }
    Vec get_origin() const { return m_origin; }
    void set_origin(Vec origin) { m_origin = origin; ++m_revision; }
    Vec get_cell_size() const {
        return m_tileset ? m_tileset->get_tile_size() : m_cell_size;
    }
    void set_cell_size(Vec cell_size) {
        if (cell_size.x > 0.0f && cell_size.y > 0.0f) {
            m_cell_size = cell_size;
            ++m_revision;
        }
    }
    std::uint64_t get_revision() const { return m_revision; }
    const std::string& get_last_error() const { return m_last_error; }
    const std::string& get_source_path() const { return m_source_path; }

    int get_tile(int column, int row) const;
    bool set_tile(int column, int row, int tile_id);
    Texture* get_cell_texture(int column, int row) const;
    bool set_cell_texture(int column, int row, Texture* texture);
    void clear();

    // ---- Editor functions ----

    /**
     * @brief Creates a new tilemap with the given dimensions and origin.
     * @param width Number of columns in the tilemap.
     * @param height Number of rows in the tilemap.
     * @param empty_tile_id Tile id to use for empty cells. This is usually -1.
     * @param origin Top-left position of the tilemap in world coordinates.
     * @return True if the tilemap was successfully created, false otherwise.
     * @attention THIS IS AN EDITOR FUNCTION.
     */
    bool create(int width, int height, int empty_tile_id = -1, Vec origin = {0.f, 0.f});

    /**
     * @brief Resizes the tilemap to new dimensions, preserving existing tiles where possible.
     * @param new_width New number of columns in the tilemap.
     * @param new_height New number of rows in the tilemap.
     * @param empty_tile_id Tile id to use for new empty cells. This is usually -1.
     * @return True if the tilemap was successfully resized, false otherwise.
     * @attention THIS IS AN EDITOR FUNCTION.
     */
    bool resize(int new_width, int new_height, int empty_tile_id = -1);

    /**
     * @brief Saves the tilemap to a JSON file.
     * @param path File path to save the tilemap.
     * @return True if the tilemap was successfully saved, false otherwise.
     * @attention THIS IS AN EDITOR FUNCTION.
     */
    bool save_json(const std::string& path);

    /**
     * @brief Erases a tile at the specified column and row, setting it to the empty tile id.
     * @param column Column index of the tile to erase.
     * @param row Row index of the tile to erase.
     * @return True if the tile was successfully erased, false otherwise.
     * @attention THIS IS AN EDITOR FUNCTION.
     */
    bool erase_tile(int column, int row) { return set_tile(column, row, -1); }

    /**
     * @brief Checks if the specified column and row are valid cell coordinates in the tilemap.
     * @param column Column index to check.
     * @param row Row index to check.
     * @return True if the cell coordinates are valid, false otherwise.
     * @attention THIS IS AN EDITOR FUNCTION.
     */
    bool is_valid_cell(int column, int row) const { return valid_cell(column, row); }

    /**
     * @brief Converts a cell's column and row indices to world coordinates.
     * @param column Column index of the cell.
     * @param row Row index of the cell.
     * @return World coordinates of the top-left corner of the specified cell.
     * @attention THIS IS AN EDITOR FUNCTION.
     */
    Vec cell_to_world(int column, int row) const {
        const Vec cell_size = get_cell_size();
        return m_origin + Vec(static_cast<float>(column) * cell_size.x,
                              static_cast<float>(row) * cell_size.y);
    }

    /**
     * @brief Converts world coordinates to cell indices in the tilemap.
     * @param world_position World coordinates to convert.
     * @param out_column Output parameter for the column index.
     * @param out_row Output parameter for the row index.
     * @return True if the world position corresponds to a valid cell, false otherwise.
     * @attention THIS IS AN EDITOR FUNCTION.
     */
    bool world_to_cell(const Vec& world_position, int& out_column, int& out_row) const {
        const Vec cell_size = get_cell_size();
        if (cell_size.x <= 0.0f || cell_size.y <= 0.0f) return false;
        Vec relative = world_position - m_origin;
        int column = static_cast<int>(relative.x / cell_size.x);
        int row = static_cast<int>(relative.y / cell_size.y);
        if (!valid_cell(column, row)) return false;
        out_column = column;
        out_row = row;
        return true;
    }

private:
    const Tileset* m_tileset = nullptr;
    int m_width = 0;
    int m_height = 0;
    Vec m_origin = {0.f, 0.f};
    Vec m_cell_size = {0.f, 0.f};
    std::vector<int> m_tiles;
    std::vector<Texture*> m_cell_textures;
    std::string m_last_error;
    std::string m_source_path;
    std::uint64_t m_revision = 0;
    mutable std::vector<SDL_Vertex> m_batch_vertices;
    mutable std::vector<int> m_batch_indices;

    bool valid_cell(int column, int row) const;

    std::size_t cell_index(int column, int row) const {
        return static_cast<std::size_t>(row * m_width + column);
    }
};

/** Runtime registry used by tools to discover named tilemap layers. */
namespace Tilemap_Registry {
    void add(const std::string& name, Tilemap* tilemap);
    void remove(const std::string& name, Tilemap* tilemap = nullptr);
    Tilemap* get(const std::string& name);
    std::vector<std::string> names();
}

#endif
