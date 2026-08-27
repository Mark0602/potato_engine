#ifndef POTATO_MODDING_MOD_MANIFEST_H
#define POTATO_MODDING_MOD_MANIFEST_H

#include <filesystem>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace potato::modding {

enum class mod_side {
    both,
    client,
    server
};

struct mod_export {
    std::string id;
    std::string script_prefix;
};

struct mod_manifest {
    std::uint32_t schema_version = 1;
    std::string id;
    std::string display_name;
    std::string version;
    std::string game_api_version;
    bool enabled = true;
    mod_side side = mod_side::both;
    std::vector<std::string> dependencies;
    std::vector<std::string> load_after;
    std::map<std::string, std::vector<std::filesystem::path>> content;
    std::vector<std::filesystem::path> shared_scripts;
    std::vector<std::filesystem::path> client_scripts;
    std::vector<std::filesystem::path> server_scripts;
    std::map<std::string, std::vector<mod_export>> exports;
    std::filesystem::path root_path;
    std::filesystem::path manifest_path;
};

/**
 * Discovers, validates and deterministically orders Potato Engine mods.
 *
 * The manager is engine-level code. Consumers interpret content and export
 * group names in their own adapter layer.
 */
class mod_manager final {
public:
    bool discover(
        const std::filesystem::path& mods_path,
        const std::string& expected_game_api_version,
        std::string* error = nullptr
    );

    const std::vector<mod_manifest>& mods() const { return mods_; }
    const std::filesystem::path& root_path() const { return root_path_; }

    std::vector<std::filesystem::path> content_paths(
        const std::string& group,
        mod_side runtime_side
    ) const;
    std::vector<std::filesystem::path> script_paths(
        const mod_manifest& manifest,
        mod_side runtime_side
    ) const;
    const std::vector<mod_export>* exports(
        const mod_manifest& manifest,
        const std::string& group
    ) const;

    std::string shared_mod_hash() const;
    bool empty() const { return mods_.empty(); }

    static bool is_snake_case(const std::string& value);
    static std::string canonical_name(const std::string& value);
    static std::string qualified_id(
        const std::string& mod_id,
        const std::string& local_id
    );
    static bool applies_to(mod_side declared_side, mod_side runtime_side);

private:
    std::filesystem::path root_path_;
    std::vector<mod_manifest> mods_;
};

} // namespace potato::modding

#endif // POTATO_MODDING_MOD_MANIFEST_H
