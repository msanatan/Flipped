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

Player player;

void resetPlayer()
{
    player.x = 0;
    player.y = HEIGHT - 24;
    player.speedX = 1;
    player.speedY = 1;
    player.size = 8;
    player.jumpDuration = 0.25;
    player.jumping = false;
    player.frame = 0;
    player.image = playerSprite;
}

void setup()
{
    arduboy.begin();
    arduboy.clear();
    arduboy.setFrameRate(FPS);
    arduboy.clear();

    // Game init
    resetPlayer();
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
    if (!player.jumping)
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

        if (deltaSeconds >= player.jumpDuration)
        {
            player.jumping = false;
            playerJumpDuration = 0;
        }
    }

    if (arduboy.pressed(LEFT_BUTTON) && player.x > 0)
    {
        player.x = player.x - player.speedX;
    }
    else if (arduboy.pressed(RIGHT_BUTTON) && player.x + player.size < WIDTH)
    {
        player.x = player.x + player.speedX;
    }

    if (arduboy.justPressed(B_BUTTON))
    {
        player.y = player.y - player.speedY;
        player.jumping = true;
        playerJumpDuration = millis();
    }
}

void drawPlayer()
{
    Sprites::drawOverwrite(player.x, player.y, player.image, 0);
}

void loop()
{
    if (!arduboy.nextFrame())
    {
        return;
    }

    arduboy.clear();
    arduboy.pollButtons();

    // Draw tiles
    drawWorld(level1, 16, 8, floorTile, 8);
    // Move player
    movePlayer();
    drawPlayer();
    // Render the state of the game scene
    arduboy.display();
}
