#include "fonts.h"

#include <algorithm>
#include <cmath>

#include "engine.h"

SDL_Font::~SDL_Font() {
    unload();
}

bool SDL_Font::load(const std::string& path, int size) {
    unload();

    if (path.empty() || size <= 0) {
        return false;
    }

    if (!TTF_WasInit() && !TTF_Init()) {
        SDL_Log("SDL_Font::load - failed to initialize SDL_ttf: %s", SDL_GetError());
        return false;
    }

    font = TTF_OpenFont(path.c_str(), static_cast<float>(size));
    if (!font) {
        SDL_Log("SDL_Font::load - failed to load font '%s': %s", path.c_str(), SDL_GetError());
        return false;
    }

    TTF_SetFontHinting(
        font,
        m_pixel_art ? TTF_HINTING_MONO : TTF_HINTING_NORMAL
    );
    m_size = size;
    return true;
}

void SDL_Font::unload() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

bool SDL_Font::is_loaded() const {
    return font != nullptr;
}

void SDL_Font::set_pixel_art(bool enabled) {
    m_pixel_art = enabled;
    if (font) {
        TTF_SetFontHinting(
            font,
            m_pixel_art ? TTF_HINTING_MONO : TTF_HINTING_NORMAL
        );
    }
}

Vec SDL_Font::get_size(const std::string& text) const {
    if (!font || text.empty()) {
        return {0.0f, 0.0f};
    }

    int width = 0;
    int height = 0;
    if (!TTF_GetStringSize(font, text.c_str(), text.size(), &width, &height)) {
        return {0.0f, 0.0f};
    }

    return {static_cast<float>(width), static_cast<float>(height)};
}

void SDL_Font::draw(const IFont_Props& props) const {
    draw(props.renderer, props.text, props.pos, props.color, props.scale);
}

void SDL_Font::draw(
    SDL_Renderer* renderer,
    const std::string& text,
    const Vec& pos,
    const Color& color,
    float scale
) const {
    if (!renderer || !font || text.empty() || scale <= 0.0f) {
        return;
    }

    SDL_Surface* surface = m_pixel_art
        ? TTF_RenderText_Solid(
            font, text.c_str(), text.size(), color.to_sdl_color()
        )
        : TTF_RenderText_Blended(
            font, text.c_str(), text.size(), color.to_sdl_color()
        );
    if (!surface) {
        SDL_Log("SDL_Font::draw - failed to render text: %s", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("SDL_Font::draw - failed to create text texture: %s", SDL_GetError());
        SDL_DestroySurface(surface);
        return;
    }

    SDL_SetTextureScaleMode(
        texture,
        m_pixel_art ? SDL_SCALEMODE_NEAREST : SDL_SCALEMODE_LINEAR
    );

    SDL_FRect dst = {
        m_pixel_art ? std::round(pos.x) : pos.x,
        m_pixel_art ? std::round(pos.y) : pos.y,
        m_pixel_art
            ? std::round(static_cast<float>(surface->w) * scale)
            : static_cast<float>(surface->w) * scale,
        m_pixel_art
            ? std::round(static_cast<float>(surface->h) * scale)
            : static_cast<float>(surface->h) * scale
    };

    SDL_RenderTexture(renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

Tileset_Font::~Tileset_Font() {
    unload();
}

bool Tileset_Font::load(const std::string& path, int size) {
    return load_tileset_font(Engine::renderer, path, {static_cast<float>(size), static_cast<float>(size)}, m_char_map);
}

void Tileset_Font::unload() {
    m_tileset = Tileset();
    m_texture.reset();
    m_loaded = false;
}

bool Tileset_Font::load_tileset_font(
    const std::string& path,
    const Vec& tile_size,
    const std::string& char_map
) {
    return load_tileset_font(Engine::renderer, path, tile_size, char_map);
}

bool Tileset_Font::load_tileset_font(
    SDL_Renderer* renderer,
    const std::string& path,
    const Vec& tile_size,
    const std::string& char_map
) {
    unload();

    if (!renderer || path.empty() || tile_size.x <= 0.0f || tile_size.y <= 0.0f || char_map.empty()) {
        return false;
    }

    auto texture = std::make_unique<Texture>(renderer, path, Engine::logger);
    if (!texture || !texture->is_loaded()) {
        return false;
    }

    Vec texture_size = texture->get_size();
    Vec grid_size = {
        static_cast<float>(static_cast<int>(texture_size.x / tile_size.x)),
        static_cast<float>(static_cast<int>(texture_size.y / tile_size.y))
    };

    if (grid_size.x <= 0.0f || grid_size.y <= 0.0f) {
        return false;
    }

    m_texture = std::move(texture);
    m_tile_size = tile_size;
    m_char_map = char_map;
    m_tileset.init(m_texture.get(), m_tile_size, grid_size);
    m_loaded = true;

    return true;
}

bool Tileset_Font::is_loaded() const {
    return m_loaded && m_texture && m_texture->is_loaded();
}

Vec Tileset_Font::get_size(const std::string& text) const {
    if (!is_loaded() || text.empty()) {
        return {0.0f, 0.0f};
    }

    int current_line_length = 0;
    int max_line_length = 0;
    int line_count = 1;

    for (char ch : text) {
        if (ch == '\n') {
            max_line_length = std::max(max_line_length, current_line_length);
            current_line_length = 0;
            ++line_count;
        } else {
            ++current_line_length;
        }
    }

    max_line_length = std::max(max_line_length, current_line_length);

    return {
        static_cast<float>(max_line_length) * m_tile_size.x,
        static_cast<float>(line_count) * m_tile_size.y
    };
}

void Tileset_Font::draw(const IFont_Props& props) const {
    draw(props.renderer, props.text, props.pos, props.color, props.scale);
}

void Tileset_Font::draw(
    SDL_Renderer* renderer,
    const std::string& text,
    const Vec& pos,
    const Color& color,
    float scale
) const {
    if (!renderer || !is_loaded() || text.empty() || scale <= 0.0f) {
        return;
    }

    SDL_Texture* raw_texture = m_texture->get_sdl_texture();
    if (raw_texture) {
        SDL_SetTextureColorMod(raw_texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(raw_texture, color.a);
    }

    Vec draw_size = m_tile_size * scale;
    Vec cursor = pos;

    for (char ch : text) {
        if (ch == '\n') {
            cursor.x = pos.x;
            cursor.y += draw_size.y;
            continue;
        }

        std::size_t index = m_char_map.find(ch);
        if (index != std::string::npos) {
            m_tileset.draw(renderer, static_cast<int>(index), cursor, draw_size);
        }

        cursor.x += draw_size.x;
    }

    if (raw_texture) {
        SDL_SetTextureColorMod(raw_texture, 255, 255, 255);
        SDL_SetTextureAlphaMod(raw_texture, 255);
    }
}
