#include "window.h"

void window::update_window_geometry(Player& player) {

    if (player.getPosition().y <= 0) {
        double distance = player.getPosition().x * -1;
        GAMESTATE::SCREEN_HEIGHT += distance;
        SetWindowSize(GAMESTATE::SCREEN_WIDTH, GAMESTATE::SCREEN_HEIGHT);
    }

}