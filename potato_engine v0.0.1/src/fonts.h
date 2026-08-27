#ifndef FONTS_H
#define FONTS_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <memory>
#include "vec.h"
#include "color.h"
#include "tileset.h"

/**
 * @brief Draw-time properties shared by every IFont implementation.
 *
 * IFont_Props lets UI code keep text rendering data in one reusable value.
 * The font owns no renderer or text data; these properties are borrowed or
 * copied in at draw time.
 *
 * @param renderer SDL renderer used for drawing.
 * @param text Text to draw.
 * @param path Optional font source path, useful when constructing props before loading.
 * @param pos Top-left draw position in logical coordinates.
 * @param color Text color and opacity.
 * @param size Base font size or tile size.
 * @param scale Draw scale multiplier.
 */
struct IFont_Props {
    SDL_Renderer* renderer = nullptr;
    std::string text;
    std::string path;
    Vec pos = {0.0f, 0.0f};
    Color color = {255, 255, 255, 255};
    int size = 16;
    float scale = 1.0f;
};

/**
 * @brief Common interface for drawable font assets.
 *
 * IFont allows text systems to use either SDL_ttf fonts or bitmap tileset fonts
 * through the same load, unload, sizing and draw calls. The class stores an
 * optional borrowed IFont_Props pointer for callers that prefer retained props,
 * but every implementation also supports direct draw arguments.
 */
class IFont {
public:
    /// Frees implementation-specific font resources.
    virtual ~IFont() = default;

    /**
     * @brief Loads a font from disk.
     * @param path Path to a TTF file or bitmap font atlas, depending on the implementation.
     * @param size Point size for SDL_Font, or tile size for Tileset_Font.
     * @return `true` when the font is ready to draw.
     */
    virtual bool load(const std::string& path, int size = 16) = 0;

    /**
     * @brief Unloads all resources held by the font.
     */
    virtual void unload() = 0;

    /**
     * @brief Checks if the font has a loaded backing resource.
     * @return `true` when the font can be measured and drawn.
     */
    virtual bool is_loaded() const = 0;

    /**
     * @brief Measures text using this font.
     * @param text Text to measure.
     * @return Width and height in logical pixels before draw scaling.
     */
    virtual Vec get_size(const std::string& text) const = 0;

    /**
     * @brief Gets the retained draw properties pointer.
     * @return Borrowed pointer to the current properties, or nullptr.
     */
    virtual IFont_Props* get_props() const { return m_props; }

    /**
     * @brief Sets the retained draw properties pointer.
     * @param new_props Borrowed pointer; ownership stays with the caller.
     */
    virtual void set_props(IFont_Props* new_props) { m_props = new_props; }

    /** Selects hard-edged, nearest-sampled rendering for pixel-art UI. */
    virtual void set_pixel_art(bool enabled) { (void)enabled; }

    /** @return Whether the font currently uses pixel-art rendering. */
    virtual bool pixel_art() const { return false; }

    /**
     * @brief Draws text using a full properties object.
     * @param props Draw properties to use for this call.
     */
    virtual void draw(const IFont_Props& props) const = 0;

    /**
     * @brief Draws text using direct arguments.
     * @param renderer SDL renderer used for drawing.
     * @param text Text to draw.
     * @param pos Top-left draw position.
     * @param color Text color and opacity.
     * @param scale Draw scale multiplier.
     */
    virtual void draw(
        SDL_Renderer* renderer,
        const std::string& text,
        const Vec& pos,
        const Color& color,
        float scale = 1.0f
    ) const = 0;

protected:
    IFont_Props* m_props = nullptr;
};

/**
 * @brief TrueType/OpenType font implementation backed by SDL_ttf.
 *
 * SDL_Font loads scalable fonts through TTF_OpenFont and renders text into a
 * temporary SDL texture each draw call. It is best for UI labels and dynamic
 * text where crisp scalable glyphs are preferred.
 */
class SDL_Font : public IFont {
public:
    SDL_Font() = default;
    ~SDL_Font() override;

    void set_pixel_art(bool enabled) override;
    bool pixel_art() const override { return m_pixel_art; }

    SDL_Font(const SDL_Font&) = delete;
    SDL_Font& operator=(const SDL_Font&) = delete;

    SDL_Font(SDL_Font&&) = delete;
    SDL_Font& operator=(SDL_Font&&) = delete;

    bool load(const std::string& path, int size = 16) override;
    void unload() override;

    bool is_loaded() const override;

    Vec get_size(const std::string& text) const override;

    void draw(const IFont_Props& props) const override;

    void draw(
        SDL_Renderer* renderer,
        const std::string& text,
        const Vec& pos,
        const Color& color,
        float scale = 1.0f
    ) const override;

private:
    TTF_Font* font = nullptr;
    int m_size = 16;
    bool m_pixel_art = false;
};

/**
 * @brief Bitmap font implementation backed by a fixed-grid texture atlas.
 *
 * Tileset_Font maps characters to tile indexes using a character map string.
 * Each character is drawn from the matching tile in the atlas. This is useful
 * for pixel fonts, retro UI, or stylized glyph sheets.
 */
class Tileset_Font : public IFont {
public:
    Tileset_Font() = default;
    ~Tileset_Font() override;

    Tileset_Font(const Tileset_Font&) = delete;
    Tileset_Font& operator=(const Tileset_Font&) = delete;

    Tileset_Font(Tileset_Font&&) = delete;
    Tileset_Font& operator=(Tileset_Font&&) = delete;

    bool load(const std::string& path, int size = 16) override;
    void unload() override;

    /**
     * @brief Loads a bitmap font atlas using Engine::renderer.
     * @param path Path to the bitmap font atlas image.
     * @param tile_size Size of one glyph tile.
     * @param char_map Characters mapped left-to-right, top-to-bottom in the atlas.
     * @return `true` when the atlas was loaded and indexed.
     */
    bool load_tileset_font(
        const std::string& path,
        const Vec& tile_size,
        const std::string& char_map
    );

    /**
     * @brief Loads a bitmap font atlas using an explicit renderer.
     * @param renderer SDL renderer used to create the atlas texture.
     * @param path Path to the bitmap font atlas image.
     * @param tile_size Size of one glyph tile.
     * @param char_map Characters mapped left-to-right, top-to-bottom in the atlas.
     * @return `true` when the atlas was loaded and indexed.
     */
    bool load_tileset_font(
        SDL_Renderer* renderer,
        const std::string& path,
        const Vec& tile_size,
        const std::string& char_map
    );

    bool is_loaded() const override;
    bool pixel_art() const override { return true; }

    Vec get_size(const std::string& text) const override;

    const std::string& get_char_map() const { return m_char_map; }
    void set_char_map(const std::string& new_map) { m_char_map = new_map; }

    const Vec& get_tile_size() const { return m_tile_size; }
    void set_tile_size(const Vec& tile_size) { m_tile_size = tile_size; }

    void draw(const IFont_Props& props) const override;

    void draw(
        SDL_Renderer* renderer,
        const std::string& text,
        const Vec& pos,
        const Color& color,
        float scale = 1.0f
    ) const override;

private:
    std::unique_ptr<Texture> m_texture;
    Tileset m_tileset;
    Vec m_tile_size = {8.0f, 8.0f};

    std::string m_char_map =
        " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,!?-+/():;%&`'*#=[]\"";

    bool m_loaded = false;
};

#endif
