#include "level.h"

Level::Level(uint8_t (*map)[16], uint8_t width, uint8_t height, uint8_t startX,
             uint8_t startY) {
  this->map = map;
  this->width = width;
  this->height = height;
  this->startPosition = Point{startX * 8, startY * 8};
}

Point Level::getStartingPoint() { return this->startPosition; }

uint8_t Level::getWidth() { return this->width; }

uint8_t Level::getHeight() { return this->height; }
