#ifndef ENTITY_H
#define ENTITY_H

#include "vec.h"
#include "texture.h"
#include "object.h"

/**
 * @brief Represents a game entity with position, size, rotation, health, and lifetime.
 * This class is only as a sample so you understand how to use the Object class. 
 * You can create your own entity classes that inherit from Object and add your own properties and methods.
 * @note Don't forget to call `free()` in the destructor of your entity class to avoid memory leaks, or
 * include a `Texture` in your entity class and let the Object class handle the texture memory management.
 */

class Entity : public Object {
public:
    float health;
    int16_t lifetime = -1;
    bool active = true;


    Entity() = default;

    Entity(Vec p, Vec s, Vec r = {0.0f, 0.0f}, Texture* t = nullptr, Object_Pool *objp = nullptr, Logger *l = nullptr)
        : Object(p, s, r, t, objp, l), health(100.0f) {}

    Entity(Transform t, Texture* tex = nullptr, Object_Pool *objp = nullptr, Logger *l = nullptr)
        : Object(t.pos, t.size, t.rotation, tex, objp, l), health(100.0f) {}

    ~Entity() {
        free();
    }

    /**
     * @brief Frees the entity's resources and marks it as inactive.
     * This method should be called when the entity is no longer needed to avoid memory leaks.
     */
    void free();

    /**
     * @brief Deactivates the entity, preventing it from being updated or rendered.
     */
    void deactivate() { active = false; }

    /**
     * @brief Activates the entity, allowing it to be updated and rendered.
     */
    void activate() { active = true; }

    /**
     * @brief Checks if the entity is alive based on its health and lifetime.
     * @return True if the entity is alive (health > 0 and lifetime is either negative or positive), false otherwise.
     */
    bool is_alive() const { return health > 0.0f && (lifetime < 0 || lifetime > 0); }

    /**
     * @brief Gets the position of the entity.
     * @return The position of the entity as a Vec.
     */
    Vec get_pos () const { return transform.pos; }

    /**
     * @brief Sets the position of the entity.
     * @param new_pos The new position to set for the entity.
     */
    void set_pos (const Vec& new_pos) { transform.pos = new_pos; }

    /**
     * @brief Gets the size of the entity.
     * @return The size of the entity as a Vec.
     */
    Texture* get_texture() const { return texture; }

    /**
     * @brief Sets the texture of the entity.
     * @param new_texture Pointer to the new texture to set for the entity.
     */
    void set_texture(Texture* new_texture);

    
private:
    uint8_t m_free_number = 0; // double freeing protection: 0 = not freed, 1 = freed once, 2 = freed twice
};

#endif