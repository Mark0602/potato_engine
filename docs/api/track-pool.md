# Track_Pool

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `audio.h`  
**Documented overloads:** 26

This page documents the engine-owned callables declared for `Track_Pool`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Usage example

~~~cpp
Audio music;
music.load("assets/audio/theme.ogg");
music.set_loop_count(-1);
music.play();
~~~

## Functions

### ~Track_Pool

~~~cpp
Track_Pool::~Track_Pool()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

---

### create_new_default_track

~~~cpp
void Track_Pool::create_new_default_track()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Creates a new default track and adds it to the pool.

**Parameters:** None.

---

### create_new_dynamic_track

~~~cpp
ITrack * Track_Pool::create_new_dynamic_track(uint32_t lifetime=5000)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `ITrack *`

Creates a new dynamic track and adds it to the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### flush_tracks

~~~cpp
void Track_Pool::flush_tracks(float dt)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates all tracks in the pool, applying their properties and managing their lifetimes.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_default_track_count

~~~cpp
uint8_t Track_Pool::get_default_track_count() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `uint8_t`

Gets the number of default tracks currently in the pool.

**Parameters:** None.

---

### get_dynamic_track_lifetime

~~~cpp
uint32_t Track_Pool::get_dynamic_track_lifetime(size_t index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `uint32_t`

Gets the lifetime of a dynamic track in frames.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### get_free_track

~~~cpp
ITrack * Track_Pool::get_free_track()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `ITrack *`

Gets a free track from the pool. If no free tracks are available, a new dynamic track is created.

**Parameters:** None.

---

### get_mixer

~~~cpp
MIX_Mixer * Track_Pool::get_mixer() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `MIX_Mixer *`

Gets the SDL_Mixer instance used by this pool.

**Parameters:** None.

---

### get_total_track_count

~~~cpp
uint8_t Track_Pool::get_total_track_count() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `uint8_t`

Gets the total number of tracks currently in the pool, including both default and dynamic tracks.

**Parameters:** None.

---

### get_track

~~~cpp
ITrack * Track_Pool::get_track(size_t index) const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `ITrack *`

Gets the track at the specified index in the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### init

~~~cpp
bool Track_Pool::init(MIX_Mixer *mixer, uint8_t default_track_count=8, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Constructs a Audio value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |


---

### operator=

~~~cpp
Track_Pool & Track_Pool::operator=(const Track_Pool &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Track_Pool &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
Track_Pool & Track_Pool::operator=(Track_Pool &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Track_Pool &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### release_track

~~~cpp
void Track_Pool::release_track(ITrack *track)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Releases a track back to the pool, making it available for reuse.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `track` | `ITrack *` | Pointer to the track to release. | — |


---

### set_default_track_count

~~~cpp
void Track_Pool::set_default_track_count(uint8_t count)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the number of default tracks to maintain in the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_dynamic_track_lifetime

~~~cpp
void Track_Pool::set_dynamic_track_lifetime(size_t index, uint32_t lifetime)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the lifetime of a dynamic track in frames.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_fps

~~~cpp
void Track_Pool::set_fps(float fps)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the frames per second (FPS) value used for lifetime calculations of dynamic tracks.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_logger

~~~cpp
void Track_Pool::set_logger(Logger *logger)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the logger to be used for logging messages from the track pool.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Pointer to the Logger instance to use for logging. If nullptr, logging will be disabled. | — |


---

### set_master_gain

~~~cpp
void Track_Pool::set_master_gain(float gain)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the master gain (volume) for all tracks in the pool.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_mixer

~~~cpp
void Track_Pool::set_mixer(MIX_Mixer *mixer)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the SDL_Mixer instance to be used for audio playback.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### shutdown

~~~cpp
void Track_Pool::shutdown()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

---

### Track_Pool

~~~cpp
Track_Pool::Track_Pool() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

---

### Track_Pool

~~~cpp
Track_Pool::Track_Pool(const Track_Pool &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Track_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Track_Pool

~~~cpp
Track_Pool::Track_Pool(MIX_Mixer *mixer, uint8_t default_track_count=8, Logger *logger=nullptr)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Track_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Value supplied for the logger parameter. | — |


---

### Track_Pool

~~~cpp
Track_Pool::Track_Pool(Track_Pool &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Track_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### update_track

~~~cpp
void Track_Pool::update_track(ITrack *track, const Audio_Props &props)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Updates the properties of a track.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `track` | `ITrack *` | Pointer to the track to update. | — |
| `props` | `const Audio_Props &` | The new properties to apply to the track. | — |



