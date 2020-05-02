#ifndef LEVEL_H
#define LEVEL_H

#include <Arduboy2.h>

class Level {
 private:
  uint8_t width;
  uint8_t height;
  Point startPosition;

 public:
  uint8_t (*map)[16];
  Level(uint8_t (*map)[16], uint8_t width, uint8_t height, uint8_t startX,
        uint8_t startY);
  Point getStartingPoint();
  uint8_t getWidth();
  uint8_t getHeight();
};

#endif  // !LEVEL_H
