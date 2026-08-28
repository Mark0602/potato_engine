# Particle_Emitter

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `particle.h`  
**Documented overloads:** 7

This page documents the engine-owned callables declared for `Particle_Emitter`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Particle_Emitter emitter;
emitter.spawn_particle();
emitter.update(delta_seconds);
~~~

## Functions

### ~Particle_Emitter

~~~cpp
Particle_Emitter::~Particle_Emitter()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

---

### draw

~~~cpp
void Particle_Emitter::draw(SDL_Renderer *renderer)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Draws all active particles using the provided SDL renderer.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### free

~~~cpp
void Particle_Emitter::free()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Performs a rendering-stage operation using the current engine state. Invoke it only while the relevant renderer and frame context are initialized.

**Parameters:** None.

---

### is_alive

~~~cpp
bool Particle_Emitter::is_alive() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if the emitter is still active (either has remaining duration or active particles).

**Parameters:** None.

---

### Particle_Emitter

~~~cpp
Particle_Emitter::Particle_Emitter(Vec pos, Vec particle_size, float radius, float duration, int max_particles, float emit_rate, float particle_lifetime, ParticlePattern pattern, std::vector< Texture * > textures, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Particle_Emitter with the specified properties.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `pos` | `Vec` | Position of the emitter in logical coordinates. | — |
| `particle_size` | `Vec` | Size of each spawned particle. | — |
| `pattern` | `ParticlePattern` | Movement pattern for the spawned particles. | — |
| `textures` | `std::vector< Texture * >` | List of textures to randomly assign to spawned particles. | — |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |


---

### spawn_particle

~~~cpp
void Particle_Emitter::spawn_particle()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters:** None.

---

### update

~~~cpp
void Particle_Emitter::update(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the emitter and its particles.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


