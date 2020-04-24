#ifndef IMAGES_H
#define IMAGES_H

#define Image const unsigned char PROGMEM

Image floorTile[] =
{
// width, height,
8, 8,
0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff,
};

Image playerSprite[] =
{
// width, height,
8, 8,
// FRAME 00
0x00, 0x1c, 0x3e, 0x7e, 0x72, 0x32, 0x1c, 0x00,
// FRAME 01
0x00, 0x1c, 0x7e, 0x3e, 0x32, 0x72, 0x1c, 0x00,
// FRAME 02
0x00, 0x0e, 0x1f, 0x7f, 0x79, 0x19, 0x0e, 0x00,
// FRAME 03
0x00, 0xb8, 0xfc, 0x7c, 0x64, 0xe4, 0xb8, 0x00,
// FRAME 04
0x00, 0x1c, 0x32, 0x72, 0x7e, 0x3e, 0x1c, 0x00,
// FRAME 05
0x00, 0x1c, 0x72, 0x32, 0x3e, 0x7e, 0x1c, 0x00,
// FRAME 06
0x00, 0x0e, 0x19, 0x79, 0x7f, 0x1f, 0x0e, 0x00,
// FRAME 07
0x00, 0xb8, 0xe4, 0x64, 0x7c, 0xfc, 0xb8, 0x00,
};

#endif // !IMAGES_H
