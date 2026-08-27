#include "texture.h"

#include <SDL3_image/SDL_image.h>

#include <utility>

Texture::Texture(SDL_Renderer* renderer, const std::string& path, Logger *logger, SDL_ScaleMode scale_mode) : m_texture_path(path), logger(logger), m_scale_mode(scale_mode) {
    load(renderer, path);

    if (logger) {
        logger->log(Log_Level::INFO, "Texture", "Loaded texture from path: " + path);
    }
}

Texture::Texture(SDL_Renderer* renderer, SDL_Surface* surface, Logger *logger, SDL_ScaleMode scale_mode) : m_texture_path(""), logger(logger), m_scale_mode(scale_mode) {
    load_from_surface(renderer, surface);
    if (logger) {
        logger->log(Log_Level::INFO, "Texture", "Loaded texture from surface");
    }
}

Texture::~Texture() {
    free();
}

Texture::Texture(Texture&& other) noexcept
    : tex(other.tex), gpu_tex(other.gpu_tex), size(other.size), m_texture_path(std::move(other.m_texture_path)), logger(other.logger),
      m_scale_mode(other.m_scale_mode), m_alpha_mask(std::move(other.m_alpha_mask))
{
    other.tex    = nullptr;
    other.gpu_tex = nullptr;
    other.size = {0, 0};
    other.m_texture_path = "";
    other.logger = nullptr;

    if (logger) {
        logger->log(Log_Level::INFO, "Texture", "New texture created via move constructor");
    }
}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        free();
        tex = other.tex;
        gpu_tex = other.gpu_tex;
        size = other.size;
        m_texture_path = std::move(other.m_texture_path);
        logger = other.logger;
        m_scale_mode = other.m_scale_mode;
        m_alpha_mask = std::move(other.m_alpha_mask);
        other.tex = nullptr;
        other.gpu_tex = nullptr;
        other.size = {0, 0};
        other.m_texture_path = "";
        other.logger = nullptr;
        other.m_alpha_mask.clear();
    }
    if (logger) {
        logger->log(Log_Level::INFO, "Texture", "New texture assigned via move assignment operator");
    }
    return *this;
}

bool Texture::load(SDL_Renderer* renderer, const std::string& path) {
    free();
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        SDL_Log("Texture::load - failed to load: %s | error: %s",
                path.c_str(), SDL_GetError());
        if (logger) {
            logger->log(Log_Level::ERROR, "Texture", "Failed to load texture: " + path);
        }
        return false;
    }
    bool ok = load_from_surface(renderer, surface);
    SDL_DestroySurface(surface);
    if (!ok) {
        if (logger) {
            logger->log(Log_Level::ERROR, "Texture", "Failed to create texture from surface for: " + path);
        }
        return false;
    }
    return ok;
}

bool Texture::load_from_surface(SDL_Renderer* renderer, SDL_Surface* surface) {
    free();
    if (!surface) {
        SDL_Log("Texture::load_from_surface - null surface");
        if (logger) {
            logger->log(Log_Level::ERROR, "Texture", "Failed to load texture from surface: null surface");
        }
        return false;
    }
    m_is_fully_transparent = true;
    
    m_alpha_mask.resize(static_cast<std::size_t>(surface->w) * static_cast<std::size_t>(surface->h), 255);
    for (int y = 0; y < surface->h; ++y) {
        for (int x = 0; x < surface->w; ++x) {
            
            Color pixel_color = {0, 0, 0, 255};

            const std::size_t index = static_cast<std::size_t>(y * surface->w + x);
            
            if (SDL_ReadSurfacePixel(surface, x, y, &pixel_color.r, &pixel_color.g, &pixel_color.b, &pixel_color.a)) {
                m_alpha_mask[index] = pixel_color.a;

                if (pixel_color.a != 0) {
                    m_is_fully_transparent = false;
                }
            }
        }
    }

    if (m_is_fully_transparent) {
        SDL_Log("Texture::load_from_surface - surface is fully transparent");
        if (logger) {
            logger->log(Log_Level::WARNING, "Texture", "Surface is fully transparent");
        }
    }

    tex = SDL_CreateTextureFromSurface(renderer, surface);
    if (!tex) {
        m_alpha_mask.clear();
        SDL_Log("Texture::load_from_surface - failed to create texture from surface: %s",
                SDL_GetError());
        if (logger) {
            logger->log(Log_Level::ERROR, "Texture", "Failed to create texture from surface: " + std::string(SDL_GetError()));
        }
        return false;
    }
    SDL_SetTextureScaleMode(tex, m_scale_mode);
    const SDL_PropertiesID texture_properties = SDL_GetTextureProperties(tex);
    gpu_tex = texture_properties
        ? static_cast<SDL_GPUTexture*>(SDL_GetPointerProperty(
              texture_properties, SDL_PROP_TEXTURE_GPU_TEXTURE_POINTER, nullptr))
        : nullptr;
    size = { static_cast<float>(surface->w), static_cast<float>(surface->h) };
    return true;
}

void Texture::free() {
    if (tex) {
        SDL_DestroyTexture(tex);
        tex    = nullptr;
        size = {0, 0};
        if (logger) {
            logger->log(Log_Level::INFO, "Texture", "Texture freed");
        }
    }
    gpu_tex = nullptr;
    size = {0, 0};
    m_alpha_mask.clear();
}

void Texture::draw(SDL_Renderer* renderer, const Vec& pos) const {
    if (!tex) return;
    SDL_FRect dst = { pos.x, pos.y,
                      static_cast<float>(size.x),
                      static_cast<float>(size.y) };
    SDL_RenderTexture(renderer, tex, nullptr, &dst);
    if (logger && logger->is_flood_logging()) {
        logger->log(Log_Level::DEBUG, "Texture", "Texture drawn at position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")");
    }
}

void Texture::draw(SDL_Renderer* renderer, const Vec& pos, const Vec& size) const {
    if (!tex) return;
    SDL_FRect dst = { pos.x, pos.y, size.x, size.y };
    SDL_RenderTexture(renderer, tex, nullptr, &dst);
    if (logger && logger->is_flood_logging()) {
        logger->log(Log_Level::DEBUG, "Texture", "Texture drawn at position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") with size: (" + std::to_string(size.x) + ", " + std::to_string(size.y) + ")");
    }
}

void Texture::draw(SDL_Renderer* renderer, const Vec& pos, const Vec& size, const Vec& rotation) const {
    if (!tex) return;
    SDL_FRect dst = { pos.x, pos.y, size.x, size.y };

    switch (static_cast<int>(rotation.y)) {
        case 0:
            SDL_RenderTextureRotated(renderer, tex, nullptr, &dst, rotation.x, nullptr, SDL_FLIP_NONE);
            break;
        case 1:
            SDL_RenderTextureRotated(renderer, tex, nullptr, &dst, rotation.x, nullptr, SDL_FLIP_HORIZONTAL);
            break;
        case 2:
            SDL_RenderTextureRotated(renderer, tex, nullptr, &dst, rotation.x, nullptr, SDL_FLIP_VERTICAL);
            break;
        case 3:
            SDL_RenderTextureRotated(renderer, tex, nullptr, &dst, rotation.x, nullptr, SDL_FLIP_HORIZONTAL_AND_VERTICAL);
            break;
        default:
            SDL_RenderTextureRotated(renderer, tex, nullptr, &dst, rotation.x, nullptr, SDL_FLIP_NONE);
            break;
    }
    if (logger && logger->is_flood_logging()) {
        logger->log(Log_Level::DEBUG, "Texture", "Texture drawn at position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") with size: (" + std::to_string(size.x) + ", " + std::to_string(size.y) + ") and rotation: (" + std::to_string(rotation.x) + ", " + std::to_string(rotation.y) + ")");

    }
}

void Texture::draw(SDL_Renderer* renderer,const SDL_FRect* src, const SDL_FRect* dst) const {
    if (!tex) return;
    SDL_RenderTexture(renderer, tex, src, dst);
    if (logger && logger->is_flood_logging()) {
        logger->log(Log_Level::DEBUG, "Texture", "Texture drawn with src and dst rectangles");
    }
}

void Texture::draw_ex(SDL_Renderer* renderer,
                      const Vec& pos, const Vec& size,
                      double angle, const Vec* center,
                      SDL_FlipMode flip) const {
    if (!tex) return;
    SDL_FRect dst = { pos.x, pos.y, size.x, size.y };
    SDL_FPoint  c_val;
    const SDL_FPoint* c_ptr = nullptr;
    if (center) {
        c_val = { center->x, center->y };
        c_ptr = &c_val;
    }
    SDL_RenderTextureRotated(renderer, tex, nullptr, &dst, angle, c_ptr, flip);
    if (logger && logger->is_flood_logging()) {
        logger->log(Log_Level::DEBUG, "Texture", "Texture drawn with rotation at position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") with size: (" + std::to_string(size.x) + ", " + std::to_string(size.y) + ") and angle: " + std::to_string(angle));
    }
}

void Texture::draw_ex(SDL_Renderer* renderer, const Transform& transform, const Color& tint) const {
    draw_ex(renderer, nullptr, transform, tint);
}

void Texture::draw_ex(SDL_Renderer* renderer, const SDL_FRect* source, const Transform& transform, const Color& tint) const {
    if (!tex) return;
    SDL_FRect dst = { transform.pos.x, transform.pos.y, transform.size.x, transform.size.y };
    SDL_SetTextureColorMod(tex, tint.r, tint.g, tint.b);
    SDL_SetTextureAlphaMod(tex, tint.a);
    SDL_RenderTextureRotated(renderer, tex, source, &dst, transform.rotation.x, nullptr, static_cast<SDL_FlipMode>(transform.rotation.y));
    if (logger && logger->is_flood_logging()) {
        logger->log(Log_Level::DEBUG, "Texture", "Texture drawn with Transform and Color at position: (" + std::to_string(transform.pos.x) + ", " + std::to_string(transform.pos.y) + ") with size: (" + std::to_string(transform.size.x) + ", " + std::to_string(transform.size.y) + "), rotation: (" + std::to_string(transform.rotation.x) + ", " + std::to_string(transform.rotation.y) + "), and color tint: (" + std::to_string(tint.r) + ", " + std::to_string(tint.g) + ", " + std::to_string(tint.b) + ", " + std::to_string(tint.a) + ")");
    }
}

bool Texture::is_region_transparent(const SDL_FRect& region, uint8_t alpha_threshold) const {
    if (m_alpha_mask.empty()) return true;

    const int width = static_cast<int>(size.x);
    const int height = static_cast<int>(size.y);

    int start_x = static_cast<int>(region.x);
    int start_y = static_cast<int>(region.y);
    int end_x = static_cast<int>(region.x + region.w);
    int end_y = static_cast<int>(region.y + region.h);

    // Clamp to texture bounds
    start_x = std::max(0, start_x);
    start_y = std::max(0, start_y);
    end_x = std::min(width, end_x);
    end_y = std::min(height, end_y);

    for (int y = start_y; y < end_y; ++y) {
        for (int x = start_x; x < end_x; ++x) {
            if (m_alpha_mask[static_cast<std::size_t>(y * width + x)] >= alpha_threshold) {
                return false;
            }
        }
    }
    return true;
}
