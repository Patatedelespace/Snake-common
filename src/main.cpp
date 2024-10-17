#include <raylib.h>

#include <cstdarg>
#include "Player.h"
#include "GAMESTATE.h"
#include <iostream>
#include <map>

void player_process(Player& player);

std::map<std::string, Music> musics_list = {
    {"main music", LoadMusicStream(ASSETS_PATH"main_bg_music.mp3")}
};

int main()
{
    std::cout << "Hello, world!" << std::endl;

    InitAudioDevice();

    Music music;

    InitWindow(GAMESTATE::SCREEN_WIDTH, GAMESTATE::SCREEN_HEIGHT, "Snake (en faite c'était plus fun de faire un platformer) (tkt frère pour les copyrights)");
    SetWindowIcon(LoadImage(ASSETS_PATH"Icon.png"));
    SetTargetFPS(60);

    Player player = Player(LoadTexture(ASSETS_PATH"Player.png"));

    float player_scale_divisor = 16;

    player.resize(player.getRectangle().width / player_scale_divisor, player.getRectangle().height / player_scale_divisor);

    GAMESTATE::PLAYING = true;

    // music = musics_list[std::string("main music")];git 

    // music.loopCount = 3;

    PlayMusicStream(/*music*/  musics_list[std::string("main music")]);

    SetMasterVolume(1);

    while (!WindowShouldClose()) {

        player_process(player);

        BeginDrawing();

        ClearBackground(BLUE);

        DrawTextureRec(player.getSprite(), player.getRectangle(), player.getPosition(), WHITE);

        for (Rectangle i : GAMESTATE::dirt_floors) {
            DrawRectangle(i.x, i.y, i.width, i.height, GREEN);
        }

        DrawLineEx({player.getCollisionRectangle().x + player.getCollisionRectangle().width, player.getCollisionRectangle().y}, {player.getCollisionRectangle().x + player.getCollisionRectangle().width, player.getCollisionRectangle().y + player.getCollisionRectangle().height}, 1, RED);

        EndDrawing();
    }

    GAMESTATE::PLAYING = false;

    UnloadTexture(player);

    CloseWindow();
    return 0;
}

void player_process(Player& player) {

    float player_x_movement;

    if ((IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)) || (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))) {

        if (player.getVelocity().x < 0.2 && player.getVelocity().x > -0.2) {
            player_x_movement = 0;
        }
        else {
            std::cout << "no key detected." << std::endl;

            int velocity_x_sign = (player.getVelocity().x > 0) - (player.getVelocity().x < 0);

            switch (velocity_x_sign) {

                case -1:
                    std::cout << "stopping left movement" << std::endl;
                    player_x_movement = (-player.getMoveSmoothness() > player.getVelocity().x) ? player.getVelocity().x + player.getMoveSmoothness() : 0;
                    break;

                case 1:
                    std::cout << "stopping right movement" << std::endl;
                    player_x_movement = (player.getMoveSmoothness() < player.getVelocity().x) ? player.getVelocity().x - player.getMoveSmoothness() : 0;
                    break;

            }

        }
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        player_x_movement = (player.getVelocity().x < player.getSpeed()) ? player.getVelocity().x + player.getMoveSmoothness() : player.getSpeed();
    }
    else if (IsKeyDown(KEY_LEFT)) {
        player_x_movement = (player.getVelocity().x > -player.getSpeed()) ? player.getVelocity().x - player.getMoveSmoothness() : -player.getSpeed();
    }


    player.setVelocityX(player_x_movement);

    std::cout << player.getVelocity().x << ";" << player.getVelocity().y << "(" << ((int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT)) * player.getSpeed() << ")" << std::endl;

    if (player.getVelocity().x != 0) {
        player.setDirection((player.getVelocity().x < 0) ? -1 : 1);
    }

    if (IsKeyDown(KEY_SPACE) && player.isOnGround()) player.setVelocityY(-player.getJumpStrengh());

    if (player.getVelocity().y < player.getJumpStrengh()) {
        player.setVelocityY(player.getVelocity().y + GAMESTATE::gravity);
    }

    player.move();

    player.setRealPosition((Vector2) {player.getPosition().x - player.getRectangle().width / 2, player.getPosition().y - player.getRectangle().width /2});

    player.setCollisionRectangle((Rectangle){player.getPosition().x, player.getPosition().y, player.getRectangle().width, player.getRectangle().height});
}
