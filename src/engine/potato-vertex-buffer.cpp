#include "potato-vertex-buffer.h"
#include <cstring>
#include <iostream>

// =============================================================================
// CONSTRUCTOR & DESTRUCTOR
// =============================================================================

potato_vertex_buffer::potato_vertex_buffer(SDL_GPUDevice* device, size_t max_vertices)
    : m_device(device)
    , m_gpu_buffer(nullptr)
    , m_transfer_buffer(nullptr)
    , m_max_vertices(max_vertices)
    , m_vertex_count(0)
    , m_locked(false)
{
    if (!device) {
        std::cerr << "ERROR: GPU device is null in vertex buffer constructor" << std::endl;
        return;
    }

    // CPU oldali tárhely
    m_vertices.reserve(max_vertices);

    // GPU vertex buffer
    SDL_GPUBufferCreateInfo buffer_info{};
    buffer_info.size  = max_vertices * sizeof(m_vertex_count);
    buffer_info.usage = SDL_GPU_BUFFERUSAGE_VERTEX;

    m_gpu_buffer = SDL_CreateGPUBuffer(device, &buffer_info);
    if (!m_gpu_buffer) {
        std::cerr << "ERROR: Failed to create GPU vertex buffer" << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
    }

    // Transfer buffer (UPLOAD)
    SDL_GPUTransferBufferCreateInfo transfer_info{};
    transfer_info.size  = max_vertices * sizeof(vertex);
    transfer_info.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD;

    m_transfer_buffer = SDL_CreateGPUTransferBuffer(device, &transfer_info);
    if (!m_transfer_buffer) {
        std::cerr << "ERROR: Failed to create GPU transfer buffer" << std::endl;
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
    }
}

potato_vertex_buffer::~potato_vertex_buffer() {
    if (m_gpu_buffer && m_device) {
        SDL_ReleaseGPUBuffer(m_device, m_gpu_buffer);
        m_gpu_buffer = nullptr;
    }

    if (m_transfer_buffer && m_device) {
        SDL_ReleaseGPUTransferBuffer(m_device, m_transfer_buffer);
        m_transfer_buffer = nullptr;
    }

    m_vertices.clear();
}

// =============================================================================
// LOCKING & UNLOCKING
// =============================================================================

bool potato_vertex_buffer::lock() {
    if (m_locked) {
        std::cerr << "WARNING: Vertex buffer already locked" << std::endl;
        return false;
    }

    m_locked = true;
    return true;
}

void potato_vertex_buffer::unlock() {
    if (!m_locked) {
        std::cerr << "WARNING: Vertex buffer is not locked" << std::endl;
        return;
    }

    m_locked = false;
    // ❗ Itt NEM töltjük fel a GPU-t, majd a render loopban: update_gpu_buffer(cmdbuf)
}

// =============================================================================
// VERTEX DATA ACCESS
// =============================================================================

vertex* potato_vertex_buffer::get_vertices() {
    if (!m_locked) {
        std::cerr << "WARNING: Trying to get vertices without locking buffer" << std::endl;
        return nullptr;
    }

    if (m_vertices.empty()) {
        std::cerr << "WARNING: Vertex buffer is empty - call set_vertex_count() first" << std::endl;
        return nullptr;
    }

    return m_vertices.data();
}

void potato_vertex_buffer::set_vertex_count(size_t count) {
    if (count > m_max_vertices) {
        std::cerr << "ERROR: Vertex count " << count
                  << " exceeds max " << m_max_vertices << std::endl;
        return;
    }

    m_vertex_count = count;
    m_vertices.resize(count);
}

// =============================================================================
// BUFFER MANAGEMENT
// =============================================================================

void potato_vertex_buffer::update_gpu_buffer(SDL_GPUCommandBuffer* cmdbuf) {
    if (!m_device || !m_gpu_buffer || !m_transfer_buffer) {
        std::cerr << "ERROR: Cannot update GPU buffer - device or buffers are null" << std::endl;
        return;
    }

    if (m_vertex_count == 0) {
        // Nincs mit feltölteni
        return;
    }

    if (!cmdbuf) {
        std::cerr << "ERROR: Command buffer is null in update_gpu_buffer" << std::endl;
        return;
    }

    const size_t size_bytes = m_vertex_count * sizeof(m_vertices);
    //const size_t size_bytes = m_vertex_count * sizeof(vertex);

    // 1) CPU -> transfer buffer (Map + memcpy)
    void* mapped = SDL_MapGPUTransferBuffer(
        m_device,
        m_transfer_buffer,
        false // was true
    );

    if (!mapped) {
        std::cerr << "ERROR: Failed to map GPU transfer buffer" << std::endl;
        return;
    }

    //std::memcpy(mapped, m_vertices.data(), size_bytes);
    SDL_memcpy(mapped, m_vertices.data(), size_bytes);

    SDL_UnmapGPUTransferBuffer(m_device, m_transfer_buffer);

    // 2) Transfer buffer -> GPU buffer copy pass
    SDL_GPUCopyPass* copy_pass = SDL_BeginGPUCopyPass(cmdbuf);
    if (!copy_pass) {
        std::cerr << "ERROR: Failed to begin GPU copy pass" << std::endl;
        return;
    }

    SDL_GPUTransferBufferLocation src{
        .transfer_buffer = m_transfer_buffer,
        .offset = 0
    };
    SDL_GPUBufferRegion dst{
        .buffer = m_gpu_buffer,
        .offset = 0,
        .size   = size_bytes
    };

    SDL_UploadToGPUBuffer(
        copy_pass,
        &src,
        &dst,
        true // was false
    );

    SDL_EndGPUCopyPass(copy_pass);
}
void potato_vertex_buffer::clear() {
    if (m_locked) {
        std::cerr << "WARNING: Cannot clear locked buffer" << std::endl;
        return;
    }

    m_vertices.clear();
    m_vertex_count = 0;
}