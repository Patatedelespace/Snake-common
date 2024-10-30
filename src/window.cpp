#include "window.h"

void window::update_window_geometry(Player& player) {

    if (player.getPosition().y <= 0 /*&& GAMESTATE::WINDOW_HEIGHT > GetScreenHeight()*/) {
        double distance = player.getPosition().y * -1;
        std::cout << "distance : " << distance << ";" << std::endl;
        std::cout << "before : {width : " << GAMESTATE::WINDOW_WIDTH << ", height : " << GAMESTATE::WINDOW_HEIGHT << "};" << std::endl;
        GAMESTATE::WINDOW_HEIGHT += distance;
        std::cout << "after : {width : " << GAMESTATE::WINDOW_WIDTH << ", height : " << GAMESTATE::WINDOW_HEIGHT << "};" << std::endl;
        SetWindowSize(GAMESTATE::WINDOW_WIDTH, GAMESTATE::WINDOW_HEIGHT);
        for (Rectangle& i : GAMESTATE::platforms) {
            i.y += distance;
        }
        player.setPositionY(player.getPosition().y + distance);

    }

}