#include "mod_service.h"

#include <utility>

namespace potato::modding {

bool mod_service::discover(
    const mod_service_config& config,
    std::string* error
) {
    const mod_service_config normalized{
        config.mods_path.lexically_normal(),
        config.game_api_version,
        config.script_line_budget
    };
    if (normalized.game_api_version.empty()) {
        if (error) *error = "game_api_version must not be empty";
        return false;
    }
    if (normalized.script_line_budget == 0) {
        if (error) *error = "script_line_budget must be greater than zero";
        return false;
    }
    if (discovered_) {
        const bool same_config =
            config_.mods_path == normalized.mods_path &&
            config_.game_api_version == normalized.game_api_version &&
            config_.script_line_budget == normalized.script_line_budget;
        if (same_config) {
            if (error) error->clear();
            return !failed_;
        }
        if (scripts_started_ || script_runtime_.initialized()) {
            if (error) {
                *error = "Mod service configuration cannot change after the "
                    "script runtime has started";
            }
            return false;
        }
    }

    std::string local_error;
    if (!manager_.discover(
            normalized.mods_path,
            normalized.game_api_version,
            &local_error)) {
        failed_ = true;
        if (error) *error = std::move(local_error);
        return false;
    }
    config_ = normalized;
    discovered_ = true;
    failed_ = false;
    if (error) error->clear();
    return true;
}

bool mod_service::start_scripts(
    mod_side runtime_side,
    script_log_sink log_sink,
    script_api_registrar register_script_api,
    mod_export_registrar register_mod_exports,
    std::string* error
) {
    if (!discovered_) {
        if (error) *error = "Mod service must discover mods before scripts start";
        return false;
    }
    if (failed_) {
        if (error) *error = "Mod service is in a failed startup state";
        return false;
    }
    if (runtime_side == mod_side::both) {
        if (error) *error = "Script runtime side must be client or server";
        return false;
    }
    if (scripts_started_) {
        if (runtime_side_ != runtime_side) {
            if (error) {
                *error = "This mod service already owns the other script side";
            }
            return false;
        }
        if (error) error->clear();
        return true;
    }

    std::string local_error;
    if (!script_runtime_.initialize(std::move(log_sink), &local_error)) {
        failed_ = true;
        if (error) *error = std::move(local_error);
        return false;
    }
    script_runtime_.set_line_budget(config_.script_line_budget);
    if (register_script_api &&
        !register_script_api(script_runtime_.engine(), local_error)) {
        failed_ = true;
        if (error) *error = std::move(local_error);
        return false;
    }

    for (const mod_manifest& manifest : manager_.mods()) {
        if (!mod_manager::applies_to(manifest.side, runtime_side)) continue;
        if (!script_runtime_.build_mod(
                manifest,
                manager_.script_paths(manifest, runtime_side),
                runtime_side,
                &local_error)) {
            failed_ = true;
            if (error) *error = std::move(local_error);
            return false;
        }
    }
    if (register_mod_exports) {
        for (const mod_manifest& manifest : manager_.mods()) {
            if (!mod_manager::applies_to(
                    manifest.side, runtime_side)) {
                continue;
            }
            if (!register_mod_exports(
                    manifest, script_runtime_, local_error)) {
                failed_ = true;
                if (error) *error = std::move(local_error);
                return false;
            }
        }
    }

    runtime_side_ = runtime_side;
    scripts_started_ = true;
    if (error) error->clear();
    return true;
}

void mod_service::shutdown_scripts() {
    script_runtime_.shutdown();
    runtime_side_ = mod_side::both;
    scripts_started_ = false;
    failed_ = false;
}

} // namespace potato::modding
