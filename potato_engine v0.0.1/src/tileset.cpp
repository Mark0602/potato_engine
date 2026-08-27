#include "tileset.h"
#include "camera.h"
#include "render.h"

#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <limits>
#include <unordered_map>

namespace {
class Tilemap_Json_Reader {
public:
    explicit Tilemap_Json_Reader(const std::string& text) : text(text) {}

    bool consume(char expected) {
        skip_whitespace();
        if (position >= text.size() || text[position] != expected) return false;
        ++position;
        return true;
    }

    bool peek(char expected) {
        skip_whitespace();
        return position < text.size() && text[position] == expected;
    }

    bool at_end() {
        skip_whitespace();
        return position == text.size();
    }

    bool read_string(std::string& output) {
        skip_whitespace();
        if (position >= text.size() || text[position++] != '"') return false;
        output.clear();
        while (position < text.size()) {
            const char character = text[position++];
            if (character == '"') return true;
            if (character == '\\') {
                if (position >= text.size()) return false;
                const char escaped = text[position++];
                switch (escaped) {
                    case '"': output.push_back('"'); break;
                    case '\\': output.push_back('\\'); break;
                    case '/': output.push_back('/'); break;
                    case 'b': output.push_back('\b'); break;
                    case 'f': output.push_back('\f'); break;
                    case 'n': output.push_back('\n'); break;
                    case 'r': output.push_back('\r'); break;
                    case 't': output.push_back('\t'); break;
                    default: return false;
                }
            } else {
                output.push_back(character);
            }
        }
        return false;
    }

    bool read_number(double& output) {
        skip_whitespace();
        if (position >= text.size()) return false;
        const char* start = text.c_str() + position;
        char* end = nullptr;
        output = std::strtod(start, &end);
        if (end == start) return false;
        position += static_cast<std::size_t>(end - start);
        return std::isfinite(output);
    }

    bool read_integer(std::int64_t& output) {
        double number = 0.0;
        if (!read_number(number) || std::floor(number) != number ||
            number < static_cast<double>(std::numeric_limits<std::int64_t>::min()) ||
            number > static_cast<double>(std::numeric_limits<std::int64_t>::max())) return false;
        output = static_cast<std::int64_t>(number);
        return true;
    }

    bool skip_value() {
        skip_whitespace();
        if (position >= text.size()) return false;
        if (text[position] == '"') {
            std::string ignored;
            return read_string(ignored);
        }
        if (text[position] == '[') {
            ++position;
            if (peek(']')) return consume(']');
            do {
                if (!skip_value()) return false;
                if (consume(']')) return true;
            } while (consume(','));
            return false;
        }
        if (text[position] == '{') {
            ++position;
            if (peek('}')) return consume('}');
            do {
                std::string key;
                if (!read_string(key) || !consume(':') || !skip_value()) return false;
                if (consume('}')) return true;
            } while (consume(','));
            return false;
        }
        for (const char* literal : {"true", "false", "null"}) {
            const std::size_t length = std::char_traits<char>::length(literal);
            if (text.compare(position, length, literal) == 0) {
                position += length;
                return true;
            }
        }
        double ignored = 0.0;
        return read_number(ignored);
    }

private:
    const std::string& text;
    std::size_t position = 0;

    void skip_whitespace() {
        while (position < text.size() &&
               std::isspace(static_cast<unsigned char>(text[position]))) ++position;
    }
};
}

Tile::Tile(int id, const Vec& position, Texture* texture, bool collidable)
    : m_id(id), m_position(position), m_texture(texture), m_collidable(collidable) {}

void Tile::draw(SDL_Renderer* renderer, const Vec& size) const {
    if (!renderer || !m_texture) {
        return;
    }

    m_texture->draw(renderer, m_position, size);
}

Tileset::Tileset(Texture* whole_texture, const Vec& tile_size, const Vec& tileset_size) {
    init(whole_texture, tile_size, tileset_size);
}

void Tileset::init(Texture* whole_texture, const Vec& tile_size, const Vec& tileset_size) {
    m_whole_texture = whole_texture;
    m_tile_size = tile_size;
    m_tileset_size = tileset_size;
    rebuild_tile_rects();
}

void Tileset::set_tile_size(const Vec& tile_size) {
    m_tile_size = tile_size;
    rebuild_tile_rects();
}

void Tileset::set_tileset_size(const Vec& tileset_size) {
    m_tileset_size = tileset_size;
    rebuild_tile_rects();
}

bool Tileset::is_valid_index(int index) const {
    return index >= 0 && static_cast<std::size_t>(index) < m_tile_rects.size();
}

const SDL_FRect* Tileset::get_tile_rect(int index) const {
    if (!is_valid_index(index)) {
        return nullptr;
    }

    return &m_tile_rects[static_cast<std::size_t>(index)];
}

Tile Tileset::create_tile(int id, const Vec& position, bool collidable) const {
    return Tile(id, position, m_whole_texture, collidable);
}

void Tileset::draw(SDL_Renderer* renderer, int index, const Vec& position) const {
    draw(renderer, index, position, m_tile_size, true);
}

void Tileset::draw(SDL_Renderer* renderer, int index, const Vec& position, const Vec& size, bool skip_when_transparent) const {
    if (!renderer || !m_whole_texture) {
        return;
    }

    if (index < 0 ||
        static_cast<std::size_t>(index) >= m_tile_rects.size() ||
        static_cast<std::size_t>(index) >= m_transparent_flags.size()) {
        return;
    }

    const std::size_t tile_index = static_cast<std::size_t>(index);

    if (skip_when_transparent && m_transparent_flags[tile_index]) {
        return;
    }

    const SDL_FRect* src = get_tile_rect(index);
    if (!src) {
        return;
    }

    const SDL_FRect dst = {
        position.x,
        position.y,
        size.x,
        size.y
    };

    m_whole_texture->draw(renderer, src, &dst);
}

void Tileset::draw_tile(SDL_Renderer* renderer, const Tile& tile) const {
    draw(renderer, tile.get_id(), tile.get_position(), m_tile_size);
}

void Tileset::draw_tile(SDL_Renderer* renderer, const Tile& tile, const Vec& size) const {
    draw(renderer, tile.get_id(), tile.get_position(), size);
}

void Tileset::rebuild_tile_rects() {
    m_transparent_flags.clear();
    m_tile_rects.clear();

    if (m_tile_size.x <= 0.0f || m_tile_size.y <= 0.0f ||
        m_tileset_size.x <= 0.0f || m_tileset_size.y <= 0.0f) {
        return;
    }

    int columns = static_cast<int>(m_tileset_size.x);
    int rows = static_cast<int>(m_tileset_size.y);

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            m_tile_rects.push_back(SDL_FRect{
                static_cast<float>(x) * m_tile_size.x,
                static_cast<float>(y) * m_tile_size.y,
                m_tile_size.x,
                m_tile_size.y
            });

            if (m_whole_texture && m_whole_texture->is_region_transparent(m_tile_rects.back())) {
                m_transparent_flags.push_back(true);
            } else {
                m_transparent_flags.push_back(false);
            }
        }
    }
}


Tileset_Group::Tileset_Group(const Tileset* tileset)
    : m_tileset(tileset) {}

Tileset_Group::Tileset_Group(const Tileset* tileset, const std::vector<int>& indexes)
    : m_tileset(tileset), m_indexes(indexes) {}

void Tileset_Group::draw_group(SDL_Renderer* renderer, const Vec& position) const {
    draw_group(renderer, position, static_cast<int>(m_indexes.size()));
}

void Tileset_Group::draw_group(SDL_Renderer* renderer, const Vec& position, int columns) const {
    if (!renderer || !m_tileset || columns <= 0) {
        return;
    }

    Vec tile_size = m_tileset->get_tile_size();

    for (std::size_t i = 0; i < m_indexes.size(); ++i) {
        int column = static_cast<int>(i) % columns;
        int row = static_cast<int>(i) / columns;

        Vec draw_position = {
            position.x + static_cast<float>(column) * tile_size.x,
            position.y + static_cast<float>(row) * tile_size.y
        };

        m_tileset->draw(renderer, m_indexes[i], draw_position);
    }
}

bool Tilemap::load_json(const std::string& path) {
    m_last_error.clear();
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        m_last_error = "Could not open tilemap file: " + path;
        return false;
    }
    const std::string contents(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
    Tilemap_Json_Reader reader(contents);
    if (!reader.consume('{')) {
        m_last_error = "Tilemap root must be a JSON object: " + path;
        return false;
    }

    std::int64_t width = -1;
    std::int64_t height = -1;
    Vec origin = {0.f, 0.f};
    std::vector<std::vector<int>> rows;
    bool has_tiles = false;

    while (!reader.peek('}')) {
        std::string key;
        if (!reader.read_string(key) || !reader.consume(':')) {
            m_last_error = "Invalid tilemap property in: " + path;
            return false;
        }

        if (key == "width") {
            if (!reader.read_integer(width)) {
                m_last_error = "Tilemap width must be an integer: " + path;
                return false;
            }
        } else if (key == "height") {
            if (!reader.read_integer(height)) {
                m_last_error = "Tilemap height must be an integer: " + path;
                return false;
            }
        } else if (key == "origin") {
            double x = 0.0;
            double y = 0.0;
            if (!reader.consume('[') || !reader.read_number(x) || !reader.consume(',') ||
                !reader.read_number(y) || !reader.consume(']')) {
                m_last_error = "Tilemap origin must be [x, y]: " + path;
                return false;
            }
            origin = {static_cast<float>(x), static_cast<float>(y)};
        }  else if (key == "tileset_path") {
            std::string tileset_path;
            if (!reader.read_string(tileset_path)) {
                m_last_error = "Tilemap tileset_path must be a string: " + path;
                return false;
            }
        } else if (key == "tiles") {
            if (!reader.consume('[')) {
                m_last_error = "Tilemap tiles must be an array: " + path;
                return false;
            }
            rows.clear();
            if (!reader.peek(']')) {
                while (true) {
                    if (!reader.consume('[')) {
                        m_last_error = "Every tilemap row must be an array: " + path;
                        return false;
                    }
                    std::vector<int> row;
                    if (!reader.peek(']')) {
                        while (true) {
                            std::int64_t tile_id = -1;
                            if (!reader.read_integer(tile_id) || tile_id < -1 || tile_id > 2147483647LL) {
                                m_last_error = "Tile ids must be -1 or a non-negative integer: " + path;
                                return false;
                            }
                            row.push_back(static_cast<int>(tile_id));
                            if (reader.consume(']')) break;
                            if (!reader.consume(',')) {
                                m_last_error = "Invalid tilemap row: " + path;
                                return false;
                            }
                        }
                    } else {
                        reader.consume(']');
                    }
                    rows.push_back(std::move(row));
                    if (reader.consume(']')) break;
                    if (!reader.consume(',')) {
                        m_last_error = "Invalid tiles array: " + path;
                        return false;
                    }
                }
            } else {
                reader.consume(']');
            }
            has_tiles = true;
        } else if (!reader.skip_value()) {
            m_last_error = "Invalid value for tilemap property '" + key + "': " + path;
            return false;
        }

        if (reader.peek('}')) break;
        if (!reader.consume(',')) {
            m_last_error = "Expected ',' between tilemap properties: " + path;
            return false;
        }
    }

    if (!reader.consume('}') || !reader.at_end()) {
        m_last_error = "Unexpected content after tilemap JSON: " + path;
        return false;
    }
    if (width <= 0 || height <= 0 || width > 10000 || height > 10000 || !has_tiles) {
        m_last_error = "Tilemap requires positive width, height and a tiles array: " + path;
        return false;
    }
    if (static_cast<std::int64_t>(rows.size()) != height) {
        m_last_error = "Tilemap must contain exactly " + std::to_string(height) + " rows: " + path;
        return false;
    }

    std::vector<int> loaded_tiles;
    loaded_tiles.reserve(static_cast<std::size_t>(width * height));
    for (const auto& row : rows) {
        if (static_cast<std::int64_t>(row.size()) != width) {
            m_last_error = "Every tilemap row must contain exactly " + std::to_string(width) + " cells: " + path;
            return false;
        }
        for (int tile_id : row) {
            if (tile_id >= 0 && m_tileset && !m_tileset->is_valid_index(tile_id)) {
                m_last_error = "Tile id is outside the assigned tileset: " + std::to_string(tile_id);
                return false;
            }
            loaded_tiles.push_back(tile_id);
        }
    }

    m_width = static_cast<int>(width);
    m_height = static_cast<int>(height);
    m_origin = origin;
    m_tiles = std::move(loaded_tiles);
    m_cell_textures.assign(m_tiles.size(), nullptr);
    m_source_path = path;
    ++m_revision;
    return true;
}

void Tilemap::draw(SDL_Renderer* renderer, const Camera* camera) const {
    if (!renderer || m_width <= 0 || m_height <= 0) return;

    const Vec tile_size = get_cell_size();
    if (tile_size.x <= 0.0f || tile_size.y <= 0.0f) return;
    Texture* texture = m_tileset ? m_tileset->get_texture() : nullptr;
    SDL_Texture* native_texture = texture ? texture->get_sdl_texture() : nullptr;

    int min_column = 0;
    int max_column = m_width - 1;
    int min_row = 0;
    int max_row = m_height - 1;
    if (camera && tile_size.x > 0.0f && tile_size.y > 0.0f) {
        const Vec view_min = camera->get_position();
        const Vec view_max = view_min + camera->screen_size_to_world(camera->get_viewport());
        if (view_max.x < m_origin.x || view_max.y < m_origin.y ||
            view_min.x > m_origin.x + m_width * tile_size.x ||
            view_min.y > m_origin.y + m_height * tile_size.y) return;
        min_column = std::clamp(static_cast<int>(std::floor((view_min.x - m_origin.x) / tile_size.x)) - 1,
                                0, m_width - 1);
        max_column = std::clamp(static_cast<int>(std::floor((view_max.x - m_origin.x) / tile_size.x)) + 1,
                                0, m_width - 1);
        min_row = std::clamp(static_cast<int>(std::floor((view_min.y - m_origin.y) / tile_size.y)) - 1,
                             0, m_height - 1);
        max_row = std::clamp(static_cast<int>(std::floor((view_max.y - m_origin.y) / tile_size.y)) + 1,
                             0, m_height - 1);
    }

    m_batch_vertices.clear();
    m_batch_indices.clear();
    const std::size_t visible_capacity = static_cast<std::size_t>(max_column - min_column + 1) *
                                         static_cast<std::size_t>(max_row - min_row + 1);
    m_batch_vertices.reserve(visible_capacity * 4);
    m_batch_indices.reserve(visible_capacity * 6);
    const float texture_width = texture ? texture->get_width() : 0.0f;
    const float texture_height = texture ? texture->get_height() : 0.0f;
    const SDL_FColor white{1.0f, 1.0f, 1.0f, 1.0f};

    for (int row = min_row; row <= max_row; ++row) {
        for (int column = min_column; column <= max_column; ++column) {
            Texture* cell_texture = get_cell_texture(column, row);
            Vec position = {
                m_origin.x + static_cast<float>(column) * tile_size.x,
                m_origin.y + static_cast<float>(row) * tile_size.y
            };
            if (camera) {
                position = camera->world_to_screen(position);
            }
            const Vec draw_size = camera ? camera->world_size_to_screen(tile_size) : tile_size;
            if (cell_texture) {
                cell_texture->draw(renderer, position, draw_size);
                continue;
            }

            const int tile_id = get_tile(column, row);
            if (!m_tileset || !native_texture || texture_width <= 0.0f || texture_height <= 0.0f) continue;
            if (tile_id < 0) continue;
            const SDL_FRect* source = m_tileset->get_tile_rect(tile_id);
            if (!source) continue;
            const float u0 = source->x / texture_width;
            const float v0 = source->y / texture_height;
            const float u1 = (source->x + source->w) / texture_width;
            const float v1 = (source->y + source->h) / texture_height;
            const int base = static_cast<int>(m_batch_vertices.size());
            m_batch_vertices.push_back({{position.x, position.y}, white, {u0, v0}});
            m_batch_vertices.push_back({{position.x + draw_size.x, position.y}, white, {u1, v0}});
            m_batch_vertices.push_back({{position.x + draw_size.x, position.y + draw_size.y}, white, {u1, v1}});
            m_batch_vertices.push_back({{position.x, position.y + draw_size.y}, white, {u0, v1}});
            m_batch_indices.insert(m_batch_indices.end(), {base, base + 1, base + 2, base, base + 2, base + 3});
        }
    }
    if (native_texture && !m_batch_vertices.empty())
        SDL_RenderGeometry(renderer, native_texture, m_batch_vertices.data(),
                           static_cast<int>(m_batch_vertices.size()), m_batch_indices.data(),
                           static_cast<int>(m_batch_indices.size()));
}

void Tilemap::submit(Render_Pool& render_pool, uint8_t z_index, const Camera* camera,
                     const Color& tint, bool camera_space, bool y_sort) const {
    if (m_width <= 0 || m_height <= 0) return;
    Texture* texture = m_tileset ? m_tileset->get_texture() : nullptr;

    const Vec tile_size = get_cell_size();
    if (tile_size.x <= 0.0f || tile_size.y <= 0.0f) return;
    int min_column = 0;
    int max_column = m_width - 1;
    int min_row = 0;
    int max_row = m_height - 1;
    if (camera && tile_size.x > 0.0f && tile_size.y > 0.0f) {
        const Vec view_min = camera->get_position();
        const Vec view_max = view_min + camera->screen_size_to_world(camera->get_viewport());
        if (view_max.x < m_origin.x || view_max.y < m_origin.y ||
            view_min.x > m_origin.x + m_width * tile_size.x ||
            view_min.y > m_origin.y + m_height * tile_size.y) return;
        min_column = std::clamp(static_cast<int>(std::floor((view_min.x - m_origin.x) / tile_size.x)) - 1,
                                0, m_width - 1);
        max_column = std::clamp(static_cast<int>(std::floor((view_max.x - m_origin.x) / tile_size.x)) + 1,
                                0, m_width - 1);
        min_row = std::clamp(static_cast<int>(std::floor((view_min.y - m_origin.y) / tile_size.y)) - 1,
                             0, m_height - 1);
        max_row = std::clamp(static_cast<int>(std::floor((view_max.y - m_origin.y) / tile_size.y)) + 1,
                             0, m_height - 1);
    }
    for (int row = min_row; row <= max_row; ++row) {
        for (int column = min_column; column <= max_column; ++column) {
            Texture* cell_texture = get_cell_texture(column, row);
            const int tile_id = get_tile(column, row);
            const SDL_FRect* source =
                (!cell_texture && m_tileset) ? m_tileset->get_tile_rect(tile_id) : nullptr;
            if (!cell_texture && (tile_id < 0 || !texture || !source)) continue;

            Draw command;
            command.texture = cell_texture ? cell_texture : texture;
            command.transform = {
                {m_origin.x + static_cast<float>(column) * tile_size.x,
                 m_origin.y + static_cast<float>(row) * tile_size.y},
                tile_size,
                {0.0f, 0.0f}
            };
            if (source) {
                command.source_rect = *source;
                command.use_source_rect = true;
            }
            command.tint = tint;
            command.z_index = z_index;
            command.y_sort = y_sort;
            command.sort_y = command.transform.pos.y + tile_size.y;
            command.camera_space = camera_space;
            render_pool.submit(command);
        }
    }
}

int Tilemap::get_tile(int column, int row) const {
    if (!valid_cell(column, row)) return -1;
    return m_tiles[static_cast<std::size_t>(row * m_width + column)];
}

bool Tilemap::set_tile(int column, int row, int tile_id) {
    if (!valid_cell(column, row) || tile_id < -1) return false;
    if (tile_id >= 0 && m_tileset && !m_tileset->is_valid_index(tile_id)) return false;
    m_tiles[static_cast<std::size_t>(row * m_width + column)] = tile_id;
    ++m_revision;
    return true;
}

Texture* Tilemap::get_cell_texture(int column, int row) const {
    if (!valid_cell(column, row) || m_cell_textures.size() != m_tiles.size()) return nullptr;
    return m_cell_textures[cell_index(column, row)];
}

bool Tilemap::set_cell_texture(int column, int row, Texture* texture) {
    if (!valid_cell(column, row)) return false;
    if (m_cell_textures.size() != m_tiles.size()) {
        m_cell_textures.assign(m_tiles.size(), nullptr);
    }
    m_cell_textures[cell_index(column, row)] = texture;
    ++m_revision;
    return true;
}

void Tilemap::clear() {
    m_width = 0;
    m_height = 0;
    m_origin = {0.f, 0.f};
    m_tiles.clear();
    m_cell_textures.clear();
    m_last_error.clear();
    m_source_path.clear();
    ++m_revision;
}

bool Tilemap::valid_cell(int column, int row) const {
    return column >= 0 && column < m_width && row >= 0 && row < m_height;
}


bool Tilemap::create(int width, int height, int empty_tile_id, Vec origin) {
    if (width <= 0 || height <= 0 || empty_tile_id < -1 ||
        (empty_tile_id >= 0 && m_tileset && !m_tileset->is_valid_index(empty_tile_id))) {
        return false;
    }
    m_width = width;
    m_height = height;
    m_origin = origin;
    m_tiles.assign(static_cast<std::size_t>(width * height), empty_tile_id);
    m_cell_textures.assign(m_tiles.size(), nullptr);
    m_source_path.clear();
    m_last_error.clear();
    ++m_revision;
    return true;
}

bool Tilemap::resize(int new_width, int new_height, int empty_tile_id) {
    if (new_width <= 0 || new_height <= 0 || empty_tile_id < -1 ||
        (empty_tile_id >= 0 && m_tileset && !m_tileset->is_valid_index(empty_tile_id))) {
        return false;
    }

    std::vector<int> new_tiles(static_cast<std::size_t>(new_width * new_height), empty_tile_id);
    std::vector<Texture*> new_cell_textures(
        static_cast<std::size_t>(new_width * new_height), nullptr
    );

    for (int row = 0; row < std::min(m_height, new_height); ++row) {
        for (int column = 0; column < std::min(m_width, new_width); ++column) {
            new_tiles[static_cast<std::size_t>(row * new_width + column)] =
                m_tiles[static_cast<std::size_t>(row * m_width + column)];
            if (m_cell_textures.size() == m_tiles.size()) {
                new_cell_textures[static_cast<std::size_t>(row * new_width + column)] =
                    m_cell_textures[static_cast<std::size_t>(row * m_width + column)];
            }
        }
    }

    m_width = new_width;
    m_height = new_height;
    m_tiles = std::move(new_tiles);
    m_cell_textures = std::move(new_cell_textures);
    ++m_revision;
    return true;
}

bool Tilemap::save_json(const std::string& path) {
    std::ofstream file(path, std::ios::binary);
    if (!file) {
        m_last_error = "Could not open tilemap file for writing: " + path;
        return false;
    }
    file << "{\n";
    file << "  \"width\": " << m_width << ",\n";
    file << "  \"height\": " << m_height << ",\n";
    file << "  \"origin\": [" << m_origin.x << ", " << m_origin.y << "],\n";
    Texture* tileset_texture = m_tileset ? m_tileset->get_texture() : nullptr;
    file << "  \"tileset_path\": \"" << (tileset_texture ? tileset_texture->get_path() : "") << "\",\n";
    file << "  \"tiles\": [\n";
    for (int row = 0; row < m_height; ++row) {
        file << "    [";
        for (int column = 0; column < m_width; ++column) {
            file << get_tile(column, row);
            if (column < m_width - 1) file << ", ";
        }
        file << "]";
        if (row < m_height - 1) file << ",";
        file << "\n";
    }
    file << "  ]\n";
    file << "}\n";
    if (!file) {
        m_last_error = "Failed to write tilemap to file: " + path;
        return false;
    }
    m_source_path = path;
    m_last_error.clear();
    return true;
}

namespace {
std::unordered_map<std::string, Tilemap*> registered_tilemaps;
}

void Tilemap_Registry::add(const std::string& name, Tilemap* tilemap) {
    if (!name.empty() && tilemap) registered_tilemaps[name] = tilemap;
}

void Tilemap_Registry::remove(const std::string& name, Tilemap* tilemap) {
    auto it = registered_tilemaps.find(name);
    if (it != registered_tilemaps.end() && (!tilemap || it->second == tilemap))
        registered_tilemaps.erase(it);
}

Tilemap* Tilemap_Registry::get(const std::string& name) {
    auto it = registered_tilemaps.find(name);
    return it != registered_tilemaps.end() ? it->second : nullptr;
}

std::vector<std::string> Tilemap_Registry::names() {
    std::vector<std::string> result;
    result.reserve(registered_tilemaps.size());
    for (const auto& entry : registered_tilemaps) result.push_back(entry.first);
    std::sort(result.begin(), result.end());
    return result;
}
