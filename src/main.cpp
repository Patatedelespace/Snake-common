#include <raylib.h>

#include "window.h"
#include <cstdarg>
#include "Player.h"
#include "GAMESTATE.h"
#include <iostream>
#include <map>
#include "Audio.h"
#include <thread>
#include <random>

#ifndef ASSETS_PATH
#define ASSETS_PATH
#endif


void player_process();

void platform_generation_process();

Audio::SoundPlayer music;

Player player;


int main() {
    std::cout << "Hello, world!" << std::endl;

    InitAudioDevice();

    InitWindow(GAMESTATE::SCREEN_WIDTH, GAMESTATE::SCREEN_HEIGHT, "Snake (en faite c'était plus fun de faire un platformer) (tkt frère pour les copyrights)");
    SetWindowIcon(LoadImage(ASSETS_PATH"Icon.png"));
    SetTargetFPS(60);

    player = Player(LoadTexture(ASSETS_PATH"Player.png"));

    float player_scale_divisor = 16;

    player.resize(player.getRectangle().width / player_scale_divisor, player.getRectangle().height / player_scale_divisor);

    GAMESTATE::PLAYING = true;

    SetMasterVolume(0.25);

    music.setCurrentSound(Audio::getMusic("main music"));

    music.setLooping(true);

    music.play();

    std::thread platform_generation_thread = std::thread(platform_generation_process);

    while (!WindowShouldClose()) {

        // !IsSoundPlaying ? PlaySound(music) : nothing();

        player_process();

        if (IsKeyPressed(KEY_S)) {
            music.stop();
        }
        if (IsKeyPressed(KEY_P)) {
            music.play();
        }
        if (IsKeyPressed(KEY_R)) {
            music.restart();
        }

        BeginDrawing();

        ClearBackground(BLUE);

        DrawTextureRec(player.getSprite(), player.getRectangle(), player.getPosition(), WHITE);

        for (Rectangle i : GAMESTATE::platforms) {
            DrawRectangle(i.x, i.y, i.width, i.height, GREEN);
        }

        DrawLineEx({player.getCollisionRectangle().x + player.getCollisionRectangle().width, player.getCollisionRectangle().y}, {player.getCollisionRectangle().x + player.getCollisionRectangle().width, player.getCollisionRectangle().y + player.getCollisionRectangle().height}, 1, RED);

        EndDrawing();

        std::cout << utility::wheel(0, 50, 55) << std::endl;
    }

    GAMESTATE::PLAYING = false;

    platform_generation_thread.join();

    UnloadTexture(player);

    CloseWindow();
    return 0;
}

void player_process() {

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


void platform_generation_process() {

    int timer = 2000;

    std::random_device rd;
    std::uniform_real_distribution<double> x_spacing_dist(-515.f, 515.f);
    double max_height = -600;
    unsigned int last_platform_index = 1;
    double y_spacing = 150;
    double width = 150;
    double height = 15;

    Rectangle last_platform;
    double x_pos;
    double y_pos;

    while (GAMESTATE::PLAYING) {
        if (timer <= 0) {
            last_platform = GAMESTATE::platforms[last_platform_index];

            x_pos = last_platform.x + x_spacing_dist(rd);
            x_pos = utility::wheel(0, GAMESTATE::SCREEN_WIDTH, x_pos);
            y_pos = last_platform.y - y_spacing;
            if (y_pos >= max_height) {
                GAMESTATE::platforms.push_back(Rectangle(x_pos, y_pos, width, height));

                last_platform_index++;
            }

            timer = 2000;
        }
        else {
            timer--;
        }
    }
    
}