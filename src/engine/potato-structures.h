#pragma once
#include <cstdint>
#include <vector>
#include <float.h>

// =============================================================================
// POS STRUCTURE
// =============================================================================
// Represents position, rotation, and scale in 2D space
struct pos {
    float x = 0.0f;
    float y = 0.0f;
    //float z = 0.0f;
    float rotation = 0.0f;  // in degrees
    float w = 1.0f;
    float h = 1.0f;

    // Helper methods
    void translate(float dx, float dy) {
        x += dx;
        y += dy;
    }

    void rotate(float degrees) {
        rotation += degrees;
        // Keep rotation in 0-360 range
        while (rotation >= 360.0f) rotation -= 360.0f;
        while (rotation < 0.0f) rotation += 360.0f;
    }

    void scale(float sx, float sy) {
        w *= sx;
        h *= sy;
    }
};

// =============================================================================
// COLOR STRUCTURE
// =============================================================================
typedef struct color {
    uint8_t r, g, b, a;

    // SDL_FColor get_sdl_fcolor() {
    //     return SDL_FColor = {}
    // }
};

// =============================================================================
// VERTEX STRUCTURE
// =============================================================================
struct vertex {
    float x, y, z;
    float u, v;
    color col;

    void set_position(float px, float py) {
        x = px;
        y = py;
        z = 0;
    }

    void set_position(float px, float py, float pz) {
        x = px;
        y = py;
        z = pz;
    }

    void set_uv(float tu, float tv) {
        u = tu;
        v = tv;
    }

    void set_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
        col.r = red;
        col.g = green;
        col.b = blue;
        col.a = alpha;
    }

    void set_color(color color) {
        this->col = color;
    }

    float get_x() const { return x; }
    float get_y() const { return y; }
    float get_z() const { return z; }
    float get_u() const { return u; }
    float get_v() const { return v; }
    color get_color() const { return col; }
};


// =============================================================================
// RENDER MODE ENUM
// =============================================================================

typedef enum {
    RENDER_MODE_VERTEX,
    RENDER_MODE_BASIC
} potato_render_mode;
