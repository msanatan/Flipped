#ifndef IMAGES_H
#define IMAGES_H

#define Image const unsigned char PROGMEM

Image floorTile[] = {
    // width, height,
    8, 8, 0xff, 0x91, 0x91, 0x91, 0x91, 0xff, 0x91, 0xff,
};

Image playerSprite[] = {
    // width, height,
    8,
    8,
    // FRAME 00
    0x3e,
    0x23,
    0xa2,
    0x2b,
    0xa2,
    0x2b,
    0x22,
    0x3f,
    // FRAME 01
    0x3f,
    0x22,
    0x2b,
    0xa2,
    0x2b,
    0xa2,
    0x23,
    0x3e,
    // FRAME 02
    0x7c,
    0xc4,
    0x45,
    0xd4,
    0x45,
    0xd4,
    0x44,
    0xfc,
    // FRAME 03
    0xfc,
    0x44,
    0xd4,
    0x45,
    0xd4,
    0x45,
    0xc4,
    0x7c,
};

#endif  // !IMAGES_H
