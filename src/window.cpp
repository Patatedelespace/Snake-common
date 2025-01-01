#include "window.h"

#include <iostream>

#include "GAMESTATE.h"
#include "raylib.h"

void window::update_window_geometry(Player& player) {

    if (player.getPosition().y <= 0 /*&& GAMESTATE::WINDOW_HEIGHT < GetScreenHeight()*/) {
        double distance = player.getPosition().y * -1 + 10;
        std::cout << "distance : " << distance << ";" << std::endl;
        std::cout << "before : {width : " << GAMESTATE::WINDOW_WIDTH << ", height : " << GAMESTATE::WINDOW_HEIGHT << "};" << std::endl;
        GAMESTATE::WINDOW_HEIGHT += distance;
        std::cout << "after : {width : " << GAMESTATE::WINDOW_WIDTH << ", height : " << GAMESTATE::WINDOW_HEIGHT << "};" << std::endl;
        SetWindowSize(GAMESTATE::WINDOW_WIDTH, GAMESTATE::WINDOW_HEIGHT);
        for (Rectangle& i : GAMESTATE::platforms) {
            i.y += distance;
        }
        player.setPositionY(player.getPosition().y + distance);

        GAMESTATE::WINDOW_Y = GetWindowPosition().y - distance/2;

        SetWindowPosition(GAMESTATE::WINDOW_X, GAMESTATE::WINDOW_Y);

    }

}


void window::window_movment_process() {
    while (GAMESTATE::PLAYING) {
        if (IsKeyDown(KEY_W) && !(IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            std::cout << "KEY_W pressed;" << std::endl;
            GAMESTATE::WINDOW_Y += (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? GAMESTATE::window_movment_speed * 2: GAMESTATE::window_movment_speed;
            SetWindowPosition(GAMESTATE::WINDOW_X, GAMESTATE::WINDOW_Y);
        }
        if (IsKeyDown(KEY_S) && !(IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            std::cout << "KEY_S pressed;" << std::endl;
            GAMESTATE::WINDOW_Y -= (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? GAMESTATE::window_movment_speed * 2: GAMESTATE::window_movment_speed;
            SetWindowPosition(GAMESTATE::WINDOW_X, GAMESTATE::WINDOW_Y);
        }
    }
}