// Marcus Sanatan (msanatan)
// April 22nd, 2020
// Flipped

#include <Arduboy2.h>
#include "src/images.h"
#include "src/levels.h"
#include "src/player.h"
Arduboy2 arduboy;

// Game settings
const int FPS = 60;
int gravity = 1;
unsigned long playerJumpDuration = 0;

Player player = {0, HEIGHT - 24, 1, 1, 8, 0.25, playerSprite};

void setup()
{
    arduboy.begin();
    arduboy.clear();
    arduboy.setFrameRate(FPS);
    arduboy.clear();
}

void drawWorld(int level[][16], int width, int height, const unsigned char PROGMEM tile[], int tileSize)
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

void movePlayer()
{
    // Apply gravity
    if (!player.isJumping())
    {
        player.y = player.y + gravity;
    }
    else // Keep going up if jumping
    {
        player.y = player.y - player.speedY;

        // Determine whether we need to stop jumping
        unsigned long currentTime = millis();
        unsigned long deltaTime = currentTime - playerJumpDuration;
        float deltaSeconds = deltaTime * (1.0f / 1000.0f);

        if (deltaSeconds >= player.getJumpDuration())
        {
            player.toggleJumping();
            playerJumpDuration = 0;
        }
    }

    if (arduboy.pressed(LEFT_BUTTON) && player.x > 0)
    {
        player.x = player.x - player.speedX;
    }
    else if (arduboy.pressed(RIGHT_BUTTON) && player.x + player.getSize() < WIDTH)
    {
        player.x = player.x + player.speedX;
    }

    if (arduboy.justPressed(B_BUTTON))
    {
        player.y = player.y - player.speedY;
        player.toggleJumping();
        playerJumpDuration = millis();
    }
}

void drawPlayer()
{
    Sprites::drawOverwrite(player.x, player.y, player.getImage(),
                           player.getFrame());
}

void loop()
{
    if (!arduboy.nextFrame())
    {
        return;
    }

    arduboy.clear();
    arduboy.pollButtons();

    // Move player
    movePlayer();

    // Draw tiles
    drawWorld(level1, 16, 8, floorTile, 8);
    // Draw player
    drawPlayer();

    // Render the state of the game scene
    arduboy.display();
}
