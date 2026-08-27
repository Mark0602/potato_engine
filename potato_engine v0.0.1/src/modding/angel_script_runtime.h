#ifndef POTATO_MODDING_ANGEL_SCRIPT_RUNTIME_H
#define POTATO_MODDING_ANGEL_SCRIPT_RUNTIME_H

#include "mod_manifest.h"

#include <angelscript.h>

#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace potato::modding {

enum class script_log_level {
    debug,
    info,
    warning,
    error
};

using script_log_sink = std::function<void(
    script_log_level,
    const std::string&,
    const std::string&
)>;

/**
 * Sandboxed AngelScript VM owned by the Potato Engine mod layer.
 *
 * The VM exposes only explicitly registered application functions/types. It
 * does not register filesystem, process, network or native pointer APIs.
 */
class angel_script_runtime final {
public:
    angel_script_runtime() = default;
    ~angel_script_runtime();

    angel_script_runtime(const angel_script_runtime&) = delete;
    angel_script_runtime& operator=(const angel_script_runtime&) = delete;

    bool initialize(script_log_sink log_sink, std::string* error = nullptr);
    void shutdown();

    bool build_mod(
        const mod_manifest& manifest,
        const std::vector<std::filesystem::path>& script_paths,
        mod_side runtime_side,
        std::string* error = nullptr
    );

    asIScriptFunction* find_function(
        const std::string& mod_id,
        mod_side runtime_side,
        const std::string& declaration
    ) const;

    bool execute(
        asIScriptFunction* function,
        const std::vector<void*>& object_arguments = {},
        std::string* error = nullptr
    );

    asIScriptEngine* engine() const { return engine_; }
    bool initialized() const { return engine_ != nullptr; }
    void set_line_budget(std::size_t value) { line_budget_ = value; }
    std::size_t line_budget() const { return line_budget_; }
    void write_log(
        script_log_level level,
        const std::string& category,
        const std::string& message
    ) const;

private:
    struct module_record {
        std::string mod_id;
        mod_side side = mod_side::both;
        std::string module_name;
        std::filesystem::path root_path;
    };

    static std::string module_key(
        const std::string& mod_id,
        mod_side side
    );
    asIScriptEngine* engine_ = nullptr;
    script_log_sink log_sink_;
    std::unordered_map<std::string, module_record> modules_;
    std::size_t line_budget_ = 10000;
};

} // namespace potato::modding

#endif // POTATO_MODDING_ANGEL_SCRIPT_RUNTIME_H
