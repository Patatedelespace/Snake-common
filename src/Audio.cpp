#include "Audio.h"

Audio::Sound Audio::getMusic(std::string title) {
    for (Audio::Sound s : Audio::musics_list) {
        if (s.title == title) {
            return s;
        }
    }

    return {"not found", rl::LoadSound("")};
}

//core functions
Audio::SoundPlayer::SoundPlayer() {
    this->thread_must_run = true;
    this->player_process_thread = std::thread(Audio::SoundPlayer::player_process);
}

Audio::SoundPlayer::~SoundPlayer() {
    this->thread_must_run = false;
    this->player_process_thread.join();
}


//getters functions
Audio::Sound Audio::SoundPlayer::getCurrentSound() {
    return this->current_sound;
}

std::string Audio::SoundPlayer::getCurrentSoundTitle() {
    return this->current_sound.title;
}

rl::Sound Audio::SoundPlayer::getCurrentSoundRLSound() {
    return this->current_sound.rl_sound;
}

bool Audio::SoundPlayer::isLooping() {
    return this->looping;
}


//setters functions
void Audio::SoundPlayer::setCurrentSound(Sound sound) {
    this->current_sound = sound;
}

void Audio::SoundPlayer::setLooping(bool looping) {
    this->looping = looping;
}


//player functions
void Audio::SoundPlayer::play() {
    rl::PlaySound(this->current_sound.rl_sound);
    this->sound_state = STARTED;
}

void Audio::SoundPlayer::stop() {
    rl::StopSound(this->current_sound.rl_sound);
    this->sound_state = STOPPED;
}

bool Audio::SoundPlayer::isPlaying() {
    return this->playing;
}


//process function
void Audio::SoundPlayer::player_process() {
    while (this->thread_must_run) {
        this->playing = rl::IsSoundPlaying(this->current_sound.rl_sound);

        if (!rl::IsSoundPlaying(this->current_sound.rl_sound) && this->sound_state == STARTED) {
            if (this->looping) {
                rl::PlaySound(this->current_sound.rl_sound);
            }
            else {
                this->sound_state = STOPPED;
            }
        }
    }
    
}
