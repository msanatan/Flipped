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

    // Get the "end" points of contact
    int playerEndY = player.y + player.getSize();
    int playerEndX = player.x + player.getSize();

    // The tile the player resides
    int playerTileY = player.y / TILE_SIZE;
    int playerTileX = player.x / TILE_SIZE;

    // Details of the surrounding tiles
    int bottomY = min(playerEndY / TILE_SIZE, height - 1);
    int rightX = min(playerEndX / TILE_SIZE, width - 1);
    int topY = max(playerTileY - 1, 0);
    int leftX = max(playerTileX - 1, 0);

    /* Bottom collision: the player's end is at the beginning of the tile and
    either there's a tile right below us or we're partially on a tile to the
    bottom right
    */
    if (playerEndY == (bottomY * TILE_SIZE) &&
        (level[bottomY][playerTileX] ||
         (level[bottomY][rightX] && playerEndX > rightX * TILE_SIZE)))
    {
        if (player.isFlipped())
        {
            player.setTouchingTop(true);
        }
        else
        {
            player.setOnFloor(true);
        }
    }

    /* Top collision: the player's y value is at the end of the top tile and
    either the tile is right above us or we're partially hitting a tile to the
    top right
    */
    if (player.y == (topY * TILE_SIZE) + TILE_SIZE &&
        (level[topY][playerTileX] ||
         (level[topY][rightX] && playerEndX > rightX * TILE_SIZE)))
    {
        if (player.isFlipped())
        {
            player.setOnFloor(true);
        }
        else
        {
            player.setTouchingTop(true);
        }
    }

    /* Left collision: the player's x value is at the end of the left tile and
    either the tile is immediately on our left or we're partially hitting a tile
    to the bottom left
    */
    if (player.x == (leftX * TILE_SIZE) + TILE_SIZE &&
        (level[playerTileY][leftX] ||
         (level[bottomY][leftX] && !player.isOnFloor())))
    {
        player.setTouchingLeft(true);
    }

    /* Right collision: the player's end is at the beginning of the right tile
    and either the tile is immediately on our right or we're partially hitting a
    tile to the bottom right
    */
    if (playerEndX == rightX * TILE_SIZE &&
        (level[playerTileY][rightX] ||
         (level[bottomY][rightX] && !player.isOnFloor())))
    {
        player.setTouchingRight(true);
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

    if (arduboy.justPressed(A_BUTTON))
    {
        gravity = -gravity;
        player.toggleFlipped();
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
