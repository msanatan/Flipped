// Marcus Sanatan (msanatan)
// April 22nd, 2020
// Flipped

#include <Arduboy2.h>
#include <math.h>

#include "src/images.h"
#include "src/level.h"
#include "src/maps.h"
#include "src/player.h"
Arduboy2 arduboy;

// Game settings
const int FPS = 60;
const int TILE_SIZE = 8;
int gravity = 1;
unsigned long playerJumpDuration = 0;
Player player = {0, HEIGHT - 16, 1, 1, 8, 0.25, playerSprite};
Level level1 = Level{map1, 16, 8, 0, 6, 15, 6, flagSprite};

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(FPS);
  arduboy.clear();
  Serial.begin(9600);
}

void drawWorld(Level level, const unsigned char tile[], int tileSize) {
  int positionY = 0;
  for (int y = 0; y < level.getHeight(); y++) {
    int positionX = 0;
    for (int x = 0; x < level.getWidth(); x++) {
      if (level.map[y][x] > 0) {
        Sprites::drawOverwrite(positionX, positionY, tile, 0);
      }
      positionX = positionX + tileSize;
    }

    positionY = positionY + tileSize;
  }

  Point goalPosition = level.getGoalPosition();
  Sprites::drawOverwrite(goalPosition.x, goalPosition.y, level.getGoalImage(),
                         0);
}

void checkCollision(Level level) {
  // Reset collision flags
  player.setOnFloor(false);
  player.setTouchingTop(false);
  player.setTouchingRight(false);
  player.setTouchingLeft(false);

  // Get the "end" points of contact
  int playerEndY = player.y + player.getSize();
  int playerEndX = player.x + player.getSize();

  // Check if out of horizontal scope
  if (player.x <= 0) {
    player.setTouchingLeft(true);
  }

  if (player.x + player.getSize() >= level.getWidth() * 8) {
    player.setTouchingRight(true);
  }

  // Check if out of vertical scope i.e. dead
  if (playerEndY <= 0 || player.y > level.getHeight() * 8) {
    if (player.isFlipped()) {
      gravity = -gravity;
    }
    player.reset(level.getStartingPoint());
    return;
  }

  // The tile the player resides
  int playerTileY = player.y / TILE_SIZE;
  int playerTileX = player.x / TILE_SIZE;

  // Details of the surrounding tiles
  int bottomY = min(playerEndY / TILE_SIZE, level.getHeight() - 1);
  int rightX = min(playerEndX / TILE_SIZE, level.getWidth() - 1);
  int topY = max(playerTileY - 1, 0);
  int leftX = max(playerTileX - 1, 0);

  /* Bottom collision: the player's end is at the beginning of the tile and
  either there's a tile right below us or we're partially on a tile to the
  bottom right
  */
  if (playerEndY == (bottomY * TILE_SIZE) &&
      (level.map[bottomY][playerTileX] ||
       (level.map[bottomY][rightX] && playerEndX > rightX * TILE_SIZE))) {
    if (player.isFlipped()) {
      player.setTouchingTop(true);
    } else {
      player.setOnFloor(true);
    }
  }

  /* Top collision: the player's y value is at the end of the top tile and
  either the tile is right above us or we're partially hitting a tile to the
  top right
  */
  if (player.y == (topY * TILE_SIZE) + TILE_SIZE &&
      (level.map[topY][playerTileX] ||
       (level.map[topY][rightX] && playerEndX > rightX * TILE_SIZE))) {
    if (player.isFlipped()) {
      player.setOnFloor(true);
    } else {
      player.setTouchingTop(true);
    }
  }

  /* Left collision: the player's x value is at the end of the left tile and
  either the tile is immediately on our left or we're partially hitting a tile
  to the bottom left
  */
  if (player.x == (leftX * TILE_SIZE) + TILE_SIZE &&
      (level.map[playerTileY][leftX] ||
       (level.map[bottomY][leftX] && !player.isOnFloor()))) {
    player.setTouchingLeft(true);
  }

  /* Right collision: the player's end is at the beginning of the right tile
  and either the tile is immediately on our right or we're partially hitting a
  tile to the bottom right
  */
  if (playerEndX == rightX * TILE_SIZE &&
      (level.map[playerTileY][rightX] ||
       (level.map[bottomY][rightX] && !player.isOnFloor()))) {
    player.setTouchingRight(true);
  }
}

void applyGravity() {
  if (!player.isJumping() && !player.isOnFloor()) {
    player.y = player.y + gravity;
  } else if (player.isJumping())  // Keep going up if jumping
  {
    player.y = player.y - player.speedY;

    // Determine whether we need to stop jumping
    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - playerJumpDuration;
    float deltaSeconds = deltaTime * (1.0f / 1000.0f);

    if ((deltaSeconds >= player.getJumpDuration()) || player.isTouchingTop()) {
      player.toggleJumping();
      playerJumpDuration = 0;
    }
  }
}

void movePlayer() {
  player.setMoving(false);
  if (arduboy.pressed(LEFT_BUTTON) && !player.isTouchingLeft()) {
    player.x = player.x - player.speedX;
    player.setMoving(true);
    player.setDirection(LEFT);
  } else if (arduboy.pressed(RIGHT_BUTTON) && !player.isTouchingRight()) {
    player.x = player.x + player.speedX;
    player.setMoving(true);
    player.setDirection(RIGHT);
  }

  if (arduboy.justPressed(B_BUTTON) && player.isOnFloor()) {
    player.y = player.y - player.speedY;
    player.toggleJumping();
    playerJumpDuration = millis();
    player.setMoving(true);
  }

  if (arduboy.justPressed(A_BUTTON) && player.isOnFloor()) {
    gravity = -gravity;
    player.toggleFlipped();
    player.setMoving(true);
  }

  player.nextFrame();
}

void drawPlayer() {
  Sprites::drawOverwrite(player.x, player.y, player.getImage(),
                         player.getFrame());
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }

  arduboy.clear();
  arduboy.pollButtons();

  // Check collision and gravity
  checkCollision(level1);
  applyGravity();
  // Move player
  movePlayer();

  // Draw tiles
  drawWorld(level1, floorTile, TILE_SIZE);
  // Draw player
  drawPlayer();

  // Render the state of the game scene
  arduboy.display();
}
