#include "label.h"

#include "asset_pool.h"
#include "engine.h"
#include "input.h"

#include <algorithm>

Label::Label(const Vec& pos, const Vec& size, const Vec& rot,
             const std::string& text, const std::string& font_name,
             Logger* logger, Object_Pool* object_pool)
    : Object(pos, size, rot, nullptr, object_pool, logger), text(text) {
    set_font_from_asset_pool(font_name);
}

bool Label::set_font_from_asset_pool(const std::string& font_name) {
    if (font_name.empty()) {
        if (logger) {
            logger->log(Log_Level::ERROR, "Label", "Cannot set label font because font name is empty.");
        }
        return false;
    }

    if (!Engine::asset_pool) {
        if (logger) {
            logger->log(Log_Level::ERROR, "Label", "Cannot set label font '" + font_name + "' because Engine::asset_pool is not initialized.");
        }
        return false;
    }

    IFont* found_font = Engine::asset_pool->get_font(font_name);
    if (!found_font) {
        if (logger) {
            logger->log(Log_Level::WARNING, "Label", "Font '" + font_name + "' was not found in Asset_Pool.");
        }
        return false;
    }

    font = found_font;
    return true;
}

void Label::set_scale(float new_scale) {
    if (new_scale <= 0.0f) {
        if (logger) {
            logger->log(Log_Level::WARNING, "Label", "Ignored invalid label scale: " + std::to_string(new_scale));
        }
        return;
    }

    scale = new_scale;
}

Vec Label::resize_to_text() {
    if (!font) {
        transform.size = {0.0f, 0.0f};
        return transform.size;
    }

    transform.size = font->get_size(text) * scale;
    return transform.size;
}

void Label::draw(SDL_Renderer* renderer) {
    if (!visible) {
        return;
    }

    if (!font || !font->is_loaded()) {
        if (logger) {
            logger->log(Log_Level::WARNING, "Label", "Attempted to draw a label with no loaded font.");
        }
        return;
    }

    font->draw(renderer, text, transform.pos, tint, scale);
}

Draw Label::make_draw_command() const {
    Draw cmd(font, text, transform, tint, z_index, scale);
    cmd.visible = visible && font && font->is_loaded();
    cmd.y_sort = y_sort;
    cmd.sort_y = transform.pos.y + transform.size.y + y_sort_offset;
    cmd.camera_space = camera_space;
    return cmd;
}

void Label::submit_draw_commands(Render_Pool& render_pool) {
    Draw text_command = make_draw_command();
    if (!text_command.visible) return;

    if (shadow_enabled) {
        Draw shadow_command = text_command;
        shadow_command.transform.pos += shadow_offset;
        shadow_command.tint = shadow_color;
        shadow_command.tint.a = static_cast<std::uint8_t>(
            (static_cast<std::uint16_t>(shadow_color.a) * tint.a) / 255u
        );
        render_pool.submit(shadow_command);
    }
    render_pool.submit(text_command);
}

TextBox::TextBox(const Transform& initial_transform,
                 IFont* font,
                 Object_Pool* object_pool,
                 Logger* logger)
    : Label(
          initial_transform.pos,
          initial_transform.size,
          initial_transform.rotation,
          "",
          font,
          logger,
          object_pool
      ) {
    name = "text_box";
    add_tag("text_box");
    camera_space = false;
    input_transparent = true;
    y_sort = false;
    z_index = 0;
    refresh_display_text();
}

TextBox::~TextBox() {
    blur();
}

bool TextBox::focus(bool clear_existing_text) {
    if (m_focused) return true;
    if (!Engine::window || !Input::acquire_block(this)) return false;

    if (!SDL_StartTextInput(Engine::window)) {
        Input::release_block(this);
        if (logger) {
            logger->log(
                Log_Level::ERROR,
                "TextBox",
                std::string("Failed to start SDL text input: ") + SDL_GetError()
            );
        }
        return false;
    }

    if (clear_existing_text) {
        m_value.clear();
        m_cursor = 0;
    } else {
        m_cursor = m_value.size();
    }

    m_waiting_for_release = false;
    m_release_scancode = SDL_SCANCODE_UNKNOWN;
    m_focused = true;
    visible = true;
    input_transparent = true;
    refresh_display_text();
    return true;
}

void TextBox::blur() {
    if (m_focused && Engine::window && SDL_TextInputActive(Engine::window)) {
        SDL_StopTextInput(Engine::window);
    }

    m_focused = false;
    m_waiting_for_release = false;
    m_release_scancode = SDL_SCANCODE_UNKNOWN;
    Input::release_block(this);
    visible = false;
    input_transparent = true;
    refresh_display_text();
}

TextBox_Result TextBox::handle_event(const SDL_Event& event) {
    if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST &&
        (m_focused || m_waiting_for_release)) {
        const bool was_focused = m_focused;
        blur();
        return was_focused
            ? TextBox_Result::CANCELLED
            : TextBox_Result::NONE;
    }

    if (m_waiting_for_release && event.type == SDL_EVENT_KEY_UP &&
        event.key.scancode == m_release_scancode) {
        m_waiting_for_release = false;
        m_release_scancode = SDL_SCANCODE_UNKNOWN;
        Input::release_block(this);
        return TextBox_Result::NONE;
    }

    if (!m_focused) return TextBox_Result::NONE;

    if (event.type == SDL_EVENT_TEXT_INPUT) {
        if (event.text.text) insert_text(event.text.text);
        return TextBox_Result::NONE;
    }
    if (event.type != SDL_EVENT_KEY_DOWN) return TextBox_Result::NONE;

    const SDL_Keycode key = event.key.key;
    const bool control = (event.key.mod & SDL_KMOD_CTRL) != 0;

    if (!event.key.repeat && (key == SDLK_RETURN || key == SDLK_KP_ENTER)) {
        finish(event.key.scancode);
        return TextBox_Result::SUBMITTED;
    }
    if (!event.key.repeat && key == SDLK_ESCAPE) {
        finish(event.key.scancode);
        return TextBox_Result::CANCELLED;
    }

    if (control && key == SDLK_V) {
        char* clipboard = SDL_GetClipboardText();
        if (clipboard) {
            insert_text(clipboard);
            SDL_free(clipboard);
        }
    } else if (control && key == SDLK_C) {
        SDL_SetClipboardText(m_value.c_str());
    } else if (control && key == SDLK_X) {
        SDL_SetClipboardText(m_value.c_str());
        clear();
    } else if (key == SDLK_BACKSPACE) {
        erase_previous_character();
    } else if (key == SDLK_DELETE) {
        erase_next_character();
    } else if (key == SDLK_LEFT) {
        m_cursor = previous_utf8_boundary(m_value, m_cursor);
        refresh_display_text();
    } else if (key == SDLK_RIGHT) {
        m_cursor = next_utf8_boundary(m_value, m_cursor);
        refresh_display_text();
    } else if (key == SDLK_HOME) {
        m_cursor = 0;
        refresh_display_text();
    } else if (key == SDLK_END) {
        m_cursor = m_value.size();
        refresh_display_text();
    }

    return TextBox_Result::NONE;
}

void TextBox::set_value(const std::string& value) {
    m_value = single_line_text(value);
    if (m_value.size() > m_max_length) {
        std::size_t safe_length = m_max_length;
        while (safe_length > 0 && safe_length < m_value.size() &&
               (static_cast<unsigned char>(m_value[safe_length]) & 0xC0u) == 0x80u) {
            --safe_length;
        }
        m_value.resize(safe_length);
    }
    m_cursor = m_value.size();
    refresh_display_text();
}

void TextBox::clear() {
    m_value.clear();
    m_cursor = 0;
    refresh_display_text();
}

void TextBox::set_prefix(const std::string& prefix) {
    m_prefix = single_line_text(prefix);
    refresh_display_text();
}

void TextBox::set_max_length(std::size_t maximum_bytes) {
    m_max_length = std::max<std::size_t>(1, maximum_bytes);
    if (m_value.size() > m_max_length) set_value(m_value);
}

void TextBox::finish(SDL_Scancode release_scancode) {
    if (Engine::window && SDL_TextInputActive(Engine::window)) {
        SDL_StopTextInput(Engine::window);
    }

    m_focused = false;
    visible = false;
    input_transparent = true;
    m_waiting_for_release = true;
    m_release_scancode = release_scancode;
    refresh_display_text();
}

void TextBox::refresh_display_text() {
    std::size_t visible_begin = 0;
    std::size_t visible_end = m_value.size();
    const std::size_t cursor = std::min(m_cursor, m_value.size());

    const auto build_display = [&]() {
        std::string display = m_prefix;
        if (visible_begin > 0) display += '<';
        const std::size_t cursor_in_display =
            display.size() + cursor - visible_begin;
        display.append(
            m_value, visible_begin, visible_end - visible_begin
        );
        if (visible_end < m_value.size()) display += '>';
        if (m_focused) display.insert(cursor_in_display, "|");
        return display;
    };

    std::string display = build_display();
    IFont* font = get_font();
    const float maximum_width = transform.size.x;
    while (font && maximum_width > 0.0f &&
           font->get_size(display).x * get_scale() > maximum_width) {
        if (visible_begin < cursor) {
            visible_begin = next_utf8_boundary(m_value, visible_begin);
        } else if (visible_end > cursor) {
            visible_end = previous_utf8_boundary(m_value, visible_end);
        } else {
            break;
        }
        display = build_display();
    }

    Label::set_text(display);
}

void TextBox::insert_text(const std::string& text) {
    const std::string normalized = single_line_text(text);
    std::size_t source = 0;
    while (source < normalized.size() && m_value.size() < m_max_length) {
        const std::size_t next = next_utf8_boundary(normalized, source);
        const std::size_t byte_count = next - source;
        if (m_value.size() + byte_count > m_max_length) break;
        m_value.insert(m_cursor, normalized, source, byte_count);
        m_cursor += byte_count;
        source = next;
    }
    refresh_display_text();
}

void TextBox::erase_previous_character() {
    if (m_cursor == 0 || m_value.empty()) return;
    const std::size_t previous = previous_utf8_boundary(m_value, m_cursor);
    m_value.erase(previous, m_cursor - previous);
    m_cursor = previous;
    refresh_display_text();
}

void TextBox::erase_next_character() {
    if (m_cursor >= m_value.size()) return;
    const std::size_t next = next_utf8_boundary(m_value, m_cursor);
    m_value.erase(m_cursor, next - m_cursor);
    refresh_display_text();
}

std::size_t TextBox::previous_utf8_boundary(const std::string& text,
                                            std::size_t position) {
    position = std::min(position, text.size());
    if (position == 0) return 0;
    --position;
    while (position > 0 &&
           (static_cast<unsigned char>(text[position]) & 0xC0u) == 0x80u) {
        --position;
    }
    return position;
}

std::size_t TextBox::next_utf8_boundary(const std::string& text,
                                        std::size_t position) {
    position = std::min(position, text.size());
    if (position >= text.size()) return text.size();
    ++position;
    while (position < text.size() &&
           (static_cast<unsigned char>(text[position]) & 0xC0u) == 0x80u) {
        ++position;
    }
    return position;
}

std::string TextBox::single_line_text(std::string text) {
    std::replace(text.begin(), text.end(), '\r', ' ');
    std::replace(text.begin(), text.end(), '\n', ' ');
    std::replace(text.begin(), text.end(), '\t', ' ');
    return text;
}
