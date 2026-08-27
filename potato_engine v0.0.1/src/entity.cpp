#include "entity.h"


void Entity::free() {
    if (m_free_number == 0) {
        if (texture) {
            if (logger) logger->log(Log_Level::DEBUG, "Entity", "Entity texture freed.");
            delete texture;
            texture = nullptr;
        }
        m_free_number = 1;
    } else if (m_free_number == 1) {
        if (logger) logger->log(Log_Level::WARNING, "Entity", "Attempted to free an already freed Entity. Double-free protection triggered.");
        m_free_number = 2;
    } else {
        if (logger) logger->log(Log_Level::ERROR, "Entity", "Double-free protection triggered multiple times. Entity may have been deleted twice.");
    }
}

void Entity::set_texture(Texture* new_texture) {
    if (texture != new_texture) {
        if (texture) {
            delete texture; // Free the old texture
        }
        texture = new_texture; // Set the new texture
    }
}