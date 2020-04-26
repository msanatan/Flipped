#include "player.h"

Player::Player(uint8_t x, uint8_t y, int speedX, int speedY,
               uint8_t size, float jumpDuration, const unsigned char *image)
{
    this->x = x;
    this->y = y;
    this->speedX = speedX;
    this->speedY = speedY;
    this->size = size;
    this->jumpDuration = jumpDuration;
    this->image = image;
    this->jumping = false;
    this->onFloor = false;
    this->frame = 0;
}

uint8_t Player::getSize()
{
    return this->size;
}

float Player::getJumpDuration()
{
    return this->jumpDuration;
}

Rect Player::getRect()
{
    return Rect{this->x, this->y, this->size, this->size};
}

bool Player::isJumping()
{
    return this->jumping;
}

void Player::toggleJumping()
{
    this->jumping = !this->jumping;
}

bool Player::isOnFloor()
{
    return this->onFloor;
}

void Player::toggleOnFloor()
{
    this->onFloor = !this->onFloor;
}

uint8_t Player::getFrame()
{
    return this->frame;
}

void Player::setFrame(uint8_t frame)
{
    this->frame = frame;
}

const unsigned char *Player::getImage()
{
    return this->image;
}

void Player::reset(uint8_t x, uint8_t y, int speedX, int speedY)
{
    this->x = x;
    this->y = y;
    this->speedX = speedX;
    this->speedY = speedY;
    this->jumping = false;
    this->onFloor = false;
    this->frame = 0;
}
