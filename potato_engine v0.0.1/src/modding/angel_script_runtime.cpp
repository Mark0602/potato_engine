#include "angel_script_runtime.h"

#include <scriptbuilder/scriptbuilder.h>
#include <scriptstdstring/scriptstdstring.h>

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <sstream>
#include <utility>

namespace potato::modding {
namespace {

struct include_state {
    std::filesystem::path root_path;
    std::string error;
};

struct execution_budget {
    std::size_t remaining = 0;
    bool exhausted = false;
};

std::string lowercase_path(std::filesystem::path path) {
    std::string value = path.lexically_normal().generic_string();
#if defined(_WIN32)
    std::transform(
        value.begin(), value.end(), value.begin(),
        [](unsigned char character) {
            return static_cast<char>(std::tolower(character));
        }
    );
#endif
    return value;
}

bool path_is_inside(
    const std::filesystem::path& root,
    const std::filesystem::path& candidate
) {
    std::error_code error;
    const auto canonical_root = std::filesystem::weakly_canonical(root, error);
    if (error) return false;
    const auto canonical_candidate = std::filesystem::weakly_canonical(
        candidate, error
    );
    if (error) return false;
    std::string root_text = lowercase_path(canonical_root);
    const std::string candidate_text = lowercase_path(canonical_candidate);
    if (!root_text.empty() && root_text.back() != '/') root_text.push_back('/');
    return candidate_text.size() > root_text.size() &&
        candidate_text.compare(0, root_text.size(), root_text) == 0;
}

int include_callback(
    const char* include,
    const char* from,
    CScriptBuilder* builder,
    void* user_data
) {
    auto* state = static_cast<include_state*>(user_data);
    if (!state || !include || !from || !builder) return -1;
    const std::filesystem::path requested(include);
    if (requested.is_absolute() || requested.has_root_path()) {
        state->error = "Absolute AngelScript include paths are not allowed";
        return -1;
    }
    if (requested.extension() != ".as") {
        state->error = "AngelScript includes must use the .as extension";
        return -1;
    }
    for (const auto& part : requested) {
        if (part == "..") {
            state->error = "AngelScript includes cannot leave the mod directory";
            return -1;
        }
    }
    const std::filesystem::path resolved =
        (std::filesystem::path(from).parent_path() / requested)
            .lexically_normal();
    if (!path_is_inside(state->root_path, resolved)) {
        state->error = "AngelScript include is outside the mod directory: " +
            requested.generic_string();
        return -1;
    }
    std::error_code filesystem_error;
    if (!std::filesystem::is_regular_file(resolved, filesystem_error)) {
        state->error = "AngelScript include does not exist: " +
            resolved.generic_string();
        return -1;
    }
    return builder->AddSectionFromFile(resolved.string().c_str());
}

int pragma_callback(
    const std::string& pragma,
    CScriptBuilder&,
    void* user_data
) {
    auto* state = static_cast<include_state*>(user_data);
    if (state) state->error = "AngelScript pragmas are not allowed: " + pragma;
    return -1;
}

void line_callback(asIScriptContext* context, void* user_data) {
    auto* budget = static_cast<execution_budget*>(user_data);
    if (!context || !budget) return;
    if (budget->remaining == 0) {
        budget->exhausted = true;
        context->Abort();
        return;
    }
    --budget->remaining;
}

std::string function_module(asIScriptFunction* function) {
    if (!function) return "angel_script";
    const char* module_name = function->GetModuleName();
    return module_name && *module_name ? module_name : "angel_script";
}

void log_debug(const std::string& message, angel_script_runtime* runtime);
void log_info(const std::string& message, angel_script_runtime* runtime);
void log_warning(const std::string& message, angel_script_runtime* runtime);
void log_error(const std::string& message, angel_script_runtime* runtime);

} // namespace

namespace {

void emit_script_log(
    angel_script_runtime* runtime,
    script_log_level level,
    const std::string& message
) {
    if (!runtime) return;
    asIScriptContext* context = asGetActiveContext();
    const std::string category = context
        ? function_module(context->GetFunction()) : "angel_script";
    runtime->write_log(level, category, message);
}

void log_debug(const std::string& message, angel_script_runtime* runtime) {
    emit_script_log(runtime, script_log_level::debug, message);
}

void log_info(const std::string& message, angel_script_runtime* runtime) {
    emit_script_log(runtime, script_log_level::info, message);
}

void log_warning(const std::string& message, angel_script_runtime* runtime) {
    emit_script_log(runtime, script_log_level::warning, message);
}

void log_error(const std::string& message, angel_script_runtime* runtime) {
    emit_script_log(runtime, script_log_level::error, message);
}

void message_callback(
    const asSMessageInfo* message,
    angel_script_runtime* runtime
) {
    if (!message || !runtime) return;
    script_log_level level = script_log_level::info;
    if (message->type == asMSGTYPE_WARNING) {
        level = script_log_level::warning;
    } else if (message->type == asMSGTYPE_ERROR) {
        level = script_log_level::error;
    }
    std::ostringstream text;
    text << (message->section ? message->section : "angel_script")
         << ':' << message->row << ':' << message->col << ' '
         << (message->message ? message->message : "");
    emit_script_log(runtime, level, "compiler: " + text.str());
}

bool register_result(
    int result,
    const char* operation,
    std::string* error
) {
    if (result >= 0) return true;
    if (error) {
        *error = std::string("AngelScript API registration failed at ") +
            operation + " (code " + std::to_string(result) + ')';
    }
    return false;
}

const char* side_name(mod_side side) {
    switch (side) {
    case mod_side::client: return "client";
    case mod_side::server: return "server";
    case mod_side::both: return "both";
    }
    return "both";
}

} // namespace

angel_script_runtime::~angel_script_runtime() {
    shutdown();
}

bool angel_script_runtime::initialize(
    script_log_sink log_sink,
    std::string* error
) {
    if (engine_) {
        log_sink_ = std::move(log_sink);
        if (error) error->clear();
        return true;
    }
    log_sink_ = std::move(log_sink);
    engine_ = asCreateScriptEngine();
    if (!engine_) {
        if (error) *error = "Could not create AngelScript engine";
        return false;
    }

    engine_->SetEngineProperty(asEP_ALLOW_UNSAFE_REFERENCES, 0);
    engine_->SetEngineProperty(asEP_DISALLOW_GLOBAL_VARS, 1);
    engine_->SetEngineProperty(asEP_DISALLOW_EMPTY_LIST_ELEMENTS, 1);
    engine_->SetEngineProperty(asEP_REQUIRE_ENUM_SCOPE, 1);
    engine_->SetEngineProperty(asEP_MAX_NESTED_CALLS, 16);
    engine_->SetEngineProperty(asEP_MAX_STACK_SIZE, 1024 * 1024);
    engine_->SetEngineProperty(asEP_MAX_CALL_STACK_SIZE, 256);

    if (!register_result(
            engine_->SetMessageCallback(
                asFUNCTION(message_callback), this, asCALL_CDECL_OBJLAST
            ),
            "message_callback", error)) {
        shutdown();
        return false;
    }

    RegisterStdString(engine_);
    if (!register_result(
            engine_->RegisterGlobalFunction(
                "void log_debug(const string &in message)",
                asFUNCTION(log_debug), asCALL_CDECL_OBJLAST, this
            ), "log_debug", error) ||
        !register_result(
            engine_->RegisterGlobalFunction(
                "void log_info(const string &in message)",
                asFUNCTION(log_info), asCALL_CDECL_OBJLAST, this
            ), "log_info", error) ||
        !register_result(
            engine_->RegisterGlobalFunction(
                "void log_warning(const string &in message)",
                asFUNCTION(log_warning), asCALL_CDECL_OBJLAST, this
            ), "log_warning", error) ||
        !register_result(
            engine_->RegisterGlobalFunction(
                "void log_error(const string &in message)",
                asFUNCTION(log_error), asCALL_CDECL_OBJLAST, this
            ), "log_error", error)) {
        shutdown();
        return false;
    }

    write_log(
        script_log_level::info,
        "angel_script",
        std::string("AngelScript ") + ANGELSCRIPT_VERSION_STRING +
            " runtime initialized"
    );
    if (error) error->clear();
    return true;
}

void angel_script_runtime::shutdown() {
    if (!engine_) return;
    for (const auto& entry : modules_) {
        asIScriptModule* module = engine_->GetModule(
            entry.second.module_name.c_str(), asGM_ONLY_IF_EXISTS
        );
        if (!module) continue;
        asIScriptFunction* unload = module->GetFunctionByDecl(
            "void on_mod_unloaded()"
        );
        if (unload) execute(unload);
    }
    modules_.clear();
    engine_->ShutDownAndRelease();
    engine_ = nullptr;
    log_sink_ = {};
}

bool angel_script_runtime::build_mod(
    const mod_manifest& manifest,
    const std::vector<std::filesystem::path>& script_paths,
    mod_side runtime_side,
    std::string* error
) {
    if (!engine_) {
        if (error) *error = "AngelScript runtime is not initialized";
        return false;
    }
    if (script_paths.empty()) {
        if (error) error->clear();
        return true;
    }

    const std::string key = module_key(manifest.id, runtime_side);
    const std::string module_name = manifest.id + "_" +
        side_name(runtime_side) + "_mod";
    if (modules_.find(key) != modules_.end()) {
        if (error) *error = "AngelScript module is already loaded: " + key;
        return false;
    }

    CScriptBuilder builder;
    if (builder.StartNewModule(engine_, module_name.c_str()) < 0) {
        if (error) *error = "Could not create AngelScript module: " +
            module_name;
        return false;
    }
    include_state state{manifest.root_path, {}};
    builder.SetIncludeCallback(include_callback, &state);
    builder.SetPragmaCallback(pragma_callback, &state);
    builder.DefineWord(runtime_side == mod_side::server
        ? "potato_server" : "potato_client");

    for (const auto& path : script_paths) {
        if (path.extension() != ".as") {
            if (error) *error = "AngelScript entry files must use the .as "
                "extension: " + path.generic_string();
            engine_->DiscardModule(module_name.c_str());
            return false;
        }
        if (!path_is_inside(manifest.root_path, path)) {
            if (error) *error = "Script path is outside mod directory: " +
                path.generic_string();
            engine_->DiscardModule(module_name.c_str());
            return false;
        }
        if (builder.AddSectionFromFile(path.string().c_str()) < 0) {
            if (error) *error = state.error.empty()
                ? "Could not read AngelScript file: " + path.generic_string()
                : state.error;
            engine_->DiscardModule(module_name.c_str());
            return false;
        }
    }
    if (builder.BuildModule() < 0) {
        if (error) *error = state.error.empty()
            ? "Could not compile AngelScript module: " + module_name
            : state.error;
        engine_->DiscardModule(module_name.c_str());
        return false;
    }

    modules_.emplace(key, module_record{
        manifest.id, runtime_side, module_name, manifest.root_path
    });
    asIScriptFunction* loaded = builder.GetModule()->GetFunctionByDecl(
        "void on_mod_loaded()"
    );
    if (loaded && !execute(loaded, {}, error)) {
        engine_->DiscardModule(module_name.c_str());
        modules_.erase(key);
        return false;
    }
    write_log(
        script_log_level::info,
        module_name,
        "Loaded mod '" + manifest.id + "' for " + side_name(runtime_side)
    );
    if (error) error->clear();
    return true;
}

asIScriptFunction* angel_script_runtime::find_function(
    const std::string& mod_id,
    mod_side runtime_side,
    const std::string& declaration
) const {
    if (!engine_) return nullptr;
    const auto found = modules_.find(module_key(mod_id, runtime_side));
    if (found == modules_.end()) return nullptr;
    asIScriptModule* module = engine_->GetModule(
        found->second.module_name.c_str(), asGM_ONLY_IF_EXISTS
    );
    return module ? module->GetFunctionByDecl(declaration.c_str()) : nullptr;
}

bool angel_script_runtime::execute(
    asIScriptFunction* function,
    const std::vector<void*>& object_arguments,
    std::string* error
) {
    if (!engine_ || !function) {
        if (error) *error = "AngelScript function is not available";
        return false;
    }
    asIScriptContext* context = engine_->CreateContext();
    if (!context) {
        if (error) *error = "Could not create AngelScript execution context";
        return false;
    }
    if (context->Prepare(function) < 0) {
        context->Release();
        if (error) *error = "Could not prepare AngelScript function: " +
            std::string(function->GetDeclaration());
        return false;
    }
    for (std::size_t index = 0; index < object_arguments.size(); ++index) {
        if (context->SetArgObject(
                static_cast<asUINT>(index), object_arguments[index]) < 0) {
            context->Release();
            if (error) *error = "Could not set AngelScript object argument";
            return false;
        }
    }

    execution_budget budget{line_budget_, false};
    context->SetLineCallback(
        asFUNCTION(line_callback), &budget, asCALL_CDECL
    );
    const int result = context->Execute();
    if (result != asEXECUTION_FINISHED) {
        std::ostringstream message;
        if (budget.exhausted || result == asEXECUTION_ABORTED) {
            message << "AngelScript execution budget exhausted";
        } else if (result == asEXECUTION_EXCEPTION) {
            int column = 0;
            const char* section = nullptr;
            const int line = context->GetExceptionLineNumber(&column, &section);
            message << (context->GetExceptionString()
                ? context->GetExceptionString() : "AngelScript exception")
                << " at " << (section ? section : "script")
                << ':' << line << ':' << column;
        } else {
            message << "AngelScript execution failed with code " << result;
        }
        const std::string text = message.str();
        write_log(script_log_level::error, function_module(function), text);
        if (error) *error = text;
        context->Release();
        return false;
    }
    context->Release();
    if (error) error->clear();
    return true;
}

std::string angel_script_runtime::module_key(
    const std::string& mod_id,
    mod_side side
) {
    return mod_id + ":" + side_name(side);
}

void angel_script_runtime::write_log(
    script_log_level level,
    const std::string& category,
    const std::string& message
) const {
    if (log_sink_) log_sink_(level, category, message);
}

} // namespace potato::modding
