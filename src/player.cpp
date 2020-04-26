#include "player.h"

Player::Player(uint8_t x, uint8_t y, uint8_t speedX, uint8_t speedY,
               uint8_t size, float jumpDuration, const unsigned char *image)
{
    this->x = x;
    this->y = y;
    this->speedX = speedX;
    this->speedY = speedY;
    this->size = size;
    this->jumpDuration = jumpDuration;
    this->image = image;
}

Player::getRect()
{
    return Rect { this->x, this->y, this->size, this->size }
}
