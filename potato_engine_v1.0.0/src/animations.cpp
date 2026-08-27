#include "animations.h"
#include <algorithm>


void Anim::start(float dur, float f, float t,
                 std::function<float(float)> ease,
                 std::function<void(float)>  apply_fn,
                 std::function<void()>       done_fn) {
    duration = dur;
    elapsed  = 0.0f;
    running  = true;
    from_val = f;
    to_val   = t;
    ease_fn  = std::move(ease);
    apply    = std::move(apply_fn);
    on_done  = std::move(done_fn);
    if (apply) apply(from_val);
}

void Anim::tick(float dt) {
    if (!running) return;
    elapsed += dt;
    float raw   = std::min(elapsed / duration, 1.0f);
    float eased = ease_fn ? ease_fn(raw) : raw;
    if (apply) apply(from_val + (to_val - from_val) * eased);
    if (elapsed >= duration) {
        running = false;
        if (on_done) on_done();
    }
}

void AnimGroup::tick(float dt) {
    bool all_done = true;
    for (auto& a : anims) {
        if (a.is_running()) {
            a.tick(dt);
            if (a.is_running()) all_done = false;
        }
    }
    if (all_done && !anims.empty() && on_done) {
        auto cb = std::move(on_done);
        on_done = nullptr;
        cb();
    }
}

bool AnimGroup::is_running() const {
    for (const auto& a : anims)
        if (a.is_running()) return true;
    return false;
}


Anim make_fade_in(Object* obj, float dur,
                  std::function<float(float)> ease,
                  std::function<void()>       on_done) {
    obj->set_texture_opacity(0.0f);
    obj->input_transparent = false;
    Anim a;
    a.start(dur, 0.0f, 1.0f, std::move(ease),
        [obj](float v) { obj->set_texture_opacity(std::max(0.0f, std::min(1.0f, v))); },
        std::move(on_done));
    return a;
}


Anim make_fade_out(Object* obj, float dur,
                   std::function<float(float)> ease,
                   std::function<void()>       on_done) {
    Anim a;
    a.start(dur, 1.0f, 0.0f, std::move(ease),
        [obj](float v) { obj->set_texture_opacity(std::max(0.0f, std::min(1.0f, v))); },
        [obj, cb = std::move(on_done)]() {
            obj->hide();
            if (cb) cb();
        });
    return a;
}


AnimGroup make_slide_in(Object* obj, Vec target_pos, Vec offset, float dur,
                        std::function<float(float)> ease,
                        std::function<void()>       on_done) {
    Vec start_pos = { target_pos.x + offset.x, target_pos.y + offset.y };
    obj->transform.pos = start_pos;
    obj->set_texture_opacity(0.0f);
    obj->input_transparent = false;

    AnimGroup g;
    Anim ax, ay, af;
    ax.start(dur, start_pos.x,  target_pos.x, ease,         [obj](float v){ obj->transform.pos.x = v; });
    ay.start(dur, start_pos.y,  target_pos.y, ease,         [obj](float v){ obj->transform.pos.y = v; });
    af.start(dur, 0.0f,         1.0f,         Ease::out_quad,
        [obj](float v){ obj->set_texture_opacity(std::max(0.0f, std::min(1.0f, v))); });
    g.add(std::move(ax));
    g.add(std::move(ay));
    g.add(std::move(af));
    g.on_done = std::move(on_done);
    return g;
}


AnimGroup make_slide_out(Object* obj, Vec offset, float dur,
                         std::function<float(float)> ease,
                         std::function<void()>       on_done) {
    Vec start_pos = obj->transform.pos;
    Vec end_pos   = { start_pos.x + offset.x, start_pos.y + offset.y };

    AnimGroup g;
    Anim ax, ay, af;
    ax.start(dur, start_pos.x, end_pos.x, ease,         [obj](float v){ obj->transform.pos.x = v; });
    ay.start(dur, start_pos.y, end_pos.y, ease,         [obj](float v){ obj->transform.pos.y = v; });
    af.start(dur, 1.0f,        0.0f,      Ease::in_quad,
        [obj](float v){ obj->set_texture_opacity(std::max(0.0f, std::min(1.0f, v))); },
        [obj, cb = std::move(on_done)]() {
            obj->hide();
            if (cb) cb();
        });
    g.add(std::move(ax));
    g.add(std::move(ay));
    g.add(std::move(af));
    g.on_done = std::move(on_done);
    return g;
}

void StaggeredSlideIn::add(Object* obj, Vec target_pos, Vec offset, float dur, float delay,
                           std::function<float(float)> ease) {
    Entry e;
    e.obj        = obj;
    e.target_pos = target_pos;
    e.offset     = offset;
    e.dur        = dur;
    e.delay      = delay;
    e.ease       = std::move(ease);
    Vec start_pos = { target_pos.x + offset.x, target_pos.y + offset.y };
    obj->transform.pos = start_pos;
    obj->set_texture_opacity(0.0f);
    obj->input_transparent = true;
    entries.push_back(std::move(e));
}

void StaggeredSlideIn::start() {
    _active = true;
    for (auto& e : entries) {
        e.elapsed_delay = 0.0f;
        e.started       = false;
        Vec start_pos = { e.target_pos.x + e.offset.x, e.target_pos.y + e.offset.y };
        e.obj->transform.pos = start_pos;
        e.obj->set_texture_opacity(0.0f);
        e.obj->input_transparent = true;
    }
}

void StaggeredSlideIn::tick(float dt) {
    if (!_active) return;
    bool all_done = true;
    for (auto& e : entries) {
        if (!e.started) {
            e.elapsed_delay += dt;
            if (e.elapsed_delay >= e.delay) {
                e.started = true;
                e.group   = make_slide_in(e.obj, e.target_pos, e.offset, e.dur, e.ease);
            } else {
                all_done = false;
                continue;
            }
        }
        if (e.group.is_running()) {
            e.group.tick(dt);
            if (e.group.is_running()) all_done = false;
        }
    }
    if (all_done && !entries.empty()) {
        _active = false;
        if (on_done) on_done();
    }
}