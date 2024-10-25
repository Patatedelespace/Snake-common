#pragma once

#include <raylib.h>

#include <stdarg.h>
#include <vector>
#include <string>


namespace GAMESTATE {
    inline bool PLAYING;
    inline bool PAUSED;

    inline float SCREEN_WIDTH  = 1200.f;
    inline float SCREEN_HEIGHT = 450.f;

    inline float gravity = 0.5;

    inline float y = SCREEN_HEIGHT - 150;
    inline float x = 80;

    //max space to the left = 515
    //max space to the right = 515

    //platform width = 150
    //platform height = 15

    inline std::vector<Rectangle> dirt_floors = {
      {0, SCREEN_HEIGHT - 10, SCREEN_WIDTH, 10}, // floor
      {80, SCREEN_HEIGHT - 150, 150, 15}
    };

    inline std::string current_music_track = "main music";
}
