#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <memory>
#include "potato-script-base.h"
#include "potato-structures.h"
#include "potato-texture.h"

// =============================================================================
// GAMEOBJECT CLASS
// =============================================================================
// Main GameObject class that can have scripts and components attached
class gameobject {
public:
    // Constructor & Destructor
    gameobject(const std::string& name = "GameObject");
    ~gameobject();

    // Lifecycle methods
    void start();
    void update(float delta_time);
    void render();
    void handle_event(const SDL_Event& event);
    void destroy();

    // Script management
    void add_script(potato_script* script);
    template<typename T>
    T* get_script();
    void remove_script(potato_script* script);

    // Transform access
    pos& get_pos() { return m_pos; }
    const pos& get_pos() const { return m_pos; }

    // Position shortcuts
    void set_position(float x, float y) { m_pos.x = x; m_pos.y = y; }
    void get_position(float& x, float& y) const { x = m_pos.x; y = m_pos.y; }
    float get_x() const { return m_pos.x; }
    float get_y() const { return m_pos.y; }

    // Rotation shortcuts
    void set_rotation(float degrees) { m_pos.rotation = degrees; }
    float get_rotation() const { return m_pos.rotation; }

    // Scale shortcuts
    void set_scale(float sx, float sy) { m_pos.w = sx; m_pos.h = sy; }
    void set_scale(float s) { m_pos.w = s; m_pos.h = s; }

    // Active state
    void set_active(bool active) { m_active = active; }
    bool is_active() const { return m_active; }

    // Name
    void set_name(const std::string& name) { m_name = name; }
    const std::string& get_name() const { return m_name; }

    // Tag system (for grouping and finding objects)
    void set_tag(const std::string& tag) { m_tag = tag; }
    const std::string& get_tag() const { return m_tag; }

    // Parent-child hierarchy
    void set_parent(gameobject* parent);
    gameobject* get_parent() const { return m_parent; }
    void add_child(gameobject* child);
    void remove_child(gameobject* child);
    const std::vector<gameobject*>& get_children() const { return m_children; }

    // World position (considering parent hierarchy)
    void get_world_position(float& x, float& y) const;
    float get_world_rotation() const;

    // Texture component management
    potato_texture* get_texture() const { return m_texture; }
    void set_texture(potato_texture* texture) { m_texture = texture; }
    void render_texture();

private:
    std::string m_name;
    std::string m_tag;
    pos m_pos;
    bool m_active;
    bool m_started;

    // Texture component (optional)
    potato_texture* m_texture;

    // Scripts attached to this object
    std::vector<potato_script*> m_scripts;

    // Parent-child hierarchy
    gameobject* m_parent;
    std::vector<gameobject*> m_children;

    // Helper methods
    void call_start_on_scripts();
    
};

// =============================================================================
// TEMPLATE IMPLEMENTATION
// =============================================================================
template<typename T>
T* gameobject::get_script() {
    for (auto* script : m_scripts) {
        T* typed_script = dynamic_cast<T*>(script);
        if (typed_script) {
            return typed_script;
        }
    }
    return nullptr;
}