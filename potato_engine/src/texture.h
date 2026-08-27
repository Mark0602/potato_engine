#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3/SDL.h>
#include <string>
#include <cstdint>
#include <vector>
#include "engine.h"
#include "vec.h"
#include "debug.h"
#include "color.h"

/**
 * @brief RAII wrapper around an SDL_Texture.
 *
 * Loads an image from a file path or an SDL_Surface and exposes
 * various `draw()` overloads for rendering it on screen.
 * Copy is disabled; use move semantics if ownership transfer is needed.
 *
 * @param tex Pointer to the underlying SDL_Texture (managed by this class).
 * @param size    Native width and height of the texture in pixels.
 * @param renderer The SDL_Renderer to create the texture with.
 * @param path     Path to the image file (PNG, JPG, etc.).
 * @param logger   Optional logger; pass `nullptr` to suppress log output.
 * @param scale_mode Scaling filter. Default: `SDL_SCALEMODE_PIXELART` (nearest-neighbour).
 * 
 * Example:
 * ```cpp
 * Texture tex(Engine::renderer, "assets/sprite.png", Engine::logger);
 * if (tex.is_loaded())
 *     tex.draw(Engine::renderer, pos, size);
 * ```
 */
class Texture {
    SDL_Texture* tex = nullptr;
    // Borrowed native resource exposed by SDL's GPU renderer. SDL_Texture
    // remains the sole owner, so CPU and GPU textures share one RAII path.
    SDL_GPUTexture* gpu_tex = nullptr;
    Vec size = {0, 0};

public:
    Texture() = default;

    /**
     * @brief Loads a texture from a file.
     * @param renderer   The SDL renderer to create the texture with.
     * @param path       Path to the image file (PNG, JPG, etc.).
     * @param logger     Optional logger; pass `nullptr` to suppress log output.
     * @param scale_mode Scaling filter. Default: `SDL_SCALEMODE_PIXELART` (nearest-neighbour).
     */
    Texture(SDL_Renderer* renderer, const std::string& path, Logger *logger = nullptr, SDL_ScaleMode scale_mode = SDL_SCALEMODE_PIXELART);

    /**
     * @brief Creates a texture from an existing SDL_Surface.
     * @param renderer   The SDL renderer to create the texture with.
     * @param surface    The source surface (not freed by this constructor).
     * @param logger     Optional logger.
     * @param scale_mode Scaling filter.
     */
    Texture(SDL_Renderer* renderer, SDL_Surface* surface, Logger *logger = nullptr, SDL_ScaleMode scale_mode = SDL_SCALEMODE_PIXELART);

    /// Frees the underlying SDL_Texture.
    virtual ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    /**
     * @brief (Re)loads the texture from a file path.
     * @param renderer The SDL renderer.
     * @param path     Path to the image file.
     * @return `true` on success.
     */
    bool load(SDL_Renderer* renderer, const std::string& path);

    /**
     * @brief (Re)loads the texture from an SDL_Surface.
     * @param renderer The SDL renderer.
     * @param surface  Source surface.
     * @return `true` on success.
     */
    bool load_from_surface(SDL_Renderer* renderer, SDL_Surface* surface);

    /// Destroys the SDL_Texture and resets internal state.
    void free();

    /**
     * @brief Draws the texture at `pos` using its native size.
     * @param renderer Target SDL renderer.
     * @param pos      Top-left position in logical coordinates.
     */
    void draw(SDL_Renderer* renderer, const Vec& pos) const;

    /**
     * @brief Draws the texture at `pos` scaled to `size`.
     * @param renderer Target SDL renderer.
     * @param pos      Top-left position in logical coordinates.
     * @param size     Desired draw size (width, height).
     */
    void draw(SDL_Renderer* renderer, const Vec& pos, const Vec& size) const;

    /**
     * @brief Draws the texture at `pos` scaled to `size` and rotated by `rotation`.
     * @param renderer Target SDL renderer.
     * @param pos      Top-left position in logical coordinates.
     * @param size     Desired draw size (width, height).
     * @param rotation Rotation angle in degrees (clockwise).
     */
    void draw(SDL_Renderer* renderer, const Vec& pos, const Vec& size, const Vec& rotation) const;

    /**
     * @brief Draws a sub-region of the texture into a destination rectangle.
     * @param renderer Target SDL renderer.
     * @param src      Source rectangle in texture coordinates (or `nullptr` for the full texture).
     * @param dst      Destination rectangle in logical coordinates.
     */
    void draw(SDL_Renderer* renderer, const SDL_FRect* src, const SDL_FRect* dst) const;

    /**
     * @brief Draws the texture with rotation and/or flip.
     * @param renderer Target SDL renderer.
     * @param pos      Top-left position in logical coordinates.
     * @param size     Desired draw size.
     * @param angle    Rotation angle in degrees (clockwise).
     * @param center   Rotation center relative to `pos`, or `nullptr` for the texture centre.
     * @param flip     One of `SDL_FLIP_NONE`, `SDL_FLIP_HORIZONTAL`, `SDL_FLIP_VERTICAL`.
     */
    void draw_ex(SDL_Renderer* renderer,
                 const Vec& pos, const Vec& size,
                 double angle, const Vec* center,
                 SDL_FlipMode flip) const;

    /**
     * @brief Draws the texture with a Transform and Color tint.
     * @param renderer Target SDL renderer.
     * @param transform Transform containing position, size, and rotation.
     * @param tint Color tint to apply.
     */
    void draw_ex(SDL_Renderer* renderer, const Transform& transform, const Color& tint) const;
    void draw_ex(SDL_Renderer* renderer, const SDL_FRect* source, const Transform& transform, const Color& tint) const;

    /// @return `true` if the texture is loaded and ready to draw.
    bool is_loaded()  const { return tex != nullptr; }
    /// @return Native texture width in pixels.
    float get_width()  const { return size.x;  }
    /// @return Native texture height in pixels.
    float get_height() const { return size.y; }
    /// @return Native texture size as a Vec.
    Vec get_size() const { return size; }

    /** @return Whether the source pixel alpha is at least `alpha_threshold`. */
    bool is_pixel_opaque(int x, int y, uint8_t alpha_threshold = 1) const {
        const int width = static_cast<int>(size.x);
        const int height = static_cast<int>(size.y);
        if (x < 0 || y < 0 || x >= width || y >= height || m_alpha_mask.empty()) return false;
        return m_alpha_mask[static_cast<std::size_t>(y * width + x)] >= alpha_threshold;
    }

    /** @return True when a CPU-side alpha mask is available for pixel-perfect collision. */
    bool has_alpha_mask() const { return !m_alpha_mask.empty(); }
    /// @return The raw SDL_Texture pointer (use with care).
    SDL_Texture* get_SDL_Texture() const { return tex; }
    /// @return The SDL_GPU texture on RendererBackend::GPU, otherwise nullptr.
    SDL_GPUTexture* get_gpu_texture() const { return gpu_tex; }
    /// @return True when this wrapper is backed by a native SDL_GPU texture.
    bool is_gpu_backed() const { return gpu_tex != nullptr; }
    /// @return The file path this texture was loaded from, or `""` if loaded from a surface.
    std::string get_texture_path() const { return m_texture_path; }
    /// @return The current SDL scale mode (filtering).
    SDL_ScaleMode get_scale_mode() const { return m_scale_mode; }
    /// @return The path of the texture file, or an empty string if not loaded from a file.
    std::string get_path() const { return m_texture_path.empty() ? "" : m_texture_path; }

    /**
     * @brief Changes the scale mode (texture filtering).
     * @param scale_mode New mode, e.g. `SDL_SCALEMODE_PIXELART` or `SDL_SCALEMODE_LINEAR`.
     */
    void set_scale_mode(SDL_ScaleMode scale_mode) {
        m_scale_mode = scale_mode;
        if (tex) {
            SDL_SetTextureScaleMode(tex, m_scale_mode);
        }
    }

    /**
     * @brief Returns the underlying SDL_Texture pointer.
     * @return Pointer to the SDL_Texture managed by this class.
     */
    SDL_Texture* get_sdl_texture() const { return tex; }

    /**
     * @brief Changes the opacity of the texture.
     * @param alpha New opacity in the range [0.0, 1.0].
     */
    void set_texture_opacity(float alpha) {
        if (tex) {
            SDL_SetTextureAlphaMod(tex, static_cast<Uint8>(alpha * 255.0f));
        }
    }

    /**
     * @brief Checks if the texture is fully transparent (all pixels have alpha = 0).
     * @return `true` if the texture is fully transparent, `false` otherwise.
     */
    bool is_fully_transparent() const { return m_is_fully_transparent; }

    /**
     * @brief Checks if a rectangular region of the texture is fully transparent.
     * @param region The region to check, in texture coordinates.
     * @param alpha_threshold The alpha threshold to consider a pixel opaque (default: 1).
     * @return `true` if all pixels in the region have alpha < alpha_threshold, `false` otherwise.
     */
    bool is_region_transparent(const SDL_FRect& region, uint8_t alpha_threshold = 1) const;

private:
    std::string m_texture_path = "";
    Logger *logger = nullptr;
    SDL_ScaleMode m_scale_mode = SDL_SCALEMODE_PIXELART;
    std::vector<uint8_t> m_alpha_mask;
    bool m_is_fully_transparent = true;
};

#endif
