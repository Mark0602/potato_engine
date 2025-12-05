#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <memory>
#include "potato-script-base.h"

// =============================================================================
// TEXTURE COMPONENT
// =============================================================================
// Represents a texture resource

class potato_texture {
public:
    potato_texture(const std::string& file_path);
    ~potato_texture();

    // Load texture from file
    bool load();

    // Unload texture
    void unload();

    // Get SDL_Texture pointer
    SDL_Texture* get_sdl_texture() const { return m_texture; }

    // Get texture dimensions
    int get_width() const { return m_width; }
    int get_height() const { return m_height; }
private:
    std::string m_file_path;
    SDL_Texture* m_texture;
    int m_width;
    int m_height;
};