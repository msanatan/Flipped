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
const int TILE_SIZE = 8;
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

bool isValidTile(int x, int y)
{
    return level1[y][x];
}

void checkCollision(int worldEndX, int worldEndY)
{
    int leftXTileLocation = player.x / TILE_SIZE;                        // 120 - 15
    int rightXTileLocation = (player.x + player.getSize()) / TILE_SIZE;  // 128 - 16
    int topYTileLocation = player.y / TILE_SIZE;                         // 40 - 5
    int bottomYTileLocation = (player.y + player.getSize()) / TILE_SIZE; // 48 - 6

    // Check if player is touching ground
    if (bottomYTileLocation < worldEndY &&
        (isValidTile(leftXTileLocation, bottomYTileLocation) ||
         isValidTile(rightXTileLocation, bottomYTileLocation)))
    {
        player.setOnFloor(true);
    }
    else
    {
        player.setOnFloor(false);
    }

    // Check if player is touching the top
    if (isValidTile(leftXTileLocation, topYTileLocation) ||
        isValidTile(rightXTileLocation, topYTileLocation))
    {
        player.setTouchingTop(true);
    }
    else
    {
        player.setTouchingTop(false);
    }

    // Check if player is touching on its right
    if (rightXTileLocation < worldEndX &&
        (isValidTile(rightXTileLocation, topYTileLocation) ||
        isValidTile(rightXTileLocation, bottomYTileLocation)))
    {
        player.setTouchingRight(true);
    }
    else
    {
        player.setTouchingRight(false);
    }

    // Check if player is touching on its left
    if (isValidTile(leftXTileLocation, topYTileLocation) ||
        isValidTile(leftXTileLocation, bottomYTileLocation))
    {
        player.setTouchingLeft(true);
    }
    else
    {
        player.setTouchingLeft(false);
    }
}

void applyGravity()
{
    if (!player.isJumping() && !player.isOnFloor())
    {
        player.y = player.y + gravity;
    }
    else if (player.isJumping()) // Keep going up if jumping
    {
        player.y = player.y - player.speedY;

        // Determine whether we need to stop jumping
        unsigned long currentTime = millis();
        unsigned long deltaTime = currentTime - playerJumpDuration;
        float deltaSeconds = deltaTime * (1.0f / 1000.0f);

        if ((deltaSeconds >= player.getJumpDuration()) || player.isTouchingTop())
        {
            player.toggleJumping();
            playerJumpDuration = 0;
        }
    }
}

void movePlayer()
{
    if (arduboy.pressed(LEFT_BUTTON) && !player.isTouchingLeft())
    {
        player.x = player.x - player.speedX;
    }
    else if (arduboy.pressed(RIGHT_BUTTON) && !player.isTouchingRight())
    {
        player.x = player.x + player.speedX;
    }

    if (arduboy.justPressed(B_BUTTON) && player.isOnFloor())
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

    // Check collision and gravity
    checkCollision(16, 8);
    applyGravity();
    // Move player
    movePlayer();

    // Draw tiles
    drawWorld(level1, 16, 8, floorTile, TILE_SIZE);
    // Draw player
    drawPlayer();

    // Render the state of the game scene
    arduboy.display();
}
