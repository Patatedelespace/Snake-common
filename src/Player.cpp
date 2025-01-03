#include "Player.h"
#include "GAMESTATE.h"
#include "window.h"
#include <iostream>
#include "utility.h"

// Core functions


// Operators functions
Player::operator Texture2D() {
    return this->sprite;
}


// Getters functions
Vector2 Player::getPosition() {
    return this->position;
}

Vector2 Player::getVelocity() {
    return this->velocity;
}

int Player::getDirection() {
    return this->direction;
}

Vector2 Player::getRealPosition() {
    return this->real_position;
}

Texture2D Player::getSprite() {
    return this->sprite;
}

Rectangle Player::getRectangle() {
    return this->rectangle;
}

Rectangle Player::getCollisionRectangle() {
    return this->collision_rectangle;
}

double Player::getSpeed() {
    return this->speed;
}

double Player::getJumpStrengh() {
    return this->jump_strengh;
}

float Player::getMoveSmoothness() {
    return this->move_smoothness;
}


// Setters functions
void Player::setPosition(Vector2 position) {
    this->position = position;
}

void Player::setPositionX(float x) {
    this->position.x = x;
}

void Player::setPositionY(float y) {
    this->position.y = y;
}

void Player::setVelocity(Vector2 velocity) {
    this->velocity = velocity;
}

void Player::setVelocityX(float x) {
    this->velocity.x = x;
}

void Player::setVelocityY(float y) {
    this->velocity.y = y;
}

void Player::setDirection(int direction) {
    this->direction = direction;
}

void Player::setRealPosition(Vector2 real_position) {
    this->real_position = real_position;
}

void Player::setSprite(Texture2D sprite) {
    this->sprite = sprite;
}

void Player::setRectangle(Rectangle rectangle) {
    this->rectangle = rectangle;
}

void Player::setCollisionRectangle(Rectangle rectangle) {
    this->collision_rectangle = rectangle;
}

void Player::setSpeed(double speed) {
    this->speed = speed;
}

void Player::setJumpStrengh(double jump_strengh) {
    this->jump_strengh = jump_strengh;
}

void Player::setMoveSmoothness(float move_smoothness) {
    this->move_smoothness = move_smoothness;
}


// Other functions
void Player::move() {
    this->collision_rectangle.x = this->position.x; this->collision_rectangle.y = this->position.y;

    float player_y_center = this->position.y + (this->rectangle.height / 2);

    float bottom_collision_offset = 0;

    // Vector2 previous_position = this->position;

    // this->position.x += velocity.x; this->position.y += velocity.y;

    CollisionType collision_type = NONE;

    this->collision_rectangle.x += this->velocity.x;

    utility::wheel(0, GAMESTATE::WINDOW_WIDTH, this->collision_rectangle.x);

    for (Rectangle i : GAMESTATE::platforms) {
        // if ( ( ( (this->position.x > i.x) && (this->position.x < i.width) ) || ( (this->position.x + this->rectangle.width > i.x) && (this->position.x + this->rectangle.width < i.width) ) ) && ( ( (this->position.y > i.y)/*under top line*/ && (this->position.y < i.height)/*over bottom line*/ )/*with y*/ || ( (this->position.y + this->rectangle.height > i.y)/*under top line*/ && (this->position.y + this->rectangle.height < i.height)/*over bottom line*/ )/*with height*/  ) ) {
        //     this->position.x = previous_position.x;
        // }
        if (CheckCollisionRecs(this->collision_rectangle, i)) {
            // if ( ( (this->position.y + this->collision_rectangle.height / 2 < i.y) && (this->position.y + this->collision_rectangle.height / 2 < i.y) ) || ( (this->position.y + this->collision_rectangle.height / 2 > i.y) && (this->position.y + this->collision_rectangle.height / 2 > i.y) ) ) {
                   // this->position.y = previous_position.y;
            // }

            std::cout << "X collision !" << std::endl;

            // if (this->collision_rectangle.x == this->position.x) {
            //     if (this->position.x > i.x + 1) {
            //         this->position.x += (i.x + i.width) - this->position.x;
            //     }
            //     else if (this->position.x < i.x - 1) {
            //         this->position.x -= (this->position.x + this->rectangle.width) - i.x;
            //     }
            // }

            this->collision_rectangle.x = this->position.x;

            collision_type = X;

            break;

        }
    }

    this->collision_rectangle.y += this->velocity.y;

    float collision_object_y_center;

    bool y_collision_bottom = false;

    for (Rectangle i : GAMESTATE::platforms) {

        if (CheckCollisionRecs(this->collision_rectangle, i)) {

            y_collision_bottom = (this->position.y < i.y);

            collision_object_y_center = i.y + (i.height / 2);

            if (collision_object_y_center > player_y_center)
                bottom_collision_offset = (collision_object_y_center /*225*/ - player_y_center /*279.5*/) - (this->rectangle.height / 2 /*27.5*/) - (i.height / 2 /*25*/);
            else if (collision_object_y_center < player_y_center)
                bottom_collision_offset = (collision_object_y_center /*225*/ - player_y_center /*279.5*/) + (this->rectangle.height / 2 /*27.5*/) + (i.height / 2 /*25*/);


            if (this->collision_rectangle.y -.5 == this->position.y) {

                std::cout << "no movment collision detected !" << std::endl;

                if (this->position.y > i.y) {
                    this->position.y += (i.y + i.height) - this->position.y - .5;
                }
                else if (this->position.y <= i.y) {
                    this->position.y -= (this->position.y + this->rectangle.height) - i.y + .5;
                }
            }


            std::cout << "Bottom collision offset : " << bottom_collision_offset << std::endl;

            std::cout << "Y collision !" << std::endl;

            this->velocity.y = 0;

            collision_type = (collision_type == NONE) ? Y : X_AND_Y;
            break;

        }
    }

    on_ground = y_collision_bottom;

    std::cout << "Collision : ";

    switch (collision_type) {
        case NONE:
            std::cout << "NONE" << std::endl;
            this->position.x += this->velocity.x;
            utility::wheel(0, GAMESTATE::WINDOW_WIDTH, this->position.x);
            this->position.y += this->velocity.y;
            break;

        case X:
            std::cout << "X" << std::endl;
            this->position.y += velocity.y;
            break;

        case Y:
            std::cout << "Y" << std::endl;
            this->position.y += bottom_collision_offset;
            this->position.x += velocity.x;
            utility::wheel(0, GAMESTATE::WINDOW_WIDTH, this->position.x);
            break;

        case X_AND_Y:
            std::cout << "X_AND_Y" << std::endl;
            break;
    }

    // Rectangle floor = GAMESTATE::CollisionObjects[0];

    std::cout << "Position : {x : " << this->position.x << "; y : " << this->position.y << "}, Velocity : {x : " << this->velocity.x << "; y : " << this->velocity.y << "}\nPlayer size : {width : " << this->rectangle.width << "; height : " << this->rectangle.height << "}" << std::endl;
    std::cout << "Collision rect. position : {x : " << this->collision_rectangle.x << "; y : " << this->collision_rectangle.y << "};" << std::endl;


    window::update_window_geometry(*this);
}


void Player::resize(int width, int height) {
    this->sprite.width = width; this->sprite.height = height;
    this->rectangle.width = width; this->rectangle.height = height;
}


bool Player::isOnGround() {
    return this->on_ground;
}
