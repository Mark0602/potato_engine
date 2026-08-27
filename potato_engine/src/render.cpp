#include "render.h"

#include "camera.h"
#include "engine.h"
#include "fonts.h"
#include "light.h"
#include "texture.h"

bool GPU_Renderer::init(SDL_Window* window) {
    shutdown();
    if (!window) {
        SDL_SetError("GPU_Renderer::init requires a window");
        return false;
    }

    // Passing nullptr asks SDL to create the best available SDL_GPU device.
    // SDL's GPU renderer is deliberately SDL_Renderer-compatible, which lets
    // the existing draw API, fonts and geometry batching run unchanged.
    m_renderer = SDL_CreateGPURenderer(nullptr, window);
    if (!m_renderer) {
        return false;
    }

    m_device = SDL_GetGPURendererDevice(m_renderer);
    if (!m_device) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
        return false;
    }

    return true;
}

void GPU_Renderer::shutdown() {
    m_device = nullptr;
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
}

bool GPU_Renderer::begin_frame() {
    if (!m_renderer) return false;
    return SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255) &&
           SDL_RenderClear(m_renderer);
}

void GPU_Renderer::end_frame() {
    if (m_renderer) {
        SDL_RenderPresent(m_renderer);
    }
}

const char* GPU_Renderer::driver_name() const {
    return m_device ? SDL_GetGPUDeviceDriver(m_device) : nullptr;
}

void Render_Pool::flush() {
    std::stable_sort(draw_commands.begin(), draw_commands.end(),
        [](const Draw& a, const Draw& b) {
            if (a.z_index != b.z_index) return a.z_index > b.z_index;

            // Keep fixed-order commands behind the Y-sorted world group. The
            // old mixed comparison returned false in both directions, which
            // broke strict weak ordering whenever two Y-sorted commands had a
            // non-Y-sorted command between them.
            if (a.y_sort != b.y_sort) return !a.y_sort;
            if (a.y_sort && a.sort_y != b.sort_y) return a.sort_y < b.sort_y;
            return false;
        }
    );

    Camera* camera = nullptr;
    if (Engine::camera_pool) {
        camera = Engine::camera_pool->active_camera();
    }
    
    for (const Draw& draw : draw_commands) {
        if (!draw.visible) continue;

        Draw visible_draw = draw;
        const bool is_screen_space = !draw.camera_space;
        if (Engine::lighting) {
            const SDL_ScaleMode scale_mode = draw.texture
                ? draw.texture->get_scale_mode()
                : SDL_SCALEMODE_LINEAR;
            Engine::lighting->set_active(!is_screen_space, scale_mode);
        }
        if (camera && !is_screen_space) {
            if (!camera->can_see(draw.transform)) {
                continue;
            }

            visible_draw.transform = camera->world_to_screen(draw.transform);
            visible_draw.scale *= camera->get_zoom();
        }

        if (draw.texture) {
            const SDL_FRect* source = visible_draw.use_source_rect ? &visible_draw.source_rect : nullptr;
            visible_draw.texture->draw_ex(renderer, source, visible_draw.transform, visible_draw.tint);
        } else if (draw.font) {
            visible_draw.font->draw(renderer, visible_draw.text, visible_draw.transform.pos, visible_draw.tint, visible_draw.scale);
        }
    }
    if (Engine::lighting) Engine::lighting->set_active(false);
    draw_commands.clear();
}
