#pragma once

#include <functional>
#include <algorithm>

/**
 * @brief Simple countdown timer with an optional callback.
 *
 * Call `tick(delta_time)` every frame from `on_update`.
 * When the timer expires it fires the callback once (if one was provided).
 *
 * Example:
 * ```cpp
 * Timer t;
 * t.start(0.2f, [&]() { btn->texture = idle_tex; });
 *
 * // in on_update():
 * t.tick(delta_time);
 *
 * // queries:
 * t.is_running()   // still counting down?
 * t.progress()     // 0.0 .. 1.0
 * t.remaining()    // seconds left
 * ```
 */
class Timer {
    float m_duration  = 0.0f;
    float m_elapsed   = 0.0f;
    bool  m_running   = false;
    bool  m_just_done = false;
    std::function<void()> m_callback;

public:
    Timer() = default;

    /**
     * @brief Starts (or restarts) the timer.
     * @param duration  How long the timer should run in seconds.
     * @param callback  Optional function called once when the timer expires.
     */
    void start(float duration, std::function<void()> callback = nullptr) {
        m_duration  = duration;
        m_elapsed   = 0.0f;
        m_running   = true;
        m_just_done = false;
        m_callback  = std::move(callback);
    }

    /**
     * @brief Advances the timer. Call every frame from `on_update(delta_time)`.
     * @param delta_time Time elapsed since the last frame, in seconds.
     */
    void tick(float delta_time) {
        m_just_done = false;
        if (!m_running) return;

        m_elapsed += delta_time;
        if (m_elapsed >= m_duration) {
            m_elapsed   = m_duration;
            m_running   = false;
            m_just_done = true;
            if (m_callback) m_callback();
        }
    }

    /// Stops and resets the timer without invoking the callback.
    void stop() {
        m_running   = false;
        m_elapsed   = 0.0f;
        m_just_done = false;
        m_callback  = nullptr;
    }

    /// @return `true` while the timer is still counting down.
    bool is_running()   const { return m_running; }

    /// @return `true` only on the single frame when the timer just expired.
    bool is_just_done() const { return m_just_done; }

    /// @return Time elapsed since the timer started, in seconds.
    float elapsed()   const { return m_elapsed; }

    /// @return Time remaining in seconds (0 if not running).
    float remaining() const { return m_running ? m_duration - m_elapsed : 0.0f; }

    /// @return Progress from 0.0 (just started) to 1.0 (expired).
    float progress()  const {
        return m_duration > 0.0f ? std::min(1.0f, m_elapsed / m_duration) : 1.0f;
    }
};
