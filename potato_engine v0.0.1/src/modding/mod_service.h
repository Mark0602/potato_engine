#ifndef POTATO_MODDING_MOD_SERVICE_H
#define POTATO_MODDING_MOD_SERVICE_H

#include "angel_script_runtime.h"
#include "mod_manifest.h"

#include <filesystem>
#include <functional>
#include <string>

namespace potato::modding {

struct mod_service_config {
    std::filesystem::path mods_path = "mods";
    std::string game_api_version;
    std::size_t script_line_budget = 10000;
};

using script_api_registrar = std::function<bool(
    asIScriptEngine*,
    std::string&
)>;

using mod_export_registrar = std::function<bool(
    const mod_manifest&,
    angel_script_runtime&,
    std::string&
)>;

/**
 * Engine-level owner for mod discovery and one side-specific script runtime.
 *
 * Games provide two narrow callbacks: one registers safe script-visible types
 * and functions, the other maps manifest exports to game-owned registries.
 */
class mod_service final {
public:
    bool discover(
        const mod_service_config& config,
        std::string* error = nullptr
    );

    bool start_scripts(
        mod_side runtime_side,
        script_log_sink log_sink,
        script_api_registrar register_script_api,
        mod_export_registrar register_mod_exports,
        std::string* error = nullptr
    );

    void shutdown_scripts();

    const mod_manager& manager() const { return manager_; }
    angel_script_runtime& script_runtime() { return script_runtime_; }
    const angel_script_runtime& script_runtime() const {
        return script_runtime_;
    }
    const mod_service_config& config() const { return config_; }

    bool discovered() const { return discovered_; }
    bool scripts_started() const { return scripts_started_; }
    bool failed() const { return failed_; }
    mod_side runtime_side() const { return runtime_side_; }

private:
    mod_service_config config_;
    mod_manager manager_;
    angel_script_runtime script_runtime_;
    mod_side runtime_side_ = mod_side::both;
    bool discovered_ = false;
    bool scripts_started_ = false;
    bool failed_ = false;
};

} // namespace potato::modding

#endif // POTATO_MODDING_MOD_SERVICE_H
