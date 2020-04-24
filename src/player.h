#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
    uint8_t x;
    uint8_t y;
    uint8_t speedX;
    uint8_t speedY;
    uint8_t size;
    float jumpDuration;
    bool jumping;
    uint8_t frame;
    const unsigned char *image;
};

#endif // !PLAYER_H
