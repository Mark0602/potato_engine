#include "asset_pool.h"

#include <algorithm>
#include <filesystem>
#include <vector>

Texture* Asset_Pool::get_texture(const std::string& name) {
    auto found = m_textures.find(name);
    if (found == m_textures.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Texture '" + name + "' does not exist.");
        return nullptr;
    }
    return found->second.get();
}

void Asset_Pool::load_texture(const std::string& name, const std::string& path, bool use_default_path) {
    const std::string full_path = use_default_path ? "assets/textures/" + path : path;
    
    if (path.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load texture '" + name + "' from '" + full_path + "' because path is empty.");
        return;
    }
    if (name.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load texture from '" + full_path + "' because name is empty.");
        return;
    }
    if (!m_renderer) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load texture '" + name + "' from '" + full_path + "' because renderer is not set.");
        return;
    }

    auto found = m_textures.find(name);
    if (found != m_textures.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Texture '" + name + "' already exists. Returning to cache.");
        return;
    }

    auto texture = std::make_unique<Texture>(m_renderer, full_path, m_logger);
    if (!texture || !texture->is_loaded()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Failed to load texture '" + name + "' from '" + full_path + "'.");
        return;
    }
    m_textures.emplace(name, std::move(texture));
    if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Loaded texture '" + name + "' from '" + full_path + "'.");

    
}

void Asset_Pool::load_texture(const std::string& name, const std::string& path, const std::string& locale_tag, bool use_default_path) {
    std::string full_path = use_default_path ? "assets/textures/" + path : path;
    if (name.empty() || path.empty() || locale_tag.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Localized texture arguments must not be empty.");
        return;
    }
    m_localized_textures[name][locale_tag] = path;
    if (locale_tag == m_current_locale) activate_localized_texture(name);
}

bool Asset_Pool::load_locale(const std::string& locale_tag, const std::string& path) {
    return m_localization.load(locale_tag, path);
}

std::size_t Asset_Pool::load_locales_from_directory(const std::string& directory) {
    namespace fs = std::filesystem;

    std::error_code error;
    if (!fs::is_directory(directory, error)) {
        if (m_logger) {
            m_logger->log(
                Log_Level::WARNING,
                "Localization",
                "Localization directory does not exist: " + directory
            );
        }
        return 0;
    }

    std::vector<fs::path> locale_paths;
    for (fs::directory_iterator entry(directory, error), end;
         !error && entry != end; entry.increment(error)) {
        if (entry->is_regular_file() && entry->path().extension() == ".json") {
            locale_paths.push_back(entry->path());
        }
    }
    if (error) {
        if (m_logger) {
            m_logger->log(
                Log_Level::ERROR,
                "Localization",
                "Could not enumerate localization directory '" + directory +
                    "': " + error.message()
            );
        }
        return 0;
    }

    std::sort(locale_paths.begin(), locale_paths.end());
    std::size_t loaded_count = 0;
    for (const fs::path& path : locale_paths) {
        const std::string tag = path.stem().string();
        if (!tag.empty() && load_locale(tag, path.generic_string())) {
            ++loaded_count;
        }
    }
    return loaded_count;
}

bool Asset_Pool::activate_localized_texture(const std::string& name) {
    auto definitions = m_localized_textures.find(name);
    if (definitions == m_localized_textures.end()) return false;
    auto variant = definitions->second.find(m_current_locale);
    if (variant == definitions->second.end()) variant = definitions->second.find(m_localization.get_fallback_tag());
    if (variant == definitions->second.end()) {
        m_textures.erase(name);
        m_active_localized_texture_paths.erase(name);
        return false;
    }
    auto active = m_active_localized_texture_paths.find(name);
    if (active != m_active_localized_texture_paths.end() && active->second == variant->second && has_texture(name)) return true;
    m_textures.erase(name);
    m_active_localized_texture_paths.erase(name);
    load_texture(name, variant->second);
    if (!has_texture(name)) return false;
    m_active_localized_texture_paths[name] = variant->second;
    return true;
}

bool Asset_Pool::set_locale(const std::string& locale_tag) {
    if (locale_tag.empty()) return false;
    const bool has_text = m_localization.has_tag(locale_tag);
    bool has_texture = false;
    for (const auto& asset : m_localized_textures) {
        if (asset.second.find(locale_tag) != asset.second.end()) { has_texture = true; break; }
    }
    if (!has_text && !has_texture) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Unknown locale tag: " + locale_tag);
        return false;
    }
    m_current_locale = locale_tag;
    if (has_text) m_localization.set_current_tag(locale_tag);
    for (const auto& asset : m_localized_textures) activate_localized_texture(asset.first);
    if (m_logger) {
        m_logger->log(
            Log_Level::INFO,
            "Localization",
            "Active locale set to '" + locale_tag + "'."
        );
    }
    return true;
}

void Asset_Pool::unload_texture(const std::string& name) {
    auto found = m_textures.find(name);
    if (found != m_textures.end()) {
        m_textures.erase(found);
        m_active_localized_texture_paths.erase(name);
        m_localized_textures.erase(name);
        if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Unloaded texture '" + name + "'.");
    } else {
        if (m_localized_textures.erase(name) > 0) {
            m_active_localized_texture_paths.erase(name);
            if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Unregistered localized texture '" + name + "'.");
        } else if (m_logger) {
            m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Cannot unload texture '" + name + "' because it does not exist.");
        }
    }
}

IFont* Asset_Pool::get_font(const std::string& name) {
    auto found = m_fonts.find(name);
    if (found == m_fonts.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Font '" + name + "' does not exist.");
        return nullptr;
    }
    return found->second.get();
}

void Asset_Pool::load_sdl_font(const std::string& name, const std::string& path,
                               int size, bool pixel_art) {
    if (path.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load SDL font '" + name + "' because path is empty.");
        return;
    }
    if (name.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load SDL font from '" + path + "' because name is empty.");
        return;
    }
    if (size <= 0) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load SDL font '" + name + "' because size is invalid.");
        return;
    }

    auto found = m_fonts.find(name);
    if (found != m_fonts.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Font '" + name + "' already exists. Returning to cache.");
        return;
    }

    auto font = std::make_unique<SDL_Font>();
    font->set_pixel_art(pixel_art);
    if (!font->load(path, size)) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Failed to load SDL font '" + name + "' from '" + path + "'.");
        return;
    }

    m_fonts.emplace(name, std::move(font));
    if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Loaded SDL font '" + name + "' from '" + path + "'.");
}

void Asset_Pool::load_tileset_font(const std::string& name, const std::string& path, const Vec& tile_size, const std::string& char_map) {
    if (path.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load tileset font '" + name + "' because path is empty.");
        return;
    }
    if (name.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load tileset font from '" + path + "' because name is empty.");
        return;
    }
    if (!m_renderer) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load tileset font '" + name + "' from '" + path + "' because renderer is not set.");
        return;
    }
    if (tile_size.x <= 0.0f || tile_size.y <= 0.0f) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load tileset font '" + name + "' because tile size is invalid.");
        return;
    }
    if (char_map.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load tileset font '" + name + "' because char map is empty.");
        return;
    }

    auto found = m_fonts.find(name);
    if (found != m_fonts.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Font '" + name + "' already exists. Returning to cache.");
        return;
    }

    auto font = std::make_unique<Tileset_Font>();
    if (!font->load_tileset_font(m_renderer, path, tile_size, char_map)) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Failed to load tileset font '" + name + "' from '" + path + "'.");
        return;
    }

    m_fonts.emplace(name, std::move(font));
    if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Loaded tileset font '" + name + "' from '" + path + "'.");
}

void Asset_Pool::unload_font(const std::string& name) {
    auto found = m_fonts.find(name);
    if (found != m_fonts.end()) {
        m_fonts.erase(found);
        if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Unloaded font '" + name + "'.");
    } else {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Cannot unload font '" + name + "' because it does not exist.");
    }
}

Audio* Asset_Pool::get_audio(const std::string& name) {
    auto found = m_audio.find(name);
    if (found == m_audio.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Audio '" + name + "' does not exist.");
        return nullptr;
    }
    return found->second.get();
}

void Asset_Pool::load_audio(const std::string& name, const std::string& path, bool predecode) {
    if (path.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load audio '" + name + "' because path is empty.");
        return;
    }
    if (name.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot load audio from '" + path + "' because name is empty.");
        return;
    }

    auto found = m_audio.find(name);
    if (found != m_audio.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Audio '" + name + "' already exists. Returning to cache.");
        return;
    }

    auto audio = std::make_unique<Audio>(path, static_cast<MIX_Mixer*>(nullptr), predecode);
    audio->set_logger(m_logger);

    if (!audio || !audio->is_loaded()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Failed to load audio '" + name + "' from '" + path + "'.");
        return;
    }

    m_audio.emplace(name, std::move(audio));
    if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Loaded audio '" + name + "' from '" + path + "'.");
}

void Asset_Pool::load_audio(const std::string& name, const std::string& path, const std::string& tag, bool predecode) {
    load_audio(name, path, predecode);
    add_audio_to_group(name, tag);
}

void Asset_Pool::load_audio(const std::string& name, const std::string& path, const std::vector<std::string>& tags, bool predecode) {
    load_audio(name, path, predecode);

    for (const std::string& tag : tags) {
        add_audio_to_group(name, tag);
    }
}

void Asset_Pool::unload_audio(const std::string& name) {
    auto found = m_audio.find(name);
    if (found != m_audio.end()) {
        remove_audio_from_all_groups(name);
        m_audio.erase(found);
        if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Unloaded audio '" + name + "'.");
    } else {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Cannot unload audio '" + name + "' because it does not exist.");
    }
}

void Asset_Pool::add_audio_to_group(const std::string& audio_name, const std::string& tag) {
    if (audio_name.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot add audio to group because audio name is empty.");
        return;
    }
    if (tag.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Asset_Pool", "Asset_Pool: Cannot add audio '" + audio_name + "' to an empty group tag.");
        return;
    }
    if (!has_audio(audio_name)) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Cannot add missing audio '" + audio_name + "' to group '" + tag + "'.");
        return;
    }

    auto& group = m_audio_groups[tag];
    auto found = std::find(group.begin(), group.end(), audio_name);

    if (found != group.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Audio '" + audio_name + "' is already in group '" + tag + "'.");
        return;
    }

    group.push_back(audio_name);

    if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Added audio '" + audio_name + "' to group '" + tag + "'.");
}

void Asset_Pool::remove_audio_from_group(const std::string& audio_name, const std::string& tag) {
    auto found_group = m_audio_groups.find(tag);
    if (found_group == m_audio_groups.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Cannot remove audio from missing group '" + tag + "'.");
        return;
    }

    auto& group = found_group->second;
    auto old_size = group.size();
    group.erase(std::remove(group.begin(), group.end(), audio_name), group.end());
    bool removed = group.size() != old_size;

    if (group.empty()) {
        m_audio_groups.erase(found_group);
    }

    if (m_logger) {
        if (removed) {
            m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Removed audio '" + audio_name + "' from group '" + tag + "'.");
        } else {
            m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Audio '" + audio_name + "' was not in group '" + tag + "'.");
        }
    }
}

std::vector<Audio*> Asset_Pool::get_audio_group(const std::string& tag) {
    std::vector<Audio*> result;

    auto found_group = m_audio_groups.find(tag);
    if (found_group == m_audio_groups.end()) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Asset_Pool", "Asset_Pool: Audio group '" + tag + "' does not exist.");
        return result;
    }

    for (const std::string& audio_name : found_group->second) {
        Audio* audio = get_audio(audio_name);
        if (audio) {
            result.push_back(audio);
        }
    }

    return result;
}

void Asset_Pool::set_audio_group_props(const std::string& tag, const Audio_Props& props) {
    auto group = get_audio_group(tag);

    for (Audio* audio : group) {
        audio->set_props(props);
    }

    if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Applied props to audio group '" + tag + "'.");
}

void Asset_Pool::set_audio_group_gain(const std::string& tag, float gain) {
    auto group = get_audio_group(tag);

    for (Audio* audio : group) {
        audio->set_gain(gain);
    }

    if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Set gain for audio group '" + tag + "'.");
}

void Asset_Pool::set_audio_group_pitch(const std::string& tag, float pitch) {
    auto group = get_audio_group(tag);

    for (Audio* audio : group) {
        audio->set_pitch(pitch);
    }

    if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Set pitch for audio group '" + tag + "'.");
}

void Asset_Pool::set_audio_group_loop_count(const std::string& tag, int loop_count) {
    auto group = get_audio_group(tag);

    for (Audio* audio : group) {
        audio->set_loop_count(loop_count);
    }

    if (m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Set loop count for audio group '" + tag + "'.");
}

void Asset_Pool::play_audio_group(const std::string& tag) {
    auto group = get_audio_group(tag);

    for (Audio* audio : group) {
        audio->play();
    }
}

void Asset_Pool::play_audio_group_shuffled(const std::string& tag) {
    auto group = get_audio_group(tag);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(group.begin(), group.end(), g);

    for (Audio* audio : group) {
        audio->play();
    }
}

void Asset_Pool::pause_audio_group(const std::string& tag) {
    auto group = get_audio_group(tag);

    for (Audio* audio : group) {
        audio->pause();
    }
}

void Asset_Pool::resume_audio_group(const std::string& tag) {
    auto group = get_audio_group(tag);

    for (Audio* audio : group) {
        audio->resume();
    }
}

void Asset_Pool::stop_audio_group(const std::string& tag) {
    auto group = get_audio_group(tag);

    for (Audio* audio : group) {
        audio->stop();
    }
}

void Asset_Pool::remove_audio_from_all_groups(const std::string& audio_name) {
    for (auto it = m_audio_groups.begin(); it != m_audio_groups.end();) {
        auto& group = it->second;
        group.erase(std::remove(group.begin(), group.end(), audio_name), group.end());

        if (group.empty()) {
            it = m_audio_groups.erase(it);
        } else {
            ++it;
        }
    }
}
