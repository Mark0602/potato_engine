#pragma once

#include <SDL3/SDL_gpu.h>
#include <vector>
#include "potato-structures.h"

// =============================================================================
// POTATO VERTEX BUFFER CLASS
// =============================================================================
// Dinamikus vertex buffer GPU rajzoláshoz SDL3 GPU API-val
// Támogat vertex zárat (lock) az adatok frissítéséhez

class potato_vertex_buffer {
public:
    potato_vertex_buffer(SDL_GPUDevice* device, size_t max_vertices);
    ~potato_vertex_buffer();

    bool lock();
    void unlock();

    vertex* get_vertices();

    size_t get_max_vertices() const { return m_max_vertices; }
    size_t get_vertex_count() const { return m_vertex_count; }
    void set_vertex_count(size_t count);

    SDL_GPUBuffer* get_gpu_buffer() const { return m_gpu_buffer; }

    void clear();

    // 🔹 ÚJ: explicit upload függvény, command bufferrel
    void update_gpu_buffer(SDL_GPUCommandBuffer* cmdbuf);

private:
    SDL_GPUDevice*          m_device;
    SDL_GPUBuffer*          m_gpu_buffer;
    SDL_GPUTransferBuffer*  m_transfer_buffer;
    std::vector<vertex>     m_vertices;
    size_t                  m_max_vertices;
    size_t                  m_vertex_count;
    bool                    m_locked;
};