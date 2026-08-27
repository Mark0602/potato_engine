#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * @brief Singleton that manages the active scene.
 *
 * Scenes are identified by an integer ID and an optional name.
 * Register scenes with `register_scene(id, name)`, then switch with
 * `set_scene(id)` or `set_scene(name)`.
 *
 * Scripts whose `scene_id()` matches `current_scene()` are executed each frame.
 * Scripts with `scene_id() == -1` (default) run in every scene.
 *
 * Example:
 * ```cpp
 * Engine::scene_manager->register_scene(0, "main_menu");
 * Engine::scene_manager->register_scene(1, "gameplay");
 * Engine::scene_manager->set_scene("gameplay");
 * ```
 */
class SceneManager {
public:
    struct Load_Task {
        std::string label;
        std::function<bool()> step;
        float weight = 1.0f;
    };

    /// @return The global singleton instance.
    static SceneManager& instance() {
        static SceneManager inst;
        return inst;
    }

    /**
     * @brief Associates an integer ID with a human-readable name.
     * Can be called multiple times to register all scenes up front.
     * @param id   Numeric scene identifier (>= 0).
     * @param name Unique name for the scene.
     */
    void register_scene(int id, const std::string& name) {
        m_id_to_name[id]   = name;
        m_name_to_id[name] = id;
    }

    /**
     * @brief Switches the active scene by numeric ID.
     * @param id The scene to make active.
     */
    void set_scene(int id) {
        m_active_id = id;
        m_requested_id = -1;
        m_transition_id = -1;
    }

    /**
     * @brief Switches the active scene by name.
     * Does nothing if the name was never registered.
     * @param name The registered scene name.
     */
    void set_scene(const std::string& name) {
        auto it = m_name_to_id.find(name);
        if (it != m_name_to_id.end()) {
            set_scene(it->second);
        }
    }

    /**
     * @brief Requests a deferred scene transition.
     *
     * The main loop consumes this request, starts the loading overlay, runs the
     * target scene's not-yet-started scripts, and only then activates the scene.
     * Prefer this over `set_scene()` for user-visible transitions.
     *
     * @return True when a new request was queued.
     */
    bool request_scene(int id) {
        if (id < 0 || id == m_active_id || id == m_requested_id ||
            id == m_transition_id) {
            return false;
        }
        m_requested_id = id;
        return true;
    }

    /** Requests a deferred transition by registered scene name. */
    bool request_scene(const std::string& name) {
        auto it = m_name_to_id.find(name);
        return it != m_name_to_id.end() && request_scene(it->second);
    }

    /**
     * Queues one-shot work for the next transition to `scene_id`.
     * Call this before `request_scene()`. The action runs behind the loading
     * overlay on the main thread and is removed after that transition.
     */
    void enqueue_load_task(int scene_id,
                           const std::string& label,
                           std::function<void()> action,
                           float weight = 1.0f) {
        if (scene_id < 0 || !action) return;
        enqueue_load_step(
            scene_id,
            label,
            [action = std::move(action)]() mutable {
                action();
                return true;
            },
            weight
        );
    }

    /**
     * Queues incremental one-shot work. The step is called once per frame until
     * it returns true, keeping the loading animation responsive.
     */
    void enqueue_load_step(int scene_id,
                           const std::string& label,
                           std::function<bool()> step,
                           float weight = 1.0f) {
        if (scene_id < 0 || !step) return;
        m_load_tasks[scene_id].push_back(
            {label, std::move(step), weight}
        );
    }

    std::vector<Load_Task> take_load_tasks(int scene_id) {
        auto found = m_load_tasks.find(scene_id);
        if (found == m_load_tasks.end()) return {};

        std::vector<Load_Task> tasks = std::move(found->second);
        m_load_tasks.erase(found);
        return tasks;
    }

    bool has_scene_request() const { return m_requested_id >= 0; }
    int requested_scene() const { return m_requested_id; }

    /** Copies out and clears the pending request. Intended for the engine loop. */
    bool consume_scene_request(int& out_id) {
        if (m_requested_id < 0) return false;
        out_id = m_requested_id;
        m_transition_id = m_requested_id;
        m_requested_id = -1;
        return true;
    }

    /** Activates a successfully loaded scene without dropping a newer request. */
    void complete_transition(int id) {
        m_active_id = id;
        if (m_transition_id == id) m_transition_id = -1;
    }

    void cancel_scene_request() { m_requested_id = -1; }

    /// @return The numeric ID of the currently active scene.
    int current_scene() const { return m_active_id; }

    /** Returns the registered name for any scene ID, or an empty string. */
    const std::string& scene_name(int id) const {
        static const std::string empty;
        auto it = m_id_to_name.find(id);
        return it != m_id_to_name.end() ? it->second : empty;
    }

    /**
     * @brief Returns the name of the currently active scene.
     * Returns an empty string if the current ID was not registered with a name.
     */
    const std::string& current_scene_name() const {
        return scene_name(m_active_id);
    }

private:
    SceneManager() = default;

    int m_active_id = 0;
    int m_requested_id = -1;
    int m_transition_id = -1;
    std::unordered_map<int, std::string> m_id_to_name;
    std::unordered_map<std::string, int> m_name_to_id;
    std::unordered_map<int, std::vector<Load_Task>> m_load_tasks;
};

#endif
