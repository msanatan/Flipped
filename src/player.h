#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>

enum Direction { LEFT, RIGHT };

class Player {
 private:
  uint8_t size;
  float jumpDuration;
  bool jumping;
  bool onFloor;
  bool touchingLeft;
  bool touchingRight;
  bool touchingTop;
  uint8_t frame;
  const unsigned char *image;
  bool flipped;
  int originalSpeedY;
  bool moving;
  Direction direction;

 public:
  int x;
  int y;
  int speedX;
  int speedY;
  Player(int x, int y, int speedX, int speedY, uint8_t size, float jumpDuration,
         const unsigned char *image);
  uint8_t getSize();
  float getJumpDuration();
  Rect getRect();
  bool isJumping();
  void toggleJumping();
  bool isOnFloor();
  void setOnFloor(bool onFloor);
  bool isTouchingLeft();
  void setTouchingLeft(bool touchingLeft);
  bool isTouchingRight();
  void setTouchingRight(bool touchingRight);
  bool isTouchingTop();
  void setTouchingTop(bool touchingTop);
  bool isFlipped();
  void toggleFlipped();
  uint8_t getFrame();
  void nextFrame();
  bool getMoving();
  void setMoving(bool moving);
  void setDirection(Direction direction);
  const unsigned char *getImage();
  void reset(Point position);
  void draw();
};

#endif  // !PLAYER_H
