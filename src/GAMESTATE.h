#pragma once

#include <raylib.h>

#include <stdarg.h>
#include <vector>
#include <string>


namespace GAMESTATE {
    inline bool PLAYING;
    inline bool PAUSED;

    inline float WINDOW_WIDTH  = 1200.f;
    inline float WINDOW_HEIGHT = 450.f;
    inline float WINDOW_X;
    inline float WINDOW_Y;

    inline float SCREEN_WIDTH;
    inline float SCREEN_HEIGHT;

    inline float window_movment_speed = 0.02;

    inline float gravity = 0.5;

    inline float y = WINDOW_HEIGHT - 150;
    inline float x = 80;

    //max space to the left = 515
    //max space to the right = 515

    //platform width = 150
    //platform height = 15

    inline std::vector<Rectangle> platforms = {
      {0, WINDOW_HEIGHT - 10, WINDOW_WIDTH, 10}, // floor
      {80, WINDOW_HEIGHT - 150, 150, 15}
    };

    inline std::string current_music_track = "main music";
}
