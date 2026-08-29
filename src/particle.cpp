#include "particle.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>

static constexpr float TAU = 6.28318530f;

Particle::Particle(Vec pos, Vec psize, Texture* tex,
                   Vec vel, float lifetime,
                   ParticlePattern pattern,
                   Vec origin,
                   float angle, float orbit_radius, float orbit_speed)
    : Object(pos, psize, Vec(angle, 0.0f), tex),
      vel(vel), lifetime(lifetime), max_lifetime(lifetime),
      pattern(pattern), origin(origin),
      angle(angle), orbit_radius(orbit_radius), orbit_speed(orbit_speed),
      wander_timer(0.0f)
{}

void Particle::update(float dt) {
    lifetime -= dt;
    if (lifetime <= 0.0f) return;

    switch (pattern) {

    case ParticlePattern::BURST:
        transform.pos += vel * dt;
        break;

    case ParticlePattern::ORBIT:
        angle += orbit_speed * dt;
        transform.pos.x = origin.x + std::cos(angle) * orbit_radius - transform.size.x * 0.5f;
        transform.pos.y = origin.y + std::sin(angle) * orbit_radius - transform.size.y * 0.5f;
        break;

    case ParticlePattern::SPIRAL: {
        angle += orbit_speed * dt;
        float t = 1.0f - (lifetime / max_lifetime);
        float r = orbit_radius * (1.0f + t * 2.5f);
        transform.pos.x = origin.x + std::cos(angle) * r - transform.size.x * 0.5f;
        transform.pos.y = origin.y + std::sin(angle) * r - transform.size.y * 0.5f;
        break;
    }

    case ParticlePattern::ATTRACT: {
        Vec to_origin = origin - transform.pos;
        float len = std::sqrt(to_origin.x * to_origin.x + to_origin.y * to_origin.y);
        if (len > 1.0f) {
            float t = 1.0f - (lifetime / max_lifetime);
            float strength = 50.0f + t * 350.0f;
            vel.x = (to_origin.x / len) * strength;
            vel.y = (to_origin.y / len) * strength;
        }
        transform.pos += vel * dt;
        break;
    }

    case ParticlePattern::RAIN:
        vel.y += 220.0f * dt;
        transform.pos += vel * dt;
        break;

    case ParticlePattern::WANDER:
        wander_timer -= dt;
        if (wander_timer <= 0.0f) {
            float new_angle = static_cast<float>(std::rand()) / RAND_MAX * TAU;
            vel.x = std::cos(new_angle) * 80.0f;
            vel.y = std::sin(new_angle) * 80.0f;
            wander_timer = 0.10f + (static_cast<float>(std::rand()) / RAND_MAX) * 0.25f;
        }
        transform.pos += vel * dt;
        break;
    }
}

void Particle::draw(SDL_Renderer* renderer) {
    if (!texture || !texture->is_loaded() || lifetime <= 0.0f) return;

    float alpha = lifetime / max_lifetime;
    texture->set_texture_opacity(alpha);
    const Transform world = get_world_transform();
    texture->draw(renderer, world.pos, world.size, world.rotation);
    texture->set_texture_opacity(1.0f);
}

Particle_Emitter::Particle_Emitter(Vec pos, Vec particle_size,
                                   float radius, float duration,
                                   int max_particles, float emit_rate,
                                   float particle_lifetime,
                                   ParticlePattern pattern,
                                   std::vector<Texture*> textures,
                                   Logger* logger)
    : pos(pos), particle_size(particle_size),
      radius(radius), duration(duration),
      max_particles(max_particles), emit_rate(emit_rate),
      particle_lifetime(particle_lifetime),
      pattern(pattern), textures(std::move(textures)),
      rng(std::random_device{}()),
      logger(logger)
{}

void Particle_Emitter::update(float dt) {
    duration -= dt;

    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [dt](std::unique_ptr<Particle>& p) {
                p->update(dt);
                return !p->is_alive();
            }),
        particles.end()
    );

    if (duration > 0.0f) {
        emit_accum += emit_rate * dt;
        while (emit_accum >= 1.0f &&
               static_cast<int>(particles.size()) < max_particles) {
            spawn_particle();
            emit_accum -= 1.0f;
        }
    }
}

void Particle_Emitter::draw(SDL_Renderer* renderer) {
    for (auto& p : particles) {
        p->draw(renderer);
    }
}

void Particle_Emitter::spawn_particle() {
    if (textures.empty()) return;

    std::uniform_real_distribution<float> angle_dist(0.0f, TAU);
    std::uniform_real_distribution<float> r_dist(0.0f, radius);
    std::uniform_int_distribution<int>    tex_dist(0, static_cast<int>(textures.size()) - 1);
    std::uniform_real_distribution<float> speed_dist(50.0f, 160.0f);
    std::uniform_real_distribution<float> ospeed_dist(1.5f, 4.0f);
    std::uniform_int_distribution<int>    sign_dist(0, 1);

    float spawn_angle = angle_dist(rng);
    float spawn_r     = r_dist(rng);
    float ospeed      = (sign_dist(rng) ? 1.0f : -1.0f) * ospeed_dist(rng);

    // Spiral particles start close to the emitter.
    if (pattern == ParticlePattern::SPIRAL) {
        spawn_r = r_dist(rng) * 0.25f;
    }

    Vec spawn_pos = {
        pos.x + std::cos(spawn_angle) * spawn_r - particle_size.x * 0.5f,
        pos.y + std::sin(spawn_angle) * spawn_r - particle_size.y * 0.5f
    };

    Vec vel = {0.0f, 0.0f};
    switch (pattern) {
    case ParticlePattern::BURST: {
        float speed = speed_dist(rng);
        vel = { std::cos(spawn_angle) * speed, std::sin(spawn_angle) * speed };
        break;
    }
    case ParticlePattern::ATTRACT: {
        // Start near the perimeter with a small outward velocity; ATTRACT pulls it back.
        float speed = speed_dist(rng) * 0.3f;
        vel = { std::cos(spawn_angle) * speed, std::sin(spawn_angle) * speed };
        break;
    }
    case ParticlePattern::RAIN: {
        std::uniform_real_distribution<float> horiz(-35.0f, 35.0f);
        vel = { horiz(rng), speed_dist(rng) * 0.35f };
        break;
    }
    case ParticlePattern::WANDER: {
        float speed = speed_dist(rng) * 0.5f;
        vel = { std::cos(spawn_angle) * speed, std::sin(spawn_angle) * speed };
        break;
    }
    default:
        break;
    }

    Texture* tex = textures[tex_dist(rng)];

    auto p = std::make_unique<Particle>(
        spawn_pos, particle_size, tex,
        vel, particle_lifetime,
        pattern, pos,
        spawn_angle, spawn_r, ospeed
    );

    if (pattern == ParticlePattern::WANDER) {
        p->wander_timer = (static_cast<float>(std::rand()) / RAND_MAX) * 0.3f;
    }

    particles.push_back(std::move(p));
}

