#ifndef PHYSICS_H
#define PHYSICS_H

#include <cstdint>
#include <functional>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>
#include "vec.h"

class Logger;
struct Object;
class Texture;

namespace Physics {

/**
 * @brief Bitmask type used for collision categories and filters.
 *
 * A body may belong to one or more categories through `mask_tag`, and may
 * choose which categories it accepts through `collision_mask`.
 */
using Mask_Tag = std::uint64_t;

constexpr Mask_Tag MASK_NONE = 0; ///< Matches no collision category.
constexpr Mask_Tag MASK_DEFAULT = 1; ///< Default category assigned to new bodies.
constexpr Mask_Tag MASK_ALL = std::numeric_limits<Mask_Tag>::max(); ///< Matches every collision category.

/**
 * @brief Creates a single collision category bit.
 * @param bit_index Bit index in the inclusive range `[0, 63]`.
 * @return The generated mask tag, or `MASK_NONE` when the index is invalid.
 *
 * Example:
 * ```cpp
 * constexpr auto ACTOR = Physics::make_mask_tag(0);
 * constexpr auto WORLD  = Physics::make_mask_tag(1);
 * ```
 */
constexpr Mask_Tag make_mask_tag(std::uint8_t bit_index) {
    return bit_index < 64 ? (Mask_Tag{1} << bit_index) : MASK_NONE;
}

/**
 * @brief Shapes supported by Collision_Body.
 */
enum class Collision_Shape {
    CIRCLE,        ///< Circle using the smaller transform dimension as its diameter.
    RECTANGLE,     ///< Rectangle using the body's transform bounds.
    OVAL,          ///< Ellipse using half of the transform size as its radii.
    PIXEL_PERFECT  ///< Texture alpha-mask collision with rectangle fallback.
};

/**
 * @brief Describes how a collision body participates in simulation.
 */
enum class Body_Type {
    STATIC,    ///< Never moved by the physics engine.
    DYNAMIC,   ///< Moved by velocity, forces, gravity and collision impulses.
    KINEMATIC  ///< Moved by velocity, but ignores forces and collision impulses.
};

/**
 * @brief Axis-aligned bounding box used by broad-phase collision checks.
 */
struct AABB {
    Vec min; ///< Top-left/minimum world-space corner.
    Vec max; ///< Bottom-right/maximum world-space corner.
};

class Physics_Engine;
class Collision_Body;

/**
 * @brief Describes one detected collision between two bodies.
 *
 * The physics world owns neither body. Pointers remain valid only while their
 * corresponding Collision_Body instances are alive.
 */
struct Collision {
    Collision_Body* body_a = nullptr; ///< First borrowed body pointer.
    Collision_Body* body_b = nullptr; ///< Second borrowed body pointer.
    Vec point{};        ///< Approximate world-space contact point.
    Vec normal{};       ///< Points from body_a towards body_b.
    float penetration = 0.0f; ///< Overlap depth in logical world units.
};

/**
 * @brief Result returned by Physics_Engine::raycast().
 */
struct Raycast_Hit {
    bool hit = false; ///< Whether the ray intersected a body.
    Collision_Body* body = nullptr; ///< Borrowed pointer to the hit body.
    Vec point{}; ///< World-space hit position.
    Vec normal{}; ///< Approximate outward surface normal at the hit position.
    float distance = 0.0f; ///< Distance from the ray origin to the hit.

    /** @return `true` when the ray hit a body. */
    explicit operator bool() const { return hit; }
};

/**
 * @brief Lightweight 2D collision body attached to an Object or standalone Transform.
 *
 * When attached to an Object, the body borrows the Object pointer. Collision tests and
 * simulation use its world transform, including any parent hierarchy. It does not own
 * or delete the Object. Bodies created
 * after `Engine::physics_engine` is initialized register themselves automatically and
 * unregister when destroyed.
 *
 * Rotation is supported by oval and pixel-perfect point tests. Rectangle collision
 * response uses an axis-aligned bounding box, which is intentional for pixel-art games.
 *
 * Example:
 * ```cpp
 * Physics::Collision_Body wall(
 *     &wall_object,
 *     Physics::Collision_Shape::RECTANGLE,
 *     Physics::Body_Type::STATIC
 * );
 * wall.mask_tag = Physics::make_mask_tag(1);
 * ```
 */
class Collision_Body {
public:
    /** @brief Callback invoked when the body collides with or overlaps another body. */
    using Collision_Callback = std::function<void(const Collision&)>;

    /**
     * @brief Constructs a collision body attached to an Object.
     * @param owner Borrowed Object pointer whose transform and texture are used.
     * @param shape Collision shape used by narrow-phase checks.
     * @param type Simulation type of the body.
     */
    explicit Collision_Body(Object* owner,
                            Collision_Shape shape = Collision_Shape::RECTANGLE,
                            Body_Type type = Body_Type::STATIC);

    /**
     * @brief Constructs a standalone collision body with its own Transform.
     * @param transform Initial world-space transform copied into the body.
     * @param shape Collision shape used by narrow-phase checks.
     * @param type Simulation type of the body.
     */
    explicit Collision_Body(const Transform& transform,
                            Collision_Shape shape = Collision_Shape::RECTANGLE,
                            Body_Type type = Body_Type::STATIC);

    /** @brief Unregisters the body from its physics world. */
    virtual ~Collision_Body();

    Collision_Body(const Collision_Body&) = delete;
    Collision_Body& operator=(const Collision_Body&) = delete;

    /**
     * @return Mutable owner-local transform, or the standalone world transform.
     * @note Use collision_transform() when a world-space value is required.
     */
    Transform& transform();
    /** @return Read-only owner-local transform, or the standalone world transform. */
    const Transform& transform() const;
    /** @return Effective transform used for collision tests, including optional local bounds. */
    Transform collision_transform() const;
    /** Uses a local transform relative to the owner transform for collision only. */
    void set_local_transform(const Transform& transform);
    const Transform& local_transform() const { return m_local_transform; }
    /** Convenience wrapper for an unrotated local collider. */
    void set_local_bounds(Vec offset, Vec size);
    void clear_local_bounds();
    bool has_local_bounds() const { return m_use_local_bounds; }
    Vec local_offset() const { return m_local_transform.pos; }
    Vec local_size() const { return m_local_transform.size; }
    /** @return Borrowed owner pointer, or `nullptr` for standalone bodies. */
    Object* owner() const { return m_owner; }

    /** @return Current collision shape. */
    Collision_Shape shape() const { return m_shape; }
    /**
     * @brief Changes the collision shape used by future checks.
     * @param shape New collision shape.
     */
    void set_shape(Collision_Shape shape);
    /** @return Current simulation type. */
    Body_Type body_type() const { return m_type; }
    /**
     * @brief Changes how the body participates in simulation.
     * @param type New static, dynamic, or kinematic body type.
     */
    void set_body_type(Body_Type type);

    /**
     * @brief Gets the texture used for pixel-perfect checks.
     * @return Explicit pixel texture, owner texture, or `nullptr`.
     */
    Texture* texture() const;
    /**
     * @brief Overrides the texture used for pixel-perfect collision.
     * @param texture Borrowed texture pointer. Passing `nullptr` uses the owner texture.
     */
    void set_pixel_texture(Texture* texture) { m_pixel_texture = texture; }
    /**
     * @brief Sets the minimum alpha value considered solid.
     * @param threshold Alpha threshold in the inclusive range `[0, 255]`.
     */
    void set_alpha_threshold(std::uint8_t threshold) { m_alpha_threshold = threshold; }
    /** @return Minimum alpha value considered solid. */
    std::uint8_t alpha_threshold() const { return m_alpha_threshold; }

    /**
     * @brief Sets body mass. Values at or below zero are clamped to a safe minimum.
     * @param mass New body mass.
     */
    void set_mass(float mass);
    /** @return Current mass. */
    float mass() const { return m_mass; }
    /** @return Reciprocal mass for dynamic bodies, otherwise `0`. */
    float inverse_mass() const;
    /**
     * @brief Accumulates a continuous force for the next simulation step.
     * @param force Force vector in world-space directions.
     */
    void apply_force(const Vec& force);
    /**
     * @brief Immediately changes dynamic body velocity using an impulse.
     * @param impulse Impulse vector applied to the body.
     */
    void apply_impulse(const Vec& impulse);
    /** @brief Removes all forces waiting for the next simulation step. */
    void clear_forces() { m_force = {}; }

    /**
     * @brief Sets the callback invoked for collision and trigger events.
     * @param callback Function receiving collision information from this body's perspective.
     */
    void set_collision_callback(Collision_Callback callback) { m_callback = std::move(callback); }

    /** Wakes a sleeping non-static body and resets its stationary counter. */
    void wake();
    /** Puts a non-static body to sleep and clears its velocity and pending force. */
    void sleep();
    bool is_awake() const { return awake; }

    /** Transform observed at the end of the previous physics step. */
    Transform previous_transform() const { return m_previous_transform; }

    Vec velocity{}; ///< Velocity in logical world units per second.
    float gravity_scale = 0.0f; ///< Multiplier applied to world gravity.
    float restitution = 0.0f; ///< Bounciness, normally in the range `[0, 1]`.
    float friction = 0.2f; ///< Surface friction used during collision response.
    float linear_damping = 0.0f; ///< Velocity loss per second.
    bool enabled = true; ///< Disabled bodies are ignored by simulation and queries.
    bool is_trigger = false; ///< Triggers report collisions without physical response.

    Mask_Tag mask_tag = MASK_DEFAULT;       ///< Categories this body belongs to.
    Mask_Tag collision_mask = MASK_ALL;     ///< Categories this body accepts.

    int active_collision_range = 0; ///< Extra broad-phase padding around this body, in world units.
    bool awake = true; ///< Sleeping non-static bodies remain collidable but are not active sources.

private:
    friend class Physics_Engine;

    Object* m_owner = nullptr;
    Transform m_standalone_transform{};
    Collision_Shape m_shape = Collision_Shape::RECTANGLE;
    Body_Type m_type = Body_Type::STATIC;
    Texture* m_pixel_texture = nullptr;
    std::uint8_t m_alpha_threshold = 1;

    float m_mass = 1.0f;
    Vec m_force{};
    Collision_Callback m_callback;
    Physics_Engine* m_world = nullptr;
    Transform m_local_transform{};

    bool m_use_local_bounds = false;
    Transform m_previous_transform{};
    Body_Type m_previous_type = Body_Type::STATIC;
    Collision_Shape m_previous_shape = Collision_Shape::RECTANGLE;
    bool m_previous_enabled = true;
    bool m_previous_is_trigger = false;
    Mask_Tag m_previous_mask_tag = MASK_DEFAULT;
    Mask_Tag m_previous_collision_mask = MASK_ALL;
    int m_previous_active_collision_range = 0;
    bool m_tracking_initialized = false;
    int m_stationary_steps = 0;

    void translate_world(const Vec& delta);
};

/**
 * @brief Dynamic collision body affected by world gravity by default.
 *
 * This is a convenience body with `Body_Type::DYNAMIC` and `gravity_scale = 1`.
 */
class Gravitational_Object : public Collision_Body {
public:
    /**
     * @brief Constructs a gravitational body attached to an Object.
     * @param owner Borrowed Object pointer.
     * @param shape Collision shape used by the body.
     * @param mass Body mass used for force and impulse calculations.
     */
    explicit Gravitational_Object(Object* owner,
                                  Collision_Shape shape = Collision_Shape::RECTANGLE,
                                  float mass = 1.0f);

    /**
     * @brief Constructs a standalone gravitational body.
     * @param transform Initial world-space transform.
     * @param shape Collision shape used by the body.
     * @param mass Body mass used for force and impulse calculations.
     */
    explicit Gravitational_Object(const Transform& transform,
                                  Collision_Shape shape = Collision_Shape::RECTANGLE,
                                  float mass = 1.0f);
};

/**
 * @brief Owns the 2D simulation state and processes registered collision bodies.
 *
 * The engine only borrows body pointers. Collision_Body automatically unregisters
 * itself when destroyed. `update()` uses a fixed timestep accumulator to keep movement
 * and collision response stable when frame time changes.
 *
 * Example:
 * ```cpp
 * auto hit = Engine::physics_engine->raycast(
 *     origin, direction, 200.0f, Physics::make_mask_tag(1)
 * );
 * if (hit) {
 *     Object* object = hit.body->owner();
 * }
 * ```
 */
class Physics_Engine {
public:
    /**
     * @brief Constructs an empty physics world.
     * @param logger Optional logger pointer. The world does not own it.
     */
    explicit Physics_Engine(Logger* logger = nullptr) : m_logger(logger) {}

    /** @brief Detaches every registered body and clears simulation state. */
    ~Physics_Engine();

    /**
     * @brief Registers a body with this world.
     * @param body Borrowed pointer. Duplicate registration is ignored.
     * @note A body already registered elsewhere is moved from the old world.
     */
    void add_body(Collision_Body* body);
    /**
     * @brief Removes a body without destroying it.
     * @param body Body pointer to remove.
     */
    void remove_body(Collision_Body* body);
    /** @brief Detaches every body and clears collisions and timestep state. */
    void clear();

    /**
     * @brief Advances the world using an accumulator and fixed timestep.
     * @param delta_seconds Frame duration in seconds.
     */
    void update(float delta_seconds);
    /**
     * @brief Performs exactly one simulation step.
     * @param delta_seconds Duration of this step in seconds.
     */
    void step(float delta_seconds);

    /**
     * @brief Sets world gravity in logical units per second squared.
     * @param gravity New gravity vector.
     */
    void set_gravity(const Vec& gravity) { m_gravity = gravity; }
    /** @return Current world gravity. */
    const Vec& gravity() const { return m_gravity; }
    /**
     * @brief Sets the fixed simulation step in seconds. Invalid values are ignored.
     * @param seconds New fixed step duration in seconds.
     */
    void set_fixed_timestep(float seconds);
    /** @return Fixed simulation step in seconds. */
    float fixed_timestep() const { return m_fixed_timestep; }
    /**
     * @brief Sets the maximum physics steps processed during one frame.
     * @param count Maximum substep count, clamped to at least one.
     */
    void set_max_substeps(int count);

    /**
     * @brief Sets the uniform-grid cell size used by broad-phase collision detection.
     * @param size Cell width and height in world units. Non-positive values are ignored.
     *
     * A value close to the typical collider size usually gives the best result. The
     * default is 64 world units, which is a good fit for the engine's 16 px tilemaps.
     */
    void set_spatial_cell_size(float size);
    /** @return Current broad-phase grid cell size in world units. */
    float spatial_cell_size() const { return m_spatial_cell_size; }

    /** Enables or disables automatic sleeping of stationary non-static bodies. */
    void set_auto_sleep(bool enabled) { m_auto_sleep = enabled; }
    bool auto_sleep() const { return m_auto_sleep; }
    /** Configures the velocity threshold and consecutive steps required for sleep. */
    void set_sleep_settings(float velocity_threshold, int stationary_steps);

    /** @return Borrowed pointers to every registered body. */
    const std::vector<Collision_Body*>& bodies() const { return m_bodies; }
    /** @return Collisions detected during the most recent simulation step. */
    const std::vector<Collision>& collisions() const { return m_collisions; }

    /**
     * @brief Tests two bodies without advancing or resolving them.
     * @param a First body.
     * @param b Second body.
     * @param result Optional output collision information.
     * @return `true` when the shapes overlap.
     */
    bool test_collision(Collision_Body& a, Collision_Body& b, Collision* result = nullptr) const;

    /**
     * @brief Finds registered bodies overlapping the supplied body.
     * @param body Body used as the query shape. It need not be registered.
     * @param mask Collision categories included in the result.
     * @return Borrowed pointers to every matching overlapping body.
     */
    std::vector<Collision_Body*> query_overlaps(const Collision_Body& body, Mask_Tag mask = MASK_ALL) const;

    /**
     * @brief Casts a ray through the physics world and returns the nearest hit.
     * @param origin Ray start in world coordinates.
     * @param direction Ray direction; normalized internally.
     * @param max_distance Maximum ray length in logical world units.
     * @param mask Collision categories accepted by the query.
     * @param ignored_body Optional body that should never be returned.
     * @return Information about the nearest hit, or an empty result.
     */
    Raycast_Hit raycast(
        const Vec& origin, const Vec& direction, float max_distance,
        Mask_Tag mask = MASK_ALL,
        const Collision_Body* ignored_body = nullptr
    ) const;

private:
    friend class Collision_Body;
    using Spatial_Grid = std::unordered_map<std::uint64_t, std::vector<std::size_t>>;

    std::vector<Collision_Body*> m_bodies; ///< Registered borrowed body pointers.
    std::vector<Collision> m_collisions; ///< Results from the latest step.
    Vec m_gravity{0.0f, 980.0f}; ///< Default downward acceleration in pixels per second squared.
    float m_fixed_timestep = 1.0f / 120.0f; ///< Default 120 Hz simulation interval.
    float m_accumulator = 0.0f; ///< Unprocessed frame time.
    int m_max_substeps = 8; ///< Spiral-of-death protection for slow frames.
    float m_spatial_cell_size = 64.0f; ///< Uniform-grid broad-phase cell size.
    Spatial_Grid m_static_grid; ///< Cached index of enabled static bodies.
    std::vector<std::size_t> m_large_static_bodies; ///< Statics too large for regular grid insertion.
    bool m_static_grid_dirty = true;
    bool m_auto_sleep = true;
    float m_sleep_velocity_threshold = 0.05f;
    int m_sleep_after_steps = 30;
    Logger* m_logger = nullptr; ///< Borrowed optional logger.

    /** @return Whether both bodies accept each other's collision categories. */
    static bool masks_allow(const Collision_Body& a, const Collision_Body& b);
    /** Rebuilds the cached static-body spatial index. */
    void rebuild_static_grid();
    /** @brief Applies positional correction, normal impulse and friction. */
    void resolve(Collision& collision);
};

// Lowercase aliases matching the component-style names used in scripts.
using collision_body = Collision_Body;
using gravitational_object = Gravitational_Object;
using mask_tag = Mask_Tag;
using raycast = Raycast_Hit;

}

#endif
