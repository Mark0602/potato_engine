#include "loading_screen.h"

#include <algorithm>
#include <cmath>
#include <exception>
#include <filesystem>
#include <utility>

#include "debug.h"
#include "texture.h"

namespace {
constexpr float PI = 3.14159265358979323846f;

    void set_draw_color(SDL_Renderer* renderer,
                        Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }

    void set_draw_color(SDL_Renderer* renderer, const Color& color) {
        set_draw_color(renderer, color.r, color.g, color.b, color.a);
    }
} // namespace

Simple_Tileset::Simple_Tileset(const std::string& texture_path,
                               SDL_Renderer* target_renderer,
                               Logger* logger,
                               Vec requested_frame_size) {
    make_tileset(
        texture_path, target_renderer, logger, requested_frame_size
    );
}

Simple_Tileset::~Simple_Tileset() = default;

Simple_Tileset::Simple_Tileset(Simple_Tileset&& other) noexcept
    : texture(std::move(other.texture)),
      frame_size(other.frame_size),
      whole_size(other.whole_size),
      renderer(other.renderer),
      current_index(other.current_index),
      path(std::move(other.path)) {
    whole_texture = texture.get();
    other.whole_texture = nullptr;
    other.frame_size = {};
    other.whole_size = {};
    other.renderer = nullptr;
    other.current_index = 0;
}

Simple_Tileset& Simple_Tileset::operator=(Simple_Tileset&& other) noexcept {
    if (this == &other) return *this;
    texture = std::move(other.texture);
    whole_texture = texture.get();
    frame_size = other.frame_size;
    whole_size = other.whole_size;
    renderer = other.renderer;
    current_index = other.current_index;
    path = std::move(other.path);

    other.whole_texture = nullptr;
    other.frame_size = {};
    other.whole_size = {};
    other.renderer = nullptr;
    other.current_index = 0;
    return *this;
}

bool Simple_Tileset::is_loaded() const {
    return whole_texture && whole_texture->is_loaded() && frame_count() > 0;
}

bool Simple_Tileset::make_tileset(const std::string& texture_path,
                                  SDL_Renderer* target_renderer,
                                  Logger* logger,
                                  Vec requested_frame_size) {
    free();
    path = texture_path;
    renderer = target_renderer;
    if (path.empty() || !renderer) return false;

    auto loaded_texture = std::make_unique<Texture>(
        renderer, path, logger, SDL_SCALEMODE_PIXELART
    );
    if (!loaded_texture->is_loaded()) return false;

    whole_size = loaded_texture->get_size();
    if (requested_frame_size.x <= 0.0f ||
        requested_frame_size.y <= 0.0f) {
        requested_frame_size = whole_size;
    }
    frame_size = requested_frame_size;
    texture = std::move(loaded_texture);
    whole_texture = texture.get();
    if (frame_count() == 0) {
        free();
        return false;
    }
    return true;
}

std::size_t Simple_Tileset::columns() const {
    if (frame_size.x <= 0.0f || whole_size.x < frame_size.x) return 0;
    return static_cast<std::size_t>(whole_size.x / frame_size.x);
}

std::size_t Simple_Tileset::rows() const {
    if (frame_size.y <= 0.0f || whole_size.y < frame_size.y) return 0;
    return static_cast<std::size_t>(whole_size.y / frame_size.y);
}

std::size_t Simple_Tileset::frame_count() const {
    return columns() * rows();
}

void Simple_Tileset::draw_frame(SDL_Renderer* target_renderer,
                                const Vec& pos,
                                std::size_t frame_index) const {
    draw_frame(target_renderer, pos, frame_index, frame_size);
}

void Simple_Tileset::draw_frame(SDL_Renderer* target_renderer,
                                const Vec& pos,
                                std::size_t frame_index,
                                const Vec& size) const {
    target_renderer = target_renderer ? target_renderer : renderer;
    const std::size_t column_count = columns();
    const std::size_t count = frame_count();
    if (!target_renderer || !whole_texture || column_count == 0 ||
        frame_index >= count || size.x <= 0.0f || size.y <= 0.0f) {
        return;
    }

    const SDL_FRect source{
        static_cast<float>(frame_index % column_count) * frame_size.x,
        static_cast<float>(frame_index / column_count) * frame_size.y,
        frame_size.x,
        frame_size.y
    };
    const SDL_FRect destination{pos.x, pos.y, size.x, size.y};
    whole_texture->draw(target_renderer, &source, &destination);
}

void Simple_Tileset::draw_current_frame(SDL_Renderer* target_renderer,
                                        const Vec& pos) const {
    draw_frame(target_renderer, pos, current_index);
}

void Simple_Tileset::draw_current_frame(SDL_Renderer* target_renderer,
                                        const Vec& pos,
                                        const Vec& size) const {
    draw_frame(target_renderer, pos, current_index, size);
}

void Simple_Tileset::advance_frame_index(std::size_t& frame_index) const {
    const std::size_t count = frame_count();
    if (count > 0) frame_index = (frame_index + 1) % count;
}

void Simple_Tileset::advance_frame() {
    advance_frame_index(current_index);
}

void Simple_Tileset::free() {
    texture.reset();
    whole_texture = nullptr;
    frame_size = {};
    whole_size = {};
    renderer = nullptr;
    current_index = 0;
    path.clear();
}

void Simple_Tileset::set_frame_size(const Vec& new_frame_size) {
    frame_size = new_frame_size.x > 0.0f && new_frame_size.y > 0.0f
        ? new_frame_size : Vec{};
    current_index = 0;
}

void Simple_Tileset::set_whole_size(const Vec& new_whole_size) {
    whole_size = new_whole_size.x > 0.0f && new_whole_size.y > 0.0f
        ? new_whole_size : Vec{};
    current_index = 0;
}

Loading_Screen::Loading_Screen(SDL_Renderer* renderer, Logger* logger)
    : m_renderer(renderer), m_logger(logger) {
    int width = 0;
    int height = 0;
    SDL_RendererLogicalPresentation presentation = SDL_LOGICAL_PRESENTATION_DISABLED;
    if (m_renderer &&
        SDL_GetRenderLogicalPresentation(
            m_renderer, &width, &height, &presentation
        ) &&
        width > 0 && height > 0) {
        m_logical_width = static_cast<float>(width);
        m_logical_height = static_cast<float>(height);
    }
}

Loading_Screen::~Loading_Screen() = default;

void Loading_Screen::begin(const std::string& title, Action on_complete) {
    m_tasks.clear();
    m_on_complete = std::move(on_complete);
    m_title = title.empty() ? "Loading" : title;
    m_current_task.clear();
    m_error.clear();
    m_total_weight = 0.0f;
    m_completed_weight = 0.0f;
    m_animation_time = 0.0f;
    m_active = true;
    m_failed = false;
    m_presented_once = false;

    if (m_logger) {
        m_logger->log(Log_Level::INFO, "Loading", "Started: " + m_title);
    }
}

void Loading_Screen::enqueue(const std::string& label,
                             Action action,
                             float weight) {
    enqueue_step(
        label,
        [action = std::move(action)]() mutable {
            if (action) action();
            return true;
        },
        weight
    );
}

void Loading_Screen::enqueue_step(const std::string& label,
                                  Step step,
                                  float weight) {
    if (!m_active || !step) return;

    const float safe_weight = std::max(weight, 0.001f);
    m_tasks.push_back({label, std::move(step), safe_weight});
    m_total_weight += safe_weight;
}

void Loading_Screen::update(float delta_seconds) {
    if (!m_active) return;

    m_animation_time += std::max(delta_seconds, 0.0f);
    if (!m_presented_once) return;

    const Uint64 frame_start = SDL_GetTicksNS();
    const Uint64 budget_ns = static_cast<Uint64>(
        std::max(m_frame_budget_ms, 0.0f) * 1000000.0f
    );

    bool processed_task = false;
    while (m_active && !m_tasks.empty()) {
        Task& task = m_tasks.front();
        m_current_task = task.label;

        bool complete = false;
        try {
            complete = task.step();
        } catch (const std::exception& exception) {
            fail(exception.what());
            return;
        } catch (...) {
            fail("Unknown exception while running task: " + task.label);
            return;
        }

        processed_task = true;
        if (!complete) {
            // Incremental work gets one step per frame so rendering stays live.
            break;
        }

        m_completed_weight += task.weight;
        m_tasks.pop_front();

        const Uint64 elapsed = SDL_GetTicksNS() - frame_start;
        if (processed_task && elapsed >= budget_ns) break;
    }

    if (m_active && m_tasks.empty()) finish();
}

void Loading_Screen::render(float delta_seconds) {
    if (!m_active || !m_renderer) return;

    (void)delta_seconds;
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    if (m_background && m_background->is_loaded()) {
        m_background->draw(
            m_renderer,
            {0.0f, 0.0f},
            {m_logical_width, m_logical_height}
        );
    } else {
        draw_fallback_background();
    }

    draw_progress_bar(progress());
    draw_spinner(m_animation_time);
    m_presented_once = true;
}

void Loading_Screen::cancel() {
    m_tasks.clear();
    m_on_complete = {};
    m_current_task.clear();
    m_active = false;
}

float Loading_Screen::progress() const {
    if (!m_active && !m_failed) return 1.0f;
    if (m_total_weight <= 0.0f) return 0.0f;
    return std::clamp(m_completed_weight / m_total_weight, 0.0f, 1.0f);
}

void Loading_Screen::set_frame_budget_ms(float milliseconds) {
    m_frame_budget_ms = std::max(milliseconds, 0.0f);
}

bool Loading_Screen::load_artwork(const std::string& background_path,
                                  const std::string& icon_path,
                                  Vec icon_frame_size) {
    namespace fs = std::filesystem;

    m_owned_background.reset();
    m_owned_icon.reset();
    m_owned_icon_tileset.free();
    m_background = nullptr;
    m_icon = nullptr;

    std::error_code error;
    if (!background_path.empty() && fs::is_regular_file(background_path, error)) {
        auto background = std::make_unique<Texture>(
            m_renderer, background_path, m_logger, SDL_SCALEMODE_PIXELART
        );
        if (background->is_loaded()) {
            m_owned_background = std::move(background);
            m_background = m_owned_background.get();
        }
    }

    error.clear();
    if (!icon_path.empty() && fs::is_regular_file(icon_path, error)) {
        if (icon_frame_size.x > 0.0f && icon_frame_size.y > 0.0f) {
            m_owned_icon_tileset.make_tileset(
                icon_path, m_renderer, m_logger, icon_frame_size
            );
        } else {
            auto icon = std::make_unique<Texture>(
                m_renderer, icon_path, m_logger, SDL_SCALEMODE_PIXELART
            );
            if (icon->is_loaded()) {
                m_owned_icon = std::move(icon);
                m_icon = m_owned_icon.get();
            }
        }
    }

    return m_background || m_icon || m_owned_icon_tileset.is_loaded();
}

void Loading_Screen::set_artwork(Texture* background, Texture* icon) {
    m_owned_background.reset();
    m_owned_icon.reset();
    m_owned_icon_tileset.free();
    m_background = background;
    m_icon = icon;
}

void Loading_Screen::finish() {
    m_completed_weight = m_total_weight;
    m_current_task.clear();
    m_active = false;

    if (m_logger) {
        m_logger->log(Log_Level::INFO, "Loading", "Completed: " + m_title);
    }

    Action completion = std::move(m_on_complete);
    m_on_complete = {};
    if (completion) completion();
}

void Loading_Screen::fail(const std::string& message) {
    m_error = message.empty() ? "Loading task failed" : message;
    m_failed = true;
    m_active = false;
    m_tasks.clear();
    m_on_complete = {};

    if (m_logger) {
        m_logger->log(Log_Level::ERROR, "Loading", m_error);
    }
}

void Loading_Screen::draw_fallback_background() {
    constexpr int band_count = 16;
    const float band_height = m_logical_height /
                              static_cast<float>(band_count);

    for (int band = 0; band < band_count; ++band) {
        const float blend = static_cast<float>(band) /
                            static_cast<float>(band_count - 1);
        const Uint8 r = static_cast<Uint8>(12.0f + 10.0f * blend);
        const Uint8 g = static_cast<Uint8>(18.0f + 18.0f * blend);
        const Uint8 b = static_cast<Uint8>(28.0f + 24.0f * blend);
        set_draw_color(m_renderer, r, g, b);
        const SDL_FRect rect{
            0.0f,
            static_cast<float>(band) * band_height,
            m_logical_width,
            band_height + 1.0f
        };
        SDL_RenderFillRect(m_renderer, &rect);
    }
}

void Loading_Screen::draw_progress_bar(float value) {
    const float bar_width = std::max(
        8.0f,
        std::min(320.0f, m_logical_width - 64.0f)
    );
    const SDL_FRect outer{
        (m_logical_width - bar_width) * 0.5f,
        m_logical_height - 46.0f,
        bar_width,
        10.0f
    };
    const SDL_FRect inner{
        outer.x + 2.0f,
        outer.y + 2.0f,
        (outer.w - 4.0f) * std::clamp(value, 0.0f, 1.0f),
        outer.h - 4.0f
    };

    set_draw_color(m_renderer, 6, 10, 18, 210);
    SDL_RenderFillRect(m_renderer, &outer);
    set_draw_color(m_renderer, 108, 196, 142, 255);
    SDL_RenderFillRect(m_renderer, &inner);
}

void Loading_Screen::draw_spinner(float elapsed_seconds) {
    const float center_x = m_logical_width * 0.5f;
    const float center_y = m_logical_height - 86.0f;

    if (m_owned_icon_tileset.is_loaded()) {
        const Vec native_size = m_owned_icon_tileset.frame_size;
        const float largest_side = std::max(native_size.x, native_size.y);
        const float scale = largest_side > 0.0f ? 48.0f / largest_side : 1.0f;
        const Vec draw_size{native_size.x * scale, native_size.y * scale};
        const Vec position{
            center_x - draw_size.x * 0.5f,
            center_y - draw_size.y * 0.5f
        };
        const std::size_t frame_index = static_cast<std::size_t>(
            std::max(elapsed_seconds, 0.0f) * 10.0f
        ) % m_owned_icon_tileset.frame_count();
        m_owned_icon_tileset.draw_frame(
            m_renderer, position, frame_index, draw_size
        );
        return;
    }

    if (m_icon && m_icon->is_loaded()) {
        const Vec native_size = m_icon->get_size();
        const float largest_side = std::max(native_size.x, native_size.y);
        const float scale = largest_side > 0.0f ? 48.0f / largest_side : 1.0f;
        const Vec draw_size{native_size.x * scale, native_size.y * scale};
        const Vec position{
            center_x - draw_size.x * 0.5f,
            center_y - draw_size.y * 0.5f
        };
        const Vec rotation_center{draw_size.x * 0.5f, draw_size.y * 0.5f};
        m_icon->draw_ex(
            m_renderer,
            position,
            draw_size,
            static_cast<double>(elapsed_seconds * 180.0f),
            &rotation_center,
            SDL_FLIP_NONE
        );
        return;
    }

    constexpr int segment_count = 8;
    constexpr float radius = 20.0f;
    const int active_segment = static_cast<int>(elapsed_seconds * 10.0f) % segment_count;

    for (int segment = 0; segment < segment_count; ++segment) {
        const float angle = (2.0f * PI * static_cast<float>(segment)) /
                            static_cast<float>(segment_count);
        const float x = center_x + std::cos(angle) * radius - 3.0f;
        const float y = center_y + std::sin(angle) * radius - 3.0f;
        const int distance = (segment - active_segment + segment_count) % segment_count;
        const Uint8 alpha = static_cast<Uint8>(255 - distance * 22);
        set_draw_color(m_renderer, 160, 224, 184, alpha);
        const SDL_FRect rect{x, y, 6.0f, 6.0f};
        SDL_RenderFillRect(m_renderer, &rect);
    }
}
