#ifndef LOCALIZATION_H
#define LOCALIZATION_H

#include <string>
#include <unordered_map>

#include "debug.h"

/**
 * @brief Manages localized text tables and tag-based string variants.
 *
 * Localization is not limited to spoken languages. Tags can represent languages,
 * themes, seasonal variants, skins, or other content variations.
 *
 * Example tags:
 * - "en"
 * - "hu"
 * - "de"
 * - "dark"
 * - "christmas"
 *
 * Texts are loaded from JSON files and stored internally as flattened keys.
 *
 * Example:
 * JSON:
 * {
 *     "menu": {
 *         "start": "Start Game"
 *     }
 * }
 *
 * Stored key:
 * "menu.start" -> "Start Game"
 */
class Localization {
public:
    Localization() = default;

    /**
     * @brief Constructs a Localization instance with default and fallback tags.
     * @param default_tag The default localization tag.
     * @param fallback_tag The fallback localization tag used when a key is missing in the default tag.
     * @param logger Pointer to a Logger instance (optional).
     */
    Localization(const std::string& default_tag, const std::string& fallback_tag, Logger* logger = nullptr)
        : m_current_tag(default_tag), m_fallback_tag(fallback_tag), m_logger(logger) {}

    ~Localization() = default;

    Localization(const Localization&) = delete;
    Localization& operator=(const Localization&) = delete;

    /**
     * @brief Loads a localization JSON file and stores it under a tag.
     *
     * @param tag The tag/language/theme name, for example "en", "hu", "dark".
     * @param path The JSON file path.
     * @return True if the file was loaded successfully.
     */
    bool load(const std::string& tag, const std::string& path);

    /**
     * @brief Sets the currently active localization tag.
     *
     * @param tag The tag to activate.
     * @return True if the tag exists and was activated.
     */
    bool set_current_tag(const std::string& tag);

    /**
     * @brief Sets the fallback tag used when a key is missing in the current tag.
     *
     * @param tag The fallback tag.
     */
    void set_fallback_tag(const std::string& tag) { m_fallback_tag = tag; }

    /**
     * @brief Gets the currently active localization tag.
     */
    const std::string& get_current_tag() const { return m_current_tag; }

    /**
     * @brief Gets the fallback localization tag.
     */
    const std::string& get_fallback_tag() const { return m_fallback_tag; }

    /**
     * @brief Retrieves a localized string by key.
     *
     * First checks the current tag, then the fallback tag.
     * If the key is missing, returns a debug missing-key string.
     *
     * @param key The localization key, for example "menu.start".
     * @return The localized string.
     */
    std::string get(const std::string& key) const;

    /**
     * @brief Retrieves a localized string and replaces placeholders.
     *
     * Example:
     * "Coins: {count}"
     *
     * Values:
     * { "count", "12" }
     *
     * Result:
     * "Coins: 12"
     */
    std::string format(
        const std::string& key,
        const std::unordered_map<std::string, std::string>& values
    ) const;

    /**
     * @brief Checks whether a tag exists.
     */
    bool has_tag(const std::string& tag) const { return m_localizations.find(tag) != m_localizations.end(); }

    /**
     * @brief Checks whether a key exists in the current or fallback tag.
     */
    bool has_key(const std::string& key) const;

    /**
     * @brief Clears all loaded localization tables.
     */
    void clear() { m_localizations.clear(); }

    /**
     * @brief Sets the logger instance for logging missing keys and other messages.
     * @param logger Pointer to a Logger instance.
     */
    void set_logger(Logger* logger) { m_logger = logger; }


private:
    std::string m_current_tag = "en";
    std::string m_fallback_tag = "en";
    Logger* m_logger = nullptr;

    std::unordered_map<
        std::string, // tag
        std::unordered_map<std::string, std::string> // key-value pairs
    > m_localizations;
};

#endif
