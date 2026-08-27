#ifndef FUNCTIONALITY_TRIGGER_H
#define FUNCTIONALITY_TRIGGER_H

#include "vec.h"

#include <cstdint>
#include <functional>
#include <string>

namespace functionality_trigger {

/**
 * Read-only data supplied while a named functionality trigger is evaluated.
 * Trigger sources may ignore fields they do not need.
 */
struct trigger_context {
    std::uint64_t actor_id = 0;
    std::string subject_id;
    std::string action_id;
    std::string instance_id;
    Vec target{};
};

using trigger_source = std::function<bool(const trigger_context&)>;

/**
 * Adds or replaces one bool source for a named trigger.
 *
 * All sources registered for the same trigger are OR-ed. `owner` is only an
 * identity token and is never dereferenced. Trigger IDs must use lowercase
 * snake_case.
 */
bool register_source(
    const std::string& trigger_id,
    const void* owner,
    trigger_source source
);

/** Removes every trigger source owned by the supplied identity token. */
void unregister_sources(const void* owner);

/** Returns true when any source for the named trigger currently returns true. */
bool evaluate(
    const std::string& trigger_id,
    const trigger_context& context = {}
);

/** Clears all sources. Intended for process shutdown and isolated tests. */
void clear();

} // namespace functionality_trigger

#endif // FUNCTIONALITY_TRIGGER_H
