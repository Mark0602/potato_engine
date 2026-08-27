#include "localization.h"

#include "simdjson.h"

namespace {
bool flatten_json(const simdjson::dom::element& value, const std::string& prefix,
                  std::unordered_map<std::string, std::string>& output, Logger* logger) {
    switch (value.type()) {
    case simdjson::dom::element_type::OBJECT:
        for (auto field : value.get_object()) {
            const std::string key(field.key);
            const std::string full_key = prefix.empty() ? key : prefix + "." + key;
            if (!flatten_json(field.value, full_key, output, logger)) return false;
        }
        return true;
    case simdjson::dom::element_type::STRING:
        if (prefix.empty()) return false;
        output[prefix] = std::string(value.get_string().value());
        return true;
    default:
        if (logger) logger->log(Log_Level::WARNING, "Localization",
            "Ignoring non-string localization value at key: " + prefix);
        return true;
    }
}
}

bool Localization::set_current_tag(const std::string& tag) {
    if (tag.empty() || !has_tag(tag)) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Localization",
            "Cannot activate unloaded localization tag: " + tag);
        return false;
    }
    m_current_tag = tag;
    return true;
}

bool Localization::has_key(const std::string& key) const {
    if (m_localizations.find(m_current_tag) != m_localizations.end() &&
        m_localizations.at(m_current_tag).find(key) != m_localizations.at(m_current_tag).end()) {
            return true;
    }
    if (m_localizations.find(m_fallback_tag) != m_localizations.end() &&
        m_localizations.at(m_fallback_tag).find(key) != m_localizations.at(m_fallback_tag).end()) {
            return true;
    }
    return false;
}

bool Localization::load(const std::string& tag, const std::string& path) {
    if (tag.empty() || path.empty()) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Localization", "Tag and path must not be empty.");
        return false;
    }

    try {
#if defined(_WIN32) && defined(__GNUC__)
        // MinGW's Windows stack alignment is incompatible with some AVX2
        // simdjson builds, so select the portable backend explicitly.
        const simdjson::implementation* portable_backend =
            simdjson::get_available_implementations()["fallback"];
        if (portable_backend != nullptr) {
            simdjson::get_active_implementation() = portable_backend;
        }
#endif
        simdjson::dom::parser parser;
        simdjson::dom::element root = parser.load(path);
        if (!root.is_object()) {
            if (m_logger) m_logger->log(Log_Level::ERROR, "Localization",
                "Localization root must be a JSON object: " + path);
            return false;
        }

        std::unordered_map<std::string, std::string> table;
        if (!flatten_json(root, "", table, m_logger)) return false;
        m_localizations[tag] = std::move(table);
        if (m_logger) m_logger->log(Log_Level::INFO, "Localization",
            "Loaded localization tag '" + tag + "' from '" + path + "'.");
        return true;
    } catch (const simdjson::simdjson_error& error) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Localization",
            "Failed to load '" + path + "': " + error.what());
        return false;
    }
}

std::string Localization::get(const std::string& key) const {
    auto current_table = m_localizations.find(m_current_tag);

    if (current_table != m_localizations.end()) {
        auto current_key = current_table->second.find(key);
        if (current_key != current_table->second.end()) {
            return current_key->second;
        }
    }
    auto fallback_table = m_localizations.find(m_fallback_tag);
    if (fallback_table != m_localizations.end()) {
        auto fallback_key = fallback_table->second.find(key);
        if (fallback_key != fallback_table->second.end()) {
            return fallback_key->second;
        }
    }
    if (m_logger) m_logger->log(Log_Level::WARNING, "Localization", "Localization key not found: " + key);
    return "[MISSING: " + key + "]";
}

std::string Localization::format(
    const std::string& key,
    const std::unordered_map<std::string, std::string>& values
) const {
    std::string result = get(key);
    for (const auto& entry : values) {
        const std::string placeholder = "{" + entry.first + "}";
        std::size_t position = 0;
        while ((position = result.find(placeholder, position)) != std::string::npos) {
            result.replace(position, placeholder.size(), entry.second);
            position += entry.second.size();
        }
    }
    return result;
}
