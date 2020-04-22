// Marcus Sanatan (msanatan)
// April 22nd, 2020
// Flipped

#include <Arduboy2.h>
Arduboy2 arduboy;

const int FPS = 60;

void setup()
{
    arduboy.begin();
    arduboy.clear();
    arduboy.setFrameRate(FPS);
    arduboy.clear();
}

void loop()
{
    if (!arduboy.nextFrame())
    {
        return;
    }

    // Render the state of the game scene
    arduboy.display();
}
