# Audio

**Engine version:** Potato Engine 1.0.0  
**Declaration header:** `audio.h`  
**Documented overloads:** 35

This page documents the engine-owned callables declared for `Audio`. Exact signatures, access levels, return types, parameters, defaults, descriptions, and per-function engine versions are preserved from the source reference.

## Detailed workflow example

~~~cpp
Audio jump_sound;
jump_sound.load("assets/audio/jump.wav", true);
jump_sound.set_gain(0.75f);
jump_sound.set_pitch(1.0f);

if (jump_sound.is_loaded()) {
    jump_sound.force_play();
}
~~~

## Usage example

~~~cpp
Audio music;
music.load("assets/audio/theme.ogg");
music.set_loop_count(-1);
music.play();
~~~

## Functions

### ~Audio

~~~cpp
Audio::~Audio()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

This function belongs to the documented engine type. Its exact behavior, inputs, and result are described by the signature and metadata in this entry.

**Parameters:** None.

---

### Audio

~~~cpp
Audio::Audio() = default
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Audio value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

---

### Audio

~~~cpp
Audio::Audio(Audio &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Audio value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Audio

~~~cpp
Audio::Audio(const Audio &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs a Audio value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Audio

~~~cpp
Audio::Audio(const std::string &file_path, MIX_Mixer *mixer=nullptr, bool predecode=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an Audio object and loads the specified audio file.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### Audio

~~~cpp
Audio::Audio(const std::string &file_path, Track_Pool *track_pool, bool predecode=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public

Constructs an Audio object and loads the specified audio file, using a track pool for playback.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `track_pool` | `Track_Pool *` | Pointer to the Track_Pool instance to use for audio playback. If nullptr, the default mixer will be used. | — |


---

### detach_track

~~~cpp
void Audio::detach_track(ITrack *track)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Detaches the currently attached track from the audio instance.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `track` | `ITrack *` | Pointer to the track to detach. | — |


---

### force_pause

~~~cpp
void Audio::force_pause()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Forces the audio to pause, regardless of its current state. This function forcefully pauses the audio playback. Unlike the regular pause() function, which only sets the state to PAUSED, and then waits for the flush_tracks() to actually pause the audio, this function will immediately stop the audio playback and set the state to PAUSED. Use this function when you need to ensure that the audio is paused, regardless of its current state.

**Parameters:** None.

---

### force_play

~~~cpp
void Audio::force_play()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Forces the audio to play, regardless of its current state. This function forcefully starts the audio playback from the beginning, even if it is already playing or paused. Unlike the regular play() function, which only sets the state to PLAYING, and then waits for the flush_tracks() to actually start the audio, this function will immediately start the audio playback and set the state to PLAYING. Use this function when you need to ensure that the audio is playing, regardless of its current state.

**Parameters:** None.

---

### force_resume

~~~cpp
void Audio::force_resume()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Forces the audio to resume, regardless of its current state. This function forcefully resumes the audio playback, even if it is already playing or stopped. Unlike the regular resume() function, which only sets the state to RESUMED, and then waits for the flush_tracks() to actually resume the audio, this function will immediately resume the audio playback and set the state to RESUMED. Use this function when you need to ensure that the audio is resumed, regardless of its current state.

**Parameters:** None.

---

### force_stop

~~~cpp
void Audio::force_stop()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Forces the audio to stop, regardless of its current state. This function forcefully stops the audio playback. Unlike the regular stop() function, which only sets the state to STOPPED, and then waits for the flush_tracks() to actually stop the audio, this function will immediately stop the audio playback and set the state to STOPPED. Use this function when you need to ensure that the audio is stopped, regardless of its current state.

**Parameters:** None.

---

### get_duration

~~~cpp
Sint64 Audio::get_duration() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Sint64`

Gets the duration of the loaded audio file in milliseconds.

**Parameters:** None.

---

### get_mixer

~~~cpp
MIX_Mixer * Audio::get_mixer()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `MIX_Mixer *`

Gets the SDL_Mixer instance used for audio playback.

**Parameters:** None.

---

### get_props

~~~cpp
Audio_Props Audio::get_props() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Audio_Props`

Gets the properties of the audio file.

**Parameters:** None.

---

### is_loaded

~~~cpp
bool Audio::is_loaded() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if an audio file is currently loaded.

**Parameters:** None.

---

### is_playing

~~~cpp
bool Audio::is_playing() const
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `bool`

Checks if this audio instance is currently playing on a managed track.

**Parameters:** None.

---

### load

~~~cpp
void Audio::load(const std::string &file_path, bool predecode=true)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Loads an audio file into memory.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
Audio & Audio::operator=(Audio &&) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Audio &`

Constructs a ITrack value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### operator=

~~~cpp
Audio & Audio::operator=(const Audio &) = delete
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `Audio &`

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### pause

~~~cpp
void Audio::pause()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Pauses playback of the audio file if it is playing.

**Parameters:** None.

---

### play

~~~cpp
void Audio::play()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Plays the loaded audio file from the beginning, stopping any currently playing audio.

**Parameters:** None.

---

### play_fnf

~~~cpp
void Audio::play_fnf()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Plays the loaded audio file from the beginning, stopping any currently playing audio.

**Parameters:** None.

---

### resolve_engine_defaults

~~~cpp
void Audio::resolve_engine_defaults()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** private · **Returns:** `void`

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

---

### resume

~~~cpp
void Audio::resume()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Resumes playback of the audio file if it is paused.

**Parameters:** None.

---

### set_gain

~~~cpp
void Audio::set_gain(float gain)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the gain (volume) of the audio file.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_logger

~~~cpp
void Audio::set_logger(Logger *logger)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the logger to be used for logging messages from the Audio class.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `logger` | `Logger *` | Pointer to the Logger instance. | — |


---

### set_loop_count

~~~cpp
void Audio::set_loop_count(int loop_count)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the the loop count of the audio file.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_mixer

~~~cpp
void Audio::set_mixer(MIX_Mixer *new_mixer)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the SDL_Mixer instance to be used for audio playback.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_panning

~~~cpp
void Audio::set_panning(float panning)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the panning of the audio file.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_pitch

~~~cpp
void Audio::set_pitch(float pitch)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the pitch of the audio file.

**Parameters:** The declaration uses an unnamed parameter; its exact type is shown in the signature.


---

### set_position

~~~cpp
void Audio::set_position(const Vec3 &position)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the 3D position of the audio file.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `position` | `const Vec3 &` | The 3D position of the audio source. | — |


---

### set_props

~~~cpp
void Audio::set_props(const Audio_Props &props)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the properties of the audio file.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `props` | `const Audio_Props &` | The new properties to set. | — |


---

### set_track_pool

~~~cpp
void Audio::set_track_pool(Track_Pool *track_pool)
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Sets the track pool to be used for audio playback.

**Parameters**

| Name | Type | Description | Default |
| --- | --- | --- | --- |
| `track_pool` | `Track_Pool *` | Pointer to the Track_Pool instance. | — |


---

### stop

~~~cpp
void Audio::stop()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Stops playback of the audio file.

**Parameters:** None.

---

### unload

~~~cpp
void Audio::unload()
~~~

> **Engine version:** Potato Engine 1.0.0
>
> **Access:** public · **Returns:** `void`

Unloads the currently loaded audio file from memory.

**Parameters:** None.

