// Marcus Sanatan (msanatan)
// April 22nd, 2020
// Flipped

#include <Arduboy2.h>
#include "src/images.h"
#include "src/levels.h"
Arduboy2 arduboy;

const int FPS = 60;

void setup()
{
    arduboy.begin();
    arduboy.clear();
    arduboy.setFrameRate(FPS);
    arduboy.clear();
}

void drawWorld(int level[][16], int width, int height, unsigned char PROGMEM tile[], int tileSize)
{
    int positionY = 0;
    for (int y = 0; y < height; y++)
    {
        int positionX = 0;
        for (int x = 0; x < width; x++)
        {
            if (level[y][x] > 0)
            {
                Sprites::drawOverwrite(positionX, positionY, tile, 0);
            }
            positionX = positionX + tileSize;
        }

        positionY = positionY + tileSize;
    }
}

void loop()
{
    if (!arduboy.nextFrame())
    {
        return;
    }

    // Draw tiles
    drawWorld(level1, 16, 8, floorTile, 8);
    // Render the state of the game scene
    arduboy.display();
}
