#ifndef LABEL_H
#define LABEL_H


#include <SDL3/SDL.h>
#include <string>
#include "object.h"
#include "color.h"
#include "fonts.h"

/**
 * @brief Renderable text object backed by an IFont asset.
 *
 * Label behaves like an Object for position, size, z-index and visibility, but
 * renders text through an IFont instead of a Texture. The font pointer is
 * borrowed, usually from Asset_Pool, which keeps font ownership in unique_ptrs.
 */
class Label : public Object {
public:

    Label() = default;

    Label(const Label&) = delete;

    /**
     * @brief Constructs a Label object with no assigned font.
     * @param transform Transform data inherited from Object.
     * @param text The text to display on the label.
     * @param logger Optional logger for debug output.
     * @param object_pool Optional pool used for automatic rendering.
     */
    Label(const Transform& transform, const std::string& text,
          IFont* font = nullptr, Logger* logger = nullptr,
          Object_Pool* object_pool = nullptr)
        : Object(transform, nullptr, object_pool, logger), text(text), font(font) {}

    /**
     * @brief Constructs a Label object with no assigned font.
     * @param pos The top-left position of the label in logical coordinates.
     * @param size The width and height of the label in logical pixels.
     * @param rot Rotation data inherited from Object.
     * @param text The text to display on the label.
     * @param logger Optional logger for debug output.
     * @param object_pool Optional pool used for automatic rendering.
     */
    Label(const Vec& pos, const Vec& size, const Vec& rot, const std::string& text,
          Logger* logger = nullptr, Object_Pool* object_pool = nullptr)
        : Object(pos, size, rot, nullptr, object_pool, logger), text(text) {}

    /**
     * @brief Constructs a Label object with a borrowed font pointer.
     * @param pos The top-left position of the label in logical coordinates.
     * @param size The width and height of the label in logical pixels.
     * @param rot Rotation data inherited from Object.
     * @param text The text to display on the label.
     * @param font Borrowed IFont pointer. Ownership stays with Asset_Pool or the caller.
     * @param logger Optional logger for debug output.
     * @param object_pool Optional pool used for automatic rendering.
     */
    Label(const Vec& pos, const Vec& size, const Vec& rot, const std::string& text,
          IFont* font, Logger* logger = nullptr, Object_Pool* object_pool = nullptr)
        : Object(pos, size, rot, nullptr, object_pool, logger), text(text), font(font) {}

    /**
     * @brief Constructs a Label object and resolves its font from Engine::asset_pool.
     * @param pos The top-left position of the label in logical coordinates.
     * @param size The width and height of the label in logical pixels.
     * @param rot Rotation data inherited from Object.
     * @param text The text to display on the label.
     * @param font_name Name of the font stored in Asset_Pool.
     * @param logger Optional logger for debug output.
     * @param object_pool Optional pool used for automatic rendering.
     */
    Label(const Vec& pos, const Vec& size, const Vec& rot, const std::string& text,
          const std::string& font_name, Logger* logger = nullptr,
          Object_Pool* object_pool = nullptr);

    /**
     * @brief Sets the text of the label.
     * @param new_text The new text to display.
     */
    void set_text(const std::string& new_text) { text = new_text; }
    
    /**
     * @brief Gets the current text of the label.
     * @return The current text.
     */
    const std::string& get_text() const { return text; }

    /**
     * @brief Sets the borrowed font pointer used for rendering.
     * @param new_font Borrowed IFont pointer. Ownership stays with the caller.
     */
    void set_font(IFont* new_font) { font = new_font; }

    /**
     * @brief Resolves and sets the font from Engine::asset_pool.
     * @param font_name Name of the font stored in Asset_Pool.
     * @return `true` if the font was found and assigned.
     */
    bool set_font_from_asset_pool(const std::string& font_name);

    /**
     * @brief Gets the currently assigned font.
     * @return Borrowed IFont pointer, or nullptr.
     */
    IFont* get_font() const { return font; }

    /**
     * @brief Sets the label color.
     * @param new_color New text color and opacity.
     */
    void set_color(const Color& new_color) { tint = new_color; }

    /**
     * @brief Gets the label color.
     * @return Current text color.
     */
    Color get_color() const { return tint; }

    /**
     * @brief Sets the draw scale used by the font.
     * @param new_scale New scale multiplier. Values <= 0 are ignored.
     */
    void set_scale(float new_scale);

    /**
     * @brief Gets the draw scale used by the font.
     * @return Current scale multiplier.
     */
    float get_scale() const { return scale; }

    /**
     * @brief Updates the Object size from the current font and text.
     * @return The calculated size after scale is applied.
     */
    Vec resize_to_text();

    /**
     * @brief Enables a simple drop shadow rendered immediately behind the text.
     * @param offset Shadow offset in logical pixels.
     * @param color Shadow color; its alpha is multiplied by the label opacity.
     */
    void set_shadow(const Vec& offset, const Color& color) {
        shadow_offset = offset;
        shadow_color = color;
        shadow_enabled = true;
    }

    /** Disables the optional text shadow. */
    void clear_shadow() { shadow_enabled = false; }

    /**
     * @brief Draws the label immediately with the assigned font.
     * @param renderer SDL renderer used for drawing.
     */
    void draw(SDL_Renderer* renderer) override;

    /**
     * @brief Creates a font draw command for Render_Pool.
     * @return Draw command containing the assigned font and current text.
     */
    Draw make_draw_command() const override;

    /** Submits the optional shadow followed by the main text draw. */
    void submit_draw_commands(Render_Pool& render_pool) override;

private:
    std::string text;
    IFont* font = nullptr;
    float scale = 1.0f;
    bool shadow_enabled = false;
    Vec shadow_offset = {1.0f, 1.0f};
    Color shadow_color = {0, 0, 0, 220};

};

/** Result produced by TextBox::handle_event(). */
enum class TextBox_Result {
    NONE,
    SUBMITTED,
    CANCELLED
};

/**
 * Single-line, keyboard-driven text input rendered as a plain Label.
 *
 * TextBox intentionally has no background or tileset. While focused it owns
 * Input's global block, so gameplay actions, axes and buttons read as neutral.
 * Enter submits, Escape cancels, and the terminating key is swallowed until
 * its key-up event so it cannot leak into gameplay.
 */
class TextBox : public Label {
public:
    TextBox(const Transform& transform = {},
            IFont* font = nullptr,
            Object_Pool* object_pool = nullptr,
            Logger* logger = nullptr);
    ~TextBox() override;

    TextBox(const TextBox&) = delete;
    TextBox& operator=(const TextBox&) = delete;

    bool focus(bool clear_existing_text = true);
    void blur();
    bool is_focused() const { return m_focused; }

    TextBox_Result handle_event(const SDL_Event& event);

    void set_value(const std::string& value);
    const std::string& get_value() const { return m_value; }
    void clear();

    void set_prefix(const std::string& prefix);
    const std::string& get_prefix() const { return m_prefix; }

    void set_max_length(std::size_t maximum_bytes);
    std::size_t get_max_length() const { return m_max_length; }
    std::size_t get_cursor_position() const { return m_cursor; }

private:
    void finish(SDL_Scancode release_scancode);
    void refresh_display_text();
    void insert_text(const std::string& text);
    void erase_previous_character();
    void erase_next_character();

    static std::size_t previous_utf8_boundary(const std::string& text,
                                              std::size_t position);
    static std::size_t next_utf8_boundary(const std::string& text,
                                          std::size_t position);
    static std::string single_line_text(std::string text);

    std::string m_value;
    std::string m_prefix = "> ";
    std::size_t m_cursor = 0;
    std::size_t m_max_length = 256;
    bool m_focused = false;
    bool m_waiting_for_release = false;
    SDL_Scancode m_release_scancode = SDL_SCANCODE_UNKNOWN;
};



#endif
