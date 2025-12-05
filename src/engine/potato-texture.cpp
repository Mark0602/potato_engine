#include "potato-texture.h"

#ifdef SDL_IMAGE_H_
    #include <SDL3/SDL_image.h>
    #define HAS_SDL_IMAGE 1
#else
    #define HAS_SDL_IMAGE 0
#endif

#include <iostream>

// =============================================================================
// CONSTRUCTOR & DESTRUCTOR
// =============================================================================

potato_texture::potato_texture(const std::string& file_path)
    : m_file_path(file_path)
    , m_texture(nullptr)
    , m_width(0)
    , m_height(0)
{
}

potato_texture::~potato_texture() {
    unload();
}

// =============================================================================
// TEXTURE LOADING
// =============================================================================

bool potato_texture::load() {
    // Unload previous texture if exists
    unload();

#if !HAS_SDL_IMAGE
    std::cerr << "SDL_image not available - cannot load texture: " << m_file_path << std::endl;
    std::cerr << "Please install SDL3_image to enable image loading" << std::endl;
    return false;
#endif

#ifdef HAS_SDL_IMAGE_REAL
    // Load image using SDL_image
    SDL_Surface* surface = IMG_Load(m_file_path.c_str());
    if (!surface) {
        std::cerr << "Failed to load texture: " << m_file_path << std::endl;
        std::cerr << "SDL_image Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Store dimensions
    m_width = surface->w;
    m_height = surface->h;

    std::cout << "Loaded texture: " << m_file_path 
              << " (" << m_width << "x" << m_height << ")" << std::endl;

    SDL_DestroySurface(surface);
    return true;
#else
    std::cerr << "SDL_image not compiled - cannot load texture: " << m_file_path << std::endl;
    return false;
#endif
}

void potato_texture::unload() {
    if (m_texture) {
        // Note: SDL3 uses SDL_DestroyTexture for SDL_Texture
        // For GPU textures, we'd use SDL_ReleaseGPUTexture
        // This depends on your rendering backend
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }
    m_width = 0;
    m_height = 0;
}
