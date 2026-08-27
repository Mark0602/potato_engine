#ifndef VEC_H
#define VEC_H

/**
 * @brief 2D floating-point vector used for positions, sizes, and directions.
 *
 * Supports all common arithmetic, compound-assignment, and comparison operators.
 * @attention
 * Please note that Vecs are not only used for positions and sizes, 
 * but also for directions and other 2D vector math.
 * You might encounter functions relying on Vecs for 2 dimensional arrays
 * or other mathematical operations, so be cautious when using them in different contexts.
 * 
 * @param x Horizontal component.
 * @param y Vertical component.
 * 
 * Example:
 * ```cpp
 * Vec pos(100.0f, 200.0f);
 * Vec size(32.0f, 32.0f);
 * Vec center = pos + size / 2.0f;
 * ```
 */
struct Vec {
    float x = 0.0f; ///< Horizontal component.
    float y = 0.0f; ///< Vertical component.

    Vec() = default;

    /**
     * @brief Constructs a Vec with given x and y values.
     * @param x Horizontal component.
     * @param y Vertical component.
     */
    Vec(float x, float y)
    : x(x), y(y) {}


    /// @name Arithmetic operators
    /// Example:
    /// ```cpp
    /// Vec a(10.f, 20.f), b(5.f, 5.f);
    /// Vec sum  = a + b;   // {15, 25}
    /// Vec diff = a - b;   // {5,  15}
    /// Vec comp = a * b;   // {50, 100}  (component-wise)
    /// Vec scaled = a * 2.f; // {20, 40}
    /// Vec halved = a / 2.f; // {5,  10}
    /// ```
    ///@{
    Vec operator+(const Vec& a) const {
        return { static_cast<float>(x + a.x), static_cast<float>(y + a.y) };
    }
    Vec operator-(const Vec& a) const {
        return { static_cast<float>(x - a.x), static_cast<float>(y - a.y) };
    }
    /// Component-wise multiplication.
    Vec operator*(const Vec& a) const {
        return { static_cast<float>(a.x * x), static_cast<float>(a.y * y) };
    }
    /// Scalar multiplication.
    Vec operator*(float b) const {
        return { static_cast<float>(x * b), static_cast<float>(y * b) };
    }
    /// Scalar division. Behaviour is undefined if `b` is zero.
    Vec operator/(float b) const {
        return { static_cast<float>(x / b), static_cast<float>(y / b) };
    }

    /// @name Compound assignment operators
    /// Example:
    /// ```cpp
    /// Vec pos(0.f, 0.f);
    /// Vec velocity(1.f, 0.5f);
    /// pos += velocity;   // move each frame
    /// pos *= 0.9f;       // apply friction
    /// ```
    ///@{
    Vec& operator+=(const Vec& a) { x += a.x; y += a.y; return *this; }
    Vec& operator-=(const Vec& b) { x -= b.x; y -= b.y; return *this; }
    /// Component-wise multiply-assign.
    Vec& operator*=(const Vec& b)  { x *= b.x; y *= b.y; return *this; }
    Vec& operator*=(float b) { x *= b;   y *= b;   return *this; }
    Vec& operator/=(float b) { x /= b;   y /= b;   return *this; }
    ///@}

    /// @name Comparison operators
    /// All comparisons are **component-wise** (both x AND y must satisfy the condition).
    /// Example:
    /// ```cpp
    /// Vec a(1.f, 2.f), b(3.f, 4.f);
    /// bool eq  = (a == b);  // false
    /// bool lt  = (a < b);   // true  — both x and y of a are less than b
    /// bool lte = (a <= b);  // true
    /// ```
    ///@{
    bool operator==(const Vec& a) const { return (a.x == x) && (a.y == y); }
    bool operator!=(const Vec& a) const { return !(*this == a); }
    /// True only if both x and y are strictly less.
    bool operator<(const Vec& a)  const { return (x < a.x)  && (y < a.y);  }
    /// True only if both x and y are strictly greater.
    bool operator>(const Vec& a)  const { return (x > a.x)  && (y > a.y);  }
    bool operator<=(const Vec& a) const { return (x <= a.x) && (y <= a.y); }
    bool operator>=(const Vec& a) const { return (x >= a.x) && (y >= a.y); }
    ///@}
};

/**
 * @brief Represents a 2D transformation, including position, size, and rotation.
 * 
 * @param pos Position in 2D space.
 * @param size Size in 2D space.
 * @param rotation Rotation in 2D space. x is the angle in degrees, y is the SDL_FlipMode.
 */
struct Transform {
    Vec pos;   ///< Position in 2D space.
    Vec size;  ///< Size in 2D space.
    Vec rotation; ///< Rotation in 2D space. x is the angle in degrees, y is the SDL_FlipMode.

    Transform() = default;

    /**
     * @brief Constructs a Transform with given position.
     * @param pos Position in 2D space.
     */
    Transform(const Vec& pos) : pos(pos), size({0, 0}), rotation({0, 0}) {}

    /**
     * @brief Constructs a Transform with given position and size.
     * @param pos Position in 2D space.
     * @param size Size in 2D space.
     */
    Transform(const Vec& pos, const Vec& size) : pos(pos), size(size), rotation({0, 0}) {}

    /**
     * @brief Constructs a Transform with given position, size, and rotation.
     * @param pos Position in 2D space.
     * @param size Size in 2D space.
     * @param rotation Rotation in 2D space. x is the angle in degrees, y is the SDL_FlipMode.
     */
    Transform(const Vec& pos, const Vec& size, const Vec& rotation) : pos(pos), size(size), rotation(rotation) {}

    Transform operator+(const Transform& other) const {
        return { pos + other.pos, size + other.size, rotation };
    }

    Transform operator-(const Transform& other) const {
        return { pos - other.pos, size - other.size, rotation };
    }   

    Transform operator*(float scalar) const {
        return { pos * scalar, size * scalar, rotation};
    }

    Transform operator/(float scalar) const {
        return { pos / scalar, size / scalar, rotation };
    }

    Transform& operator+=(const Transform& other) {
        pos += other.pos;
        size += other.size;
        return *this;
    }

    Transform& operator-=(const Transform& other) {
        pos -= other.pos;
        size -= other.size;
        return *this;
    }

    Transform& operator*=(float scalar) {
        pos *= scalar;
        size *= scalar;
        return *this;
    }

    Transform& operator/=(float scalar) {
        pos /= scalar;
        size /= scalar;
        return *this;
    }

};

/**
 * @brief Represents a 3D vector. Right now only used for 3D audio panning, but could be used for other things in the future.
 */
struct Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Vec4 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
};

#endif
