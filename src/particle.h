#ifndef PARTICLE_H
#define PARTICLE_H

#include "object.h"
#include "vec.h"
#include "texture.h"
#include <vector>
#include <memory>
#include <random>
#include <cmath>

/**
 * @brief Particle movement patterns used by Particle_Emitter.
 * @param BURST: Particles move outward in a burst from the emitter position.
 * @param ORBIT: Particles orbit around the emitter position.
 * @param SPIRAL: Particles move in a spiral pattern around the emitter position.
 * @param ATTRACT: Particles are attracted towards a point.
 * @param RAIN: Particles fall downwards like rain.
 * @param WANDER: Particles move in a random wandering pattern.
 */
enum class ParticlePattern {
    BURST,
    ORBIT,
    SPIRAL,
    ATTRACT,
    RAIN,
    WANDER
};

/**
 * @brief A particle represents a single moving object with a texture, position, velocity, and lifetime.
 * 
 * Particles are managed by a Particle_Emitter, which spawns and updates them according to a specified pattern.
 * 
 */
struct Particle : Object {
    Vec   vel;           
    float lifetime;      
    float max_lifetime;
    ParticlePattern pattern;

    Vec   origin;
    float angle;
    float orbit_radius;
    float orbit_speed;
    float wander_timer;

    /**
     * @brief Constructs a Particle with the specified properties.
     * @param pos           Initial position of the particle.
     * @param psize         Size of the particle.
     * @param tex           Pointer to the texture to render for this particle.
     * @param vel           Initial velocity of the particle.
     * @param lifetime      How long the particle should live (in seconds).
     * @param pattern       The movement pattern for the particle.
     * @param origin        The origin point for orbiting or attracting patterns.
     * @param angle         Initial angle for orbiting or spiral patterns.
     * @param orbit_radius  Radius for orbiting or spiral patterns.
     * @param orbit_speed   Angular speed for orbiting or spiral patterns.
     */
    Particle(Vec pos, Vec psize, Texture* tex,
             Vec vel, float lifetime,
             ParticlePattern pattern,
             Vec origin,
             float angle, float orbit_radius, float orbit_speed);

    /**
     * @brief Updates the particle's position and state based on its movement pattern and elapsed time.
     * @param dt Time elapsed since the last update (in seconds).
     */
    void update(float dt);
    
    /**
     * @brief Draws the particle using its texture at its current position and size.
     * @param renderer The SDL renderer to draw with.
     */
    void draw(SDL_Renderer* renderer);

    /**
     * @brief Checks if the particle is still alive (i.e., its lifetime is greater than zero).
     * @return `true` if the particle is alive; `false` otherwise.
     */
    bool is_alive() const { return lifetime > 0.0f; }
};

/**
 * @brief A particle emitter spawns a specified number of particles around its position within a given radius for a certain duration.
 *
 * The `duration` specifies how long the emitter is active, during which it spawns `emit_rate` particles per second (up to `max_particles` active at once).
 * The particles move according to the specified `pattern` and randomly receive a texture from the provided list.
 *
 * Usage (from script):
 * ```cpp
 * // on_start():
 * emitter = std::make_unique<Particle_Emitter>(
 *     Vec{400, 300},   // emitter position
 *     Vec{12, 12},     // particle size
 *     80.0f,           // spawn radius (r)
 *     4.0f,            // emitter duration (s)
 *     40,              // max concurrent particles
 *     12.0f,           // spawn rate (particles/s)
 *     1.5f,            // particle lifetime (s)
 *     ParticlePattern::ORBIT,
 *     { &tex1, &tex2 }
 * );
 *
 * // on_update(dt):  emitter->update(dt);
 * // on_render():    emitter->draw(Engine::renderer);
 * ```
 */
class Particle_Emitter {
public:
    /**
     * @brief Constructs a Particle_Emitter with the specified properties.
     * @param pos               Position of the emitter in logical coordinates.
     * @param particle_size     Size of each spawned particle.
     * @param radius            Radius around the emitter position to spawn particles.
     * @param duration          How long the emitter should emit particles (in seconds).
     * @param max_particles     Maximum number of active particles at once.
     * @param emit_rate         Number of particles to spawn per second.
     * @param particle_lifetime Lifetime of each particle (in seconds).
     * @param pattern           Movement pattern for the spawned particles.
     * @param textures          List of textures to randomly assign to spawned particles.
     */
    Particle_Emitter(Vec pos, Vec particle_size,
                     float radius, float duration,
                     int max_particles, float emit_rate,
                     float particle_lifetime,
                     ParticlePattern pattern,
                     std::vector<Texture*> textures, Logger* logger = nullptr);

    ~Particle_Emitter() {
        free();
    };

    /**
     * @brief Updates the emitter and its particles.
     * @param dt Time elapsed since the last update (in seconds).
     */
    void update(float dt);

    /**
     * @brief Draws all active particles using the provided SDL renderer.
     * @param renderer The SDL renderer to draw with.
     */
    void draw(SDL_Renderer* renderer);

    /**
     * @brief Checks if the emitter is still active (either has remaining duration or active particles).
     * @return `true` if the emitter is still active; `false` otherwise.
     */
    bool is_alive() const { return duration > 0.0f || !particles.empty(); }

    void free() {
        if (m_free_number == 0) {
            for (auto& p : particles) {
                if (p) {
                    p->free();
                }
            }
            particles.clear();
            m_free_number = 1;
            if (logger) logger->log(Log_Level::DEBUG, "Particle_Emitter", "Particle_Emitter freed successfully.");
        } else if (m_free_number == 1) {
            if (logger) logger->log(Log_Level::WARNING, "Particle_Emitter", "Attempted to free an already freed Particle_Emitter. Double-free protection triggered.");
            m_free_number = 2;
        } else {
            if (logger) logger->log(Log_Level::ERROR, "Particle_Emitter", "Double-free protection triggered multiple times. Emitter may have been deleted twice.");
        }
    }

    Vec pos;

private:
    Vec   particle_size;
    float radius;
    float duration;
    int   max_particles;
    float emit_rate;
    float particle_lifetime;
    ParticlePattern pattern;
    std::vector<Texture*> textures;

    Logger* logger = nullptr;

    float emit_accum = 0.0f;
    std::mt19937 rng;
    std::vector<std::unique_ptr<Particle>> particles;

    uint8_t m_free_number = 0; // double freeing protection: 0 = not freed, 1 = freed once, 2 = freed twice

    void spawn_particle();
};

#endif