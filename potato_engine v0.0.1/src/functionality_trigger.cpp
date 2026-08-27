#include "functionality_trigger.h"

#include <algorithm>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

namespace functionality_trigger {
namespace {

struct source_entry {
    const void* owner = nullptr;
    trigger_source source;
};

std::unordered_map<std::string, std::vector<source_entry>> sources;
std::mutex sources_mutex;

bool is_snake_case(const std::string& value) {
    if (value.empty() || value.front() == '_' || value.back() == '_') {
        return false;
    }
    bool previous_underscore = false;
    for (const char character : value) {
        const bool letter = character >= 'a' && character <= 'z';
        const bool number = character >= '0' && character <= '9';
        const bool underscore = character == '_';
        if (!letter && !number && !underscore) return false;
        if (underscore && previous_underscore) return false;
        previous_underscore = underscore;
    }
    return true;
}

} // namespace

bool register_source(
    const std::string& trigger_id,
    const void* owner,
    trigger_source source
) {
    if (!owner || !source || !is_snake_case(trigger_id)) return false;
    const std::lock_guard<std::mutex> lock(sources_mutex);
    std::vector<source_entry>& trigger_sources = sources[trigger_id];
    const auto existing = std::find_if(
        trigger_sources.begin(), trigger_sources.end(),
        [owner](const source_entry& entry) { return entry.owner == owner; }
    );
    if (existing != trigger_sources.end()) {
        existing->source = std::move(source);
    } else {
        trigger_sources.push_back({owner, std::move(source)});
    }
    return true;
}

void unregister_sources(const void* owner) {
    if (!owner) return;
    const std::lock_guard<std::mutex> lock(sources_mutex);
    for (auto iterator = sources.begin(); iterator != sources.end();) {
        std::vector<source_entry>& trigger_sources = iterator->second;
        trigger_sources.erase(
            std::remove_if(
                trigger_sources.begin(), trigger_sources.end(),
                [owner](const source_entry& entry) {
                    return entry.owner == owner;
                }
            ),
            trigger_sources.end()
        );
        if (trigger_sources.empty()) {
            iterator = sources.erase(iterator);
        } else {
            ++iterator;
        }
    }
}

bool evaluate(
    const std::string& trigger_id,
    const trigger_context& context
) {
    // Copy the callables so a source may safely alter registry ownership while
    // it runs without invalidating this evaluation.
    std::vector<trigger_source> active_sources;
    {
        const std::lock_guard<std::mutex> lock(sources_mutex);
        const auto found = sources.find(trigger_id);
        if (found == sources.end()) return false;
        active_sources.reserve(found->second.size());
        for (const source_entry& entry : found->second) {
            active_sources.push_back(entry.source);
        }
    }
    for (const trigger_source& source : active_sources) {
        if (source && source(context)) return true;
    }
    return false;
}

void clear() {
    const std::lock_guard<std::mutex> lock(sources_mutex);
    sources.clear();
}

} // namespace functionality_trigger
