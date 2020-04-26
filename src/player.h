#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    uint8_t x;
    uint8_t y;
    uint8_t speedX;
    uint8_t speedY;
    uint8_t size;
    float jumpDuration;
    bool jumping;
    uint8_t frame;
    const unsigned char *image;

public:
    Player(uint8_t x, uint8_t y, uint8_t speedX, uint8_t speedY, uint8_t size,
           float jumpDuration, const unsigned char *image);
    Rect getRect();
};

#endif // !PLAYER_H
