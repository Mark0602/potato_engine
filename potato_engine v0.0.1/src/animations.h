#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "vec.h"
#include "texture.h"
#include "object.h"
#include "particle.h"
#include <functional>
#include <vector>
#include <cmath>

/**
 * @brief A namespace containing various easing functions for animations.
 * Easing functions are mathematical functions that control the rate of change of a parameter over time.
 * These functions can be used to create smooth and visually appealing animations by adjusting the speed of transitions.
 * The functions provided in this namespace include linear, quadratic, cubic, back, and elastic easing
 * functions, each with different characteristics for controlling the animation's acceleration and deceleration.
 * You can use these easing functions when creating animations to achieve different visual effects.
 */
namespace Ease {
    inline float linear       (float t) { return t; }
    inline float in_quad      (float t) { return t * t; }
    inline float out_quad     (float t) { return t * (2.0f - t); }
    inline float in_out_quad  (float t) { return t < 0.5f ? 2.0f*t*t : -1.0f + (4.0f - 2.0f*t)*t; }
    inline float out_cubic    (float t) { float u = 1.0f - t; return 1.0f - u*u*u; }
    
    /**
     * @brief Easing function that creates a "back" effect, where the animation overshoots and then returns to the target value.
     * This function is useful for creating animations that have a sense of elasticity or bounce.
     * @param t A normalized time value between 0 and 1, representing the progress of the animation.
     * @return A float value representing the eased progress of the animation, with overshoot and return behavior.
     */
    inline float out_back     (float t) {
        constexpr float c = 1.70158f;
        float u = t - 1.0f;
        return 1.0f + u*u*((c + 1.0f)*u + c);
    }

    /**
     * @brief Easing function that creates an "elastic" effect, where the animation oscillates before settling.
     * This function is useful for creating animations that have a spring-like or bouncy behavior.
     * @param t A normalized time value between 0 and 1, representing the progress of the animation.
     * @return A float value representing the eased progress of the animation, with oscillation and settling behavior.
     */
    inline float out_elastic  (float t) {
        if (t == 0.0f || t == 1.0f) return t;
        return std::pow(2.0f, -10.0f * t)
             * std::sin((t * 10.0f - 0.75f) * (2.0f * 3.14159265f / 3.0f))
             + 1.0f;
    }
}

/**
 * @brief Represents a single animation that interpolates a value over time.
 * The Anim struct allows you to define an animation that transitions a value from `from_val` to `to_val`
 * over a specified duration, using an optional easing function. You can provide a callback to apply
 * the interpolated value and another callback to be invoked when the animation is complete.
 */
struct Anim {
    float duration = 0.0f;
    float elapsed  = 0.0f;
    bool  running  = false;
    float from_val = 0.0f;
    float to_val   = 1.0f;
    std::function<float(float)> ease_fn;
    std::function<void(float)>  apply;
    std::function<void()>       on_done;

    void start(float dur, float f, float t,
               std::function<float(float)> ease,
               std::function<void(float)>  apply_fn,
               std::function<void()>       done_fn = nullptr);

    void tick(float dt);

    bool  is_running() const { return running; }
    float progress()   const { return duration > 0.0f ? elapsed / duration : 1.0f; }
};

/**
 * @brief A group of Anim objects that can be ticked together.
 * An AnimGroup allows you to manage multiple animations simultaneously,
 * and provides a callback when all animations in the group have completed.
 * You can add Anim objects to the group using the `add` method, and tick them
 * together using the `tick` method. The `on_done` callback will be invoked
 * when all animations in the group have finished running.
 */
struct AnimGroup {
    std::vector<Anim>     anims;
    std::function<void()> on_done;

    /**
     * @brief Adds an Anim to the group.
     * @param a The Anim to add to the group.
     */
    void add(Anim a) { anims.push_back(std::move(a)); }

    /**
     * @brief Ticks all Anim objects in the group by the specified delta time.
     * If all Anim objects have completed, the `on_done` callback will be invoked.
     * @param dt The delta time to tick the animations by, in seconds.
     */
    void tick(float dt);

    bool is_running() const;
};

/**
 * @brief Creates an Anim that fades an object in.
 * The object's opacity will be increased from 0 to 1 over the specified duration.
 * @param obj Pointer to the Object to animate.
 * @param dur Duration of the animation in seconds.
 * @param ease Easing function to use for the animation. Defaults to Ease::out_quad.
 * @param on_done Optional callback to invoke when the animation is complete.
 * @return An Anim representing the fade-in animation.
 */
Anim make_fade_in (Object* obj, float dur,
                   std::function<float(float)> ease    = Ease::out_quad,
                   std::function<void()>       on_done = nullptr);

/**
 * @brief Creates an Anim that fades an object out and hides it.
 * The object's opacity will be reduced from 1 to 0 over the specified duration.
 * After the animation completes, the object will be hidden and its opacity will be reset to 1.
 * @param obj Pointer to the Object to animate.
 * @param dur Duration of the animation in seconds.
 * @param ease Easing function to use for the animation. Defaults to Ease::in_quad.
 * @param on_done Optional callback to invoke when the animation is complete.
 * @return An Anim representing the fade-out animation.
 */
Anim make_fade_out(Object* obj, float dur,
                   std::function<float(float)> ease    = Ease::in_quad,
                   std::function<void()>       on_done = nullptr);

/**
 * @brief Creates an AnimGroup that slides an object into view and fades it in.
 * The object will be moved from (target_pos + offset) to target_pos over the specified duration,
 * and its opacity will be increased from 0 to 1. After the animation completes,
 * the object will be fully visible and interactive.
 * @param obj Pointer to the Object to animate.
 * @param target_pos The final position of the object after the slide-in animation.
 * @param offset The offset to apply to the target position for the starting position of the slide-in effect.
 * @param dur Duration of the animation in seconds.
 * @param ease Easing function to use for the animation. Defaults to Ease::out_back.
 * @param on_done Optional callback to invoke when the animation is complete.
 * @return An AnimGroup representing the slide-in animation.
 */
AnimGroup make_slide_in (Object* obj, Vec target_pos, Vec offset, float dur,
                         std::function<float(float)> ease    = Ease::out_back,
                         std::function<void()>       on_done = nullptr);

/**
 * @brief Creates an AnimGroup that slides an object out of view and fades it out.
 * The object will be moved to (current position + offset) over the specified duration,
 * and its opacity will be reduced to 0. After the animation completes, the object will be hidden.
 * @param obj Pointer to the Object to animate.
 * @param offset The offset to apply to the object's current position for the slide-out effect.
 * @param dur Duration of the animation in seconds.
 * @param ease Easing function to use for the animation. Defaults to Ease::in_quad.
 * @param on_done Optional callback to invoke when the animation is complete.
 * @return An AnimGroup representing the slide-out animation.
 */
AnimGroup make_slide_out(Object* obj, Vec offset, float dur,
                         std::function<float(float)> ease    = Ease::in_quad,
                         std::function<void()>       on_done = nullptr);

/**
 * @brief A class that manages a sequence of slide-in animations for multiple objects with staggered delays.
 * The StaggeredSlideIn class allows you to add multiple objects to be animated with a
 * specified target position, offset, duration, and delay. Each object will start its slide-in animation
 * after the specified delay, creating a staggered effect. The class provides methods to add objects
 * to the sequence, start the animations, and tick the animations over time. You can also provide
 * a callback to be invoked when all animations in the sequence have completed.
 */
struct StaggeredSlideIn {
    struct Entry {
        Object*                     obj;
        Vec                         target_pos;
        Vec                         offset;
        float                       dur;
        float                       delay;
        float                       elapsed_delay = 0.0f;
        bool                        started       = false;
        std::function<float(float)> ease;
        AnimGroup                   group;
    };

    std::vector<Entry>    entries;
    std::function<void()> on_done;
    bool                  _active = false;

    void add(Object* obj, Vec target_pos, Vec offset, float dur, float delay, std::function<float(float)> ease = Ease::out_back);

    void start();

    void tick(float dt);

    bool is_running() const { return _active; }
};

#endif