#pragma once

#include "potato-script-base.h"

#include <iostream>
#include <string_view>
#include <typeinfo>
#include <cmath>
#include <cstdint>
#include <type_traits>

namespace debug
{
    // Toggle at runtime (can also be overridden by macros below)
    inline bool debug_mode = true;

    inline void set_debug_mode(bool enabled) { debug_mode = enabled; }
    inline bool get_debug_mode() { return debug_mode; }

    inline void log(std::string_view message)
    {
        if (!debug_mode) return;
        std::cout << "[potato_log] " << message << '\n';
    }

    inline void error(std::string_view message)
    {
        std::cerr << "[potato_error] " << message << '\n';
    }

    inline void console_log(std::string_view message)
    {
        if (!debug_mode) return;
        std::cout << message << '\n';
    }

    inline void console_error(std::string_view message)
    {
        std::cerr << message << '\n';
    }

    inline void script_log(std::string_view message, const potato_script* script)
    {
        if (!debug_mode) return;

        if (!script)
        {
            std::cout << "[script:null] " << message << '\n';
            return;
        }

        std::cout << "[" << typeid(*script).name() << "] " << message << '\n';
    }

    inline void script_error(std::string_view message, const potato_script* script)
    {
        if (!script)
        {
            std::cerr << "[script:null ERROR] " << message << '\n';
            return;
        }

        std::cerr << "[" << typeid(*script).name() << " ERROR] " << message << '\n';
    }
}

#ifdef POTATO_DEBUG
    #define POTATO_LOG(msg)::potato::debug::log(msg)
    #define POTATO_ERROR(msg)::potato::debug::error(msg)
    #define POTATO_CONSOLE(msg)::potato::debug::console_log(msg)
    #define POTATO_CONSOLE_ERR(msg)::potato::debug::console_error(msg)
    #define POTATO_SCRIPT_LOG(msg, self)::potato::debug::script_log(msg, self)
    #define POTATO_SCRIPT_ERROR(msg, self)::potato::debug::script_error(msg, self)
#else
    // In Release: logs off, errors still on (usually what you want)
    #define POTATO_LOG(msg)((void)0)
    #define POTATO_CONSOLE(msg)((void)0)
    #define POTATO_SCRIPT_LOG(msg, self)((void)0)

    #define POTATO_ERROR(msg)::potato::debug::error(msg)
    #define POTATO_CONSOLE_ERR(msg)::potato::debug::console_error(msg)
    #define POTATO_SCRIPT_ERROR(msg, self)::potato::debug::script_error(msg, self)
#endif


namespace pmath
{
    // --- Constants ---
    constexpr float PI = 3.14159265358979323846f;
    constexpr float HALF_PI = PI * 0.5f;
    constexpr float TAU = PI * 2.0f;

    // --- Basic helpers ---
    template<typename T>
    constexpr T min(T a, T b)
    {
        return (a < b) ? a : b;
    }

    template<typename T>
    constexpr T max(T a, T b)
    {
        return (a > b) ? a : b;
    }

    template<typename T>
    constexpr T clamp(T v, T lo, T hi)
    {
        return (v < lo) ? lo : (v > hi) ? hi : v;
    }

    template<typename T>
    constexpr T abs(T v)
    {
        return (v < T(0)) ? -v : v;
    }

    // --- Interpolation ---
    constexpr float lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    constexpr float inverse_lerp(float a, float b, float v)
    {
        return (v - a) / (b - a);
    }

    constexpr float remap(float in_min, float in_max,
                           float out_min, float out_max,
                           float v)
    {
        return lerp(out_min, out_max, inverse_lerp(in_min, in_max, v));
    }

    // --- Angle helpers ---
    constexpr float deg2rad(float deg)
    {
        return deg * (PI / 180.0f);
    }

    constexpr float rad2deg(float rad)
    {
        return rad * (180.0f / PI);
    }

    // --- Float comparisons ---
    constexpr bool nearly_equal(float a, float b, float epsilon = 1e-6f)
    {
        return abs(a - b) <= epsilon;
    }

    // --- Power-of-two helpers (GPU friendly) ---
    constexpr bool is_pow2(uint32_t v)
    {
        return v && ((v & (v - 1)) == 0);
    }

    constexpr uint32_t next_pow2(uint32_t v)
    {
        if (v == 0) return 1;
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        return v + 1;
    }

    // --- Clamp + lerp combo (very common in engines) ---
    constexpr float saturate(float v)
    {
        return clamp(v, 0.0f, 1.0f);
    }

    // --- Fast sqrt / inv sqrt wrappers (can be optimized later) ---
    inline float sqrt(float v)
    {
        return std::sqrt(v);
    }

    inline float rsqrt(float v)
    {
        return 1.0f / std::sqrt(v);
    }
}