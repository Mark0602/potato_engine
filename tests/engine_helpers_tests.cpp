#include "animations.h"
#include "object.h"
#include "physics.h"
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

    Object parent(Transform{{10.0f, 20.0f}, {32.0f, 32.0f}, {90.0f, 1.0f}});
    Object child(Transform{{5.0f, 0.0f}, {8.0f, 6.0f}, {15.0f, 1.0f}});
    success &= require(
        child.set_parent(&parent, false),
        "an object can be parented while keeping its local transform"
    );
    Transform child_world = child.get_world_transform();
    success &= require(
        nearly_equal(child_world.pos.x, 10.0f) &&
        nearly_equal(child_world.pos.y, 25.0f) &&
        nearly_equal(child_world.size.x, 8.0f) &&
        nearly_equal(child_world.size.y, 6.0f) &&
        nearly_equal(child_world.rotation.x, 105.0f) &&
        nearly_equal(child_world.rotation.y, 0.0f),
        "world transforms compose position, angle, and flip without scaling size"
    );
    success &= require(
        parent.get_children().size() == 1 && parent.get_children().front() == &child &&
        child.get_parent() == &parent && parent.is_ancestor_of(&child),
        "both sides of the hierarchy relationship are registered"
    );
    success &= require(
        !parent.set_parent(&child),
        "hierarchy cycles are rejected"
    );

    const Transform requested_world{{40.0f, 50.0f}, {9.0f, 7.0f}, {120.0f, 3.0f}};
    child.set_world_transform(requested_world);
    child_world = child.get_world_transform();
    success &= require(
        nearly_equal(child_world.pos.x, requested_world.pos.x) &&
        nearly_equal(child_world.pos.y, requested_world.pos.y) &&
        nearly_equal(child_world.rotation.x, requested_world.rotation.x) &&
        nearly_equal(child_world.rotation.y, requested_world.rotation.y),
        "setting world space converts back to parent-local space"
    );
    success &= require(
        child.set_parent(nullptr, true) && !child.has_parent() &&
        nearly_equal(child.transform.pos.x, requested_world.pos.x) &&
        nearly_equal(child.transform.pos.y, requested_world.pos.y),
        "detaching can preserve the world transform"
    );

    Object surviving_child(Transform{{3.0f, 4.0f}, {2.0f, 2.0f}});
    Transform world_before_parent_destruction;
    {
        Object temporary_parent(Transform{{20.0f, 30.0f}, {1.0f, 1.0f}, {45.0f, 0.0f}});
        surviving_child.set_parent(&temporary_parent, false);
        world_before_parent_destruction = surviving_child.get_world_transform();
    }
    const Transform world_after_parent_destruction = surviving_child.get_world_transform();
    success &= require(
        !surviving_child.has_parent() &&
        nearly_equal(world_before_parent_destruction.pos.x, world_after_parent_destruction.pos.x) &&
        nearly_equal(world_before_parent_destruction.pos.y, world_after_parent_destruction.pos.y) &&
        nearly_equal(world_before_parent_destruction.rotation.x, world_after_parent_destruction.rotation.x),
        "destroying a parent safely detaches children and preserves world space"
    );

    Object hit_test_child(Transform{{10.0f, 10.0f}, {20.0f, 20.0f}});
    Object hit_test_parent(Transform{{100.0f, 50.0f}, {1.0f, 1.0f}});
    hit_test_child.set_parent(&hit_test_parent, false);
    success &= require(
        hit_test_child.on_hover({115.0f, 65.0f}) &&
        !hit_test_child.on_hover({15.0f, 15.0f}) &&
        nearly_equal(hit_test_child.make_draw_command().transform.pos.x, 110.0f),
        "render commands and pointer hit tests use world space"
    );

    Object physics_parent(Transform{{50.0f, 60.0f}, {1.0f, 1.0f}, {90.0f, 0.0f}});
    Object physics_child(Transform{{4.0f, 0.0f}, {10.0f, 12.0f}});
    physics_child.set_parent(&physics_parent, false);
    Physics::Collision_Body physics_body(&physics_child);
    const Transform collision_world = physics_body.collision_transform();
    success &= require(
        nearly_equal(collision_world.pos.x, 50.0f) &&
        nearly_equal(collision_world.pos.y, 64.0f) &&
        nearly_equal(collision_world.rotation.x, 90.0f),
        "attached physics bodies read the composed world transform"
    );
    Physics::Physics_Engine physics_world;
    physics_world.add_body(&physics_body);
    physics_body.set_body_type(Physics::Body_Type::KINEMATIC);
    physics_body.velocity = {10.0f, 0.0f};
    physics_world.step(1.0f);
    const Transform moved_collision_world = physics_body.collision_transform();
    success &= require(
        nearly_equal(moved_collision_world.pos.x, 60.0f) &&
        nearly_equal(moved_collision_world.pos.y, 64.0f),
        "physics velocity remains world-aligned below a rotated parent"
    );

    Object ui_parent(Transform{{100.0f, 20.0f}, {1.0f, 1.0f}});
    Slider child_slider({10.0f, 5.0f}, {20.0f, 10.0f}, 0.0f, 1.0f, 0.0f);
    child_slider.set_parent(&ui_parent, false);
    success &= require(
        nearly_equal(child_slider.value_at({120.0f, 30.0f}), 0.5f) &&
        nearly_equal(child_slider.thumb_center().x, 110.0f),
        "parented UI geometry reads world-space pointer coordinates"
    );

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
