#include "mod_manifest.h"

#include "simdjson.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

namespace potato::modding {
namespace {

constexpr std::uint32_t supported_schema_version = 1;

std::string json_string(
    const simdjson::dom::object& object,
    const char* key,
    const std::string& fallback = {}
) {
    auto value = object[key].get_string();
    return value.error() ? fallback : std::string(value.value());
}

bool json_bool(
    const simdjson::dom::object& object,
    const char* key,
    bool fallback
) {
    auto value = object[key].get_bool();
    return value.error() ? fallback : value.value();
}

std::uint64_t json_uint(
    const simdjson::dom::object& object,
    const char* key,
    std::uint64_t fallback
) {
    auto value = object[key].get_uint64();
    return value.error() ? fallback : value.value();
}

std::vector<std::string> string_array(
    const simdjson::dom::object& object,
    const char* key
) {
    std::vector<std::string> result;
    auto values = object[key].get_array();
    if (values.error()) return result;
    for (simdjson::dom::element value : values.value()) {
        auto text = value.get_string();
        if (!text.error()) result.emplace_back(text.value());
    }
    return result;
}

bool parse_side(const std::string& value, mod_side& result) {
    if (value == "both") {
        result = mod_side::both;
        return true;
    }
    if (value == "client") {
        result = mod_side::client;
        return true;
    }
    if (value == "server") {
        result = mod_side::server;
        return true;
    }
    return false;
}

bool safe_relative_path(
    const std::filesystem::path& mod_root,
    const std::string& value,
    std::filesystem::path& destination,
    std::string& error
) {
    const std::filesystem::path relative(value);
    if (value.empty() || relative.is_absolute() || relative.has_root_path()) {
        error = "Mod path must be relative: " + value;
        return false;
    }
    for (const auto& part : relative) {
        if (part == "..") {
            error = "Mod path cannot leave its own directory: " + value;
            return false;
        }
    }
    std::error_code filesystem_error;
    const auto canonical_root = std::filesystem::weakly_canonical(
        mod_root, filesystem_error
    );
    if (filesystem_error) {
        error = "Could not resolve mod directory: " +
            mod_root.generic_string();
        return false;
    }
    const auto candidate = std::filesystem::weakly_canonical(
        mod_root / relative, filesystem_error
    );
    if (filesystem_error) {
        error = "Could not resolve mod path: " + value;
        return false;
    }
    const auto inside_path = candidate.lexically_relative(canonical_root);
    if (inside_path.empty() || inside_path.is_absolute()) {
        error = "Mod path cannot leave its own directory: " + value;
        return false;
    }
    for (const auto& part : inside_path) {
        if (part == "..") {
            error = "Mod path cannot leave its own directory: " + value;
            return false;
        }
    }
    destination = candidate;
    if (!std::filesystem::is_regular_file(destination, filesystem_error)) {
        error = "Referenced mod file does not exist: " +
            destination.generic_string();
        return false;
    }
    return true;
}

bool parse_path_array(
    const simdjson::dom::object& object,
    const char* key,
    const std::filesystem::path& mod_root,
    std::vector<std::filesystem::path>& destination,
    std::string& error
) {
    auto values = object[key].get_array();
    if (values.error()) return true;
    for (simdjson::dom::element value : values.value()) {
        auto text = value.get_string();
        if (text.error()) {
            error = std::string("Expected a path string in '") + key + "'";
            return false;
        }
        std::filesystem::path path;
        if (!safe_relative_path(
                mod_root, std::string(text.value()), path, error)) {
            return false;
        }
        destination.push_back(std::move(path));
    }
    return true;
}

bool validate_name_list(
    const std::vector<std::string>& names,
    const std::string& field,
    const std::string& mod_id,
    std::string& error
) {
    std::unordered_set<std::string> seen;
    for (const std::string& name : names) {
        if (!mod_manager::is_snake_case(name)) {
            error = "Field '" + field + "' must contain lowercase snake_case "
                "IDs in mod '" + mod_id + "': " + name;
            return false;
        }
        if (!seen.emplace(name).second) {
            error = "Duplicate '" + field + "' entry in mod '" + mod_id +
                "': " + name;
            return false;
        }
    }
    return true;
}

bool load_manifest(
    const std::filesystem::path& path,
    const std::string& expected_game_api_version,
    mod_manifest& result,
    std::string& error
) {
    try {
#if defined(_WIN32) && defined(__GNUC__)
        const simdjson::implementation* portable =
            simdjson::get_available_implementations()["fallback"];
        if (portable) simdjson::get_active_implementation() = portable;
#endif
        simdjson::dom::parser parser;
        simdjson::dom::element root = parser.load(path.string());
        if (!root.is_object()) {
            error = "Mod manifest root must be a JSON object: " +
                path.generic_string();
            return false;
        }
        const simdjson::dom::object object = root.get_object().value();
        result.schema_version = static_cast<std::uint32_t>(
            json_uint(object, "schema_version", 1)
        );
        result.id = json_string(object, "id");
        result.display_name = json_string(object, "display_name", result.id);
        result.version = json_string(object, "version");
        result.game_api_version = json_string(object, "game_api_version");
        result.enabled = json_bool(object, "enabled", true);
        std::error_code filesystem_error;
        result.root_path = std::filesystem::weakly_canonical(
            path.parent_path(), filesystem_error
        );
        result.manifest_path = std::filesystem::weakly_canonical(
            path, filesystem_error
        );
        if (filesystem_error) {
            error = "Could not resolve mod manifest path: " +
                path.generic_string();
            return false;
        }

        if (result.schema_version != supported_schema_version) {
            error = "Unsupported mod schema_version in " +
                path.generic_string() + ": " +
                std::to_string(result.schema_version);
            return false;
        }
        if (!mod_manager::is_snake_case(result.id)) {
            error = "Mod id must be lowercase snake_case: " + result.id;
            return false;
        }
        if (result.version.empty()) {
            error = "Mod version must not be empty: " + result.id;
            return false;
        }
        if (result.game_api_version != expected_game_api_version) {
            error = "Mod '" + result.id + "' targets game_api_version '" +
                result.game_api_version + "', expected '" +
                expected_game_api_version + "'";
            return false;
        }
        if (!parse_side(json_string(object, "side", "both"), result.side)) {
            error = "Mod side must be 'both', 'client' or 'server': " +
                result.id;
            return false;
        }

        result.dependencies = string_array(object, "dependencies");
        result.load_after = string_array(object, "load_after");
        if (!validate_name_list(
                result.dependencies, "dependencies", result.id, error) ||
            !validate_name_list(
                result.load_after, "load_after", result.id, error)) {
            return false;
        }

        if (!result.enabled) return true;

        auto script_object = object["angel_script"].get_object();
        if (!script_object.error()) {
            const auto scripts = script_object.value();
            if (!parse_path_array(
                    scripts, "shared", result.root_path,
                    result.shared_scripts, error) ||
                !parse_path_array(
                    scripts, "client", result.root_path,
                    result.client_scripts, error) ||
                !parse_path_array(
                    scripts, "server", result.root_path,
                    result.server_scripts, error)) {
                return false;
            }
        }

        auto content_object = object["content"].get_object();
        if (!content_object.error()) {
            for (auto field : content_object.value()) {
                const std::string group(field.key);
                if (!mod_manager::is_snake_case(group)) {
                    error = "Content group must be lowercase snake_case in mod '" +
                        result.id + "': " + group;
                    return false;
                }
                auto values = field.value.get_array();
                if (values.error()) {
                    error = "Content group must be an array in mod '" +
                        result.id + "': " + group;
                    return false;
                }
                auto& paths = result.content[group];
                for (simdjson::dom::element value : values.value()) {
                    auto text = value.get_string();
                    if (text.error()) {
                        error = "Content path must be a string in mod '" +
                            result.id + "': " + group;
                        return false;
                    }
                    std::filesystem::path resolved;
                    if (!safe_relative_path(
                            result.root_path, std::string(text.value()),
                            resolved, error)) {
                        return false;
                    }
                    paths.push_back(std::move(resolved));
                }
            }
        }

        auto exports_object = object["exports"].get_object();
        if (!exports_object.error()) {
            for (auto field : exports_object.value()) {
                const std::string group(field.key);
                if (!mod_manager::is_snake_case(group)) {
                    error = "Export group must be lowercase snake_case in mod '" +
                        result.id + "': " + group;
                    return false;
                }
                auto values = field.value.get_array();
                if (values.error()) {
                    error = "Export group must be an array in mod '" +
                        result.id + "': " + group;
                    return false;
                }
                std::unordered_set<std::string> ids;
                for (simdjson::dom::element value : values.value()) {
                    mod_export export_value;
                    if (value.is_string()) {
                        export_value.id = std::string(value.get_string().value());
                        export_value.script_prefix = export_value.id;
                    } else if (value.is_object()) {
                        const auto export_object = value.get_object().value();
                        export_value.id = json_string(export_object, "id");
                        export_value.script_prefix = json_string(
                            export_object, "script_prefix", export_value.id
                        );
                    } else {
                        error = "Export entry must be a string or object in mod '" +
                            result.id + "': " + group;
                        return false;
                    }
                    if (!mod_manager::is_snake_case(export_value.id) ||
                        !mod_manager::is_snake_case(
                            export_value.script_prefix)) {
                        error = "Export id and script_prefix must be lowercase "
                            "snake_case in mod '" + result.id + "'";
                        return false;
                    }
                    if (!ids.emplace(export_value.id).second) {
                        error = "Duplicate export id in mod '" + result.id +
                            "': " + export_value.id;
                        return false;
                    }
                    result.exports[group].push_back(std::move(export_value));
                }
            }
        }
        return true;
    } catch (const simdjson::simdjson_error& exception) {
        error = "Could not parse mod manifest '" + path.generic_string() +
            "': " + exception.what();
        return false;
    }
}

void hash_bytes(std::uint64_t& hash, const void* data, std::size_t size) {
    constexpr std::uint64_t fnv_prime = 1099511628211ull;
    const auto* bytes = static_cast<const unsigned char*>(data);
    for (std::size_t index = 0; index < size; ++index) {
        hash ^= bytes[index];
        hash *= fnv_prime;
    }
}

void hash_string(std::uint64_t& hash, const std::string& value) {
    hash_bytes(hash, value.data(), value.size());
    const unsigned char separator = 0xff;
    hash_bytes(hash, &separator, 1);
}

bool hash_file(
    std::uint64_t& hash,
    const std::filesystem::path& path
) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return false;
    char buffer[8192];
    while (file) {
        file.read(buffer, sizeof(buffer));
        const std::streamsize count = file.gcount();
        if (count > 0) {
            hash_bytes(hash, buffer, static_cast<std::size_t>(count));
        }
    }
    return true;
}

} // namespace

bool mod_manager::discover(
    const std::filesystem::path& mods_path,
    const std::string& expected_game_api_version,
    std::string* error
) {
    mods_.clear();
    root_path_ = mods_path.lexically_normal();

    std::error_code filesystem_error;
    if (!std::filesystem::exists(root_path_, filesystem_error)) {
        if (error) error->clear();
        return true;
    }
    if (!std::filesystem::is_directory(root_path_, filesystem_error)) {
        if (error) *error = "Mods path is not a directory: " +
            root_path_.generic_string();
        return false;
    }

    std::vector<std::filesystem::path> manifest_paths;
    for (const auto& entry : std::filesystem::directory_iterator(root_path_)) {
        if (!entry.is_directory()) continue;
        const auto manifest_path = entry.path() / "manifest.json";
        if (std::filesystem::is_regular_file(manifest_path)) {
            manifest_paths.push_back(manifest_path);
        }
    }
    std::sort(manifest_paths.begin(), manifest_paths.end());

    std::vector<mod_manifest> loaded;
    std::unordered_map<std::string, std::size_t> index_by_id;
    for (const auto& manifest_path : manifest_paths) {
        mod_manifest manifest;
        std::string manifest_error;
        if (!load_manifest(
                manifest_path, expected_game_api_version,
                manifest, manifest_error)) {
            if (error) *error = std::move(manifest_error);
            return false;
        }
        if (!manifest.enabled) continue;
        if (!index_by_id.emplace(manifest.id, loaded.size()).second) {
            if (error) *error = "Duplicate enabled mod id: " + manifest.id;
            return false;
        }
        loaded.push_back(std::move(manifest));
    }

    std::vector<std::vector<std::size_t>> outgoing(loaded.size());
    std::vector<std::size_t> indegree(loaded.size(), 0);
    std::set<std::pair<std::string, std::size_t>> ready;
    for (std::size_t index = 0; index < loaded.size(); ++index) {
        std::unordered_set<std::size_t> prerequisites;
        for (const std::string& dependency : loaded[index].dependencies) {
            const auto found = index_by_id.find(dependency);
            if (found == index_by_id.end()) {
                if (error) *error = "Missing dependency '" + dependency +
                    "' required by mod '" + loaded[index].id + "'";
                return false;
            }
            if (found->second == index) {
                if (error) *error = "Mod cannot depend on itself: " +
                    loaded[index].id;
                return false;
            }
            prerequisites.emplace(found->second);
        }
        for (const std::string& optional : loaded[index].load_after) {
            const auto found = index_by_id.find(optional);
            if (found != index_by_id.end()) prerequisites.emplace(found->second);
        }
        prerequisites.erase(index);
        indegree[index] = prerequisites.size();
        for (std::size_t prerequisite : prerequisites) {
            outgoing[prerequisite].push_back(index);
        }
    }
    for (std::size_t index = 0; index < loaded.size(); ++index) {
        if (indegree[index] == 0) ready.emplace(loaded[index].id, index);
    }

    while (!ready.empty()) {
        const std::size_t index = ready.begin()->second;
        ready.erase(ready.begin());
        mods_.push_back(std::move(loaded[index]));
        for (std::size_t dependent : outgoing[index]) {
            if (--indegree[dependent] == 0) {
                ready.emplace(loaded[dependent].id, dependent);
            }
        }
    }
    if (mods_.size() != loaded.size()) {
        mods_.clear();
        if (error) *error = "Mod dependency or load_after cycle detected";
        return false;
    }
    if (error) error->clear();
    return true;
}

std::vector<std::filesystem::path> mod_manager::content_paths(
    const std::string& group,
    mod_side runtime_side
) const {
    std::vector<std::filesystem::path> result;
    for (const mod_manifest& manifest : mods_) {
        if (!applies_to(manifest.side, runtime_side)) continue;
        const auto found = manifest.content.find(group);
        if (found != manifest.content.end()) {
            result.insert(result.end(), found->second.begin(), found->second.end());
        }
    }
    return result;
}

std::vector<std::filesystem::path> mod_manager::script_paths(
    const mod_manifest& manifest,
    mod_side runtime_side
) const {
    std::vector<std::filesystem::path> result;
    if (!applies_to(manifest.side, runtime_side)) return result;
    result.insert(
        result.end(), manifest.shared_scripts.begin(),
        manifest.shared_scripts.end()
    );
    const auto& side_scripts = runtime_side == mod_side::server
        ? manifest.server_scripts : manifest.client_scripts;
    result.insert(result.end(), side_scripts.begin(), side_scripts.end());
    return result;
}

const std::vector<mod_export>* mod_manager::exports(
    const mod_manifest& manifest,
    const std::string& group
) const {
    const auto found = manifest.exports.find(group);
    return found == manifest.exports.end() ? nullptr : &found->second;
}

std::string mod_manager::shared_mod_hash() const {
    std::uint64_t hash = 14695981039346656037ull;
    for (const mod_manifest& manifest : mods_) {
        if (manifest.side != mod_side::both) continue;
        hash_string(hash, manifest.id);
        hash_string(hash, manifest.version);
        hash_file(hash, manifest.manifest_path);
        for (const auto& entry : manifest.content) {
            hash_string(hash, entry.first);
            for (const auto& path : entry.second) {
                hash_string(hash, path.lexically_relative(
                    manifest.root_path).generic_string());
                hash_file(hash, path);
            }
        }
        std::set<std::filesystem::path> script_files;
        script_files.insert(
            manifest.shared_scripts.begin(), manifest.shared_scripts.end()
        );
        script_files.insert(
            manifest.client_scripts.begin(), manifest.client_scripts.end()
        );
        script_files.insert(
            manifest.server_scripts.begin(), manifest.server_scripts.end()
        );
        std::error_code filesystem_error;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(
                 manifest.root_path, filesystem_error)) {
            if (filesystem_error) break;
            if (entry.is_regular_file() && entry.path().extension() == ".as") {
                script_files.emplace(entry.path().lexically_normal());
            }
        }
        for (const auto& path : script_files) {
            hash_string(hash, path.lexically_relative(
                manifest.root_path).generic_string());
            hash_file(hash, path);
        }
    }
    std::ostringstream stream;
    stream << std::hex << std::setfill('0') << std::setw(16) << hash;
    return stream.str();
}

bool mod_manager::is_snake_case(const std::string& value) {
    if (value.empty() || value.front() < 'a' || value.front() > 'z' ||
        value.back() == '_') {
        return false;
    }
    bool previous_separator = false;
    for (char character : value) {
        const bool letter = character >= 'a' && character <= 'z';
        const bool digit = character >= '0' && character <= '9';
        if (letter || digit) {
            previous_separator = false;
            continue;
        }
        if (character != '_' || previous_separator) return false;
        previous_separator = true;
    }
    return true;
}

std::string mod_manager::canonical_name(const std::string& value) {
    std::string result;
    bool separator = false;
    for (unsigned char character : value) {
        const bool lower = character >= 'a' && character <= 'z';
        const bool upper = character >= 'A' && character <= 'Z';
        const bool digit = character >= '0' && character <= '9';
        if (lower || upper || digit) {
            if (separator && !result.empty()) result.push_back('_');
            result.push_back(upper
                ? static_cast<char>(character - 'A' + 'a')
                : static_cast<char>(character));
            separator = false;
        } else if (!result.empty()) {
            separator = true;
        }
    }
    return result;
}

std::string mod_manager::qualified_id(
    const std::string& mod_id,
    const std::string& local_id
) {
    if (!is_snake_case(mod_id) || !is_snake_case(local_id)) return {};
    return mod_id + "_" + local_id;
}

bool mod_manager::applies_to(
    mod_side declared_side,
    mod_side runtime_side
) {
    return declared_side == mod_side::both || declared_side == runtime_side;
}

} // namespace potato::modding
