#include "potato-gameobject.h"
#include "potato-structures.h"
#include <algorithm>

// =============================================================================
// CONSTRUCTOR & DESTRUCTOR
// =============================================================================

gameobject::gameobject(const std::string& name)
    : m_name(name)
    , m_tag("")
    , m_pos()
    , m_active(true)
    , m_started(false)
    , m_parent(nullptr)
    , m_texture(nullptr)
{
}

gameobject::~gameobject() {
    destroy();
}

// =============================================================================
// LIFECYCLE METHODS
// =============================================================================

void gameobject::start() {
    if (m_started) return;
    m_started = true;
    call_start_on_scripts();

    // Start all children
    for (auto* child : m_children) {
        if (child && child->is_active()) {
            child->start();
        }
    }
}

void gameobject::update(float delta_time) {
    if (!m_active) return;

    // Ensure scripts are started
    if (!m_started) {
        start();
    }

    // Update all scripts
    for (auto* script : m_scripts) {
        if (script) {
            script->on_update(delta_time);
        }
    }

    // Update all children
    for (auto* child : m_children) {
        if (child && child->is_active()) {
            child->update(delta_time);
        }
    }
}

void gameobject::render() {
    if (!m_active) return;

    // Render all scripts
    for (auto* script : m_scripts) {
        if (script) {
            script->on_render();
        }
    }

    // Render all children
    for (auto* child : m_children) {
        if (child && child->is_active()) {
            child->render();
        }
    }
}

void gameobject::handle_event(const SDL_Event& event) {
    if (!m_active) return;

    // Pass event to all scripts
    for (auto* script : m_scripts) {
        if (script) {
            script->on_event(event);
        }
    }

    // Pass event to all children
    for (auto* child : m_children) {
        if (child && child->is_active()) {
            child->handle_event(event);
        }
    }
}

void gameobject::destroy() {
    // Destroy all scripts
    for (auto* script : m_scripts) {
        if (script) {
            script->on_destroy();
            delete script;
        }
    }
    m_scripts.clear();

    // Don't destroy children here - let the owner manage them
    m_children.clear();
    m_parent = nullptr;
}

// =============================================================================
// SCRIPT MANAGEMENT
// =============================================================================

void gameobject::add_script(potato_script* script) {
    if (!script) return;
    
    m_scripts.push_back(script);
    
    // If object is already started, start the new script immediately
    if (m_started) {
        script->on_start();
    }
}

void gameobject::remove_script(potato_script* script) {
    if (!script) return;

    auto it = std::find(m_scripts.begin(), m_scripts.end(), script);
    if (it != m_scripts.end()) {
        (*it)->on_destroy();
        delete *it;
        m_scripts.erase(it);
    }
}

// =============================================================================
// HIERARCHY MANAGEMENT
// =============================================================================

void gameobject::set_parent(gameobject* parent) {
    // Remove from old parent
    if (m_parent) {
        m_parent->remove_child(this);
    }

    // Set new parent
    m_parent = parent;

    // Add to new parent's children
    if (m_parent) {
        m_parent->add_child(this);
    }
}

void gameobject::add_child(gameobject* child) {
    if (!child) return;
    
    // Check if already a child
    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it == m_children.end()) {
        m_children.push_back(child);
        child->m_parent = this;
    }
}

void gameobject::remove_child(gameobject* child) {
    if (!child) return;

    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end()) {
        (*it)->m_parent = nullptr;
        m_children.erase(it);
    }
}

// =============================================================================
// WORLD TRANSFORM
// =============================================================================

void gameobject::get_world_position(float& x, float& y) const {
    x = m_pos.x;
    y = m_pos.y;

    if (m_parent) {
        float parent_x, parent_y;
        m_parent->get_world_position(parent_x, parent_y);
        x += parent_x;
        y += parent_y;
    }
}

float gameobject::get_world_rotation() const {
    float rotation = m_pos.rotation;

    if (m_parent) {
        rotation += m_parent->get_world_rotation();
    }

    // Keep in 0-360 range
    while (rotation >= 360.0f) rotation -= 360.0f;
    while (rotation < 0.0f) rotation += 360.0f;

    return rotation;
}

// =============================================================================
// TEXTURE MANAGEMENT
// =============================================================================

void gameobject::render_texture() {
    if (m_texture->get_sdl_texture()) {
        float rotation = get_world_rotation();

        SDL_FRect dest_rect = {
            static_cast<float>(m_pos.x),
            static_cast<float>(m_pos.y),
            static_cast<float>(m_pos.w),
            static_cast<float>(m_pos.h)
        };
        
    }
}



// =============================================================================
// HELPER METHODS
// =============================================================================

void gameobject::call_start_on_scripts() {
    for (auto* script : m_scripts) {
        if (script) {
            script->on_start();
        }
    }
}
