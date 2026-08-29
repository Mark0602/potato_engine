#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"
#include "debug.h"
#include "texture.h"
#include "vec.h"
#include "render.h"
#include <string>
#include <vector>

class script;

/**
 * @brief A renderable game object with a position, size, and optional texture.
 *
 * `pos` is the top-left corner in logical coordinates.
 * `size` is the width and height. Add the object to `Engine::render_pool` with `submit()`
 * to have it drawn automatically each frame, or call `draw()` manually.
 *
 * @param texture  Pointer to a loaded Texture, or `nullptr` for invisible objects.
 * @param transform Contains position, size, and rotation. If you use this option, ignore the `pos`, `size`, and `rotation` as separate parameters.
 * @param pos      Top-left position in logical coordinates.
 * @param size     Width and height in logical pixels.
 * @param rotation First value is the rotation angle in degrees. Second value is used for facing direction (not implemented yet).
 * @param logger   Optional Logger for debug output.
 * @param input_transparent If true, the object does not block input events (e.g. mouse clicks) from reaching objects behind it.
 * @param z_index Determines the draw order. Lower values are drawn later (on top of higher values). 0 should be used for UI. Default is 128 (middle of the range).
 * @param auto_submit If true, the object is automatically submitted to the render pool each frame. Set to false if you want to manage submission manually.
 * @param tint Color tint applied to the texture when drawn. Default is white (no tint).
 * @param component Pointer to a script component attached to this object. Set with `attach_script()`. `nullptr` if no script is attached.
 * 
 * Example:
 * ```cpp
 * Texture tex(Engine::renderer, "assets/sprite.png");
 * Object sprite(100.f, 200.f, 32.f, 32.f, &tex);
 * ```
 */
struct Object {
public:
    std::string name;
    std::vector<std::string> tags;
    Texture* texture = nullptr;
    SDL_FRect source_rect{};
    bool use_source_rect = false;
    /**
     * Local transform when this object has a parent; world transform otherwise.
     * Use get_world_transform() whenever a world-space value is required.
     */
    Transform transform = {Vec(0.f, 0.f), Vec(0.f, 0.f), Vec(0.f, 0.f)};
    Logger* logger = nullptr;

    Object_Pool* object_pool = nullptr; ///< Pointer to the object pool that manages this object. Set automatically when the object is added to a pool.
    
    bool input_transparent = false;
    bool visible = true; ///< If false, the object is not drawn.

    bool auto_submit = true; ///< If true, the object is automatically submitted to the render pool each frame. Set to false if you want to manage submission manually.
    bool camera_space = true; ///< World-space objects use the active camera; set false for UI/cursors.
    
    Color tint = Color::white(); ///< Color tint applied to the texture when drawn. Default is white (no tint).
    uint8_t z_index = 128; ///< Layer order. Higher values draw first; lower values draw later/on top.
    bool y_sort = false; ///< Sort this object by its bottom edge among commands with the same z-index.
    float y_sort_offset = 0.0f; ///< Moves the Y-sort pivot relative to the object's bottom edge.

    script* component = nullptr;

    /**
     * @brief Constructs an Object from Vec structs.
     * @param p Top-left position.
     * @param s Size (width, height).
     * @param r Rotation (angle, facing direction). 
     * @param t Pointer to a loaded Texture, or `nullptr`.
     * @param l Optional logger.
     * 
     * @attention The `rotation.y` paramater can take 4 different values to indicate the facing direction of the object:
     * 0 - None, 1 - Horizontal flip, 2 - Vertical flip, 3 - Both flips. This relies on the SDL_FlipMode enum.
     * 
     * Example:
     * ```cpp
     * Vec pos(100.f, 200.f);
     * Vec size(32.f, 32.f);
     * Vec rotation(0.f, 0.f);
     * Object sprite(pos, size, rotation, &tex);
     * ```
     */
    Object(Vec p, Vec s, Vec r = {0.0f, 0.0f}, Texture* t = nullptr, Object_Pool *objp = nullptr, Logger *l = nullptr) : transform({p, s, r}), texture(t), logger(l), object_pool(objp) {
        if (logger) {
            logger->log(Log_Level::DEBUG, "Object", "Object created at position: (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ") with size: (" + std::to_string(s.x) + ", " + std::to_string(s.y) + ")");
        }
        register_with_pool();
    }

    /**
     * @brief Constructs an Object from individual floats.
     * @param x Left edge in logical pixels.
     * @param y Top edge in logical pixels.
     * @param w Width in logical pixels.
     * @param h Height in logical pixels.
     * @param rx Rotation angle in degrees (default 0).
     * @param ry Facing direction (not implemented yet, default 0).
     * @param t Pointer to a loaded Texture, or `nullptr`.
     * @param l Optional logger.
     *      * 
     * @attention The `rotation.y` paramater can take 4 different values to indicate the facing direction of the object:
     * 0 - None, 1 - Horizontal flip, 2 - Vertical flip, 3 - Both flips. This relies on the SDL_FlipMode enum.
     * 
     * Example:
     * ```cpp
     * Vec pos(100.f, 200.f);
     * Vec size(32.f, 32.f);
     * Vec rotation(0.f, 0.f);
     * Object sprite(pos, size, rotation, &tex);
     * ```
     */
    Object(float x, float y, float w, float h, float rx = 0.f, float ry = 0.f, Texture* t = nullptr, Object_Pool *objp = nullptr, Logger *l = nullptr) : transform({Vec(x, y), Vec(w, h), Vec(rx, ry)}), texture(t), logger(l), object_pool(objp) {
        if (logger) {
            logger->log(Log_Level::DEBUG, "Object", "Object created at position: (" + std::to_string(x) + ", " + std::to_string(y) + ") with size: (" + std::to_string(w) + ", " + std::to_string(h) + ")");
        }
        register_with_pool();
    }

    /**
     * @brief Constructs an Object from individual floats, with default rotation and logger.
     * @param x Left edge in logical pixels.
     * @param y Top edge in logical pixels.
     * @param w Width in logical pixels.
     * @param h Height in logical pixels.
     * @param t Pointer to a loaded Texture, or `nullptr`.
     * @param l Optional logger.
     * @param objp Optional object pool.
     */
    Object(float x, float y, float w, float h, Texture* t = nullptr, Object_Pool *objp = nullptr, Logger *l = nullptr) : transform({Vec(x, y), Vec(w, h), Vec(0.f, 0.f)}), texture(t), logger(l), object_pool(objp) {
        if (logger) {
            logger->log(Log_Level::DEBUG, "Object", "Object created at position: (" + std::to_string(x) + ", " + std::to_string(y) + ") with size: (" + std::to_string(w) + ", " + std::to_string(h) + ")");
        }
        register_with_pool();
    }

    Object(Transform transform, Texture* t = nullptr, Object_Pool *objp = nullptr, Logger *l = nullptr) : transform(transform), texture(t), logger(l), object_pool(objp) {
        if (logger) {
            logger->log(Log_Level::DEBUG, "Object", "Object created at position: (" + std::to_string(transform.pos.x) + ", " + std::to_string(transform.pos.y) + ") with size: (" + std::to_string(transform.size.x) + ", " + std::to_string(transform.size.y) + ")");
        }
        register_with_pool();
    }

    // Object stores borrowed registry and hierarchy pointers plus an owned
    // script component. Address identity is therefore part of its state.
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;

    virtual ~Object();

    /**
     * @brief Returns the object pool that manages this object.
     * @return Pointer to the Object_Pool, or `nullptr` if not managed by any pool.
     */
    Object_Pool* get_object_pool() const {
        return object_pool;
    }

    void add_tag(const std::string& tag);
    void remove_tag(const std::string& tag);
    bool has_tag(const std::string& tag) const;

    /**
     * @brief Sets the object pool that manages this object. Automatically adds the object to the pool if not already present.
     * @param objp Pointer to the Object_Pool. Pass `nullptr` to remove from the current pool.
     */
    void set_object_pool(Object_Pool* objp) {
        object_pool = objp;
    }

    /** @brief Returns the local transform (identical to world space for root objects). */
    Transform get_transform() const {
        return transform;
    }

    /** @brief Explicit alias for get_transform(). */
    Transform get_local_transform() const {
        return transform;
    }

    /**
     * @brief Returns the transform composed through the complete parent chain.
     * @return World-space position, size, angle, and flip flags.
     */
    Transform get_world_transform() const;

    /** @brief Sets the local transform (world transform for root objects). */
    void set_transform(const Transform& new_transform) {
        transform = new_transform;
    }

    /** @brief Explicit alias for set_transform(). */
    void set_local_transform(const Transform& new_transform) {
        transform = new_transform;
    }

    /**
     * @brief Sets the world transform, converting it to parent-local space when needed.
     */
    void set_world_transform(const Transform& new_transform);

    /**
     * @brief Changes this object's parent.
     *
     * Parenting is non-owning. A parent never deletes its children. Cycles and
     * self-parenting are rejected.
     *
     * @param new_parent New parent, or nullptr to make this object a root.
     * @param keep_world_transform Preserve the current world-space appearance.
     *        When false, the existing transform is kept as the new local transform.
     * @return true on success, false if the requested relationship is invalid.
     */
    bool set_parent(Object* new_parent, bool keep_world_transform = true);

    /** @brief Makes child a direct child of this object. */
    bool add_child(Object* child, bool keep_world_transform = true);

    /** @brief Detaches a direct child from this object. */
    bool remove_child(Object* child, bool keep_world_transform = true);

    /** @brief Detaches every direct child without deleting them. */
    void clear_children(bool keep_world_transform = true);

    Object* get_parent() const { return m_parent; }
    const std::vector<Object*>& get_children() const { return m_children; }
    bool has_parent() const { return m_parent != nullptr; }
    bool is_ancestor_of(const Object* object) const;

    /**
     * @brief Returns `true` if `mouse_pos` is within the object's bounding box.
     * @param mouse_pos Cursor position in logical coordinates.
     */
    virtual bool on_hover(const Vec& mouse_pos) const {
        if (input_transparent) return false;
        const Transform world = get_world_transform();
        return (mouse_pos.x >= world.pos.x && mouse_pos.x <= world.pos.x + world.size.x &&
                mouse_pos.y >= world.pos.y && mouse_pos.y <= world.pos.y + world.size.y);
    }

    /**
     * @brief Returns `true` if `mouse_pos` is within the object's bounding box (alias for `on_hover`).
     * @param mouse_pos Cursor position in logical coordinates.
     */
    virtual bool on_click(const Vec& mouse_pos) const {
        return on_hover(mouse_pos);
    }

    /**
     * @brief Renders the object using its texture at its current `pos` and `size`.
     * Does nothing if the texture is not loaded. Logs a warning if a logger is set.
     * @param renderer The SDL renderer to draw with.
     */
    virtual void draw(SDL_Renderer* renderer);
    

    virtual Draw make_draw_command() const;

    /**
     * @brief Submits every draw command needed by this object.
     *
     * Most objects submit the single command returned by make_draw_command().
     * Composite UI elements can override this to submit several ordered layers.
     */
    virtual void submit_draw_commands(Render_Pool& render_pool);

    /**
     * @brief Moves the object to the given position.
     * @param pos2 The new top-left position.
     */
    void position_update(const Vec &pos2) {
        this->transform.pos.x = pos2.x;
        this->transform.pos.y = pos2.y;
    }


    /**
     * @brief Resizes the object to the given size.
     * @param size2 The new width and height.
     */
    void size_update(const Vec &size2) {
        this->transform.size.x = size2.x;
        this->transform.size.y = size2.y;
    }

    /**
     * @brief Rotates the object to the given angle and facing direction.
     * @param rotation2 The new rotation angle and facing direction.
     */
    void rotation_update(const Vec &rotation2) {
        this->transform.rotation.x = rotation2.x;
        this->transform.rotation.y = rotation2.y;
    }

    /**
     * @brief Sets the texture for the object.
     * @param t Pointer to a loaded Texture, or `nullptr` for no texture.
     */
    void set_texture(Texture* t) {
        this->texture = t;
    }

    /**
     * @brief Sets whether the object should ignore hover/click checks.
     * @param transparent If `true`, the object will not respond to hover/click events.
     */
    void set_input_transparent(bool transparent) {
        this->input_transparent = transparent;
    }

    /**
     * @brief Sets the logger for the object.
     * @param l Pointer to a Logger instance, or `nullptr` for no logging.
     */
    void set_logger(Logger* l) {
        this->logger = l;
    }

    /**
     * @brief Scales the object around its center by a given factor when the condition is met, otherwise resets to original size.
     * Useful for hover effects or conditional scaling.
     * @param scale_factor   The target scale multiplier (e.g. `1.1f` = 10% larger).
     * @param original_size  The base size to scale from / reset to.
     * @param condition      If `true`, scale up; if `false`, reset to original.
     * @param animated       If `true`, lerp smoothly towards the target size each frame.
     * @param anim_speed     How fast the animation plays (lerp units/sec). Default `10.0f`.
     *
     * Example:
     * ```cpp
     * // in on_update(float dt):
     * btn->scale_centered_condition(1.1f, btn_size, btn->on_hover(mouse_pos), true, 12.0f);
     * ```
     */
    void scale_centered_condition(float scale_factor, Vec original_size, bool condition, bool animated = false, float anim_speed = 10.0f);

    /**
     * @brief Scales the object around its center by a given factor.
     * @attention Does not reset the size automatically. Use `scale_centered_condition()` for hover effects.
     * @param scale_factor  The multiplier to apply to the current size.
     * @param animated      If `true`, lerp smoothly towards the scaled size.
     * @param anim_speed    Lerp speed in units/sec. Default `10.0f`.
     */
    void scale_centered(float scale_factor, bool animated = false, float anim_speed = 10.0f);

    /**
     * @brief Changes the opacity of the texture.
     * @param alpha New opacity in the range [0.0, 1.0].
     */
    void set_texture_opacity(float alpha);

    /**
     * @brief Centers the object on the screen based on the current window size.
     * Uses `Engine::window` to get the current window dimensions.
     */
    void center_on_screen() {
        Transform world = get_world_transform();
        world.pos.x = (Engine::logical_width  - world.size.x) / 2.0f;
        world.pos.y = (Engine::logical_height - world.size.y) / 2.0f;
        set_world_transform(world);
    }
    /**
     * @brief Hides the object by setting its visibility to false and making it input transparent.
     */
    void hide() { visible = false; input_transparent = true; }
    /**
     * @brief Shows the object by setting its visibility to true and making it respond to input.
     */
    void show() { visible = true; input_transparent = false; }

    /**
     * @brief Toggles the visibility and input transparency of the object.
     * If the object is currently visible, it will be hidden and made input transparent.
     * If the object is currently hidden, it will be shown and made responsive to input.
     */
    void toggle_visibility() { visible = !visible; input_transparent = !input_transparent; }

    /// Releases the texture and resets state.
    void free();

    /**
     * @brief Attaches a script to this object. The script's `owner` pointer will be set to this object.
     * The script will be added to `Engine::object_scripts` and its `on_start()` method will be called immediately, when this function is called.
     * Every instance of `script` is responsible for cleaning up its own resources in `on_destroy()`.
     * Every instance of this `object` is responsible for calling `on_destroy()` on its attached script before the script is deleted.
     * Every instance of `script` is responsible for removing itself from `Engine::object_scripts` when it is destroyed.
     * If you want to use a script in multiple objects, create a new instance for each object.
     * 
     * Example:
     * ```cpp
     * auto* s = new my_script();
     * my_object.attach_script(s);
     * // on_destroy()-ban:
     * // s->on_destroy(); delete s;
     * ```
     */
    void attach_script(script* s);

    /**
     * @brief Detaches and deletes the script from this object, if any.
     *
     * Calls the script's `on_destroy()` method, removes it from
     * `Engine::object_scripts`, then deletes the script instance.
     */
    void detach_script();

    void register_with_pool();

private:
    Object* m_parent = nullptr;
    std::vector<Object*> m_children;
    uint8_t m_free_number = 0; // double freeing protection: 0 = not freed, 1 = freed once, 2 = freed twice
};

/**
 * @brief Base class for fixed, screen-space UI elements.
 *
 * UI objects are not affected by the active camera, render on the UI layer,
 * and can be disabled without changing their visibility.
 */
class UI_Object : public Object {
public:
    static constexpr uint8_t default_z_index = 0;

    bool enabled = true; ///< Disabled UI objects remain visible but ignore pointer input.

    UI_Object();
    UI_Object(Vec p, Vec s, Vec r = {0.0f, 0.0f}, Texture* t = nullptr,
              Object_Pool* objp = nullptr, Logger* l = nullptr);
    UI_Object(float x, float y, float w, float h, Texture* t = nullptr,
              Object_Pool* objp = nullptr, Logger* l = nullptr);
    UI_Object(float x, float y, float w, float h, float rx, float ry = 0.0f,
              Texture* t = nullptr, Object_Pool* objp = nullptr, Logger* l = nullptr);
    UI_Object(Transform transform, Texture* t = nullptr,
              Object_Pool* objp = nullptr, Logger* l = nullptr);
    UI_Object(const UI_Object&) = delete;
    UI_Object& operator=(const UI_Object&) = delete;

    void set_enabled(bool value) { enabled = value; }
    bool is_interactive() const { return visible && enabled && !input_transparent; }

    bool on_hover(const Vec& mouse_pos) const override;
    bool on_click(const Vec& mouse_pos) const override;

    void set_font(IFont* font) { m_font = font; }
    IFont* get_font() const { return m_font; }

private:
    void configure_as_ui();
    IFont* m_font = nullptr; ///< Optional font for text rendering. Set with `set_font()`.
};

// Lower-case alias for scripts which use the name `ui_object`.
using ui_object = UI_Object;

/**
 * @brief A screen-space UI object that responds to mouse hover and click tests.
 *
 * Call `on_click()` only when the input system reports a press event; the
 * method performs hit testing and does not poll SDL input by itself.
 */
struct Button : public UI_Object {
    Button() = default;
    using UI_Object::UI_Object;

    bool on_hover(const Vec& mouse_pos) const override;
    bool on_click(const Vec& mouse_pos) const override;
};

/** @brief Direction used by value-based UI widgets. */
enum class UI_Orientation : uint8_t {
    Horizontal,
    Vertical
};

/**
 * @brief Reusable clamped value/range state for UI controls.
 *
 * A positive `step` snaps values to increments measured from `min_value`.
 * Set `step` to zero for continuous values.
 */
struct UI_Value {
    float min_value = 0.0f;
    float max_value = 1.0f;
    float value = 0.0f;
    float step = 0.0f;

    UI_Value() = default;
    UI_Value(float minimum, float maximum, float initial_value, float value_step = 0.0f);

    void set_range(float minimum, float maximum);
    void set_step(float value_step);
    bool set_value(float new_value);
    float normalized_value() const;
};

/**
 * @brief Interactive screen-space slider state and geometry helper.
 *
 * The inherited texture represents the track. `thumb_transform()` returns the
 * transform at which a separate thumb UI object can be drawn. Horizontal
 * sliders grow left-to-right; vertical sliders grow bottom-to-top.
 */
struct Slider : public UI_Object, public UI_Value {
    UI_Orientation orientation = UI_Orientation::Horizontal;

    Slider();
    Slider(Vec p, Vec s, float minimum = 0.0f, float maximum = 1.0f,
           float initial_value = 0.0f,
           UI_Orientation direction = UI_Orientation::Horizontal,
           Texture* t = nullptr, Object_Pool* objp = nullptr, Logger* l = nullptr,
           float value_step = 0.0f);
    Slider(float x, float y, float w, float h,
           float minimum = 0.0f, float maximum = 1.0f, float initial_value = 0.0f,
           UI_Orientation direction = UI_Orientation::Horizontal,
           Texture* t = nullptr, Object_Pool* objp = nullptr, Logger* l = nullptr,
           float value_step = 0.0f);

    float value_at(const Vec& pointer_pos) const;
    bool update_from_pointer(const Vec& pointer_pos);
    Vec thumb_center() const;
    Transform thumb_transform(Vec thumb_size) const;
};

/** @brief A two-state button with explicit toggle handling. */
struct Toggle : public Button {
    bool checked = false;

    Toggle();
    Toggle(Vec p, Vec s, bool initial_state = false, Texture* t = nullptr,
           Object_Pool* objp = nullptr, Logger* l = nullptr);
    Toggle(float x, float y, float w, float h, bool initial_state = false,
           Texture* t = nullptr, Object_Pool* objp = nullptr, Logger* l = nullptr);

    void set_checked(bool value) { checked = value; }
    bool toggle_at(const Vec& pointer_pos);
};

/**
 * @brief Non-interactive progress value with a screen-space fill transform.
 *
 * The inherited texture can be used as the background. Draw the fill with a
 * second UI object using `fill_transform()`.
 */
struct Progress_Bar : public UI_Object, public UI_Value {
    UI_Orientation orientation = UI_Orientation::Horizontal;

    Progress_Bar();
    Progress_Bar(Vec p, Vec s, float minimum = 0.0f, float maximum = 1.0f,
                 float initial_value = 0.0f,
                 UI_Orientation direction = UI_Orientation::Horizontal,
                 Texture* t = nullptr, Object_Pool* objp = nullptr, Logger* l = nullptr);
    Progress_Bar(float x, float y, float w, float h,
                 float minimum = 0.0f, float maximum = 1.0f,
                 float initial_value = 0.0f,
                 UI_Orientation direction = UI_Orientation::Horizontal,
                 Texture* t = nullptr, Object_Pool* objp = nullptr, Logger* l = nullptr);

    Transform fill_transform() const;
};

class Object_Pool {
public:
    Object_Pool() = default;

    /**
     * @brief Adds an object to the pool.
     * @param obj Pointer to the Object to add.
     */
    void add(Object* obj);

    /**
     * @brief Removes an object from the pool.
     * @param obj Pointer to the Object to remove.
     */
    void remove(Object* obj);

    Object* find_by_name(const std::string& name) const;
    Object* find_by_tag(const std::string& tag) const;
    std::vector<Object*> find_all_by_tag(const std::string& tag) const;

    /**
     * @brief Returns a vector of all objects in the pool.
     */
    std::vector<Object*> get_all() const {
        return objects;
    }

private:
    std::vector<Object*> objects;
};

#endif
