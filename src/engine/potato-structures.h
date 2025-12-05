#include "potato-engine.h"
#include "potato-script-base.h"
#include "potato-texture.h"


// =============================================================================
// POS STRUCTURE
// =============================================================================
// Represents position, rotation, and scale in 2D space
struct pos {
    float x = 0.0f;
    float y = 0.0f;
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
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} color;

// =============================================================================
// VERTEX STRUCTURE
// =============================================================================
typedef struct vertex {
    float x, y;
    color color;
};


// =============================================================================
// RENDER MODE ENUM
// =============================================================================

typedef enum {
    RENDER_MODE_VERTEX,
    RENDER_MODE_BASIC
} potato_render_mode;
