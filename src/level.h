#ifndef LEVEL_H
#define LEVEL_H

#include <Arduboy2.h>

class Level {
 private:
  uint8_t width;
  uint8_t height;
  Point startPosition;
  Point goalPosition;
  const unsigned char *goalImage;

 public:
  uint8_t (*map)[16];
  Level(uint8_t (*map)[16], uint8_t width, uint8_t height, uint8_t startX,
        uint8_t startY, uint8_t goalX, uint8_t goalY,
        const unsigned char *goalImage);
  Point getStartingPoint();
  Point getGoalPosition();
  uint8_t getWidth();
  uint8_t getHeight();
  const unsigned char *getGoalImage();
};

#endif  // !LEVEL_H
