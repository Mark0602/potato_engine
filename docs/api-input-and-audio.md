# Input, Audio, and Localization API

**Engine version:** Potato Engine 1.0.0  
**Language:** C++

This reference lists every engine-owned function overload declared in the covered headers. Signatures preserve parameter types, names, default values, qualifiers, and namespaces from the source. Access labels identify members that are not part of the public calling surface.

## Detailed workflow example

~~~cpp
Input::bind_key("jump", SDL_SCANCODE_SPACE);
Input::bind_gamepad_button("jump", SDL_GAMEPAD_BUTTON_SOUTH);
Input::bind_axis_key("move_x", SDL_SCANCODE_A, -1.0f);
Input::bind_axis_key("move_x", SDL_SCANCODE_D, 1.0f);

Audio jump_sound;
jump_sound.load("assets/audio/jump.wav", true);
jump_sound.set_gain(0.75f);

if (!Input::is_blocked() && Input::action_pressed("jump")) {
    player_jump();
    jump_sound.force_play();
}

Localization text;
text.load("en-US", "assets/locales/en-US.json");
hud_label.set_text(text.format("hud.score", {std::to_string(score)}));
~~~

## input.h

### acquire_block

~~~cpp
bool Input::acquire_block(const void *owner)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Performs the acquire block operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `owner` (`const void *`): Value supplied for the owner parameter.

### action_down

~~~cpp
bool Input::action_down(const std::string &action_name)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether an action is currently held.

**Parameters**

- `action_name` (`const std::string &`): Name passed to a bind function.

### action_pressed

~~~cpp
bool Input::action_pressed(const std::string &action_name)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether an action was pressed this frame.

**Parameters**

- `action_name` (`const std::string &`): Name passed to a bind function.

### action_released

~~~cpp
bool Input::action_released(const std::string &action_name)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether an action was released this frame.

**Parameters**

- `action_name` (`const std::string &`): Name passed to a bind function.

### axis

~~~cpp
float Input::axis(const std::string &axis_name)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Gets the current value of a named axis.

**Parameters**

- `axis_name` (`const std::string &`): Name passed to an axis bind function.

### axis_delta

~~~cpp
float Input::axis_delta(const std::string &axis_name)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Gets how much a named axis changed since the previous frame.

**Parameters**

- `axis_name` (`const std::string &`): Name passed to an axis bind function.

### begin_frame

~~~cpp
void Input::begin_frame()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Starts a new input frame.

**Parameters:** None.

### bind_axis_gamepad_axis

~~~cpp
void Input::bind_axis_gamepad_axis(const std::string &axis_name, SDL_GamepadAxis axis, float scale=1.0f, float deadzone=0.15f, int gamepad_index=0)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Binds a gamepad analog axis to a named axis.

**Parameters**

- `axis_name` (`const std::string &`): Name of the axis.
- `axis` (`SDL_GamepadAxis`): SDL gamepad axis, e.g. SDL_GAMEPAD_AXIS_LEFTX.
- `scale` (`float`): Multiplier applied to the raw axis value.
- `deadzone` (`float`): Values below this magnitude become 0.
- `gamepad_index` (`int`): Index of the opened gamepad. Defaults to 0.

### bind_axis_key

~~~cpp
void Input::bind_axis_key(const std::string &axis_name, SDL_Scancode key, float scale)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Binds a keyboard key to a named analog axis.

**Parameters**

- `axis_name` (`const std::string &`): Name of the axis, e.g. "move_x".
- `key` (`SDL_Scancode`): SDL scancode to bind.
- `scale` (`float`): Axis contribution while the key is held.

### bind_gamepad_button

~~~cpp
void Input::bind_gamepad_button(const std::string &action_name, SDL_GamepadButton button, int gamepad_index=0)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Binds a gamepad button to a named digital action.

**Parameters**

- `action_name` (`const std::string &`): Name of the action.
- `button` (`SDL_GamepadButton`): SDL gamepad button, e.g. SDL_GAMEPAD_BUTTON_SOUTH.
- `gamepad_index` (`int`): Index of the opened gamepad. Defaults to 0.

### bind_key

~~~cpp
void Input::bind_key(const std::string &action_name, SDL_Scancode key)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Binds a keyboard key to a named digital action.

**Parameters**

- `action_name` (`const std::string &`): Name of the action, e.g. "jump".
- `key` (`SDL_Scancode`): SDL scancode to bind.

### bind_mouse_button

~~~cpp
void Input::bind_mouse_button(const std::string &action_name, Uint8 button)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Binds an SDL mouse button to a named digital action.

**Parameters**

- `action_name` (`const std::string &`): Name of the action.
- `button` (`Uint8`): SDL mouse button id, e.g. SDL_BUTTON_LEFT.

### clear_mouse_viewport

~~~cpp
void Input::clear_mouse_viewport()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs the action down operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters:** None.

### controller_at

~~~cpp
Controller_State * Input::detail::controller_at(int index)
~~~

**Access:** public  **Returns:** `Controller_State *`  **Engine version:** Potato Engine 1.0.0

Performs the controller at operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `index` (`int`): Value supplied for the index parameter.

### controller_axis

~~~cpp
float Input::controller_axis(SDL_GamepadAxis axis, int gamepad_index=0, float deadzone=0.15f)
~~~

**Access:** public  **Returns:** ``float``  **Engine version:** Potato Engine 1.0.0

Reads a gamepad axis.

**Parameters**

- `axis` (`SDL_GamepadAxis`): SDL gamepad axis.
- `gamepad_index` (`int`): Index of the opened gamepad. Defaults to 0.
- `deadzone` (`float`): Values below this magnitude become 0.

### controller_button_down

~~~cpp
bool Input::controller_button_down(SDL_GamepadButton button, int gamepad_index)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a gamepad button is held on a selected gamepad.

**Parameters**

- `button` (`SDL_GamepadButton`): SDL gamepad button.
- `gamepad_index` (`int`): Index of the opened gamepad.

### controller_button_down

~~~cpp
bool Input::controller_button_down(SDL_GamepadButton button)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a gamepad button is held on gamepad 0.

**Parameters**

- `button` (`SDL_GamepadButton`): SDL gamepad button.

### controller_button_pressed

~~~cpp
bool Input::controller_button_pressed(SDL_GamepadButton button, int gamepad_index=0)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a gamepad button was pressed this frame.

**Parameters**

- `button` (`SDL_GamepadButton`): SDL gamepad button.
- `gamepad_index` (`int`): Index of the opened gamepad. Defaults to 0.

### controller_button_released

~~~cpp
bool Input::controller_button_released(SDL_GamepadButton button, int gamepad_index=0)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a gamepad button was released this frame.

**Parameters**

- `button` (`SDL_GamepadButton`): SDL gamepad button.
- `gamepad_index` (`int`): Index of the opened gamepad. Defaults to 0.

### find_action

~~~cpp
const Action * Input::detail::find_action(const std::string &name)
~~~

**Access:** public  **Returns:** `const Action *`  **Engine version:** Potato Engine 1.0.0

Performs the controller axis operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.

### find_axis

~~~cpp
const Axis_Action * Input::detail::find_axis(const std::string &name)
~~~

**Access:** public  **Returns:** `const Axis_Action *`  **Engine version:** Potato Engine 1.0.0

Returns or locates the requested engine value without changing the caller-visible state. Check the return type for pointer ownership and whether failure is represented by a null or empty value.

**Parameters**

- `name` (`const std::string &`): Value supplied for the name parameter.

### handle_event

~~~cpp
void Input::handle_event(const SDL_Event &event)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Feeds an SDL event into the input system.

**Parameters**

- `event` (`const SDL_Event &`): SDL event to process.

### init

~~~cpp
void Input::init()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Initializes the input system and opens available gamepads.

**Parameters:** None.

### is_blocked

~~~cpp
bool Input::is_blocked()
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Handles an engine lifecycle callback or input event. Override or call it only at the event-processing phase described by the owning type.

**Parameters:** None.

### key_down

~~~cpp
bool Input::key_down(SDL_Scancode key)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a keyboard key is currently held.

**Parameters**

- `key` (`SDL_Scancode`): SDL scancode.

### key_pressed

~~~cpp
bool Input::key_pressed(SDL_Scancode key)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a keyboard key was pressed this frame.

**Parameters**

- `key` (`SDL_Scancode`): SDL scancode.

### key_released

~~~cpp
bool Input::key_released(SDL_Scancode key)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a keyboard key was released this frame.

**Parameters**

- `key` (`SDL_Scancode`): SDL scancode.

### mouse_button_down

~~~cpp
bool Input::mouse_button_down(Uint8 button)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a mouse button is currently held.

**Parameters**

- `button` (`Uint8`): SDL mouse button id.

### mouse_button_pressed

~~~cpp
bool Input::mouse_button_pressed(Uint8 button)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a mouse button was pressed this frame.

**Parameters**

- `button` (`Uint8`): SDL mouse button id, e.g. SDL_BUTTON_LEFT.

### mouse_button_released

~~~cpp
bool Input::mouse_button_released(Uint8 button)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a mouse button was released this frame.

**Parameters**

- `button` (`Uint8`): SDL mouse button id.

### mouse_delta

~~~cpp
Vec Input::mouse_delta()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets relative mouse movement for the current frame.

**Parameters:** None.

### mouse_position

~~~cpp
Vec Input::mouse_position()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets the current mouse position.

**Parameters:** None.

### mouse_scroll_delta

~~~cpp
Vec Input::mouse_scroll_delta()
~~~

**Access:** public  **Returns:** `Vec`  **Engine version:** Potato Engine 1.0.0

Gets mouse wheel movement for the current frame.

**Parameters:** None.

### quit_requested

~~~cpp
bool Input::quit_requested()
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether an SDL quit event was seen this frame.

**Parameters:** None.

### release_block

~~~cpp
void Input::release_block(const void *owner)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Performs the key down operation for the owning engine component. The exact inputs, result type, access level, and default values are shown below so callers can validate the required state before invoking it.

**Parameters**

- `owner` (`const void *`): Value supplied for the owner parameter.

### set_mouse_viewport

~~~cpp
void Input::set_mouse_viewport(const Vec &origin, const Vec &size, const Vec &logical_size)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates the selected property using the supplied value. The change applies to subsequent engine processing and rendering unless the type documents deferred behavior.

**Parameters**

- `origin` (`const Vec &`): Value supplied for the origin parameter.
- `size` (`const Vec &`): Value supplied for the size parameter.
- `logical_size` (`const Vec &`): Value supplied for the logical_size parameter.

### shutdown

~~~cpp
void Input::shutdown()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Releases gamepads and clears registered actions and axes.

**Parameters:** None.

### update

~~~cpp
void Input::update()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Refreshes keyboard, mouse, gamepad, action, and axis states.

**Parameters:** None.

### valid_gamepad_axis

~~~cpp
bool Input::detail::valid_gamepad_axis(SDL_GamepadAxis axis)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters**

- `axis` (`SDL_GamepadAxis`): Value supplied for the axis parameter.

### valid_gamepad_button

~~~cpp
bool Input::detail::valid_gamepad_button(SDL_GamepadButton button)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `button` (`SDL_GamepadButton`): Value supplied for the button parameter.

### valid_mouse_button

~~~cpp
bool Input::detail::valid_mouse_button(Uint8 button)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `button` (`Uint8`): Value supplied for the button parameter.

### valid_scancode

~~~cpp
bool Input::detail::valid_scancode(SDL_Scancode key)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `key` (`SDL_Scancode`): Value supplied for the key parameter.

### Header usage example

~~~cpp
Input::bind_key("jump", SDL_SCANCODE_SPACE);
if (Input::action_pressed("jump")) player_jump();
~~~

## audio.h

### ~Audio

~~~cpp
Audio::~Audio()
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Header usage example value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### ~ITrack

~~~cpp
ITrack::~ITrack()
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### ~Track_Pool

~~~cpp
Track_Pool::~Track_Pool()
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Destroys the instance and releases the engine resources it owns. Objects borrowed from other services are not implicitly transferred unless the owning type states otherwise.

**Parameters:** None.

### Audio

~~~cpp
Audio::Audio()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Audio value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters:** None.

### Audio

~~~cpp
Audio::Audio(Audio &&)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Audio value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`Audio &&`): Value supplied for the  parameter.

### Audio

~~~cpp
Audio::Audio(const Audio &)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Audio value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Audio &`): Value supplied for the  parameter.

### Audio

~~~cpp
Audio::Audio(const std::string &file_path, MIX_Mixer *mixer=nullptr, bool predecode=true)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs an Audio object and loads the specified audio file.

**Parameters**

- `file_path` (`const std::string &`): Path to the audio file.
- `mixer` (`MIX_Mixer *`): Pointer to the SDL_Mixer instance to use for audio playback. If nullptr, the default mixer will be used.
- `predecode` (`bool`): If true, the audio will be fully decoded into memory. If false, it will be streamed from disk.

### Audio

~~~cpp
Audio::Audio(const std::string &file_path, Track_Pool *track_pool, bool predecode=true)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs an Audio object and loads the specified audio file, using a track pool for playback.

**Parameters**

- `file_path` (`const std::string &`): Path to the audio file.
- `track_pool` (`Track_Pool *`): Pointer to the Track_Pool instance to use for audio playback. If nullptr, the default mixer will be used.
- `predecode` (`bool`): If true, the audio will be fully decoded into memory. If false, it will be streamed from disk.

### create_new_default_track

~~~cpp
void Track_Pool::create_new_default_track()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Creates a new default track and adds it to the pool.

**Parameters:** None.

### create_new_dynamic_track

~~~cpp
ITrack * Track_Pool::create_new_dynamic_track(uint32_t lifetime=5000)
~~~

**Access:** public  **Returns:** `ITrack *`  **Engine version:** Potato Engine 1.0.0

Creates a new dynamic track and adds it to the pool.

**Parameters**

- `lifetime` (`uint32_t`): The lifetime of the track in frames, 0 for infinite. After this many frames, the track will be automatically released back to the pool.

### detach_track

~~~cpp
void Audio::detach_track(ITrack *track)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Detaches the currently attached track from the audio instance.

**Parameters**

- `track` (`ITrack *`): Pointer to the track to detach.

### flush_tracks

~~~cpp
void Track_Pool::flush_tracks(float dt)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates all tracks in the pool, applying their properties and managing their lifetimes.

**Parameters**

- `dt` (`float`): The time delta in seconds since the last update, used to decrement the lifetime of dynamic tracks.

### force_pause

~~~cpp
void Audio::force_pause()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Forces the audio to pause, regardless of its current state. This function forcefully pauses the audio playback. Unlike the regular pause() function, which only sets the state to PAUSED, and then waits for the flush_tracks() to actually pause the audio, this function will immediately stop the audio playback and set the state to PAUSED. Use this function when you need to ensure that the audio is paused, regardless of its current state.

**Parameters:** None.

### force_play

~~~cpp
void Audio::force_play()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Forces the audio to play, regardless of its current state. This function forcefully starts the audio playback from the beginning, even if it is already playing or paused. Unlike the regular play() function, which only sets the state to PLAYING, and then waits for the flush_tracks() to actually start the audio, this function will immediately start the audio playback and set the state to PLAYING. Use this function when you need to ensure that the audio is playing, regardless of its current state.

**Parameters:** None.

### force_resume

~~~cpp
void Audio::force_resume()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Forces the audio to resume, regardless of its current state. This function forcefully resumes the audio playback, even if it is already playing or stopped. Unlike the regular resume() function, which only sets the state to RESUMED, and then waits for the flush_tracks() to actually resume the audio, this function will immediately resume the audio playback and set the state to RESUMED. Use this function when you need to ensure that the audio is resumed, regardless of its current state.

**Parameters:** None.

### force_stop

~~~cpp
void Audio::force_stop()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Forces the audio to stop, regardless of its current state. This function forcefully stops the audio playback. Unlike the regular stop() function, which only sets the state to STOPPED, and then waits for the flush_tracks() to actually stop the audio, this function will immediately stop the audio playback and set the state to STOPPED. Use this function when you need to ensure that the audio is stopped, regardless of its current state.

**Parameters:** None.

### get_default_track_count

~~~cpp
uint8_t Track_Pool::get_default_track_count() const
~~~

**Access:** public  **Returns:** ``uint8_t``  **Engine version:** Potato Engine 1.0.0

Gets the number of default tracks currently in the pool.

**Parameters:** None.

### get_duration

~~~cpp
Sint64 Audio::get_duration() const
~~~

**Access:** public  **Returns:** ``Sint64``  **Engine version:** Potato Engine 1.0.0

Gets the duration of the loaded audio file in milliseconds.

**Parameters:** None.

### get_dynamic_track_lifetime

~~~cpp
uint32_t Track_Pool::get_dynamic_track_lifetime(size_t index) const
~~~

**Access:** public  **Returns:** ``uint32_t``  **Engine version:** Potato Engine 1.0.0

Gets the lifetime of a dynamic track in frames.

**Parameters**

- `index` (`size_t`): The index of the track in the pool.

### get_free_track

~~~cpp
ITrack * Track_Pool::get_free_track()
~~~

**Access:** public  **Returns:** `ITrack *`  **Engine version:** Potato Engine 1.0.0

Gets a free track from the pool. If no free tracks are available, a new dynamic track is created.

**Parameters:** None.

### get_mixer

~~~cpp
MIX_Mixer * Audio::get_mixer()
~~~

**Access:** public  **Returns:** ``MIX_Mixer *``  **Engine version:** Potato Engine 1.0.0

Gets the SDL_Mixer instance used for audio playback.

**Parameters:** None.

### get_mixer

~~~cpp
MIX_Mixer * Track_Pool::get_mixer() const
~~~

**Access:** public  **Returns:** ``MIX_Mixer *``  **Engine version:** Potato Engine 1.0.0

Gets the SDL_Mixer instance used by this pool.

**Parameters:** None.

### get_props

~~~cpp
Audio_Props Audio::get_props() const
~~~

**Access:** public  **Returns:** `Audio_Props`  **Engine version:** Potato Engine 1.0.0

Gets the properties of the audio file.

**Parameters:** None.

### get_total_track_count

~~~cpp
uint8_t Track_Pool::get_total_track_count() const
~~~

**Access:** public  **Returns:** ``uint8_t``  **Engine version:** Potato Engine 1.0.0

Gets the total number of tracks currently in the pool, including both default and dynamic tracks.

**Parameters:** None.

### get_track

~~~cpp
ITrack * Track_Pool::get_track(size_t index) const
~~~

**Access:** public  **Returns:** `ITrack *`  **Engine version:** Potato Engine 1.0.0

Gets the track at the specified index in the pool.

**Parameters**

- `index` (`size_t`): The index of the track to retrieve.

### init

~~~cpp
bool Track_Pool::init(MIX_Mixer *mixer, uint8_t default_track_count=8, Logger *logger=nullptr)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Constructs a Audio value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `mixer` (`MIX_Mixer *`): Value supplied for the mixer parameter.
- `default_track_count` (`uint8_t`): Value supplied for the default_track_count parameter.
- `logger` (`Logger *`): Value supplied for the logger parameter.

### is_loaded

~~~cpp
bool Audio::is_loaded() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks if an audio file is currently loaded.

**Parameters:** None.

### is_playing

~~~cpp
bool Audio::is_playing() const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks if this audio instance is currently playing on a managed track.

**Parameters:** None.

### ITrack

~~~cpp
ITrack::ITrack()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs an ITrack object with the specified track, audio, and lifetime.

**Parameters:** None.

### ITrack

~~~cpp
ITrack::ITrack(const ITrack &)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Queries the current state and returns a Boolean-style result. It does not intentionally mutate the resource beyond implementation-level bookkeeping.

**Parameters**

- `` (`constITrack &`): Value supplied for the  parameter.

### ITrack

~~~cpp
ITrack::ITrack(ITrack &&)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a ITrack value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`ITrack &&`): Value supplied for the  parameter.

### ITrack

~~~cpp
ITrack::ITrack(MIX_Track *t, Audio *a, uint32_t l)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs an ITrack object with the specified track, audio, and lifetime.

**Parameters**

- `t` (`MIX_Track *`): Pointer to the SDL_Mixer track.
- `a` (`Audio *`): Pointer to the Audio instance associated with the track.
- `l` (`uint32_t`): Lifetime of the track in frames, 0 for infinite.

### load

~~~cpp
void Audio::load(const std::string &file_path, bool predecode=true)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Loads an audio file into memory.

**Parameters**

- `file_path` (`const std::string &`): Path to the audio file.
- `predecode` (`bool`): If true, the audio will be fully decoded into memory. If false, it will be streamed from disk.

### operator=

~~~cpp
Audio & Audio::operator=(Audio &&)=delete
~~~

**Access:** public  **Returns:** `Audio &`  **Engine version:** Potato Engine 1.0.0

Constructs a ITrack value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`Audio &&`): Value supplied for the  parameter.

### operator=

~~~cpp
Audio & Audio::operator=(const Audio &)=delete
~~~

**Access:** public  **Returns:** `Audio &`  **Engine version:** Potato Engine 1.0.0

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const Audio &`): Value supplied for the  parameter.

### operator=

~~~cpp
ITrack & ITrack::operator=(const ITrack &)=delete
~~~

**Access:** public  **Returns:** `ITrack &`  **Engine version:** Potato Engine 1.0.0

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`constITrack &`): Value supplied for the  parameter.

### operator=

~~~cpp
ITrack & ITrack::operator=(ITrack &&)=delete
~~~

**Access:** public  **Returns:** `ITrack &`  **Engine version:** Potato Engine 1.0.0

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`ITrack &&`): Value supplied for the  parameter.

### operator=

~~~cpp
Track_Pool & Track_Pool::operator=(const Track_Pool &)=delete
~~~

**Access:** public  **Returns:** `Track_Pool &`  **Engine version:** Potato Engine 1.0.0

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`const Track_Pool &`): Value supplied for the  parameter.

### operator=

~~~cpp
Track_Pool & Track_Pool::operator=(Track_Pool &&)=delete
~~~

**Access:** public  **Returns:** `Track_Pool &`  **Engine version:** Potato Engine 1.0.0

Implements the operator= operation for this engine type. The exact operand and result types are shown in the signature, including disabled copy or assignment overloads.

**Parameters**

- `` (`Track_Pool &&`): Value supplied for the  parameter.

### pause

~~~cpp
void Audio::pause()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Pauses playback of the audio file if it is playing.

**Parameters:** None.

### play

~~~cpp
void Audio::play()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Plays the loaded audio file from the beginning, stopping any currently playing audio.

**Parameters:** None.

### play_fnf

~~~cpp
void Audio::play_fnf()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Plays the loaded audio file from the beginning, stopping any currently playing audio.

**Parameters:** None.

### release_track

~~~cpp
void Track_Pool::release_track(ITrack *track)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Releases a track back to the pool, making it available for reuse.

**Parameters**

- `track` (`ITrack *`): Pointer to the track to release.

### resolve_engine_defaults

~~~cpp
void Audio::resolve_engine_defaults()
~~~

**Access:** private  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### resume

~~~cpp
void Audio::resume()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Resumes playback of the audio file if it is paused.

**Parameters:** None.

### set_default_track_count

~~~cpp
void Track_Pool::set_default_track_count(uint8_t count)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the number of default tracks to maintain in the pool.

**Parameters**

- `count` (`uint8_t`): The new number of default tracks to maintain.

### set_dynamic_track_lifetime

~~~cpp
void Track_Pool::set_dynamic_track_lifetime(size_t index, uint32_t lifetime)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the lifetime of a dynamic track in frames.

**Parameters**

- `index` (`size_t`): The index of the track in the pool.
- `lifetime` (`uint32_t`): The new lifetime of the track in frames, 0 for infinite.

### set_fps

~~~cpp
void Track_Pool::set_fps(float fps)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the frames per second (FPS) value used for lifetime calculations of dynamic tracks.

**Parameters**

- `fps` (`float`): The new FPS value. Must be greater than 0.0.

### set_gain

~~~cpp
void Audio::set_gain(float gain)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the gain (volume) of the audio file.

**Parameters**

- `gain` (`float`): The gain value, where 0.0 is silent and 1.0 is full volume.

### set_logger

~~~cpp
void Audio::set_logger(Logger *logger)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the logger to be used for logging messages from the Audio class.

**Parameters**

- `logger` (`Logger *`): Pointer to the Logger instance.

### set_logger

~~~cpp
void Track_Pool::set_logger(Logger *logger)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the logger to be used for logging messages from the track pool.

**Parameters**

- `logger` (`Logger *`): Pointer to the Logger instance to use for logging. If nullptr, logging will be disabled.

### set_loop_count

~~~cpp
void Audio::set_loop_count(int loop_count)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the the loop count of the audio file.

**Parameters**

- `loop_count` (`int`): The number of times to loop the audio, where 0 is no looping, 1 is one loop (play twice), and -1 is infinite looping.

### set_master_gain

~~~cpp
void Track_Pool::set_master_gain(float gain)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the master gain (volume) for all tracks in the pool.

**Parameters**

- `gain` (`float`): The master gain value, where 0.0 is silent and 1.0 is full volume. Values above 1.0 will amplify the audio (may cause distortion).

### set_mixer

~~~cpp
void Audio::set_mixer(MIX_Mixer *new_mixer)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the SDL_Mixer instance to be used for audio playback.

**Parameters**

- `new_mixer` (`MIX_Mixer *`): Pointer to the new SDL_Mixer instance.

### set_mixer

~~~cpp
void Track_Pool::set_mixer(MIX_Mixer *mixer)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the SDL_Mixer instance to be used for audio playback.

**Parameters**

- `mixer` (`MIX_Mixer *`): Pointer to the new SDL_Mixer instance.

### set_panning

~~~cpp
void Audio::set_panning(float panning)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the panning of the audio file.

**Parameters**

- `panning` (`float`): The panning value, where -1.0 is full left, 0.0 is center, and 1.0 is full right.

### set_pitch

~~~cpp
void Audio::set_pitch(float pitch)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the pitch of the audio file.

**Parameters**

- `pitch` (`float`): The pitch value, where 1.0 is normal pitch, 0.5 is half speed, and 2.0 is double speed.

### set_position

~~~cpp
void Audio::set_position(const Vec3 &position)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the 3D position of the audio file.

**Parameters**

- `position` (`const Vec3 &`): The 3D position of the audio source.

### set_props

~~~cpp
void Audio::set_props(const Audio_Props &props)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the properties of the audio file.

**Parameters**

- `props` (`const Audio_Props &`): The new properties to set.

### set_track_pool

~~~cpp
void Audio::set_track_pool(Track_Pool *track_pool)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the track pool to be used for audio playback.

**Parameters**

- `track_pool` (`Track_Pool *`): Pointer to the Track_Pool instance.

### shutdown

~~~cpp
void Track_Pool::shutdown()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Moves the component into its active state and makes it eligible for subsequent updates or playback. Repeated calls follow the state rules of the owning type.

**Parameters:** None.

### stop

~~~cpp
void Audio::stop()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Stops playback of the audio file.

**Parameters:** None.

### Track_Pool

~~~cpp
Track_Pool::Track_Pool()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Moves the component out of its active state or ends the current operation. Any retained resource ownership remains governed by the owning class.

**Parameters:** None.

### Track_Pool

~~~cpp
Track_Pool::Track_Pool(const Track_Pool &)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Track_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Track_Pool &`): Value supplied for the  parameter.

### Track_Pool

~~~cpp
Track_Pool::Track_Pool(MIX_Mixer *mixer, uint8_t default_track_count=8, Logger *logger=nullptr)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Track_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `mixer` (`MIX_Mixer *`): Value supplied for the mixer parameter.
- `default_track_count` (`uint8_t`): Value supplied for the default_track_count parameter.
- `logger` (`Logger *`): Value supplied for the logger parameter.

### Track_Pool

~~~cpp
Track_Pool::Track_Pool(Track_Pool &&)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Track_Pool value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`Track_Pool &&`): Value supplied for the  parameter.

### unload

~~~cpp
void Audio::unload()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Unloads the currently loaded audio file from memory.

**Parameters:** None.

### update_track

~~~cpp
void Track_Pool::update_track(ITrack *track, const Audio_Props &props)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Updates the properties of a track.

**Parameters**

- `track` (`ITrack *`): Pointer to the track to update.
- `props` (`const Audio_Props &`): The new properties to apply to the track.

### Header usage example

~~~cpp
Audio music;
music.load("assets/audio/theme.ogg");
music.set_loop_count(-1);
music.play();
~~~

## localization.h

### ~Localization

~~~cpp
Localization::~Localization()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### clear

~~~cpp
void Localization::clear()
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Clears all loaded localization tables.

**Parameters:** None.

### format

~~~cpp
std::string Localization::format(const std::string &key, const std::unordered_map< std::string, std::string > &values) const
~~~

**Access:** public  **Returns:** ``std::string``  **Engine version:** Potato Engine 1.0.0

Retrieves a localized string and replaces placeholders.

**Parameters**

- `key` (`const std::string &`): Value supplied for the key parameter.
- `values` (`std::string > &`): Value supplied for the values parameter.

### get

~~~cpp
std::string Localization::get(const std::string &key) const
~~~

**Access:** public  **Returns:** ``std::string``  **Engine version:** Potato Engine 1.0.0

Retrieves a localized string by key.

**Parameters**

- `key` (`const std::string &`): The localization key, for example "menu.start".

### get_current_tag

~~~cpp
const std::string & Localization::get_current_tag() const
~~~

**Access:** public  **Returns:** ``const std::string &``  **Engine version:** Potato Engine 1.0.0

Gets the currently active localization tag.

**Parameters:** None.

### get_fallback_tag

~~~cpp
const std::string & Localization::get_fallback_tag() const
~~~

**Access:** public  **Returns:** ``const std::string &``  **Engine version:** Potato Engine 1.0.0

Gets the fallback localization tag.

**Parameters:** None.

### has_key

~~~cpp
bool Localization::has_key(const std::string &key) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a key exists in the current or fallback tag.

**Parameters**

- `key` (`const std::string &`): Value supplied for the key parameter.

### has_tag

~~~cpp
bool Localization::has_tag(const std::string &tag) const
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Checks whether a tag exists.

**Parameters**

- `tag` (`const std::string &`): Value supplied for the tag parameter.

### load

~~~cpp
bool Localization::load(const std::string &tag, const std::string &path)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Loads a localization JSON file and stores it under a tag.

**Parameters**

- `tag` (`const std::string &`): The tag/language/theme name, for example "en", "hu", "dark".
- `path` (`const std::string &`): The JSON file path.

### Localization

~~~cpp
Localization::Localization()=default
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Removes or releases the selected state from this engine component. References to removed resources must not be reused unless another owner keeps them alive.

**Parameters:** None.

### Localization

~~~cpp
Localization::Localization(const Localization &)=delete
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Localization value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Localization &`): Value supplied for the  parameter.

### Localization

~~~cpp
Localization::Localization(const std::string &default_tag, const std::string &fallback_tag, Logger *logger=nullptr)
~~~

**Access:** public  **Engine version:** Potato Engine 1.0.0

Constructs a Localization instance with default and fallback tags.

**Parameters**

- `default_tag` (`const std::string &`): The default localization tag.
- `fallback_tag` (`const std::string &`): The fallback localization tag used when a key is missing in the default tag.
- `logger` (`Logger *`): Pointer to a Logger instance (optional).

### operator=

~~~cpp
Localization & Localization::operator=(const Localization &)=delete
~~~

**Access:** public  **Returns:** `Localization &`  **Engine version:** Potato Engine 1.0.0

Constructs a Localization value from the parameters shown below. Default arguments provide the engine's standard initial state, while pointer arguments remain subject to the ownership rules of the type.

**Parameters**

- `` (`const Localization &`): Value supplied for the  parameter.

### set_current_tag

~~~cpp
bool Localization::set_current_tag(const std::string &tag)
~~~

**Access:** public  **Returns:** ``bool``  **Engine version:** Potato Engine 1.0.0

Sets the currently active localization tag.

**Parameters**

- `tag` (`const std::string &`): The tag to activate.

### set_fallback_tag

~~~cpp
void Localization::set_fallback_tag(const std::string &tag)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the fallback tag used when a key is missing in the current tag.

**Parameters**

- `tag` (`const std::string &`): The fallback tag.

### set_logger

~~~cpp
void Localization::set_logger(Logger *logger)
~~~

**Access:** public  **Returns:** ``void``  **Engine version:** Potato Engine 1.0.0

Sets the logger instance for logging missing keys and other messages.

**Parameters**

- `logger` (`Logger *`): Pointer to a Logger instance.

### Header usage example

~~~cpp
Localization strings;
strings.load("en-US", "assets/locales/en-US.json");
std::string title = strings.get("menu.title");
~~~









