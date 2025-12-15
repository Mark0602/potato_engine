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
    , m_sdltexture(nullptr)
    , m_gputexture(nullptr)
    , m_device(nullptr)
    , m_width(0)
    , m_height(0)
{
    if (!m_file_path.empty()) {
        load();
    }
    if (m_gputexture && m_sdltexture) { 
        debug::error("Please avoid using both gpu and sdl textures in potato_texture, as it may lead to resource management issues. In this scenario, the gpu texture will be prioritized.");
        m_sdltexture = nullptr;
    }
}

potato_texture::~potato_texture() {
    unload();
}

// =============================================================================
// TEXTURE LOADING
// =============================================================================

bool potato_texture::load() {
    //m_gputexture = SDL_CreateGPUTexture(m_device)
    return true;
}

void potato_texture::unload() {
    if (m_sdltexture) {
        SDL_DestroyTexture(m_sdltexture);
        m_sdltexture = nullptr;
    }
    if (m_gputexture) {
        SDL_ReleaseGPUTexture(m_device, m_gputexture);
        m_gputexture = nullptr;
    }
    m_width = 0;
    m_height = 0;
}
