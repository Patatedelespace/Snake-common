#pragma once

namespace rl {
    #include <raylib.h>
}

#include <cstdarg>
#include "Player.h"
#include "GAMESTATE.h"
#include <iostream>
#include <map>
#include <thread>

#ifndef ASSETS_PATH
#define ASSETS_PATH
#endif


namespace Audio {

struct Sound {
    std::string title;
    rl::Sound rl_sound;
};

enum SoundState {
    STOPPED = 0,
    STARTED = 1
};

std::vector<Sound> musics_list = {
    {"main music", LoadSound(ASSETS_PATH"main_bg_music.mp3")}
};

Sound getMusic(std::string title);


class SoundPlayer {
private:
    Sound current_sound;
    bool looping = false;
    bool playing = false;
    std::thread player_process_thread;
    bool thread_must_run;
    SoundState sound_state = STOPPED;

public:
    //core functions
    SoundPlayer();
    ~SoundPlayer();

    //getters functions
    Sound getCurrentSound();
    std::string getCurrentSoundTitle();
    rl::Sound getCurrentSoundRLSound();
    bool isLooping();

    //setters functions
    void setCurrentSound(Sound sound);
    void setLooping(bool looping);

    //player functions
    void play();
    void stop();
    bool isPlaying();

    //process function
    void player_process();
};










}