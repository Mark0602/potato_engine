#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <memory>
#include "potato-script-base.h"
#include <SDL3/SDL_gpu.h>
#include "potato-utils.h"
#include "potato-engine.h"

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
    SDL_Texture* get_sdl_texture() const { return m_sdltexture; }

    // Set SDL Texture pointer
    void set_sdl_texture(SDL_Texture* texture) { m_sdltexture = texture; }

    // Get SDL_GPUTexture pointer
    SDL_GPUTexture* get_gpu_texture() const { return m_gputexture; }

    // Set SDL GPU Texture pointer
    void set_gpu_texture(SDL_GPUTexture* texture) { m_gputexture = texture; }

    // Get texture dimensions
    int get_width() const { return m_width; }
    int get_height() const { return m_height; }
private:
    std::string m_file_path;
    SDL_GPUTexture* m_gputexture = nullptr;
    SDL_Texture* m_sdltexture = nullptr;
    SDL_GPUDevice *m_device = nullptr;
    int m_width;
    int m_height;
};