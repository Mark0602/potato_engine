#ifndef SCRIPT_REGISTRY_H
#define SCRIPT_REGISTRY_H

#include <vector>
#include <functional>
#include <algorithm>
#include "script-base.h"

/**
 * @brief Singleton registry that collects and instantiates all registered scripts.
 *
 * Scripts self-register at static initialisation time via `REGISTER_SCRIPT()`.
 * Call `create_all_scripts()` once in `main()` to get the sorted list.
 *
 * You should never need to call `register_script()` manually.
 */
class script_registry {
public:
    using script_factory = std::function<script*()>;

    /// @return The global singleton instance.
    static script_registry& instance() {
        static script_registry registry;
        return registry;
    }

    /**
     * @brief Registers a factory function that creates one script instance.
     * Called automatically by `REGISTER_SCRIPT` at startup.
     * @param factory A callable that returns a heap-allocated `script*`.
     */
    void register_script(script_factory factory) {
        factories.push_back(factory);
    }

    /**
     * @brief Creates all registered scripts and sorts them by `execution_order()`.
     * Lower `execution_order()` values appear first.
     * The caller takes ownership of the returned pointers.
     * @return Sorted vector of heap-allocated script instances.
     */
    std::vector<script*> create_all_scripts() {
        std::vector<script*> scripts;
        scripts.reserve(factories.size());
        for (auto& factory : factories) {
            scripts.push_back(factory());
        }
        std::stable_sort(scripts.begin(), scripts.end(), [](script* a, script* b) {
            return a->execution_order() < b->execution_order();
        });
        return scripts;
    }

private:
    script_registry() = default;
    std::vector<script_factory> factories;
};

/**
 * @brief Registers a script class so the engine instantiates it automatically.
 *
 * Place this macro at the bottom of a script's `.cpp` file.
 * The script will be created and started without any changes to `main()`.
 *
 * Example:
 * ```cpp
 * REGISTER_SCRIPT(my_script)
 * ```
 */
#define REGISTER_SCRIPT(ScriptClass) \
    namespace { \
        struct ScriptClass##_Registrar { \
            ScriptClass##_Registrar() { \
                script_registry::instance().register_script([]() -> script* { \
                    return new ScriptClass(); \
                }); \
            } \
        }; \
        static ScriptClass##_Registrar ScriptClass##_registrar_instance; \
    }
/**
 * @brief Sets the execution order of a script class.
 * Lower values run earlier. Default is 0.
 * Place this macro inside the class definition.
 */
#define SCRIPT_ORDER(n) \
    int execution_order() const override { return (n); }

/**
 * @brief Binds a script to a specific scene ID.
 * The script's on_update, on_render and on_event are only called while that
 * scene is active. Use -1 (the default) to run (global script) in every scene.
 * Place this macro inside the class definition.
 *
 * Example:
 * ```cpp
 * class my_script : public script {
 *     SCRIPT_SCENE(1)  // only active in scene 1
 * ...
 * ```
 */
#define SCRIPT_SCENE(id) \
    int scene_id() const override { return (id); }

#endif