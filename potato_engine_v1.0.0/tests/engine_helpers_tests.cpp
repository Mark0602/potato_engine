#include "animations.h"
#include "scene.h"
#include "timer.h"

#include <cmath>
#include <iostream>
#include <string>

namespace {

bool require(bool condition, const std::string& message) {
    if (condition) return true;
    std::cerr << "FAIL: " << message << '\n';
    return false;
}

bool nearly_equal(float left, float right) {
    return std::fabs(left - right) < 0.0001f;
}

} // namespace

int main() {
    bool success = true;

    bool timer_called = false;
    Timer timer;
    timer.start(0.5f, [&timer_called]() { timer_called = true; });
    timer.tick(0.2f);
    success &= require(
        timer.is_running() && nearly_equal(timer.progress(), 0.4f),
        "timer reports deterministic progress"
    );
    timer.tick(0.3f);
    success &= require(
        timer_called && timer.is_just_done() && !timer.is_running(),
        "timer completes and invokes its callback once"
    );

    float animated_value = 0.0f;
    Anim animation;
    animation.start(
        1.0f,
        0.0f,
        10.0f,
        Ease::linear,
        [&animated_value](float value) { animated_value = value; }
    );
    animation.tick(0.25f);
    success &= require(
        nearly_equal(animated_value, 2.5f),
        "animation interpolates through the selected easing function"
    );

    SceneManager& scenes = SceneManager::instance();
    scenes.register_scene(7, "helper_test");
    bool load_task_called = false;
    scenes.enqueue_load_task(7, "prepare", [&load_task_called]() {
        load_task_called = true;
    });
    success &= require(
        scenes.request_scene("helper_test"),
        "scene transition can be requested by name"
    );
    int target = -1;
    success &= require(
        scenes.consume_scene_request(target) && target == 7,
        "scene transition request is consumed exactly once"
    );
    auto tasks = scenes.take_load_tasks(target);
    success &= require(
        tasks.size() == 1 && tasks.front().step() && load_task_called,
        "scene load tasks are returned to the application loop"
    );
    scenes.complete_transition(target);
    success &= require(
        scenes.current_scene() == 7,
        "completed transition activates its scene"
    );

    if (!success) return 1;
    std::cout << "Potato Engine helper tests passed\n";
    return 0;
}
