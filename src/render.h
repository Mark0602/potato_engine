#ifndef RENDER_H
#define RENDER_H

#include "debug.h"
#include "vec.h"
#include <SDL3/SDL.h>
#include <vector>
#include <algorithm>
#include <string>
#include "color.h"

class Texture;
class IFont;

/**
 * @brief Represents a single draw command for the render pool.
 * Contains a pointer to the texture to draw, the transform (position, size, rotation),
 * the color tint, and the z-index for draw order.
 */
struct Draw {
    Texture* texture = nullptr;
    IFont* font = nullptr;
    std::string text;
    
    Transform transform{};
    SDL_FRect source_rect{};
    bool use_source_rect = false;
    Color tint = Color::white();
    float scale = 1.0f;

    uint8_t z_index = 128; ///< Layer order. Higher values draw first; lower values draw later/on top.
    bool y_sort = false; ///< Within the same z-index, draw lower world-space feet later (in front).
    float sort_y = 0.0f; ///< World-space Y coordinate used when y_sort is enabled.

    bool visible = true; ///< If false, the draw command is skipped.
    bool camera_space = true; ///< If true, the active camera transforms and culls this command. Independent from z_index.

    Draw() = default;

    /**
     * @brief Constructs a Draw_Command with the specified texture and transform.
     * @param texture Pointer to the Texture to draw.
     * @param transform The Transform (position, size, rotation) for the draw command.
     */
    Draw(Texture* texture, const Transform& transform)
        : texture(texture), transform(transform) {}

    /**
     * @brief Constructs a Draw_Command with the specified texture, transform, and z-index.
     * @param texture Pointer to the Texture to draw.
     * @param transform The Transform (position, size, rotation) for the draw command.
     * @param z_index The z-index for draw order. Lower values are drawn later (on top).
     */
    Draw(Texture* texture, const Transform& transform, uint8_t z_index)
        : texture(texture), transform(transform), z_index(z_index) {}

    /**
     * @brief Constructs a Draw_Command with the specified texture, transform, tint, and z-index.
     * @param texture Pointer to the Texture to draw.
     * @param transform The Transform (position, size, rotation) for the draw command.
     * @param tint The Color tint to apply to the texture.
     * @param z_index The z-index for draw order. Lower values are drawn later (on top).
     */
    Draw(Texture* texture, const Transform& transform, const Color& tint, uint8_t z_index = 128)
        : texture(texture), transform(transform), tint(tint), z_index(z_index) {}

    /**
     * @brief Constructs a text draw command with the specified font, text, transform, tint, z-index and scale.
     * @param font Pointer to the IFont to draw with. The font is borrowed from Asset_Pool or another owner.
     * @param text Text to draw.
     * @param transform Position and optional bounds for the text.
     * @param tint Text color.
     * @param z_index The z-index for draw order.
     * @param scale Text scale multiplier.
     */
    Draw(IFont* font, const std::string& text, const Transform& transform, const Color& tint, uint8_t z_index = 128, float scale = 1.0f)
        : font(font), text(text), transform(transform), tint(tint), z_index(z_index), scale(scale) {}
};

/**
 * @brief Manages a collection of Objects and draws them each frame.
 *
 * Add objects with `submit()`. The render pool will automatically sort them by z-index and draw them in the correct order.
 * We suggest using z_index = 0 for the cursor, z_index = 1 for UI elements, and z_index = 255 for background elements. The default z_index is 128 (middle of the range).
 * (also `flush()` can be used to sort all the draw commands by z-index, it is already called in the main loop.
 * You usually don't need to call it manually, unless you want to rewrite the main loop).
 * Please use the Render_Pool to manage all your draw commands, as it will handle sorting and drawing them in the correct order.
 * Also you can still draw objects manually, but it is not recommended as it will not be sorted by z-index and will not be managed by the render pool.
 *
 * @attention You do not have to care about removing Draw calls from the Render_Pool, as it will automatically clear them each frame after drawing.
 * You only need to submit new Draw calls each frame.
 * Example:
 * // on_start():
 * ```cpp
 * Engine::render_pool->submit(Draw{
 *     texture,
 *     transform,
 *     tint,
 *     z_index
 * });
 * ```
 */
class Render_Pool {
public:
    /**
     * @brief Constructs a Render_Pool.
     * @param renderer The SDL renderer used for all draw calls.
     * @param logger   Optional logger for debug messages.
     */
    Render_Pool(SDL_Renderer* renderer) : renderer(renderer) {};
    ~Render_Pool() = default;

    /**
     * @brief Clears all draw commands from the pool.
     * This does not delete the textures or objects; it simply clears the list of commands to be drawn.
     */
    void clear() { draw_commands.clear(); }

    /**
     * @brief Sorts the draw commands by z-index and submits them to the SDL renderer.
     * This should be called once per frame to render all queued draw commands.
     */
    void flush();

    /**
     * @brief Submits a draw command to the render pool.
     * If both the texture and font are null, or the command is not visible, it will be ignored.
     */
    void submit(const Draw& draw_command) {
        if (draw_command.texture == nullptr && draw_command.font == nullptr) return;
        if (!draw_command.visible) return;
        draw_commands.push_back(draw_command);
    }

    /**
     * @brief Checks if the render pool is empty (no draw commands).
     * @return True if there are no draw commands, false otherwise.
     */
    bool empty() const { return draw_commands.empty(); }

    /**
     * @brief Returns the number of draw commands in the render pool.
     * @return The number of draw commands.
     */
    size_t size() const { return draw_commands.size(); }
    

private:
    SDL_Renderer* renderer;
    std::vector<Draw> draw_commands;
};



class GPU_Renderer {
public:
    GPU_Renderer() = default;
    ~GPU_Renderer() { shutdown(); }

    GPU_Renderer(const GPU_Renderer&) = delete;
    GPU_Renderer& operator=(const GPU_Renderer&) = delete;

    /**
     * Creates SDL's 2D renderer on top of a native SDL_GPU device.
     * The returned SDL_Renderer-compatible handle keeps the rest of the engine
     * and all scripts independent from the selected rendering backend.
     */
    bool init(SDL_Window* window);
    void shutdown();

    bool begin_frame();
    void end_frame();

    SDL_Renderer* renderer() const { return m_renderer; }
    SDL_GPUDevice* device() const { return m_device; }
    const char* driver_name() const;

private:
    SDL_Renderer* m_renderer = nullptr;
    // Borrowed from m_renderer. SDL_DestroyRenderer releases the device that
    // SDL_CreateGPURenderer created for us.
    SDL_GPUDevice* m_device = nullptr;
};

#endif
