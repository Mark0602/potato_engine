#ifndef ASSET_POOL_H
#define ASSET_POOL_H

#include <unordered_map>
#include <memory>
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include "debug.h"
#include "texture.h"
#include "audio.h"
#include "fonts.h"
#include "localization.h"
#include <iostream>
#include <map>
#include <random>

/**
 * @brief Asset_Pool manages a collection of assets, like
 * textures, audio files and fonts, allowing for loading, retrieval, and unloading of assets by name.
 * It uses an SDL_Renderer for texture creation and an optional Logger for logging messages.
 * Please use the Asset_Pool class to manage your textures, audio files and fonts
 * instead of creating objects directly, as it handles caching and resource management.
 * The asset pool uses unique_ptr to manage the lifetime of assets, ensuring proper cleanup when they are no longer needed.
 * 
 * You can access the global asset pool via `Engine::asset_pool` after it has been initialised in `main()`.
 */
class Asset_Pool {  
public:
    Asset_Pool() = default;

    /**
     * @brief Constructs an Asset_Pool with a given SDL_Renderer and optional Logger.
     * @param renderer Pointer to the SDL_Renderer used for texture loading.
     * @param logger Optional pointer to a Logger for logging messages; defaults to nullptr.
     */
    Asset_Pool(SDL_Renderer* renderer, Logger* logger = nullptr)
        : m_renderer(renderer), m_logger(logger), m_localization("en", "en", logger) {};
    
    ~Asset_Pool() = default;

    /**
     * @brief Sets the SDL_Renderer to be used for texture loading.
     * @param renderer Pointer to the SDL_Renderer.
     */
    void set_renderer(SDL_Renderer* renderer) { m_renderer = renderer; }
    /**
     * @brief Sets the Logger to be used for logging messages.
     * @param logger Pointer to the Logger.
     */
    void set_logger(Logger* logger) { m_logger = logger; m_localization.set_logger(logger); }
    
    /**
     * @brief Retrieves a texture by name.
     * @param name The name of the texture.
     * @return Pointer to the Texture if found; nullptr otherwise.
     */
    Texture* get_texture(const std::string& name);

    /**
     * @brief Checks if a texture with the given name exists in the pool.
     * @param name The name of the texture.
     */
    bool has_texture(const std::string& name) const { return m_textures.find(name) != m_textures.end(); }
    
    /**
     * @brief Loads a texture from a file and adds it to the pool.
     * @param name The name to associate with the texture.
     * @param path The file path to the texture image.
     */
    void load_texture(const std::string& name, const std::string& path, bool use_default_path = true);
    /**
     * @brief Registers a locale-specific texture variant under a shared logical name.
     * Inactive variants stay unloaded. Locale changes invalidate previously returned
     * pointers for localized textures, so callers should resolve them again by name.
     */
    void load_texture(const std::string& name, const std::string& path, const std::string& locale_tag, bool use_default_path = true);

    /**
     * @brief Loads a texture from a file and adds it to the pool, with an option to specify a custom SDL_Renderer.
     * @param name The name to associate with the texture.
     * @param path The file path to the texture image.
     * @param renderer Pointer to the SDL_Renderer used for texture loading.
     */
    bool load_locale(const std::string& locale_tag, const std::string& path);
    
    /**
     * @brief Loads all locale JSON files from a directory and adds them to the pool.
     * @param directory The directory path containing locale JSON files.
     * @return The number of successfully loaded locales.
     */
    std::size_t load_locales_from_directory(const std::string& directory);
    
    /**
     * @brief Sets the current locale for localized assets.
     * @param locale_tag The locale tag to set (e.g., "en", "fr").
     * @return `true` if the locale was successfully set; `false` if the locale tag does not exist.
     */
    bool set_locale(const std::string& locale_tag);
    
    /**
     * @brief Gets the current locale tag.
     * @return The current locale tag as a string.
     */
    const std::string& get_locale() const { return m_current_locale; }
    
    /**
     * @brief Retrieves the Localization object for managing localized text.
     * @return Reference to the Localization object.
     */
    Localization& localization() { return m_localization; }

    /**
     * @brief Retrieves the Localization object for managing localized text (const version).
     * @return Const reference to the Localization object.
     */
    const Localization& localization() const { return m_localization; }
    
    /**
     * @brief Retrieves a localized string by key using the current locale.
     * @param key The localization key.
     * @return The localized string corresponding to the key.
     */
    std::string get_text(const std::string& key) const { return m_localization.get(key); }
    
    /**
     * @brief Retrieves a localized string by key and formats it with provided values.
     * @param key The localization key.
     * @param values A map of placeholder names to their replacement values.
     * @return The formatted localized string corresponding to the key.
     */
    std::string format_text(const std::string& key, const std::unordered_map<std::string, std::string>& values) const {
        return m_localization.format(key, values);
    }

    /**
     * @brief Unloads a texture from the pool by name.
     * @param name The name of the texture to unload.
     */
    void unload_texture(const std::string& name);

    /**
     * @brief Retrieves a font by name.
     * @param name The name of the font.
     * @return Pointer to the IFont if found; nullptr otherwise.
     */
    IFont* get_font(const std::string& name);

    /**
     * @brief Checks if a font with the given name exists in the pool.
     * @param name The name of the font.
     */
    bool has_font(const std::string& name) const { return m_fonts.find(name) != m_fonts.end(); }

    /**
     * @brief Loads an SDL_ttf font from disk and adds it to the pool.
     * @param name The name to associate with the font.
     * @param path The file path to the TTF/OTF font file.
     * @param size Font point size.
     */
    void load_sdl_font(const std::string& name, const std::string& path,
                       int size = 16, bool pixel_art = false);

    /**
     * @brief Loads a tileset font atlas from disk and adds it to the pool.
     * @param name The name to associate with the font.
     * @param path The file path to the bitmap font atlas image.
     * @param tile_size Size of one glyph tile in the atlas.
     * @param char_map Characters mapped left-to-right, top-to-bottom in the atlas.
     */
    void load_tileset_font(const std::string& name, const std::string& path, const Vec& tile_size, const std::string& char_map);

    /**
     * @brief Unloads a font from the pool by name.
     * @param name The name of the font to unload.
     */
    void unload_font(const std::string& name);

    /**
     * @brief Retrieves an audio file by name.
     * @param name The name of the audio file.
     * @return Pointer to the Audio if found; nullptr otherwise.
     */
    Audio* get_audio(const std::string& name);

    /**
     * @brief Checks if an audio file with the given name exists in the pool.
     * @param name The name of the audio file.
     */
    bool has_audio(const std::string& name) const { return m_audio.find(name) != m_audio.end(); }

    /**
     * @brief Loads an audio file from disk and adds it to the pool.
     * @param name The name to associate with the audio file.
     * @param path The file path to the audio file.
     * @param predecode If `true`, the audio will be decoded into memory. If `false`, it will stream from disk.
     */
    void load_audio(const std::string& name, const std::string& path, bool predecode = true);

    /**
     * @brief Loads an audio file from disk and adds it to an audio group tag.
     * @param name The name to associate with the audio file.
     * @param path The file path to the audio file.
     * @param tag The group tag to attach to this audio file, for example "ui" or "music".
     * @param predecode If `true`, the audio will be decoded into memory. If `false`, it will stream from disk.
     */
    void load_audio(const std::string& name, const std::string& path, const std::string& tag, bool predecode = true);

    /**
     * @brief Loads an audio file from disk and adds it to multiple audio group tags.
     * @param name The name to associate with the audio file.
     * @param path The file path to the audio file.
     * @param tags The group tags to attach to this audio file.
     * @param predecode If `true`, the audio will be decoded into memory. If `false`, it will stream from disk.
     */
    void load_audio(const std::string& name, const std::string& path, const std::vector<std::string>& tags, bool predecode = true);

    /**
     * @brief Unloads an audio file from the pool by name.
     * @param name The name of the audio file to unload.
     */
    void unload_audio(const std::string& name);

    /**
     * @brief Adds an already loaded audio file to a group tag.
     * @param audio_name The name of the loaded audio file.
     * @param tag The group tag to attach.
     */
    void add_audio_to_group(const std::string& audio_name, const std::string& tag);

    /**
     * @brief Removes an audio file from a group tag.
     * @param audio_name The name of the loaded audio file.
     * @param tag The group tag to detach.
     */
    void remove_audio_from_group(const std::string& audio_name, const std::string& tag);

    /**
     * @brief Checks if an audio group tag exists.
     * @param tag The group tag to check.
     * @return `true` if the tag exists; `false` otherwise.
     */
    bool has_audio_group(const std::string& tag) const { return m_audio_groups.find(tag) != m_audio_groups.end(); }

    /**
     * @brief Gets every loaded audio file attached to a group tag.
     * @param tag The group tag to query.
     * @return A vector of borrowed Audio pointers. Do not delete these pointers.
     */
    std::vector<Audio*> get_audio_group(const std::string& tag);

    /**
     * @brief Applies a full Audio_Props value to every audio file in a group.
     * @param tag The group tag to modify.
     * @param props The properties to apply.
     */
    void set_audio_group_props(const std::string& tag, const Audio_Props& props);

    /**
     * @brief Sets the gain for every audio file in a group.
     * @param tag The group tag to modify.
     * @param gain The gain value to apply.
     */
    void set_audio_group_gain(const std::string& tag, float gain);

    /**
     * @brief Sets the pitch for every audio file in a group.
     * @param tag The group tag to modify.
     * @param pitch The pitch value to apply.
     */
    void set_audio_group_pitch(const std::string& tag, float pitch);

    /**
     * @brief Sets the loop count for every audio file in a group.
     * @param tag The group tag to modify.
     * @param loop_count The loop count to apply.
     */
    void set_audio_group_loop_count(const std::string& tag, int loop_count);

    /**
     * @brief Plays every audio file in a group.
     * @param tag The group tag to play.
     */
    void play_audio_group(const std::string& tag);

    /**
     * @brief Plays every audio file in a group in a shuffled order.
     * @param tag The group tag to play.
     */
    void play_audio_group_shuffled(const std::string& tag);

    /**
     * @brief Pauses every audio file in a group.
     * @param tag The group tag to pause.
     */
    void pause_audio_group(const std::string& tag);

    /**
     * @brief Resumes every audio file in a group.
     * @param tag The group tag to resume.
     */
    void resume_audio_group(const std::string& tag);

    /**
     * @brief Stops every audio file in a group.
     * @param tag The group tag to stop.
     */
    void stop_audio_group(const std::string& tag);

    /**
     * @brief Clears all cached assets from the pool.
     */
    void clear() {
        m_audio_groups.clear();
        m_audio.clear();
        m_fonts.clear();
        m_textures.clear();
        m_localized_textures.clear();
        m_active_localized_texture_paths.clear();
        m_localization.clear();
        if(m_logger) m_logger->log(Log_Level::INFO, "Asset_Pool", "Asset_Pool: Cleared all assets.");
    }

private:
    SDL_Renderer* m_renderer = nullptr;
    Logger* m_logger = nullptr;

    std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_localized_textures;
    std::unordered_map<std::string, std::string> m_active_localized_texture_paths;
    std::unordered_map<std::string, std::unique_ptr<Audio>> m_audio;
    std::unordered_map<std::string, std::unique_ptr<IFont>> m_fonts;
    std::unordered_map<std::string, std::vector<std::string>> m_audio_groups;
    Localization m_localization;
    std::string m_current_locale = "en";

    void remove_audio_from_all_groups(const std::string& audio_name);
    bool activate_localized_texture(const std::string& name);
};



#endif
