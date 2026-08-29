#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>

#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <iostream>
#include <utility>
#include <source_location>
#include <chrono>
#include <mutex>
#include "engine.h"
#include "debug.h"
#include "vec.h"
#include "color.h"

inline constexpr float PI = 3.14159265358979323846f;

/**
 * @brief Calculates the distance between two Vec points.
 * 
 * @param a The first Vec point.
 * @param b The second Vec point.
 * @return float The distance between the two points.
 */
inline float distance(const Vec& a, const Vec& b) {
    return sqrtf(powf(b.x - a.x, 2) + powf(b.y - a.y, 2));
}
/**
 * @brief Calculates the squared distance between two Vec points.
 * 
 * @param a The first Vec point.
 * @param b The second Vec point.
 * @return float The squared distance between the two points.
 */
inline float distance_squared(const Vec& a, const Vec& b) {
    return powf(b.x - a.x, 2) + powf(b.y - a.y, 2);
}
/**
 * @brief Calculates the length (magnitude) of a Vec.
 * 
 * @param a The Vec whose length is to be calculated.
 * @return float The length of the Vec.
 */
inline float length(const Vec& a) {
    return sqrtf(powf(a.x, 2) + powf(a.y, 2));
}
/**
 * @brief Calculates the squared length (magnitude) of a Vec.
 * 
 * @param a The Vec whose squared length is to be calculated.
 * @return float The squared length of the Vec.
 */
inline float length_squared(const Vec& a) {
    return powf(a.x, 2) + powf(a.y, 2);
}
/**
 * @brief Checks if two Vec points are nearly equal within a given epsilon.
 * 
 * @param a The first Vec point.
 * @param b The second Vec point.
 * @param epsilon The tolerance for equality. Default is 0.01f.
 * @return bool True if the points are nearly equal, false otherwise.
 */
inline bool nearly_equal(const Vec& a, const Vec& b, float epsilon = 0.01f) {
    return (fabsf(a.x - b.x) < epsilon) && (fabsf(a.y - b.y) < epsilon);
}

/// @brief Returns a unit vector in the same direction as `a`. Returns `{0,0}` if `a` is zero.
inline Vec normalize(const Vec& a) {
    float len = length(a);
    if (len == 0) {
        return { 0, 0 };
    }
    return { a.x / len, a.y / len };
}

/// @brief Dot product of two vectors. Positive = same direction, 0 = perpendicular, negative = opposite.
inline float dot(const Vec& a, const Vec& b) {
    return a.x * b.x + a.y * b.y;
}

/// @brief 2D cross product (scalar). Positive if `b` is counter-clockwise from `a`.
inline float cross(const Vec& a, const Vec& b) {
    return a.x * b.y - a.y * b.x;
}

/**
 * @brief Angle (radians) from point `a` to point `b`, measured from the positive X axis.
 * @return Angle in radians in the range `[-PI, PI]`.
 */
inline float angle(const Vec& a, const Vec& b) {
    return atan2f(b.y - a.y, b.x - a.x);
}

/**
 * @brief Unsigned angle between two direction vectors (radians).
 * @return Angle in `[0, PI]`. Returns 0 if either vector is zero.
 */
inline float angle_between(const Vec& a, const Vec& b) {
    float dot_product = dot(a, b);
    float lengths = length(a) * length(b);
    if (lengths == 0) {
        return 0;
    }
    return acosf(dot_product / lengths);
}

/**
 * @brief Signed angle from `a` to `b` (radians). Positive = counter-clockwise.
 * @return Angle in `[-PI, PI]`.
 */
inline float angle_between_signed(const Vec& a, const Vec& b) {
    return atan2f(cross(a, b), dot(a, b));
}

/// @brief Unsigned angle between two vectors in degrees. See `angle_between()`.
inline float angle_between_degrees(const Vec& a, const Vec& b) {
    return angle_between(a, b) * (180.0f / PI);
}

/// @brief Signed angle from `a` to `b` in degrees. See `angle_between_signed()`.
inline float angle_between_signed_degrees(const Vec& a, const Vec& b) {
    return angle_between_signed(a, b) * (180.0f / PI);
}

/// @brief Alias for `angle_between()` — returns the unsigned angle in radians.
inline float angle_between_radians(const Vec& a, const Vec& b) {
    return angle_between(a, b);
}

/// @brief Alias for `angle_between_signed()` — returns the signed angle in radians.
inline float angle_between_signed_radians(const Vec& a, const Vec& b) {
    return angle_between_signed(a, b);
}

/**
 * @brief Tests whether a point is inside an SDL_FRect offset by `rect_Vec`.
 * @param point    Point to test in logical coordinates.
 * @param rect_Vec Top-left offset added to `rect.x/y`.
 * @param rect     Rectangle (x, y ignored; w, h used for size).
 */
inline bool is_point_in_rect(const Vec& point, const Vec& rect_Vec, const SDL_FRect& rect) {
    return (point.x >= rect_Vec.x && point.x <= rect_Vec.x + rect.w &&
            point.y >= rect_Vec.y && point.y <= rect_Vec.y + rect.h);
}

/**
 * @brief Tests whether a point lies inside or on the boundary of a circle.
 * @param point         Point to test.
 * @param circle_center Centre of the circle.
 * @param radius        Radius of the circle.
 */
inline bool is_point_in_circle(const Vec& point, const Vec& circle_center, float radius) {
    return distance_squared(point, circle_center) <= radius * radius;
}

/**
 * @brief Linearly interpolates between two vectors.
 * @param a Start value (`t = 0`).
 * @param b End value (`t = 1`).
 * @param t Blend factor. Clamping to `[0, 1]` is the caller's responsibility.
 */
inline Vec lerp(const Vec& a, const Vec& b, float t) {
    return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t };
}

/**
 * @brief Clamps each component of `a` between the corresponding components of `min` and `max`.
 * @param a   Value to clamp.
 * @param min Per-component minimum.
 * @param max Per-component maximum.
 */
inline Vec clamp(const Vec& a, const Vec& min, const Vec& max) {
    return { std::max(min.x, std::min(max.x, a.x)), std::max(min.y, std::min(max.y, a.y)) };
}

/**
 * @brief Clamps a float value between a minimum and maximum.
 * @param value The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The clamped value.
 */
inline float clamp(float value, float min, float max) {
    return std::max(min, std::min(max, value));
}

/**
 * @brief Clamps an integer value between a minimum and maximum.
 * @param value The value to clamp.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return The clamped value.
 */
inline int clamp(int value, int min, int max) {
    return std::max(min, std::min(max, value));
}

/**
 * @brief Reflects vector `a` off a surface with the given unit normal.
 * @param a      Incoming direction vector.
 * @param normal Unit normal of the surface.
 */
inline Vec reflect(const Vec& a, const Vec& normal) {
    float dot_product = dot(a, normal);
    return { a.x - 2 * dot_product * normal.x, a.y - 2 * dot_product * normal.y };
}

/**
 * @brief Rotates vector `a` by `angle` degrees counter-clockwise.
 * @param a     Vector to rotate.
 * @param angle Rotation angle in degrees.
 */
inline Vec rotate(const Vec& a, float angle) {
    float rad = angle * (PI / 180.0f);
    float cos_a = cosf(rad);
    float sin_a = sinf(rad);
    return { a.x * cos_a - a.y * sin_a, a.x * sin_a + a.y * cos_a };
}

/// @brief Returns a vector pointing in the opposite direction (`-x, -y`).
inline Vec invert(const Vec& a) {
    return { -a.x, -a.y };
}

/// @brief Returns a vector with each component replaced by its absolute value.
inline Vec abs(const Vec& a) {
    return { fabsf(a.x), fabsf(a.y) };
}

/// @brief Returns a vector with each component rounded down to the nearest integer.
inline Vec floor(const Vec& a) {
    return { floorf(a.x), floorf(a.y) };
}

/// @brief Returns a vector with each component rounded up to the nearest integer.
inline Vec ceil(const Vec& a) {
    return { ceilf(a.x), ceilf(a.y) };
}

/// @brief Returns a vector with each component rounded to the nearest integer.
inline Vec round(const Vec& a) {
    return { roundf(a.x), roundf(a.y) };
}

/// @brief Returns a vector perpendicular to `a`, rotated 90° counter-clockwise.
inline Vec perpendicular(const Vec& a) {
    return { -a.y, a.x };
}

/// @brief Extracts the top-left position `{x, y}` from an SDL_FRect as a Vec.
inline Vec convert_FRect_to_Vec(const SDL_FRect& rect) {
    return { rect.x, rect.y };
}

/**
 * @brief Converts a position Vec and a size Vec into an SDL_FRect.
 * @param a    Top-left position.
 * @param size Width and height.
 */
inline SDL_FRect convert_Vec_to_FRect(const Vec& a, const Vec& size) {
    return { a.x, a.y, size.x, size.y };
}

// mouse related

/**
 * @brief Gets the current mouse position in logical coordinates.
 * This function retrieves the current mouse position in window coordinates and converts it to logical coordinates based on the current SDL renderer.
 * @return Vec The mouse position in logical coordinates.
 */
inline static Vec get_mouse_position() {
    float window_x = 0.0f;
    float window_y = 0.0f;

    SDL_GetMouseState(&window_x, &window_y);

    float render_x = 0.0f;
    float render_y = 0.0f;

    SDL_RenderCoordinatesFromWindow(
        Engine::renderer,
        window_x,
        window_y,
        &render_x,
        &render_y
    );

    return Vec{render_x, render_y};
}
/**
 * @brief Changes the visibility of the OS cursor
 *
 * This function allows you to show or hide the OS cursor. 
 * You can use it to create your own custom cursor or to hide the cursor during gameplay.
 * 
 * @param visible If true, the cursor will be shown; if false, it will be hidden.
 * @param logger Optional logger for debugging purposes. By default nullptr, which means no logging will occur.
 */
inline void os_cursor_visibility(bool visible, Logger* logger = nullptr) {
    bool success = true;
    if (visible) {
        success = SDL_ShowCursor();
    } else {
        success = SDL_HideCursor();
    }
    if (logger) {
        logger->log(Log_Level::DEBUG, "Cursor", std::string("Cursor visibility set to ") + (visible ? "true" : "false"));
        if (!success) {
            logger->log(Log_Level::ERROR, "Cursor", std::string("Failed to set cursor visibility. SDL_Error: ") + SDL_GetError());
        }
    }
}

/**
 * @brief Linearly interpolates between two colors.
 * @param color  The starting color, which will be modified to the interpolated value.
 * @param target The target color to interpolate towards.
 * @param t      The interpolation factor, where 0.0 returns `color` and 1.0 returns `target`.
 *               Values outside the range [0.0, 1.0] will extrapolate beyond the two colors.
 */
inline void lerp_color(Color& color, const Color& target, float t) {
    color.r = static_cast<uint8_t>(color.r + (target.r - color.r) * t);
    color.g = static_cast<uint8_t>(color.g + (target.g - color.g) * t);
    color.b = static_cast<uint8_t>(color.b + (target.b - color.b) * t);
    color.a = static_cast<uint8_t>(color.a + (target.a - color.a) * t);
}

/**
 * @brief Gets the window size in logical coordinates as a Vec.
 * This function retrieves the current size of the SDL window and returns it as a Vec, where `x` is the width and `y` is the height.
 * @return Vec The window size in logical coordinates.
 */
inline Vec get_window_size() {
    int w = 0, h = 0;
    SDL_GetWindowSize(Engine::window, &w, &h);
    return Vec(static_cast<float>(w), static_cast<float>(h));
}

/**
 * @brief Gets the center of the window in logical coordinates as a Vec.
 * This function calculates the center point of the SDL window based on its current size and returns it as a Vec.
 * @return Vec The center of the window in logical coordinates.
 */
inline Vec get_window_center() {
    Vec size = get_window_size();
    return Vec(size.x / 2.0f, size.y / 2.0f);
}

/**
 * @brief Gets the top-left corner of the window in logical coordinates as a Vec.
 * This function returns the top-left corner of the SDL window, which is always at (0, 0) in logical coordinates.
 * @return Vec The top-left corner of the window in logical coordinates.
 */
inline Vec get_window_top_left() {
    return Vec(0.0f, 0.0f);
}

/**
 * @brief Gets the bottom-right corner of the window in logical coordinates as a Vec.
 * This function calculates the bottom-right corner of the SDL window based on its current size and returns it as a Vec.
 * @return Vec The bottom-right corner of the window in logical coordinates.
 */
inline Vec get_window_bottom_right() {
    return get_window_size();
}

/**
 * @brief Gets the top-right corner of the window in logical coordinates as a Vec.
 * This function calculates the top-right corner of the SDL window based on its current size and returns it as a Vec.
 * @return Vec The top-right corner of the window in logical coordinates.
 */
inline Vec get_window_bottom_left() {
    Vec size = get_window_size();
    return Vec(0.0f, size.y);
}

/**
 * @brief Gets the bottom-left corner of the window in logical coordinates as a Vec.
 * This function calculates the bottom-left corner of the SDL window based on its current size and returns it as a Vec.
 * @return Vec The bottom-left corner of the window in logical coordinates.
 */
inline Vec get_window_top_right() {
    Vec size = get_window_size();
    return Vec(size.x, 0.0f);
}

/**
 * @brief Gets the left-center point of the window in logical coordinates as a Vec.
 * This function calculates the left-center point of the SDL window based on its current size and returns it as a Vec.
 * @return Vec The left-center point of the window in logical coordinates.
 */
inline Vec get_window_left_center() {
    Vec size = get_window_size();
    return Vec(0.0f, size.y / 2.0f);
}

/**
 * @brief Gets the right-center point of the window in logical coordinates as a Vec.
 * This function calculates the right-center point of the SDL window based on its current size and returns it as a Vec.
 * @return Vec The right-center point of the window in logical coordinates.
 */
inline Vec get_window_right_center() {
    Vec size = get_window_size();
    return Vec(size.x, size.y / 2.0f);
}

/**
 * @brief Gets the top-center point of the window in logical coordinates as a Vec.
 * This function calculates the top-center point of the SDL window based on its current size and returns it as a Vec.
 * @return Vec The top-center point of the window in logical coordinates.
 */
inline Vec get_window_top_center() {
    Vec size = get_window_size();
    return Vec(size.x / 2.0f, 0.0f);
}

/**
 * @brief Gets the bottom-center point of the window in logical coordinates as a Vec.
 * This function calculates the bottom-center point of the SDL window based on its current size and returns it as a Vec.
 * @return Vec The bottom-center point of the window in logical coordinates.
 */
inline Vec get_window_bottom_center() {
    Vec size = get_window_size();
    return Vec(size.x / 2.0f, size.y);
}

/**
 * @brief Maximizes the SDL window if it is valid.
 * @param window Pointer to the SDL_Window to maximize. If nullptr, the function does nothing.
 */
inline void maximize_window(SDL_Window* window) {
    if (window) {
        SDL_MaximizeWindow(window);
    }
}

/**
 * @brief Sets the SDL window to fullscreen mode if it is valid.
 * @param window Pointer to the SDL_Window to set to fullscreen. If nullptr, the function
 */
inline void fullscreen_window(SDL_Window* window) {
    if (window) {
        SDL_SetWindowFullscreen(window, 1);
    }
}

/**
 * @brief Sets the SDL window to windowed mode if it is valid.
 * @param window Pointer to the SDL_Window to set to windowed mode. If nullptr, the function does nothing.
 */
inline void windowed_window(SDL_Window* window) {
    if (window) {
        SDL_SetWindowFullscreen(window, 0);
    }
}

/// @brief Cardinal directions for movement, input, and layout logic.
enum class Direction {
    UP,    ///< Negative Y axis.
    DOWN,  ///< Positive Y axis.
    LEFT,  ///< Negative X axis.
    RIGHT  ///< Positive X axis.
};

/// @brief The two primary screen axes.
enum class Axis {
    HORIZONTAL, ///< X axis.
    VERTICAL    ///< Y axis.
};


#endif
