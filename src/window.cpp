#include "window.h"

void window::update_window_geometry(Player& player) {

    if (player.getPosition().y <= 0) {
        double distance = player.getPosition().x * -1;
        std::cout << "distance : " << distance << ";" << std::endl;
        std::cout << "before : {width : " << GAMESTATE::SCREEN_WIDTH << ", height : " << GAMESTATE::SCREEN_HEIGHT << "};" << std::endl;
        GAMESTATE::SCREEN_HEIGHT += distance;
        std::cout << "after : {width : " << GAMESTATE::SCREEN_WIDTH << ", height : " << GAMESTATE::SCREEN_HEIGHT << "};" << std::endl;
        SetWindowSize(GAMESTATE::SCREEN_WIDTH, GAMESTATE::SCREEN_HEIGHT);
    }

}