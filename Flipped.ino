// Marcus Sanatan (msanatan)
// April 22nd, 2020
// Flipped

#include <Arduboy2.h>
#include <math.h>
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
Rect tileRect; // Used for collision checking

void setup()
{
    arduboy.begin();
    arduboy.clear();
    arduboy.setFrameRate(FPS);
    arduboy.clear();
    Serial.begin(9600);
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

void checkCollision(int level[][16], int width, int height)
{
    // Reset collision flags
    player.setOnFloor(false);
    player.setTouchingTop(false);
    player.setTouchingRight(false);
    player.setTouchingLeft(false);

    // Check if out of horizontal scope
    if (player.x <= 0)
    {
        player.setTouchingLeft(true);
    }

    if (player.x + player.getSize() >= width * 8)
    {
        player.setTouchingRight(true);
    }

    // We don't want to check every object, just those around us
    int playerXTile = player.x / TILE_SIZE;
    int leftX = max(playerXTile - 1, 0);
    int rightX = min(playerXTile + 1, width - 1);

    int playerYTile = player.y / TILE_SIZE;
    int topY = max(playerYTile - 1, 0);
    int bottomY = min(playerYTile + 1, height - 1);
    int leftTileX = leftX * TILE_SIZE;
    int rightTileX = rightX * TILE_SIZE;
    int topTileY = topY * TILE_SIZE;
    int bottomTileY = bottomY * TILE_SIZE;

    // Check if touching ground
    if (level[bottomY][playerXTile] ||
        (level[bottomY][rightX] &&
         player.x + player.getSize() > rightTileX))
    {
        player.setOnFloor(true);
    }
    else if (player.y == topTileY + TILE_SIZE &&
             (level[topY][playerXTile] ||
              (level[topY][rightX] &&
               player.x + player.getSize() > rightTileX)))
    {
        player.setTouchingTop(true);
    }

    // Check if touching right
    if (level[playerYTile][rightX])
    {
        player.setTouchingRight(true);
    }
    else if (level[playerYTile][leftX] && // and check left
             player.x == leftTileX + TILE_SIZE)
    {
        player.setTouchingLeft(true);
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
    checkCollision(level1, 16, 8);
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
