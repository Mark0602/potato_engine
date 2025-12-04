#pragma once

#include <vector>
#include <functional>
#include "potato-script-base.h"

class potato_script_registry {
public:
    using script_factory = std::function<potato_script*()>;

    static potato_script_registry& instance() {
        static potato_script_registry registry;
        return registry;
    }

    void register_script(script_factory factory) {
        factories.push_back(factory);
    }

    std::vector<potato_script*> create_all_scripts() {
        std::vector<potato_script*> scripts;
        for (auto& factory : factories) {
            scripts.push_back(factory());
        }
        return scripts;
    }

private:
    potato_script_registry() = default;
    std::vector<script_factory> factories;
};

// Helper macro for automatic registration
#define REGISTER_SCRIPT(ScriptClass) \
    namespace { \
        struct ScriptClass##_Registrar { \
            ScriptClass##_Registrar() { \
                potato_script_registry::instance().register_script([]() -> potato_script* { \
                    return new ScriptClass(); \
                }); \
            } \
        }; \
        static ScriptClass##_Registrar ScriptClass##_registrar_instance; \
    }
