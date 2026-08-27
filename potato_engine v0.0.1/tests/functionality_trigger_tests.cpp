#include "functionality_trigger.h"

#include <iostream>
#include <string>

namespace {

bool require(bool condition, const std::string& message) {
    if (condition) return true;
    std::cerr << "FAIL: " << message << '\n';
    return false;
}

} // namespace

int main() {
    using namespace functionality_trigger;

    bool success = true;
    int input_owner = 0;
    int collision_owner = 0;
    bool input_pressed = false;
    bool collision_entered = false;
    bool context_received = false;

    const trigger_context context{
        42,
        "test_subject",
        "test_action",
        "test_instance",
        {12.0f, 34.0f}
    };

    success &= require(
        !register_source("Invalid-Trigger", &input_owner, [](const auto&) {
            return true;
        }),
        "trigger ids require lowercase snake_case"
    );
    success &= require(
        register_source(
            "activate_action",
            &input_owner,
            [&input_pressed](const trigger_context&) {
                return input_pressed;
            }
        ),
        "input bool source registers"
    );
    success &= require(
        register_source(
            "activate_action",
            &collision_owner,
            [&collision_entered, &context_received](
                const trigger_context& received
            ) {
                context_received = received.actor_id == 42 &&
                    received.subject_id == "test_subject" &&
                    received.action_id == "test_action" &&
                    received.instance_id == "test_instance" &&
                    received.target == Vec{12.0f, 34.0f};
                return collision_entered;
            }
        ),
        "collision bool source registers on the same trigger"
    );
    success &= require(
        !evaluate("activate_action", context) && context_received,
        "false sources do not activate and receive trigger context"
    );

    input_pressed = true;
    success &= require(
        evaluate("activate_action", context),
        "an input bool can activate the trigger"
    );
    input_pressed = false;
    collision_entered = true;
    success &= require(
        evaluate("activate_action", context),
        "a non-input bool can activate the same trigger"
    );

    unregister_sources(&collision_owner);
    success &= require(
        !evaluate("activate_action", context),
        "removing one owner leaves other false sources intact"
    );
    unregister_sources(&input_owner);
    success &= require(
        !evaluate("activate_action", context),
        "all sources can be removed by owner"
    );
    clear();

    if (!success) return 1;
    std::cout << "Functionality trigger tests passed\n";
    return 0;
}
