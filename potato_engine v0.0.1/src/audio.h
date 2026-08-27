#ifndef AUDIO_H
#define AUDIO_H

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "debug.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include "vec.h"
#include "utils.h"
#include "timer.h"
#include <memory>

class Audio;
class Track_Pool;
/**
 * @brief Represents the playback state of an audio file.
 */
enum class Audio_State {
    STOPPED,
    PLAYING,
    PAUSED,
    RESUMED
};

/**
 * @brief Represents the properties of an audio file, such as gain, panning, pitch, fade-in/out duration, and loop count.
 * This struct is used to control the playback of an audio file, the track will read it and sets itself accordingly.
 * You can change these properties at any time, and the track will update itself accordingly.
 */
struct Audio_Props {
    float gain = 1.0f; // Volume multiplier (0.0 to 1.0)
    Vec3 position = {0.0f, 0.0f, 0.0f}; // 3D position of the audio source. Panning is calculated based on the position of the audio source relative to the listener.
    float pitch = 1.0f; // Playback speed multiplier (0.5 half speed to 2.0 double speed), must be between 0.1f and 100.0f
    int loop_count = 0; // Number of times to loop the audio (-1 for infinite)
    Audio_State state = Audio_State::STOPPED; // Current playback state
    Sint64 fade_out_duration = 0; // Duration of fade-out in milliseconds when stop is called, 0 for no fade-out
};

/**
 * @brief Represents a track in the audio system, which can be used to play an audio file.
 * This struct is used to manage the playback of an audio file, and is used by the `Track_Pool` class to
 * manage a pool of tracks. It contains a pointer to the SDL_Mixer track, a pointer to the Audio instance associated with the track, and a lifetime in frames.
 * The lifetime is used to determine when to release the track back to the pool. A lifetime of 0 means the track is 
 * infinite and will not be released automatically. A positive lifetime means the track will be released after that many frames. 
 * The lifetime is decremented each frame by the `Track_Pool` class, and when it reaches 0, the track is released back to the pool.
 */
struct ITrack {
    MIX_Track *track = nullptr; // Pointer to the SDL_Mixer track
    Audio* audio = nullptr; // Current audio instance associated with the track
    uint32_t lifetime = 0; // Lifetime of the track in frames, 0 for infinite
    Timer timer; // Timer to track the lifetime of the track
    bool has_timer = false; // Whether the track has a timer to track its lifetime
    bool is_dynamic = false; // Whether the track is dynamic (created on demand) or default (pre-allocated)

    Audio_State current_state = Audio_State::STOPPED; // Current playback state of the track
    Audio_State previous_state = Audio_State::STOPPED; // Previous playback state of the track

    /**
     * @brief Constructs an ITrack object with the specified track, audio, and lifetime.
     * @note The destructor destroys the MIX_Track and Timer.
     * It does not delete `audio`, because Audio is only borrowed.
     */
    ITrack() = default;

    /**
     * @brief Constructs an ITrack object with the specified track, audio, and lifetime.
     * @param t Pointer to the SDL_Mixer track.
     * @param a Pointer to the Audio instance associated with the track.
     * @param l Lifetime of the track in frames, 0 for infinite.
     * @note The destructor destroys the MIX_Track and Timer.
     * It does not delete `audio`, because Audio is only borrowed.
     */
    ITrack(MIX_Track* t, Audio* a, uint32_t l) : track(t), audio(a), lifetime(l) {}

    ~ITrack() {
        if (track) {
            MIX_DestroyTrack(track);
            track = nullptr;
        }
        audio = nullptr;
    }

    ITrack(const ITrack&) = delete;
    ITrack& operator=(const ITrack&) = delete;

    ITrack(ITrack&&) = delete;
    ITrack& operator=(ITrack&&) = delete;
};

/**
 * @brief Represents an audio file that can be loaded, played, and manipulated.
 */
class Audio {
public:
    Audio() = default;

    /**
     * @brief Constructs an Audio object and loads the specified audio file.
     * @param file_path Path to the audio file.
     * @param mixer Pointer to the SDL_Mixer instance to use for audio playback. If
     * `nullptr`, the default mixer will be used.
     * @param predecode If `true`, the audio will be fully decoded into memory. If `false`, it will be streamed from disk.
     */
    Audio(const std::string& file_path, MIX_Mixer* mixer = nullptr, bool predecode = true);

    /**
     * @brief Constructs an Audio object and loads the specified audio file, using a track pool for playback.
     * @param file_path Path to the audio file.
     * @param track_pool Pointer to the Track_Pool instance to use for audio playback. If `nullptr`, the default mixer will be used.
     * @param predecode If `true`, the audio will be fully decoded into memory. If `false`, it will be streamed from disk.
     */
    Audio(const std::string& file_path, Track_Pool* track_pool, bool predecode = true);

    Audio(const Audio&) = delete; // Disable copy constructor
    Audio& operator=(const Audio&) = delete; // Disable copy assignment

    Audio(Audio&&) = delete;
    Audio& operator=(Audio&&) = delete;

    ~Audio() { unload(); }

    /**
     * @brief Gets the properties of the audio file.
     * @return The properties of the audio file.
     */
    Audio_Props get_props() const { return m_props; }

    /**
     * @brief Sets the properties of the audio file.
     * @param props The new properties to set.
     */
    void set_props(const Audio_Props& props) { m_props = props; }

    /**
     * @brief Loads an audio file into memory.
     * @param file_path Path to the audio file.
     * @param predecode If `true`, the audio will be fully decoded into memory. If `false`, it will be streamed from disk.
     * @note If an audio file is already loaded, it will be unloaded before loading the new file.
     * Predecode is useful for small audio files (like sound effects) that need to be played with low latency,
     * while streaming (so false) is better for large files (like music).
     */
    void load(const std::string& file_path, bool predecode = true);

    /**
     * @brief Detaches the currently attached track from the audio instance.
     * @param track Pointer to the track to detach.
     * @note This function is used internally by the Track_Pool class to manage track lifetimes.
     */
    void detach_track(ITrack* track) { if(m_track == track) m_track = nullptr; }

    /**
     * @brief Unloads the currently loaded audio file from memory.
     * @note If no audio file is loaded, this function does nothing.
     */
    void unload();

    /**
     * @brief Checks if an audio file is currently loaded.
     * @return `true` if an audio file is loaded, `false` otherwise.
     */
    bool is_loaded() const { return m_audio != nullptr; }

    /**
     * @brief Checks if this audio instance is currently playing on a managed track.
     * @return `true` if the attached track is currently playing, `false` otherwise.
     */
    bool is_playing() const;

    /**
     * @brief Gets the SDL_Mixer instance used for audio playback.
     * @return Pointer to the SDL_Mixer instance.
     */
    MIX_Mixer* get_mixer() { return m_mixer; }

    /**
     * @brief Sets the SDL_Mixer instance to be used for audio playback.
     * @param new_mixer Pointer to the new SDL_Mixer instance.
     */
    void set_mixer(MIX_Mixer* new_mixer) { m_mixer = new_mixer; }

    /**
     * @brief Gets the duration of the loaded audio file in milliseconds.
     * @return The duration of the audio file in milliseconds, or 0 if no audio file is loaded.
     */
    Sint64 get_duration() const { return m_audio ? MIX_GetAudioDuration(m_audio) : 0; }
    
    /**
     * @brief Plays the loaded audio file from the beginning, stopping any currently playing audio.
     */
    void play();

    /**
     * @brief Forces the audio to play, regardless of its current state.
     * This function forcefully starts the audio playback from the beginning, even if it is already playing or paused.
     * Unlike the regular `play()` function, which only sets the state to `PLAYING`, and then waits for the `flush_tracks()` to actually start the audio, this function will immediately start the audio playback and set the state to `PLAYING`.
     * Use this function when you need to ensure that the audio is playing, regardless of its current state.
     */
    void force_play();

    /**
     * @brief Resumes playback of the audio file if it is paused.
     */
    void resume();

    /**
     * @brief Forces the audio to resume, regardless of its current state.
     * This function forcefully resumes the audio playback, even if it is already playing or stopped.
     * Unlike the regular `resume()` function, which only sets the state to `RESUMED`, and then waits for the `flush_tracks()` to actually resume the audio, this function will immediately resume the audio playback and set the state to `RESUMED`.
     * Use this function when you need to ensure that the audio is resumed, regardless of its current state.
     */
    void force_resume();

    /**
     * @brief Pauses playback of the audio file if it is playing.
     */
    void pause();

    /**
     * @brief Forces the audio to pause, regardless of its current state.
     * This function forcefully pauses the audio playback.
     * Unlike the regular `pause()` function, which only sets 
     * the state to `PAUSED`, and then waits for the `flush_tracks()` to actually pause the audio,
     * this function will immediately stop the audio playback and set the state to `PAUSED`.
     * Use this function when you need to ensure that the audio is paused, regardless of its current state.
     */
    void force_pause();

    /**
     * @brief Stops playback of the audio file.
     */
    void stop();

    /**
     * @brief Forces the audio to stop, regardless of its current state.
     * This function forcefully stops the audio playback.
     * Unlike the regular `stop()` function, which only sets the state to `STOPPED`, and then waits for the `flush_tracks()` to actually stop the audio, this function will immediately stop the audio playback and set the state to `STOPPED`.
     * Use this function when you need to ensure that the audio is stopped, regardless of its current state.
     */
    void force_stop();

    /**
     * @brief Plays the loaded audio file from the beginning, stopping any currently playing audio.
     * @note If no audio file is loaded, this function does nothing.
     * @attention You shouldn't rely on this function as it uses
     * the SDL_Mixer `MIX_PlayAudio()` function, which is a "fire-and-forget" function.
     * We created a dynamic track pool for a reason. 
     * Only use this if you are sure you only need to play one audio file at a time, and don't care about stopping it or controlling it later, 
     * and barely use any sounds in your game. Otherwise, use the `Track_Pool` class to play audio files.
    */
    void play_fnf();

    /**
     * @brief Sets the gain (volume) of the audio file.
     * @param gain The gain value, where 0.0 is silent and 1.0 is full volume.
     * @note The gain value 0.0f is silent, 1.0f is full volume, and values above 1.0f will amplify the audio (may cause distortion).
     */
    void set_gain(float gain) { m_props.gain = gain; }

    /**
     * @brief Sets the 3D position of the audio file.
     * @param position The 3D position of the audio source.
     * @note The position is used to calculate panning and volume based on the listener's position.
     * The x-axis is left/right, the y-axis is up/down, and the z-axis is forward/backward. The listener is assumed to be at the origin (0, 0, 0).
     */
    void set_position(const Vec3& position) { m_props.position = position; }
    
    /**
     * @brief Sets the panning of the audio file.
     * @param panning The panning value, where -1.0 is full left, 0.0 is center, and 1.0 is full right.
     * @note This function only affects the horizontal panning of the audio.
     */
    void set_panning(float panning) { m_props.position.x = clamp(panning, -1.0f, 1.0f); }

    /**
     * @brief Sets the pitch of the audio file.
     * @param pitch The pitch value, where 1.0 is normal pitch, 0.5 is half speed, and 2.0 is double speed.
     * @note The pitch value must be between 0.1f and 100.0f. Values outside this range will be clamped.
     */
    void set_pitch(float pitch) { m_props.pitch =  clamp(pitch, 0.1f, 100.0f); }

    /**
     * @brief Sets the the loop count of the audio file.
     * @param loop_count The number of times to loop the audio, where 0 is
     * no looping, 1 is one loop (play twice), and -1 is infinite looping.
     */
    void set_loop_count(int loop_count) { m_props.loop_count = loop_count; }

    /**
     * @brief Sets the logger to be used for logging messages from the Audio class.
     * @param logger Pointer to the Logger instance.
     */
    void set_logger(Logger* logger) { m_logger = logger; }

    /**
     * @brief Sets the track pool to be used for audio playback.
     * @param track_pool Pointer to the Track_Pool instance.
     */
    void set_track_pool(Track_Pool* track_pool) { m_track_pool = track_pool; }

private:
    MIX_Mixer* m_mixer = nullptr;
    Track_Pool* m_track_pool = nullptr;
    ITrack* m_track = nullptr;
    MIX_Audio* m_audio = nullptr;
    Logger* m_logger = nullptr;

    std::string m_current_file_path;
    Audio_Props m_props;

    void resolve_engine_defaults();
};

/**
 * @brief A pool of mixer tracks that can be used to play multiple audio files simultaneously.
 * This class manages memory allocation and deallocation for the tracks, and provides a simple interface for playing audio.
 * It does everything dynamically, so you don't have to worry about memory management or track allocation.
 * However you can still set a default number of tracks to allocate on construction, and the pool will grow as needed.
 */
class Track_Pool {
public:
    uint32_t default_lifetime = 5000; // Default lifetime of dynamic tracks in frames

    Track_Pool() = default;
    Track_Pool(MIX_Mixer* mixer, uint8_t default_track_count = 8, Logger* logger = nullptr) 
    : m_mixer(mixer), m_default_track_count(default_track_count), m_logger(logger) {
        init(mixer, default_track_count, logger);
    }

    ~Track_Pool() { shutdown(); }


    bool init(MIX_Mixer* mixer, uint8_t default_track_count = 8, Logger* logger = nullptr);

    void shutdown();

    /**
     * @brief Gets the track at the specified index in the pool.
     * @param index The index of the track to retrieve.
     * @return Pointer to the track at the specified index, or `nullptr` if the index is out of bounds.
     */
    ITrack* get_track(size_t index) const {
        if (index < m_tracks.size()) {
            return m_tracks[index].get();
        }
        return nullptr; // Return nullptr if index is out of bounds
    }

    /**
     * @brief Gets a free track from the pool. If no free tracks are available, a new dynamic track is created.
     * @return Pointer to a free track, or `nullptr` if no tracks are available, otherwise makes a new dynamic track and returns it.
     * @note A free track is defined as a track that is not currently playing any audio. If all tracks are in use, a new dynamic track will be created and added to the pool.
     * The new dynamic track will have a lifetime of `default_lifetime` frames, after which it will be automatically released back to the pool. You can change the lifetime of a dynamic track using `set_dynamic_track_lifetime()`.
     */
    ITrack* get_free_track();

    /**
     * @brief Creates a new default track and adds it to the pool.
     * @note Default tracks are pre-allocated and have a lifetime of 0 (infinite). They will not be automatically released back to the pool, and must be manually released using `release_track()`.
     */
    void create_new_default_track();

    /**
     * @brief Creates a new dynamic track and adds it to the pool.
     * @param lifetime The lifetime of the track in frames, 0 for infinite. After this many frames, the track will be automatically released back to the pool.
     * @note Dynamic tracks are created on demand and have a finite lifetime. They will be automatically released back to the pool after their lifetime expires. You can change the lifetime of a dynamic track using `set_dynamic_track_lifetime()`.
     * @attention You should not create too many dynamic tracks, as they will consume memory and may cause performance issues. Use default tracks for frequently used audio, and dynamic tracks for occasional or one-off audio.
     * @return Pointer to the newly created dynamic track, or `nullptr` if the track could not be created.
     */
    ITrack* create_new_dynamic_track(uint32_t lifetime = 5000); // Default lifetime of 5000 frames for dynamic tracks
    
    /**
     * @brief Releases a track back to the pool, making it available for reuse.
     * @param track Pointer to the track to release.
     */
    void release_track(ITrack* track);

    /**
     * @brief Updates the properties of a track.
     * @param track Pointer to the track to update.
     * @param props The new properties to apply to the track.
     */
    void update_track(ITrack* track, const Audio_Props& props);

    /**
     * @brief Updates all tracks in the pool, applying their properties and managing their lifetimes.
     * @param dt The time delta in seconds since the last update, used to decrement the lifetime of dynamic tracks.
     */
    void flush_tracks(float dt);

    /**
     * @brief Gets the number of default tracks currently in the pool.
     * @return The number of default tracks in the pool.
     */
    uint8_t get_default_track_count() const { return m_default_track_count; }

    /**
     * @brief Sets the number of default tracks to maintain in the pool.
     * @param count The new number of default tracks to maintain.
     */
    void set_default_track_count(uint8_t count) { m_default_track_count = count; }

    /**
     * @brief Gets the total number of tracks currently in the pool, including both default and dynamic tracks.
     * @return The total number of tracks in the pool.
     */
    uint8_t get_total_track_count() const { return static_cast<uint8_t>(m_tracks.size()); }

    /**
     * @brief Gets the lifetime of a dynamic track in frames.
     * @param index The index of the track in the pool.
     * @return The lifetime of the track in frames, or 0 if the index is out of bounds.
     * @note A lifetime of 0 means the track is infinite and will not be released automatically. A positive lifetime means the track will be released after that many frames. The lifetime is decremented each frame by the `Track_Pool` class, and when it reaches 0, the track is released back to the pool.
     */
    uint32_t get_dynamic_track_lifetime(size_t index) const {
        if (index < m_tracks.size()) {
            return m_tracks[index]->lifetime;
        }
        return 0; // Return 0 if index is out of bounds
    }

    /**
     * @brief Sets the lifetime of a dynamic track in frames.
     * @param index The index of the track in the pool.
     * @param lifetime The new lifetime of the track in frames, 0 for infinite.
     * @note This function does nothing if the index is out of bounds.
     */
    void set_dynamic_track_lifetime(size_t index, uint32_t lifetime) {
        if (index < m_tracks.size()) {
            m_tracks[index]->lifetime = lifetime;
        }
    }

    /**
     * @brief Sets the master gain (volume) for all tracks in the pool.
     * @param gain The master gain value, where 0.0 is silent and
     * 1.0 is full volume. Values above 1.0 will amplify the audio (may cause distortion).
     */
    void set_master_gain(float gain) {
        if (m_mixer) {
            MIX_SetMixerGain(m_mixer, gain);
        }
    }

    /**
     * @brief Sets the frames per second (FPS) value used for lifetime calculations of dynamic tracks.
     * @param fps The new FPS value. Must be greater than 0.0.
     * @note You should insert the `Engine::avg_fps` value here, or the FPS value you are using for your game loop.
     */
    void set_fps(float fps) { if(fps > 0.0f) this->fps = fps; else this->fps = 60.0f; } // Default to 60.0 if invalid value is provided

    /**
     * @brief Sets the logger to be used for logging messages from the track pool.
     * @param logger Pointer to the Logger instance to use for logging. If `nullptr`, logging will be disabled.
     */
    void set_logger(Logger* logger) { m_logger = logger; }

    /**
     * @brief Sets the SDL_Mixer instance to be used for audio playback.
     * @param mixer Pointer to the new SDL_Mixer instance.
     */
    void set_mixer(MIX_Mixer* mixer) { m_mixer = mixer; }

    /**
     * @brief Gets the SDL_Mixer instance used by this pool.
     * @return Pointer to the SDL_Mixer instance.
     */
    MIX_Mixer* get_mixer() const { return m_mixer; }

    Track_Pool(const Track_Pool&) = delete;
    Track_Pool& operator=(const Track_Pool&) = delete;

    Track_Pool(Track_Pool&&) = delete;
    Track_Pool& operator=(Track_Pool&&) = delete;

private:
    bool m_initialized = false;
    MIX_Mixer* m_mixer = nullptr;
    std::vector<std::unique_ptr<ITrack>> m_tracks;
    uint8_t m_default_track_count = 8;
    float fps = 60.0f; // Default frames per second for lifetime calculations

    Logger* m_logger = nullptr;
};

#endif
