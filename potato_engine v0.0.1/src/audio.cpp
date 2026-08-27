#include "audio.h"
#include "engine.h"

Audio::Audio(const std::string& file_path, MIX_Mixer* mixer, bool predecode)
    : m_mixer(mixer) {
    resolve_engine_defaults();
    load(file_path, predecode);
}

Audio::Audio(const std::string& file_path, Track_Pool* track_pool, bool predecode)
    : m_track_pool(track_pool) {
    resolve_engine_defaults();
    load(file_path, predecode);
}

void Audio::resolve_engine_defaults() {
    if (!m_logger) {
        m_logger = Engine::logger;
    }

    if (!m_track_pool) {
        m_track_pool = Engine::track_pool;
    }

    if (!m_mixer && m_track_pool) {
        m_mixer = m_track_pool->get_mixer();
    }
}

void Audio::play() {
    resolve_engine_defaults();

    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No audio loaded to play.");
        return;
    }

    if (!m_track_pool) {
        if (m_mixer) {
            if (!MIX_PlayAudio(m_mixer, m_audio) && m_logger) {
                m_logger->log(Log_Level::ERROR, "Audio", std::string("Failed to play audio: ") + SDL_GetError());
            }
            m_props.state = Audio_State::PLAYING;
            return;
        }

        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No track pool or mixer available to play audio.");
        return;
    }

    if (m_track && m_track->track) {
        MIX_StopTrack(m_track->track, 0);
        MIX_SetTrackAudio(m_track->track, nullptr);
        m_track->audio = nullptr;
        m_track->current_state = Audio_State::STOPPED;
        m_track = nullptr;
    }

    m_track = m_track_pool->get_free_track();
    if (!m_track) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No free track available to play audio.");
        return;
    }
    m_track->audio = this;
    m_props.state = Audio_State::PLAYING;

    MIX_SetTrackAudio(m_track->track, m_audio);
    m_track_pool->update_track(m_track, m_props);
}

bool Audio::is_playing() const {
    return m_track && m_track->track && MIX_TrackPlaying(m_track->track);
}

void Audio::resume() {
    resolve_engine_defaults();

    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No audio loaded to resume.");
        return;
    }
    m_props.state = Audio_State::RESUMED;
}

void Audio::pause() {
    resolve_engine_defaults();

    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No audio loaded to pause.");
        return;
    }
    m_props.state = Audio_State::PAUSED;
}

void Audio::force_pause() {
    resolve_engine_defaults();

    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No audio loaded to force pause.");
        return;
    }

    m_props.state = Audio_State::PAUSED;

    if (m_track && m_track->track) {
        MIX_PauseTrack(m_track->track);
    }
}

void Audio::stop() {
    resolve_engine_defaults();

    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No audio loaded to stop.");
        return;
    }

    m_props.state = Audio_State::STOPPED;

    if (m_track && m_track->track) {
        MIX_StopTrack(m_track->track, m_props.fade_out_duration);

        if (m_track->audio && !MIX_TrackPlaying(m_track->track) && !MIX_TrackPaused(m_track->track)) {
            MIX_SetTrackAudio(m_track->track, nullptr);
            m_track->audio = nullptr;
            m_track->current_state = Audio_State::STOPPED;
            m_track = nullptr;
        }
    }
}

void Audio::force_stop() {
    resolve_engine_defaults();

    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No audio loaded to force stop.");
        return;
    }
    m_props.state = Audio_State::STOPPED;
    if (m_track && m_track->track) {
        MIX_StopTrack(m_track->track, 0); // Force stop without fade-out
        MIX_SetTrackAudio(m_track->track, nullptr);
        m_track->audio = nullptr;
    }
    m_track = nullptr;
}

void Audio::force_play() {
    resolve_engine_defaults();

    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No audio loaded to force play.");
        return;
    }

    if (!m_track_pool) {
        if (m_mixer) {
            if (!MIX_PlayAudio(m_mixer, m_audio) && m_logger) {
                m_logger->log(Log_Level::ERROR, "Audio", std::string("Failed to force play audio: ") + SDL_GetError());
            }
            m_props.state = Audio_State::PLAYING;
            return;
        }

        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No track pool or mixer available to play audio.");
        return;
    }

    if (m_track && m_track->track) {
        MIX_StopTrack(m_track->track, 0);
        MIX_SetTrackAudio(m_track->track, nullptr);
        m_track->audio = nullptr;
        m_track->current_state = Audio_State::STOPPED;
        m_track = nullptr;
    }

    m_track = m_track_pool->get_free_track();

    if (!m_track || !m_track->track) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No free track available to play audio.");
        return;
    }

    m_track->audio = this;
    m_props.state = Audio_State::PLAYING;

    MIX_SetTrackAudio(m_track->track, m_audio);
    m_track_pool->update_track(m_track, m_props);
}

void Audio::force_resume() {
    resolve_engine_defaults();

    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No audio loaded to force resume.");
        return;
    }

    m_props.state = Audio_State::RESUMED;

    if (m_track && m_track->track) {
        MIX_ResumeTrack(m_track->track);
        m_track->previous_state = m_track->current_state;
        m_track->current_state = Audio_State::PLAYING;
        m_props.state = Audio_State::PLAYING;
    }
}

void Audio::load(const std::string& file_path, bool predecode) {
    resolve_engine_defaults();

    if(m_audio) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Audio", "Audio already loaded, unloading first.");
        unload();
    }

    if (!m_mixer) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No mixer available to load audio.");
        return;
    }

    m_audio = MIX_LoadAudio(m_mixer, file_path.c_str(), predecode);
    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", std::string("Failed to load audio: ") + SDL_GetError());
    } else {
        if (m_logger) m_logger->log(Log_Level::INFO, "Audio", std::string("Loaded audio: ") + file_path);
        m_current_file_path = file_path;
    }
}

void Audio::unload() {
    resolve_engine_defaults();

    if (m_track && m_track->track) {
        MIX_StopTrack(m_track->track, 0);
        MIX_SetTrackAudio(m_track->track, nullptr);
        m_track->audio = nullptr;
        m_track = nullptr;
    }

    if (m_audio) {
        MIX_DestroyAudio(m_audio);
        m_audio = nullptr;

        if (m_logger) {
            m_logger->log(
                Log_Level::INFO,
                "Audio",
                std::string("Unloaded audio: ") + m_current_file_path
            );
        }

        m_current_file_path.clear();
    } else {
        if (m_logger) {
            m_logger->log(Log_Level::WARNING, "Audio", "No audio loaded to unload.");
        }
    }
}

void Audio::play_fnf() {
    resolve_engine_defaults();

    if (!m_audio) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No audio loaded to play.");
        return;
    }
    if (!m_mixer) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Audio", "No mixer available to play audio.");
        return;
    }
    if (!MIX_PlayAudio(m_mixer, m_audio) && m_logger) {
        m_logger->log(Log_Level::ERROR, "Audio", std::string("Failed to play audio: ") + SDL_GetError());
    }
}

bool Track_Pool::init(MIX_Mixer* mixer, uint8_t default_track_count, Logger* logger) {
    if (m_initialized) {
        if (logger) logger->log(Log_Level::WARNING, "Track_Pool", "Track pool already initialized.");
        return false;
    }
    if (!mixer) {
        if (logger) logger->log(Log_Level::ERROR, "Track_Pool", "No mixer provided for track pool initialization.");
        return false;
    }
    m_mixer = mixer;
    m_default_track_count = default_track_count;
    m_logger = logger;

    for (uint8_t i = 0; i < m_default_track_count; ++i) {
        create_new_default_track();
    }
    m_initialized = true;
    return true;
}

void Track_Pool::shutdown() {
    m_tracks.clear();
    m_initialized = false;
    m_mixer = nullptr;
    m_logger = nullptr;
}

ITrack* Track_Pool::get_free_track() {
    for (auto& track : m_tracks) {
        if (!track || !track->track) {
            if (m_logger) {
                m_logger->log(Log_Level::WARNING, "Track_Pool", "Found an invalid track in the pool.");
            }
            continue;
        }

        bool is_free = !MIX_TrackPlaying(track->track) && !MIX_TrackPaused(track->track);

        if (is_free) {
            if (track->audio) {
                track->audio->detach_track(track.get());
                track->audio = nullptr;
            }
            MIX_SetTrackAudio(track->track, nullptr);
            track->audio = nullptr;
            track->current_state = Audio_State::STOPPED;
            track->previous_state = Audio_State::STOPPED;

            if (m_logger) {
                m_logger->log(Log_Level::DEBUG, "Track_Pool", "Found a free track.");
            }

            return track.get();
        }
    }

    if (m_logger) {
        m_logger->log(Log_Level::WARNING, "Track_Pool", "No free tracks available. Creating a dynamic track.");
    }

    return create_new_dynamic_track(default_lifetime);
}

ITrack* Track_Pool::create_new_dynamic_track(uint32_t lifetime) {
    MIX_Track* new_track = MIX_CreateTrack(m_mixer);

    if (!new_track) {
        if (m_logger) {
            m_logger->log(
                Log_Level::ERROR,
                "Track_Pool",
                std::string("Failed to create new track: ") + SDL_GetError()
            );
        }
        return nullptr;
    }

    auto track = std::make_unique<ITrack>();
    track->track = new_track;
    track->lifetime = lifetime;

    if (lifetime > 0) {
        track->is_dynamic = true;
        track->has_timer = true;
        track->timer.start(static_cast<float>(lifetime) / fps);
    } else {
        track->is_dynamic = false;
        track->has_timer = false;
    }

    ITrack* raw_track = track.get();

    m_tracks.push_back(std::move(track));

    if (m_logger) {
        m_logger->log(Log_Level::INFO, "Track_Pool", "Created a new dynamic track.");
    }

    return raw_track;
}

void Track_Pool::create_new_default_track() {
    MIX_Track* new_track = MIX_CreateTrack(m_mixer);

    if (!new_track) {
        if (m_logger) {
            m_logger->log(
                Log_Level::ERROR,
                "Track_Pool",
                std::string("Failed to create new default track: ") + SDL_GetError()
            );
        }
        return;
    }

    auto track = std::make_unique<ITrack>();
    track->track = new_track;
    track->is_dynamic = false;
    track->has_timer = false;
    track->lifetime = 0;

    m_tracks.push_back(std::move(track));

    if (m_logger) {
        m_logger->log(Log_Level::INFO, "Track_Pool", "Created a new default track.");
    }
}

void Track_Pool::release_track(ITrack* track) {
    auto it = std::find_if(
        m_tracks.begin(),
        m_tracks.end(),
        [track](const std::unique_ptr<ITrack>& ptr) {
            return ptr.get() == track;
        }
    );

    if (it == m_tracks.end() || !track || !track->is_dynamic) {
        if (m_logger) {
            m_logger->log(Log_Level::WARNING, "Track_Pool", "Attempted to release an invalid or non-dynamic track.");
        }
        return;
    }

    if (track->audio) {
        track->audio->detach_track(track);
        track->audio = nullptr;
    }

    if (track->track) {
        MIX_StopTrack(track->track, 0);
        MIX_SetTrackAudio(track->track, nullptr);
    }

    m_tracks.erase(it);

    if (m_logger) {
        m_logger->log(Log_Level::INFO, "Track_Pool", "Released a dynamic track.");
    }
}

void Track_Pool::update_track(ITrack* track, const Audio_Props& props) {
    if (!track) {
        if (m_logger) m_logger->log(Log_Level::ERROR, "Track_Pool", "Attempted to update a null track.");
        return;
    }
    MIX_Audio* audio = MIX_GetTrackAudio(track->track);
    if (!audio) {
        if (m_logger) m_logger->log(Log_Level::WARNING, "Track_Pool", "Attempted to update a track with no audio.");
        return;
    }
    MIX_SetTrackGain(track->track, props.gain);
    const MIX_Point3D position = {props.position.x, props.position.y, props.position.z};
    MIX_SetTrack3DPosition(track->track, &position);
    MIX_SetTrackFrequencyRatio(track->track, props.pitch);
    MIX_SetTrackLoops(track->track, props.loop_count);
    if (track->current_state != props.state) {
        track->previous_state = track->current_state;
    switch (props.state) 
        {
        case Audio_State::STOPPED:
            MIX_StopTrack(track->track, props.fade_out_duration);
            track->current_state = Audio_State::STOPPED;
            break;
        case Audio_State::PLAYING:
            MIX_PlayTrack(track->track, 0);
            track->current_state = Audio_State::PLAYING;
            break;
        case Audio_State::PAUSED:
            MIX_PauseTrack(track->track);
            track->current_state = Audio_State::PAUSED;
            break;
        case Audio_State::RESUMED:
            MIX_ResumeTrack(track->track);
            track->current_state = Audio_State::PLAYING;
            break;
        default:
            break;
        }
    }
}

void Track_Pool::flush_tracks(float dt) {
    for (size_t i = 0; i < m_tracks.size(); ++i) {
        ITrack* track = m_tracks[i].get();

        if (!track) {
            continue;
        }

        if (track->audio) {
            update_track(track, track->audio->get_props());
        }

        if (track->is_dynamic && track->has_timer) {
            track->timer.tick(dt);

            if (track->timer.is_just_done()) {
                release_track(track);
                if (i > 0) {
                    --i;
                } else {
                    i = static_cast<size_t>(-1);
                }
            }
        }
    }
}
