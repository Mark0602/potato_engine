#include "modding/mod_service.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace {

bool require(bool condition, const std::string& message) {
    if (condition) return true;
    std::cerr << "FAIL: " << message << '\n';
    return false;
}

} // namespace

int main() {
    using namespace potato::modding;

    bool success = true;
    std::string error;
    mod_service service;
    mod_service_config config;
    config.mods_path = "tests/data/core_mods";
    config.game_api_version = "core_test_1";
    config.script_line_budget = 512;
    std::vector<std::string> log_messages;
    std::vector<std::string> export_order;
    int api_registration_count = 0;

    success &= require(
        service.discover(config, &error),
        "core service discovers manifests: " + error
    );
    success &= require(
        service.manager().mods().size() == 2 &&
        service.manager().mods()[0].id == "base_mod" &&
        service.manager().mods()[1].id == "dependent_mod",
        "core service applies deterministic dependency ordering"
    );
    success &= require(
        !service.start_scripts(
            mod_side::both, {}, {}, {}, &error
        ),
        "core service rejects an ambiguous runtime side"
    );
    success &= require(
        service.start_scripts(
            mod_side::server,
            [&log_messages](
                script_log_level,
                const std::string&,
                const std::string& message
            ) {
                log_messages.push_back(message);
            },
            [&api_registration_count](
                asIScriptEngine* engine,
                std::string&
            ) {
                ++api_registration_count;
                return engine != nullptr;
            },
            [&export_order](
                const mod_manifest& manifest,
                angel_script_runtime&,
                std::string&
            ) {
                export_order.push_back(manifest.id);
                return true;
            },
            &error
        ),
        "core service starts without a game-specific adapter: " + error
    );
    success &= require(
        service.scripts_started() &&
        service.runtime_side() == mod_side::server &&
        service.script_runtime().line_budget() == 512,
        "core service owns side and execution-budget lifecycle"
    );
    success &= require(
        api_registration_count == 1,
        "core service registers the game API exactly once"
    );
    success &= require(
        export_order == std::vector<std::string>{
            "base_mod", "dependent_mod"
        },
        "core service registers exports in dependency order"
    );
    success &= require(
        std::find(
            log_messages.begin(), log_messages.end(), "base_loaded"
        ) != log_messages.end(),
        "core service compiles scripts and invokes on_mod_loaded"
    );

    asIScriptFunction* probe = service.script_runtime().find_function(
        "base_mod", mod_side::server, "void core_probe()"
    );
    success &= require(
        probe != nullptr &&
        service.script_runtime().execute(probe, {}, &error),
        "core service exposes compiled functions to the game adapter: " + error
    );
    success &= require(
        std::find(
            log_messages.begin(), log_messages.end(), "core_probe"
        ) != log_messages.end(),
        "core service executes a compiled AngelScript function"
    );
    service.shutdown_scripts();
    success &= require(
        !service.scripts_started(),
        "core service shuts down its script runtime"
    );

    if (!success) return 1;
    std::cout << "Potato modding core tests passed\n";
    return 0;
}
