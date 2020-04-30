#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>

class Player
{
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

public:
    uint8_t x;
    uint8_t y;
    int speedX;
    int speedY;
    Player(uint8_t x, uint8_t y, int speedX, int speedY, uint8_t size,
           float jumpDuration, const unsigned char *image);
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
    void setFrame(uint8_t frame);
    const unsigned char *getImage();
    void reset(uint8_t x, uint8_t y, int speedX, int speedY);
    void draw();
};

#endif // !PLAYER_H
