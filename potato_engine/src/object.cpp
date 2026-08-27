#include "object.h"
#include "script-base.h"
#include "engine.h"
#include <algorithm>
#include <cmath>

void Object::free() {
    if (m_free_number == 0) {
        detach_script();
        m_free_number = 1;
    } else if (m_free_number == 1) {
        if (logger) {
            logger->log(Log_Level::WARNING, "Object", "Attempted to free an already freed Object. Double free protection triggered.");
        }
        m_free_number = 2;
    } else {
        if (logger) {
            logger->log(Log_Level::ERROR, "Object", "Double-free protection triggered multiple times. Object may have been deleted twice.");
        }
    }
}

void Object::draw(SDL_Renderer* renderer) {
    if (texture && texture->is_loaded()) {
        texture->draw(renderer, transform.pos, transform.size, transform.rotation);
    if (logger && logger->is_flood_logging()) {
        logger->log(Log_Level::DEBUG, "Object", "Object drawn at position: (" + std::to_string(transform.pos.x) + ", " + std::to_string(transform.pos.y) + ") with size: (" + std::to_string(transform.size.x) + ", " + std::to_string(transform.size.y) + ")");
        }
    } else {
        if (logger) {
            logger->log(Log_Level::WARNING, "Object", "Attempted to draw an object with no loaded texture.");
        }
    }
}

Draw Object::make_draw_command() const {
    Draw cmd;
    cmd.texture = texture;
    cmd.transform = transform;
    cmd.source_rect = source_rect;
    cmd.use_source_rect = use_source_rect;
    cmd.tint = tint;
    cmd.z_index = z_index;
    cmd.y_sort = y_sort;
    cmd.sort_y = transform.pos.y + transform.size.y + y_sort_offset;
    cmd.camera_space = camera_space;
    return cmd;
}

void Object::submit_draw_commands(Render_Pool& render_pool) {
    render_pool.submit(make_draw_command());
}

void Object::scale_centered(float scale_factor, bool animated, float anim_speed) {
    Vec target_size = transform.size * scale_factor;
    Vec center = { transform.pos.x + transform.size.x / 2.0f, transform.pos.y + transform.size.y / 2.0f };

    if (animated) {
        float t = std::min(1.0f, anim_speed * (Engine::delta_time / 1000.0f));
        transform.size.x += (target_size.x - transform.size.x) * t;
        transform.size.y += (target_size.y - transform.size.y) * t;
    } else {
        transform.size = target_size;
    }

    transform.pos.x = center.x - transform.size.x / 2.0f;
    transform.pos.y = center.y - transform.size.y / 2.0f;
}

void Object::scale_centered_condition(float scale_factor, Vec original_size, bool condition, bool animated, float anim_speed) {
    Vec target_size = condition ? original_size * scale_factor : original_size;
    Vec center = { transform.pos.x + transform.size.x / 2.0f, transform.pos.y + transform.size.y / 2.0f };

    if (animated) {
        float t = std::min(1.0f, anim_speed * (Engine::delta_time / 1000.0f));
        transform.size.x += (target_size.x - transform.size.x) * t;
        transform.size.y += (target_size.y - transform.size.y) * t;
    } else {
        transform.size = target_size;
    }

    transform.pos.x = center.x - transform.size.x / 2.0f;
    transform.pos.y = center.y - transform.size.y / 2.0f;
}

UI_Object::UI_Object()
    : Object(Vec{}, Vec{}) {
    configure_as_ui();
}

UI_Object::UI_Object(Vec p, Vec s, Vec r, Texture* t, Object_Pool* objp, Logger* l)
    : Object(p, s, r, t, objp, l) {
    configure_as_ui();
}

UI_Object::UI_Object(float x, float y, float w, float h, Texture* t,
                     Object_Pool* objp, Logger* l)
    : Object(x, y, w, h, t, objp, l) {
    configure_as_ui();
}

UI_Object::UI_Object(float x, float y, float w, float h, float rx, float ry,
                     Texture* t, Object_Pool* objp, Logger* l)
    : Object(x, y, w, h, rx, ry, t, objp, l) {
    configure_as_ui();
}

UI_Object::UI_Object(Transform value, Texture* t, Object_Pool* objp, Logger* l)
    : Object(value, t, objp, l) {
    configure_as_ui();
}

void UI_Object::configure_as_ui() {
    camera_space = false;
    z_index = default_z_index;
    y_sort = false;
}

bool UI_Object::on_hover(const Vec& mouse_pos) const {
    return is_interactive() && Object::on_hover(mouse_pos);
}

bool UI_Object::on_click(const Vec& mouse_pos) const {
    return on_hover(mouse_pos);
}

bool Button::on_hover(const Vec& mouse_pos) const {
    return UI_Object::on_hover(mouse_pos);
}

    void Object::set_texture_opacity(float alpha) {
        if (texture && texture->get_sdl_texture()) {
            SDL_SetTextureAlphaMod(texture->get_sdl_texture(), static_cast<Uint8>(alpha * 255.0f));
        }
    }

bool Button::on_click(const Vec& mouse_pos) const {
    if (UI_Object::on_click(mouse_pos)) {
        if (logger) {
            logger->log(Log_Level::DEBUG, "Button", "Button clicked at position: (" + std::to_string(mouse_pos.x) + ", " + std::to_string(mouse_pos.y) + ")");
        }
        return true;
    } else {
        if (logger && logger->is_flood_logging()) {
            logger->log(Log_Level::DEBUG, "Button", "Button click attempted outside button bounds at position: (" + std::to_string(mouse_pos.x) + ", " + std::to_string(mouse_pos.y) + ")");
        }
        return false;
    }
}

UI_Value::UI_Value(float minimum, float maximum, float initial_value, float value_step) {
    set_range(minimum, maximum);
    set_step(value_step);
    set_value(initial_value);
}

void UI_Value::set_range(float minimum, float maximum) {
    if (minimum > maximum) std::swap(minimum, maximum);
    min_value = minimum;
    max_value = maximum;
    set_value(value);
}

void UI_Value::set_step(float value_step) {
    step = std::abs(value_step);
    set_value(value);
}

bool UI_Value::set_value(float new_value) {
    const float old_value = value;
    value = std::clamp(new_value, min_value, max_value);

    if (step > 0.0f && max_value > min_value) {
        value = min_value + std::round((value - min_value) / step) * step;
        value = std::clamp(value, min_value, max_value);
    }

    return value != old_value;
}

float UI_Value::normalized_value() const {
    const float range = max_value - min_value;
    if (range <= 0.0f) return 0.0f;
    return std::clamp((value - min_value) / range, 0.0f, 1.0f);
}

Slider::Slider()
    : UI_Object(), UI_Value() {}

Slider::Slider(Vec p, Vec s, float minimum, float maximum, float initial_value,
               UI_Orientation direction, Texture* t, Object_Pool* objp, Logger* l,
               float value_step)
    : UI_Object(p, s, Vec{}, t, objp, l),
      UI_Value(minimum, maximum, initial_value, value_step),
      orientation(direction) {}

Slider::Slider(float x, float y, float w, float h, float minimum, float maximum,
               float initial_value, UI_Orientation direction, Texture* t,
               Object_Pool* objp, Logger* l, float value_step)
    : Slider(Vec{x, y}, Vec{w, h}, minimum, maximum, initial_value, direction,
             t, objp, l, value_step) {}

float Slider::value_at(const Vec& pointer_pos) const {
    float normalized = 0.0f;
    if (orientation == UI_Orientation::Horizontal) {
        if (transform.size.x > 0.0f) {
            normalized = (pointer_pos.x - transform.pos.x) / transform.size.x;
        }
    } else if (transform.size.y > 0.0f) {
        normalized = 1.0f - (pointer_pos.y - transform.pos.y) / transform.size.y;
    }

    normalized = std::clamp(normalized, 0.0f, 1.0f);
    return min_value + normalized * (max_value - min_value);
}

bool Slider::update_from_pointer(const Vec& pointer_pos) {
    if (!is_interactive()) return false;
    set_value(value_at(pointer_pos));
    return true;
}

Vec Slider::thumb_center() const {
    const float normalized = normalized_value();
    if (orientation == UI_Orientation::Horizontal) {
        return {transform.pos.x + transform.size.x * normalized,
                transform.pos.y + transform.size.y * 0.5f};
    }

    return {transform.pos.x + transform.size.x * 0.5f,
            transform.pos.y + transform.size.y * (1.0f - normalized)};
}

Transform Slider::thumb_transform(Vec thumb_size) const {
    const Vec center = thumb_center();
    return {{center.x - thumb_size.x * 0.5f, center.y - thumb_size.y * 0.5f},
            thumb_size,
            transform.rotation};
}

Toggle::Toggle()
    : Button(), checked(false) {}

Toggle::Toggle(Vec p, Vec s, bool initial_state, Texture* t,
               Object_Pool* objp, Logger* l)
    : Button(p, s, Vec{}, t, objp, l), checked(initial_state) {}

Toggle::Toggle(float x, float y, float w, float h, bool initial_state,
               Texture* t, Object_Pool* objp, Logger* l)
    : Toggle(Vec{x, y}, Vec{w, h}, initial_state, t, objp, l) {}

bool Toggle::toggle_at(const Vec& pointer_pos) {
    if (!on_click(pointer_pos)) return false;
    checked = !checked;
    return true;
}

Progress_Bar::Progress_Bar()
    : UI_Object(), UI_Value() {
    input_transparent = true;
}

Progress_Bar::Progress_Bar(Vec p, Vec s, float minimum, float maximum,
                           float initial_value, UI_Orientation direction,
                           Texture* t, Object_Pool* objp, Logger* l)
    : UI_Object(p, s, Vec{}, t, objp, l),
      UI_Value(minimum, maximum, initial_value),
      orientation(direction) {
    input_transparent = true;
}

Progress_Bar::Progress_Bar(float x, float y, float w, float h, float minimum,
                           float maximum, float initial_value,
                           UI_Orientation direction, Texture* t,
                           Object_Pool* objp, Logger* l)
    : Progress_Bar(Vec{x, y}, Vec{w, h}, minimum, maximum, initial_value,
                   direction, t, objp, l) {}

Transform Progress_Bar::fill_transform() const {
    Transform fill = transform;
    const float normalized = normalized_value();

    if (orientation == UI_Orientation::Horizontal) {
        fill.size.x *= normalized;
    } else {
        fill.size.y *= normalized;
        fill.pos.y += transform.size.y - fill.size.y;
    }

    return fill;
}

void Object::attach_script(script* s) {
    component = s;
    s->owner   = this;
    Engine::object_scripts.push_back(s);
    s->on_start();
}

void Object::detach_script() {
    if (!component) return;

    component->on_destroy();

    auto& list = Engine::object_scripts;
    list.erase(std::remove(list.begin(), list.end(), component), list.end());

    delete component;
    component = nullptr;
}

Object::~Object() {
    if (object_pool) {
        object_pool->remove(this);
    }
    free();
}

void Object::add_tag(const std::string& tag) {
    if (tag.empty() || has_tag(tag)) return;
    tags.push_back(tag);
}

void Object::remove_tag(const std::string& tag) {
    tags.erase(std::remove(tags.begin(), tags.end(), tag), tags.end());
}

bool Object::has_tag(const std::string& tag) const {
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

void Object::register_with_pool() {
    if (object_pool) {
        object_pool->add(this);
    } else {
        if (logger) {
            logger->log(Log_Level::WARNING, "Object", "Engine::object_pool is not initialized. Object will not be tracked in the object pool.");
        }
    }
}

void Object_Pool::add(Object* obj) {
    if (!obj) return;
    if (std::find(objects.begin(), objects.end(), obj) == objects.end()) objects.push_back(obj);
}

void Object_Pool::remove(Object* obj) {
    if (!obj) return;

    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

Object* Object_Pool::find_by_name(const std::string& name) const {
    if (name.empty()) return nullptr;
    auto it = std::find_if(objects.begin(), objects.end(), [&](const Object* object) {
        return object && object->name == name;
    });
    return it != objects.end() ? *it : nullptr;
}

Object* Object_Pool::find_by_tag(const std::string& tag) const {
    if (tag.empty()) return nullptr;
    auto it = std::find_if(objects.begin(), objects.end(), [&](const Object* object) {
        return object && object->has_tag(tag);
    });
    return it != objects.end() ? *it : nullptr;
}

std::vector<Object*> Object_Pool::find_all_by_tag(const std::string& tag) const {
    std::vector<Object*> matches;
    if (tag.empty()) return matches;

    for (Object* object : objects) {
        if (object && object->has_tag(tag)) matches.push_back(object);
    }
    return matches;
}
