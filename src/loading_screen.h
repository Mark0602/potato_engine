#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <cstddef>
#include <deque>
#include <functional>
#include <memory>
#include <string>

#include <SDL3/SDL.h>

#include "vec.h"

class Logger;
class Texture;

/**
 * @brief Simple tileset wrapper for loading screen artwork.
 * This is meant to be used with `Loading_Screen::load_artwork()` and does not support
 * the full Tileset interface.
 * You can use it however in other minimalist scenarios where you just need a texture with some fixed sized frames 
 * and don't want to deal with the full Tileset class.
 */
struct Simple_Tileset {
    std::unique_ptr<Texture> texture;
    Texture *whole_texture = nullptr;
    Vec frame_size = {0, 0};
    Vec whole_size = {0, 0};

    SDL_Renderer* renderer = nullptr;

    std::size_t current_index = 0;

    std::string path;

    Simple_Tileset() = default;
    Simple_Tileset(const std::string& path, SDL_Renderer* renderer, Logger* logger = nullptr, Vec frame_size = {0, 0});
    ~Simple_Tileset();

    Simple_Tileset(const Simple_Tileset&) = delete;
    Simple_Tileset& operator=(const Simple_Tileset&) = delete;
    Simple_Tileset(Simple_Tileset&& other) noexcept;
    Simple_Tileset& operator=(Simple_Tileset&& other) noexcept;

    bool is_loaded() const;
    bool make_tileset(const std::string& path, SDL_Renderer* renderer,
                      Logger* logger = nullptr, Vec frame_size = {0, 0});
    std::size_t columns() const;
    std::size_t rows() const;
    std::size_t frame_count() const;
    void draw_frame(SDL_Renderer* renderer, const Vec& pos, std::size_t frame_index) const;
    void draw_frame(SDL_Renderer* renderer, const Vec& pos, std::size_t frame_index, const Vec& size) const;
    void draw_current_frame(SDL_Renderer* renderer, const Vec& pos) const;
    void draw_current_frame(SDL_Renderer* renderer, const Vec& pos,
                            const Vec& size) const;
    void advance_frame_index(std::size_t& frame_index) const;
    void advance_frame();
    void reset_frame() { current_index = 0; }
    void free();

    void set_frame_size(const Vec& new_frame_size);
    void set_whole_size(const Vec& new_whole_size);
};

/**
 * @brief Main-thread loading queue and engine-level transition overlay.
 *
 * A loading operation is split into small tasks. `update()` executes tasks for
 * at most the configured frame budget, while `render()` keeps the loading
 * artwork and animation responsive between tasks. SDL resource creation must
 * stay in these main-thread tasks.
 *
 * Long CPU-only work can be made incremental with `enqueue_step()`: its step is
 * called once per frame until it returns `true`.
 */
class Loading_Screen {
public:
    using Action = std::function<void()>;
    using Step = std::function<bool()>;

    explicit Loading_Screen(SDL_Renderer* renderer, Logger* logger = nullptr);
    ~Loading_Screen();

    Loading_Screen(const Loading_Screen&) = delete;
    Loading_Screen& operator=(const Loading_Screen&) = delete;

    /** Starts a new loading operation and discards any unfinished old tasks. */
    void begin(const std::string& title = "Loading", Action on_complete = {});

    /** Adds one atomic main-thread task. */
    void enqueue(const std::string& label, Action action, float weight = 1.0f);

    /**
     * Adds an incremental task. The step is called at most once per frame and
     * must return true when the task is complete.
     */
    void enqueue_step(const std::string& label, Step step, float weight = 1.0f);

    /**
     * Advances the queue within the frame budget. The first call waits until
     * `render()` has presented at least one loading frame.
     */
    void update(float delta_seconds);

    /** Draws either the configured artwork or the built-in fallback. */
    void render(float delta_seconds);

    /** Stops the current operation without invoking its completion callback. */
    void cancel();

    bool active() const { return m_active; }
    bool failed() const { return m_failed; }
    const std::string& error() const { return m_error; }
    float progress() const;
    const std::string& title() const { return m_title; }
    const std::string& current_task() const { return m_current_task; }
    std::size_t pending_task_count() const { return m_tasks.size(); }

    /** Sets how much time atomic tasks may consume after the first task/frame. */
    void set_frame_budget_ms(float milliseconds);
    float frame_budget_ms() const { return m_frame_budget_ms; }

    /**
     * Loads optional boot artwork independently from the regular Asset_Pool.
     * Missing paths are ignored, so the built-in fallback remains usable.
     * A positive icon_frame_size treats the icon as a row-major sprite sheet;
     * otherwise the complete icon texture is rotated.
     */
    bool load_artwork(const std::string& background_path,
                      const std::string& icon_path,
                      Vec icon_frame_size = {});

    /** Uses borrowed textures. They must outlive the active loading operation. */
    void set_artwork(Texture* background, Texture* icon);

private:
    struct Task {
        std::string label;
        Step step;
        float weight = 1.0f;
    };

    void finish();
    void fail(const std::string& message);
    void draw_fallback_background();
    void draw_progress_bar(float value);
    void draw_spinner(float elapsed_seconds);

    SDL_Renderer* m_renderer = nullptr;
    Logger* m_logger = nullptr;
    std::deque<Task> m_tasks;
    Action m_on_complete;

    std::unique_ptr<Texture> m_owned_background;
    std::unique_ptr<Texture> m_owned_icon;
    Simple_Tileset m_owned_icon_tileset;
    Texture* m_background = nullptr;
    Texture* m_icon = nullptr;

    std::string m_title = "Loading";
    std::string m_current_task;
    std::string m_error;
    float m_total_weight = 0.0f;
    float m_completed_weight = 0.0f;
    float m_frame_budget_ms = 4.0f;
    float m_animation_time = 0.0f;
    float m_logical_width = 1024.0f;
    float m_logical_height = 512.0f;
    bool m_active = false;
    bool m_failed = false;
    bool m_presented_once = false;
};

#endif
