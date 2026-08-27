# Animation, particles, and timers

## Easing

The `Ease` namespace supplies normalized easing functions for `t` in `[0, 1]`:

- `linear`;
- `in_quad`, `out_quad`, and `in_out_quad`;
- `out_cubic`;
- overshooting `out_back`;
- oscillating `out_elastic`.

They are plain functions and can be used anywhere a `std::function<float(float)>` is accepted.

## Value animation

`Anim` interpolates one float from `from_val` to `to_val` over a duration. `start()` receives the easing function, an `apply(value)` callback, and an optional completion callback. Call `tick(dt)` with seconds while it is running.

```cpp
Anim fade;
fade.start(
    0.25f, 0.0f, 1.0f, Ease::out_quad,
    [&object](float alpha) { object.set_texture_opacity(alpha); },
    [] { /* complete */ }
);
```

`progress()` reports elapsed/duration and `is_running()` reports active state. `AnimGroup` ticks multiple animations together and calls its own `on_done` after every member finishes.

## Object transitions

Convenience builders create correctly configured animations:

- `make_fade_in` shows and fades an object to full opacity;
- `make_fade_out` fades, hides, and restores base opacity for reuse;
- `make_slide_in` moves from an offset to a target while fading in;
- `make_slide_out` moves by an offset while fading out and hiding.

The caller owns and ticks the returned `Anim` or `AnimGroup`. These helpers borrow the object, so it must outlive the animation.

`StaggeredSlideIn` schedules multiple slide-in groups with individual delays. Add entries, set optional `on_done`, call `start()`, then `tick(dt)` until `is_running()` becomes false.

## Particles

`Particle` derives from `Object` and adds velocity, lifetime, origin, orbit state, and a movement pattern. `Particle_Emitter` owns active particles and randomly assigns one of its borrowed textures.

Available `ParticlePattern` values are:

- `BURST`: outward motion;
- `ORBIT`: rotation around the origin;
- `SPIRAL`: changing radial orbit;
- `ATTRACT`: motion toward the origin;
- `RAIN`: downward motion;
- `WANDER`: randomized direction changes.

```cpp
Particle_Emitter emitter(
    {400.0f, 300.0f}, {8.0f, 8.0f},
    32.0f, 2.0f,
    100, 30.0f, 1.5f,
    ParticlePattern::BURST,
    {particle_texture}, Engine::logger
);

void update(float dt) { emitter.update(dt); }
void render() { emitter.draw(Engine::renderer); }
```

Constructor parameters define emitter position, particle size, spawn radius, emission duration, maximum live particles, rate per second, particle lifetime, pattern, textures, and optional logger. `is_alive()` remains true while emission time or live particles remain.

The emitter draws immediately rather than submitting to `Render_Pool`; call it from the appropriate render phase and account for ordering/lighting yourself. Its textures are borrowed and must outlive it.

## Timer

`Timer` is a reusable one-shot countdown. `start(duration, callback)` restarts it, `tick(dt)` advances it, and `stop()` resets it without calling the callback.

Queries include `is_running`, `is_just_done`, `elapsed`, `remaining`, and normalized `progress`. `is_just_done()` is true only immediately after the tick that completed the timer and is cleared by the next tick/start/stop.

Timers, animations, particles, camera following, physics, audio maintenance, and loading all use seconds. `Engine::delta_time` is the exceptional convenience value stored in milliseconds; script `on_update(dt)` already receives seconds and should normally be used instead.

