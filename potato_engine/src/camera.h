#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"

#include <memory>
#include <string>
#include <unordered_map>

class Object;

/**
 * @brief Represents a 2D camera that can be used to view a portion of the game world.
 * The camera can be moved, zoomed, and rotated, and it can follow a target object.
 */
class Camera {
public:
    /**
     * @brief Default constructor for the Camera class.
     */
    Camera() = default;

    /**
     * @brief Sets the viewport dimensions for the camera.
     * @param width The width of the viewport in pixels.
     * @param height The height of the viewport in pixels.
     */
    void set_viewport(float width, float height);

    /**
     * @brief Sets the viewport dimensions for the camera using a Vec.
     * @param size A Vec where x is the width and y is the height of the viewport in pixels.
     */
    void set_viewport(Vec size) { set_viewport(size.x, size.y); }

    /**
     * @brief Sets the position of the camera in world coordinates.
     * @param position A Vec representing the new position of the camera.
     */
    void set_position(Vec position);

    /**
     * @brief Moves the camera by a specified delta in world coordinates.
     * @param delta A Vec representing the change in position for the camera.
     */
    void move(Vec delta);

    /**
     * @brief Resets the camera to its default state: position at (0,0), zoom level of 1, and no rotation.
     * This function is useful for resetting the camera after a scene change or when you want to return to a default view.
     */
    void reset() {
        m_position = {0.0f, 0.0f};
        m_zoom = 1.0f;
        m_rotation = 0.0f;
        m_use_bounds = false;
    }

    /**
     * @brief Gets the viewport size in logical screen pixels.
     * @return A Vec where x is width and y is height.
     */
    Vec get_viewport() const { return {m_viewport_width, m_viewport_height}; }

    /**
     * @brief Gets the current position of the camera in world coordinates.
     * @return A Vec representing the current position of the camera.
     */
    Vec get_position() const;

    /**
     * @brief Sets the zoom level of the camera.
     * @param zoom The new zoom level. Must be greater than 0.
     */
    void set_zoom(float zoom);

    /**
     * @brief Gets the current zoom level of the camera.
     * @return The current zoom level.
     */
    float get_zoom() const;

    /**
     * @brief Sets the rotation of the camera in radians.
     * @param rotation The new rotation angle in radians.
     */
    void set_rotation(float rotation);

    /**
     * @brief Gets the current rotation of the camera in radians.
     * @return The current rotation angle in radians.
     */
    float get_rotation() const;

    /**
     * @brief Converts a position from world coordinates to screen coordinates.
     * @param world_pos A Vec representing the position in world coordinates.
     */
    Vec world_to_screen(Vec world_pos) const;

    /**
     * @brief Converts a position from screen coordinates to world coordinates.
     * @param screen_pos A Vec representing the position in screen coordinates.
     */
    Vec screen_to_world(Vec screen_pos) const;

    /**
     * @brief Converts a size from world coordinates to screen coordinates.
     * @param world_size A Vec representing the size in world coordinates.
     */
    Vec world_size_to_screen(Vec world_size) const;

    /**
     * @brief Shakes the camera for a specified duration and intensity.
     * @param intensity The intensity of the shake effect.
     * @param duration The duration of the shake effect in seconds.
     */
    void shake(float intensity, float duration);

    /**
     * @brief Converts a size from screen coordinates to world coordinates.
     * @param screen_size A Vec representing the size in screen coordinates.
     */
    Vec screen_size_to_world(Vec screen_size) const;

    /**
     * @brief Converts a full world transform into screen-space.
     * The position is offset by the camera and the size is scaled by zoom.
     */
    Transform world_to_screen(const Transform& world_transform) const;

    /**
     * @brief Converts a full screen transform back into world-space.
     * Useful when placing objects from mouse or UI coordinates.
     */
    Transform screen_to_world(const Transform& screen_transform) const;

    /**
     * @brief Returns true when a world-space transform overlaps the camera view.
     * This is used by the render pipeline to skip objects outside the visible area.
     */
    bool can_see(const Transform& world_transform) const;

    /**
     * @brief Makes the camera follow a target object with optional smoothing.
     * @param target Pointer to the Object to follow.
     * @param smoothing The smoothing factor for following the target.
     * @param dt The delta time since the last frame.
     */
    void follow(Object* target, float smoothing, float dt);

    /**
     * @brief Sets the bounds for the camera's position.
     * @param min A Vec representing the minimum bounds (top-left corner).
     * @param max A Vec representing the maximum bounds (bottom-right corner).
     */
    void set_bounds(Vec min, Vec max);

    /**
     * @brief Clears any bounds set for the camera, allowing it to move freely.
     */
    void clear_bounds();

private:
    Vec m_position = {0.0f, 0.0f};

    float m_zoom = 1.0f;
    float m_rotation = 0.0f;

    float m_viewport_width = 1280.0f;
    float m_viewport_height = 720.0f;

    bool m_use_bounds = false;
    Vec m_bounds_min = {0.0f, 0.0f};
    Vec m_bounds_max = {0.0f, 0.0f};

    void apply_bounds();
};

/**
 * @brief Owns all cameras and exposes one active camera for rendering.
 *
 * The pool stores cameras in `std::unique_ptr`, so removing a camera from the
 * pool automatically destroys it. A default camera named `main_cam` always
 * exists and cannot be removed.
 *
 * Example:
 * ```cpp
 * Camera* camera = Engine::camera_pool->get("main_cam");
 * camera->set_position({100.0f, 50.0f});
 *
 * Camera* cutscene = Engine::camera_pool->create("cutscene_cam");
 * Engine::camera_pool->set_active("cutscene_cam");
 * ```
 */
class Camera_Pool {
public:
    static constexpr const char* MAIN_CAMERA_NAME = "main_cam";

    /**
     * @brief Creates the pool and the default `main_cam`.
     */
    Camera_Pool();
    ~Camera_Pool() = default;

    Camera_Pool(const Camera_Pool&) = delete;
    Camera_Pool& operator=(const Camera_Pool&) = delete;

    /**
     * @brief Creates a camera with the given name.
     * @return The camera, or the existing camera if the name is already taken.
     */
    Camera* create(const std::string& name);

    /**
     * @brief Finds a camera by name.
     * @return A borrowed pointer, or nullptr when the camera does not exist.
     */
    Camera* get(const std::string& name);
    const Camera* get(const std::string& name) const;

    /**
     * @brief Returns the always-present default camera.
     */
    Camera* main_camera() { return get(MAIN_CAMERA_NAME); }
    const Camera* main_camera() const { return get(MAIN_CAMERA_NAME); }

    /**
     * @brief Returns the camera currently used by the render pipeline.
     */
    Camera* active_camera() { return m_active_camera; }
    const Camera* active_camera() const { return m_active_camera; }

    /**
     * @brief Makes an existing camera the active render camera.
     * @return `true` when the camera exists and became active.
     */
    bool set_active(const std::string& name);

    /**
     * @brief Removes a camera from the pool.
     * `main_cam` is protected and will never be removed by this function.
     */
    bool remove(const std::string& name);

    /**
     * @brief Deletes every non-main camera and makes `main_cam` active again.
     */
    void clear();

    /**
     * @brief Returns how many cameras are owned by the pool.
     */
    size_t size() const { return m_cameras.size(); }

private:
    std::unordered_map<std::string, std::unique_ptr<Camera>> m_cameras;
    Camera* m_active_camera = nullptr;
};

#endif
