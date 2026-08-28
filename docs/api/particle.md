# Particle

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `particle.h`  
**Documented overloads:** 4

This page documents the engine-owned callables declared for `Particle`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Particle_Emitter emitter;
emitter.spawn_particle();
emitter.update(delta_seconds);
~~~

## Functions

### draw

~~~cpp
void Particle::draw(SDL_Renderer *renderer)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws the particle using its texture at its current position and size.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `renderer` | `SDL_Renderer *` | The SDL renderer to draw with. | — |


---

### is_alive

~~~cpp
bool Particle::is_alive() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the particle is still alive (i.e., its lifetime is greater than zero).

**Parameters:** None.

---

### Particle

~~~cpp
Particle::Particle(Vec pos, Vec psize, Texture *tex, Vec vel, float lifetime, ParticlePattern pattern, Vec origin, float angle, float orbit_radius, float orbit_speed)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Particle with the specified properties.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `Vec` | Initial position of the particle. | — |
| `psize` | `Vec` | Size of the particle. | — |
| `tex` | `Texture *` | Pointer to the texture to render for this particle. | — |
| `vel` | `Vec` | Initial velocity of the particle. | — |
| `lifetime` | `float` | How long the particle should live (in seconds). | — |
| `pattern` | `ParticlePattern` | The movement pattern for the particle. | — |
| `origin` | `Vec` | The origin point for orbiting or attracting patterns. | — |
| `angle` | `float` | Initial angle for orbiting or spiral patterns. | — |
| `orbit_radius` | `float` | Radius for orbiting or spiral patterns. | — |
| `orbit_speed` | `float` | Angular speed for orbiting or spiral patterns. | — |


---

### update

~~~cpp
void Particle::update(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the particle's position and state based on its movement pattern and elapsed time.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `dt` | `float` | Time elapsed since the last update (in seconds). | — |


