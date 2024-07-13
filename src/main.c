#include "../include/structs.h"
#include "../include/consts.h"
#include "../include/helpers.h"
#include "../include/rendering.h"

int arena[NUM_ROWS][NUM_COLS];
Player player_01;
Player player_02;
Bomb bombs[MAX_BOMBS];
int bombCount = 0;

void start_player_01() {
  player_01.position.x = (1.5 * CELL_SIZE);
  player_01.position.y = (1.5 * CELL_SIZE);
  player_01.numOfBombsPlanted = 0;
  player_01.numOfBombsToPlant = 1;
  player_01.id = 1;
  player_01.newBombCoordPtr = NULL;
}

void start_player_02() {
  player_02.position.x = (2.5 * CELL_SIZE);
  player_02.position.y = (1.5 * CELL_SIZE);
  player_02.numOfBombsPlanted = 0;
  player_02.numOfBombsToPlant = 1;
  player_02.id = 2;
  player_02.newBombCoordPtr = NULL;
}

void prepareArena() {
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLS; j++) {
      arena[i][j] = BREAKABLE_WALL;
    }
  }

  for (int j = 0; j < NUM_COLS; j++) {
    arena[0][j] = arena[NUM_ROWS - 1][j] = UNBREAKABLE_WALL;
  }

  for (int j = 1; j < NUM_COLS - 1; j++) {
    arena[1][j] = arena[NUM_ROWS - 2][j] = OPENED;
  }

  arena[1][0] = arena[1][NUM_COLS - 1] = UNBREAKABLE_WALL;
  arena[NUM_ROWS - 2][0] = arena[NUM_ROWS - 2][NUM_COLS - 1] = UNBREAKABLE_WALL;

  for (int i = 1; i < NUM_ROWS - 1; i++) {
    arena[i][0] = UNBREAKABLE_WALL;
    arena[i][1] = OPENED;
    arena[i][NUM_COLS - 1] = UNBREAKABLE_WALL;
    arena[i][NUM_COLS - 2] = OPENED;
  }

  for (int i = 4; i < NUM_ROWS - 4; i++) {
    arena[i][1] = arena[i][NUM_COLS - 2] = BREAKABLE_WALL;
  }

  for (int i = 4; i < NUM_COLS - 4; i++) {
    arena[NUM_ROWS - 2][i] = arena[1][i] = BREAKABLE_WALL;
  }

  for (int i = 2; i < NUM_ROWS - 2; i += 2) {
    for (int j = 2; j < NUM_COLS - 2; j += 2) {
      arena[i][j] = UNBREAKABLE_WALL;
    }
  }
}

void action(Player* player, actions act) {
  Coord new_position = player->position;

  switch(act) {
    case MOVE_LEFT:
      new_position.x -= SPEED;
    break;

    case MOVE_RIGHT:
      new_position.x += SPEED;
    break;

    case MOVE_UP:
      new_position.y -= SPEED;
    break;

    case MOVE_DOWN:
      new_position.y += SPEED;
    break;

    case PLANT_BOMB:
      if (isPlayerAbleToPlantBomb(*player)) {
          bombs[bombCount] = plant_bomb(player);
      }

    break;
  }

  if (isPositionAnOpenCell(new_position) || canPlayerWalkThroughBomb(*player, new_position)) {
      if (player->newBombCoordPtr != NULL) {

          Coord bombCell;
          bombCell.x = player->newBombCoordPtr->x;
          bombCell.y = player->newBombCoordPtr->y;

          int offset = 1;
          Coord cell_top_left;
          cell_top_left.x = (new_position.x - (int)HALF_PLAYER_SIZE) / CELL_SIZE;
          cell_top_left.y = (new_position.y - (int)HALF_PLAYER_SIZE) / CELL_SIZE;

          Coord cell_bottom_right;
          cell_bottom_right.x = (new_position.x - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;
          cell_bottom_right.y = (new_position.y - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;

          bool bottom_right_still_on_bomb = (bombCell.x == cell_bottom_right.x && bombCell.y == cell_bottom_right.y);
          bool top_left_still_on_bomb = (bombCell.x == cell_top_left.x && bombCell.y == cell_top_left.y);

          if (!(bottom_right_still_on_bomb || top_left_still_on_bomb)) {
              arena[bombCell.y][bombCell.x] = BOMB;
              player->newBombCoordPtr = NULL;
          }
      }

    player->position = new_position;
  }
}

Bomb plant_bomb(Player* player) {
    Coord playerCell;
    playerCell.x = (player->position.x) / CELL_SIZE;
    playerCell.y = (player->position.y) / CELL_SIZE;

    Bomb bomb;
    bomb.playerId = player->id;
    bomb.timer = 5;
    bomb.cell = playerCell;

    arena[bomb.cell.y][bomb.cell.x] = NEW_BOMB;

    player->newBombCoordPtr = &(bombs[bombCount].cell);
    player->numOfBombsToPlant--;
    player->numOfBombsPlanted++;

    bombCount++;

    return bomb;
}

bool isPlayerAbleToPlantBomb(Player player) {
    if (isPositionAnOpenCell(player.position) && player.numOfBombsToPlant > 0) {
      return true;
    }

    return false;
}

bool isPositionAnOpenCell(Coord position) {
    int offset = 1;
    Coord cell_top_left;
    cell_top_left.x = (position.x - (int)HALF_PLAYER_SIZE) / CELL_SIZE;
    cell_top_left.y = (position.y - (int)HALF_PLAYER_SIZE) / CELL_SIZE;

    Coord cell_bottom_right;
    cell_bottom_right.x = (position.x - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;
    cell_bottom_right.y = (position.y - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;

    return (arena[cell_top_left.y][cell_top_left.x] == arena[cell_bottom_right.y][cell_bottom_right.x] && arena[cell_bottom_right.y][cell_bottom_right.x] == OPENED);
}

bool canPlayerWalkThroughBomb(Player player, Coord new_position) {
    int offset = 1;
    Coord cell_top_left;
    cell_top_left.x = (new_position.x - (int)HALF_PLAYER_SIZE) / CELL_SIZE;
    cell_top_left.y = (new_position.y - (int)HALF_PLAYER_SIZE) / CELL_SIZE;

    Coord cell_bottom_right;
    cell_bottom_right.x = (new_position.x - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;
    cell_bottom_right.y = (new_position.y - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;

    if (player.newBombCoordPtr == NULL) {
        return false;
    }

    bool top_left_is_own_bomb = (arena[cell_top_left.y][cell_top_left.x] == NEW_BOMB && isBombPlantedByPlayer(cell_top_left, player.id));
    bool bottom_right_is_own_bomb = (arena[cell_bottom_right.y][cell_bottom_right.x] == NEW_BOMB && isBombPlantedByPlayer(cell_bottom_right, player.id));

    bool top_left_is_open = (arena[cell_top_left.y][cell_top_left.x] == OPENED);
    bool bottom_right_is_open = (arena[cell_bottom_right.y][cell_bottom_right.x] == OPENED);

    return (top_left_is_own_bomb && bottom_right_is_open) || (bottom_right_is_own_bomb && top_left_is_open) || (top_left_is_own_bomb && bottom_right_is_own_bomb);
}

bool isBombPlantedByPlayer(Coord cell, int playerId) {
    for (int i = 0; i < bombCount; i++) {
        if (bombs[i].cell.x == cell.x && bombs[i].cell.y == cell.y && bombs[i].playerId == playerId) {
            return true;
        }
    }
    return false;
}

void setup() {
  start_player_01();
  start_player_02();
  prepareArena();
}

int main(UNUSED int argc, UNUSED char** argv) {
  setup();
  glutStart();

  return 0;
}
