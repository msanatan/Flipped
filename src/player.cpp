#include "player.h"

Player::Player(uint8_t x, uint8_t y, int speedX, int speedY, uint8_t size,
               float jumpDuration, const unsigned char *image) {
  this->x = x;
  this->y = y;
  this->speedX = speedX;
  this->speedY = speedY;
  this->originalSpeedY = speedY;
  this->size = size;
  this->jumpDuration = jumpDuration;
  this->image = image;
  this->jumping = false;
  this->onFloor = false;
  this->touchingLeft = false;
  this->touchingRight = false;
  this->touchingTop = false;
  this->frame = 0;
}

uint8_t Player::getSize() { return this->size; }

float Player::getJumpDuration() { return this->jumpDuration; }

Rect Player::getRect() {
  return Rect{this->x, this->y, this->size, this->size};
}

bool Player::isJumping() { return this->jumping; }

void Player::toggleJumping() { this->jumping = !this->jumping; }

bool Player::isOnFloor() { return this->onFloor; }

void Player::setOnFloor(bool onFloor) { this->onFloor = onFloor; }

bool Player::isTouchingLeft() { return this->touchingLeft; }

void Player::setTouchingLeft(bool touchingLeft) {
  this->touchingLeft = touchingLeft;
}

bool Player::isTouchingRight() { return this->touchingRight; }

void Player::setTouchingRight(bool touchingRight) {
  this->touchingRight = touchingRight;
}

bool Player::isTouchingTop() { return this->touchingTop; }

void Player::setTouchingTop(bool touchingTop) {
  this->touchingTop = touchingTop;
}

bool Player::isFlipped() { return this->flipped; }

void Player::toggleFlipped() {
  this->flipped = !flipped;
  this->speedY = -this->speedY;
}

uint8_t Player::getFrame() { return this->frame; }

void Player::setFrame(uint8_t frame) { this->frame = frame; }

const unsigned char *Player::getImage() { return this->image; }

void Player::reset(Point position) {
  this->x = position.x;
  this->y = position.y;
  this->speedY = this->originalSpeedY;
  this->jumping = false;
  this->onFloor = true;
  this->touchingLeft = false;
  this->touchingRight = false;
  this->touchingTop = false;
  this->flipped = false;
  this->frame = 0;
}
