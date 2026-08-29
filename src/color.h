#ifndef COLOR_H
#define COLOR_H

#include <SDL3/SDL.h>
#include <cstdint>
#include <string>
#include <algorithm>
#include <stdexcept>

/**
 * @brief Represents a color with red, green, blue, and alpha components.
 */
struct Color {
    uint8_t r = 255; ///< Red component (0-255).
    uint8_t g = 255; ///< Green component (0-255).
    uint8_t b = 255; ///< Blue component (0-255).
    uint8_t a = 255; ///< Alpha component (0-255).

    /**
     * @brief Constructs a Color with specified red, green, blue, and alpha values.
     * @param r Red component (0-255).
     * @param g Green component (0-255).
     * @param b Blue component (0-255).
     * @param a Alpha component (0-255).
     */
    Color() = default; ///< Default constructor initializes to white with full opacity.

    /**
     * @brief Constructs a Color with specified red, green, blue, and alpha values.
     * @param r Red component (0-255).
     * @param g Green component (0-255).
     * @param b Blue component (0-255).
     * @param a Alpha component (0-255).
     */
    Color (uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r), g(g), b(b), a(a) {} ///< Constructs a Color with specified RGBA values.

    /**
     * @brief Constructs a Color from an SDL_Color.
     * @param color SDL_Color to convert to Color.
     */
    Color(const SDL_Color& color)
        : r(color.r), g(color.g), b(color.b), a(color.a) {} ///< Constructs a Color from an SDL_Color.

    /**
     * @brief Converts the Color to an SDL_Color.
     * @return SDL_Color representation of the Color.
     */
    SDL_Color to_sdl_color() const {
        return SDL_Color{ r, g, b, a }; ///< Converts the Color to an SDL_Color.
    }

    /**
     * @brief Creates a Color from an SDL_Color.
     * @param color SDL_Color to convert to Color.
     * @return Color representation of the SDL_Color.
     */
    static Color from_sdl_color(const SDL_Color& color) {
        return Color(color.r, color.g, color.b, color.a); ///< Creates a Color from an SDL_Color.
    }

    /**
     * @brief Creates a Color from a hexadecimal value.
     * @param hex Hexadecimal value representing the color (0xRRGGBBAA).
     * @return Color representation of the hexadecimal value.
     */
    static Color from_hex(uint32_t hex) {
        uint8_t r = (hex >> 24) & 0xFF;
        uint8_t g = (hex >> 16) & 0xFF;
        uint8_t b = (hex >> 8) & 0xFF;
        uint8_t a = hex & 0xFF;
        return Color(r, g, b, a); ///< Creates a Color from a hexadecimal value.
    }

    /**
     * @brief Creates a Color from a hexadecimal string.
     * @param hex_string Hexadecimal string representing the color (e.g., "FF00FF00").
     * @return Color representation of the hexadecimal string.
     */
    static Color from_hex_string(std::string hex_string) {
        if (!hex_string.empty() && hex_string[0] == '#') {
            hex_string.erase(0, 1);
        }
        uint32_t hex = static_cast<uint32_t>(std::stoul(hex_string, nullptr, 16));

        if (hex_string.length() == 6) {
            return Color{
                static_cast<uint8_t>((hex >> 16) & 0xFF),
                static_cast<uint8_t>((hex >> 8) & 0xFF),
                static_cast<uint8_t>(hex & 0xFF),
                255
            };
        }
        return from_hex(hex); // RRGGBBAA
    }

    /**
     * @brief Creates a Color with specified alpha value.
     * @param alpha Alpha component (0.0f - 1.0f).
     * @return Color representation of the current color with specified alpha.
     */
    Color with_alpha(uint8_t alpha) const {
        return {r, g, b, alpha}; ///< Creates a white Color with specified alpha.
    }
    
    Color operator+(const Color& other) const {
        return {
            static_cast<uint8_t>(std::min(255, static_cast<int>(r) + static_cast<int>(other.r))),
            static_cast<uint8_t>(std::min(255, static_cast<int>(g) + static_cast<int>(other.g))),
            static_cast<uint8_t>(std::min(255, static_cast<int>(b) + static_cast<int>(other.b))),
            static_cast<uint8_t>(std::min(255, static_cast<int>(a) + static_cast<int>(other.a)))
        };
    }

    Color operator-(const Color& other) const {
        return {
            static_cast<uint8_t>(std::max(0, static_cast<int>(r) - static_cast<int>(other.r))),
            static_cast<uint8_t>(std::max(0, static_cast<int>(g) - static_cast<int>(other.g))),
            static_cast<uint8_t>(std::max(0, static_cast<int>(b) - static_cast<int>(other.b))),
            static_cast<uint8_t>(std::max(0, static_cast<int>(a) - static_cast<int>(other.a)))
        };
    }

    Color operator*(float scalar) const {
        return {
            static_cast<uint8_t>(std::min(255, static_cast<int>(r * scalar))),
            static_cast<uint8_t>(std::min(255, static_cast<int>(g * scalar))),
            static_cast<uint8_t>(std::min(255, static_cast<int>(b * scalar))),
            static_cast<uint8_t>(std::min(255, static_cast<int>(a * scalar)))
        };
    }

    Color operator/(float scalar) const {
        if (scalar == 0.0f) {
            throw std::invalid_argument("Division by zero in Color division."); ///< Handle division by zero.
        }
        return {
            static_cast<uint8_t>(std::min(255, static_cast<int>(r / scalar))),
            static_cast<uint8_t>(std::min(255, static_cast<int>(g / scalar))),
            static_cast<uint8_t>(std::min(255, static_cast<int>(b / scalar))),
            static_cast<uint8_t>(std::min(255, static_cast<int>(a / scalar)))
        };
    }

    Color& operator+=(const Color& other) {
        r = static_cast<uint8_t>(std::min(255, static_cast<int>(r) + static_cast<int>(other.r)));
        g = static_cast<uint8_t>(std::min(255, static_cast<int>(g) + static_cast<int>(other.g)));
        b = static_cast<uint8_t>(std::min(255, static_cast<int>(b) + static_cast<int>(other.b)));
        a = static_cast<uint8_t>(std::min(255, static_cast<int>(a) + static_cast<int>(other.a)));
        return *this; ///< Compound addition assignment operator for Color.
    }

    Color& operator-=(const Color& other) {
        r = static_cast<uint8_t>(std::max(0, static_cast<int>(r) - static_cast<int>(other.r)));
        g = static_cast<uint8_t>(std::max(0, static_cast<int>(g) - static_cast<int>(other.g)));
        b = static_cast<uint8_t>(std::max(0, static_cast<int>(b) - static_cast<int>(other.b)));
        a = static_cast<uint8_t>(std::max(0, static_cast<int>(a) - static_cast<int>(other.a)));
        return *this; ///< Compound subtraction assignment operator for Color.
    }

    Color& operator*=(float scalar) {
        r = static_cast<uint8_t>(std::min(255, static_cast<int>(r * scalar)));
        g = static_cast<uint8_t>(std::min(255, static_cast<int>(g * scalar)));
        b = static_cast<uint8_t>(std::min(255, static_cast<int>(b * scalar)));
        a = static_cast<uint8_t>(std::min(255, static_cast<int>(a * scalar)));
        return *this; ///< Compound multiplication assignment operator for Color.
    }

    Color& operator/=(float scalar) {
        if (scalar == 0.0f) {
            throw std::invalid_argument("Division by zero in Color division."); ///< Handle division by zero.
        }
        r = static_cast<uint8_t>(std::min(255, static_cast<int>(r / scalar)));
        g = static_cast<uint8_t>(std::min(255, static_cast<int>(g / scalar)));
        b = static_cast<uint8_t>(std::min(255, static_cast<int>(b / scalar)));
        a = static_cast<uint8_t>(std::min(255, static_cast<int>(a / scalar)));
        return *this; ///< Compound division assignment operator for Color.
    }

    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a; ///< Equality operator for Color.
    }

    bool operator!=(const Color& other) const {
        return !(*this == other); ///< Inequality operator for Color.
    }

    inline static const Color white() { return Color(255, 255, 255, 255); } ///< Predefined white color (255, 255, 255, 255).
    inline static const Color black() { return Color(0, 0, 0, 255); } ///< Predefined black color (0, 0, 0, 255).
    inline static const Color red() { return Color(255, 0, 0, 255); }   ///< Predefined red color (255, 0, 0, 255).
    inline static const Color green() { return Color(0, 255, 0, 255); } ///< Predefined green color (0, 255, 0, 255).
    inline static const Color blue() { return Color(0, 0, 255, 255); }  ///< Predefined blue color (0, 0, 255, 255).
    inline static const Color transparent() { return Color(0, 0, 0, 0); } ///< Predefined transparent color (0, 0, 0, 0).
    inline static const Color yellow() { return Color(255, 255, 0, 255); } ///< Predefined yellow color (255, 255, 0, 255).
    inline static const Color cyan() { return Color(0, 255, 255, 255); } ///< Predefined cyan color (0, 255, 255, 255).
    inline static const Color magenta() { return Color(255, 0, 255, 255); } ///< Predefined magenta color (255, 0, 255, 255).
    inline static const Color gray() { return Color(128, 128, 128, 255); } ///< Predefined gray color (128, 128, 128, 255).
    inline static const Color orange() { return Color(255, 165, 0, 255); } ///< Predefined orange color (255, 165, 0, 255).
    inline static const Color purple() { return Color(128, 0, 128, 255); } ///< Predefined purple color (128, 0, 128, 255).
    inline static const Color brown() { return Color(165, 42, 42, 255); } ///< Predefined brown color (165, 42, 42, 255).
    inline static const Color pink() { return Color(255, 192, 203, 255); } ///< Predefined pink color (255, 192, 203, 255).
    inline static const Color light_gray() { return Color(211, 211, 211, 255); } ///< Predefined light gray color (211, 211, 211, 255).
    inline static const Color dark_gray() { return Color(169, 169, 169, 255); } ///< Predefined dark gray color (169, 169, 169, 255).
    inline static const Color light_blue() { return Color(173, 216, 230, 255); } ///< Predefined light blue color (173, 216, 230, 255).
    inline static const Color dark_blue() { return Color(0, 0, 139, 255); } ///< Predefined dark blue color (0, 0, 139, 255).
    inline static const Color light_green() { return Color(144, 238, 144, 255); } ///< Predefined light green color (144, 238, 144, 255).
    inline static const Color dark_green() { return Color(0, 100, 0, 255); } ///< Predefined dark green color (0, 100, 0, 255).
    inline static const Color light_red() { return Color(255, 182, 193, 255); } ///< Predefined light red color (255, 182, 193, 255).
    inline static const Color dark_red() { return Color(139, 0, 0, 255); } ///< Predefined dark red color (139, 0, 0, 255).
    inline static const Color light_yellow() { return Color(255, 255, 224, 255); } ///< Predefined light yellow color (255, 255, 224, 255).
    inline static const Color dark_yellow() { return Color(204, 204, 0, 255); } ///< Predefined dark yellow color (204, 204, 0, 255).
    inline static const Color light_cyan() { return Color(224, 255, 255, 255); } ///< Predefined light cyan color (224, 255, 255, 255).
    inline static const Color dark_cyan() { return Color(0, 139, 139, 255); } ///< Predefined dark cyan color (0, 139, 139, 255).
    inline static const Color light_magenta() { return Color(255, 182, 255, 255); } ///< Predefined light magenta color (255, 182, 255, 255).
    inline static const Color dark_magenta() { return Color(139, 0, 139, 255); } ///< Predefined dark magenta color (139, 0, 139, 255).

};

#endif