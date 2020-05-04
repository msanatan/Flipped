#include "level.h"

Level::Level(uint8_t (*map)[16], uint8_t width, uint8_t height, uint8_t startX,
             uint8_t startY, uint8_t goalX, uint8_t goalY,
             const unsigned char *goalImage) {
  this->map = map;
  this->width = width;
  this->height = height;
  this->startPosition = Point{startX * 8, startY * 8};
  this->goalPosition = Point{goalX * 8, goalY * 8};
  this->goalImage = goalImage;
}

Point Level::getStartingPoint() { return this->startPosition; }

Point Level::getGoalPosition() { return this->goalPosition; }

uint8_t Level::getWidth() { return this->width; }

uint8_t Level::getHeight() { return this->height; }

const unsigned char *Level::getGoalImage() { return this->goalImage; }