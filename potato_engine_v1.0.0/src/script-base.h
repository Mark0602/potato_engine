#pragma once

#include <SDL3/SDL_events.h>

struct Object;  // Forward declaration; the complete definition is in object.h.

/**
 * @brief Base class for all game scripts — similar to Unity's MonoBehaviour.
 *
 * Derive from this class and override the lifecycle methods you need.
 * Register the class with `REGISTER_SCRIPT(MyScript)` at the bottom of the
 * `.cpp` file so the engine picks it up automatically.
 *
 * Execution order is controlled by `SCRIPT_ORDER(n)` or by overriding
 * `execution_order()`. Lower values run first (default 0).
 *
 * Example:
 * ```cpp
 * class my_script : public script {
 *     SCRIPT_ORDER(-10)  // runs before default scripts
 * public:
 *     void on_start() override {
 *         // load textures, init state
 *     }
 *     void on_update(float dt) override {
 *         // move objects, run logic
 *     }
 *     void on_render() override {
 *         // custom draw calls
 *     }
 * };
 * REGISTER_SCRIPT(my_script)
 * ```
 */
class script {
public:
    virtual ~script() = default;

    /**
     * @brief Controls the order this script is updated and rendered.
     * Lower value = called earlier. Default is 0.
     * Override via the `SCRIPT_ORDER(n)` macro inside the class.
     */
    virtual int execution_order() const { return 0; }

    /**
     * @brief The scene this script belongs to.
     * The script's on_update, on_render and on_event are only called when the
     * active scene matches this value.
     * Return -1 (default) to run in every scene regardless of the active scene.
     * Override via the `SCRIPT_SCENE(id)` macro inside the class.
     */
    virtual int scene_id() const { return -1; }

    /**
     * @brief Called once when the script is first created, before the first frame.
     * Use this to load textures, initialise state, etc.
     */
    virtual void on_start() {}

    /**
     * @brief Called every frame before rendering.
     * @param delta_time Time in seconds since the last frame.
     */
    virtual void on_update(float delta_time) {}

    /**
     * @brief Called every frame during the render phase.
     * Runs after `on_update`. Use for custom draw calls or debug overlays.
     */
    virtual void on_render() {}

    /**
     * @brief Called after the world render queue and lighting pass have finished.
     *
     * Full-screen overlays and menus should render here so they always appear
     * above world objects, including objects submitted automatically by the
     * engine after regular script rendering.
     */
    virtual void on_post_render() {}

    /**
     * @brief Called for every SDL event before `on_update`.
     * @param event The SDL_Event that occurred (keyboard, mouse, window, etc.).
     */
    virtual void on_event(const SDL_Event& event) {}

    /**
     * @brief Called once when the script is about to be destroyed.
     * Release any resources allocated in `on_start`.
     */
    virtual void on_destroy() {}

    /**
     * @brief The Object this script is attached to, if any.
     * Set by `Object::attach_script()`. `nullptr` if the script is not attached to an object.
     * Use this to access the object's position, size, texture, etc.
     */
    Object* owner = nullptr;
};
