#include "../include/player.h"

Player player_01;
Player player_02;

void start_player_01() {
  player_01.position.x = (1.5 * CELL_SIZE);
  player_01.position.y = (1.5 * CELL_SIZE);
  player_01.numOfBombsPlanted = 0;
  player_01.numOfBombsToPlant = 1;
  player_01.id = 1;
  player_01.newBombCoordPtr = NULL;
  player_01.life = 1;
}

void start_player_02() {
  player_02.position.x = (2.5 * CELL_SIZE);
  player_02.position.y = (1.5 * CELL_SIZE);
  player_02.numOfBombsPlanted = 0;
  player_02.numOfBombsToPlant = 1;
  player_02.id = 2;
  player_02.newBombCoordPtr = NULL;
  player_02.life = 1;
}

Bomb plant_bomb(Player *player) {
  Coord playerCell;
  playerCell.x = (player->position.x) / CELL_SIZE;
  playerCell.y = (player->position.y) / CELL_SIZE;

  Bomb bomb;
  bomb.playerId = player->id;
  bomb.timer = 5000;
  bomb.cell = playerCell;
  bomb.radius = 1;

  arena[bomb.cell.y][bomb.cell.x] = BOMB;

  player->newBombCoordPtr = &(bombs[bombCount].cell);
  player->numOfBombsToPlant--;
  player->numOfBombsPlanted++;

  bombCount++;

  return bomb;
}

Player *getPlayerById(int id) {
  if (id == 1) {
    return &player_01;
  } else if (id == 2) {
    return &player_02;
  }

  return NULL;
}

bool isPlayerAbleToPlantBomb(Player player) {
  if (player.life > 0 && isPositionAnOpenCell(player.position) &&
      player.numOfBombsToPlant > 0) {
    return true;
  }

  return false;
}

bool canPlayerWalk(Player player, Coord new_position) {
  if (player.life <= 0) {
    return false;
  }

  int offset = 1;
  Coord outer_cell_top_left;
  outer_cell_top_left.x = (new_position.x - (int)HALF_PLAYER_SIZE) / CELL_SIZE;
  outer_cell_top_left.y = (new_position.y - (int)HALF_PLAYER_SIZE) / CELL_SIZE;

  Coord outer_cell_bottom_right;
  outer_cell_bottom_right.x =
      (new_position.x - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;
  outer_cell_bottom_right.y =
      (new_position.y - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;

  Coord outer_cell_top_right;
  outer_cell_top_right.x = outer_cell_bottom_right.x;
  outer_cell_top_right.y = outer_cell_top_left.y;

  Coord outer_cell_bottom_left;
  outer_cell_bottom_left.x = outer_cell_top_left.x;
  outer_cell_bottom_left.y = outer_cell_bottom_right.y;

  int outer_cell_top_left_arena =
      arena[outer_cell_top_left.y][outer_cell_top_left.x];
  int outer_cell_bottom_right_arena =
      arena[outer_cell_bottom_right.y][outer_cell_bottom_right.x];
  int outer_cell_top_right_arena =
      arena[outer_cell_top_right.y][outer_cell_top_right.x];
  int outer_cell_bottom_left_arena =
      arena[outer_cell_bottom_left.y][outer_cell_bottom_left.x];

  Coord inner_cell_top_left;
  inner_cell_top_left.x =
      (new_position.x + SPEED - (int)HALF_PLAYER_SIZE) / CELL_SIZE;
  inner_cell_top_left.y =
      (new_position.y + SPEED - (int)HALF_PLAYER_SIZE) / CELL_SIZE;

  Coord inner_cell_bottom_right;
  inner_cell_bottom_right.x =
      (new_position.x - offset - SPEED + (int)HALF_PLAYER_SIZE) / CELL_SIZE;
  inner_cell_bottom_right.y =
      (new_position.y - offset - SPEED + (int)HALF_PLAYER_SIZE) / CELL_SIZE;

  Coord inner_cell_top_right;
  inner_cell_top_right.x = inner_cell_bottom_right.x;
  inner_cell_top_right.y = inner_cell_top_left.y;

  Coord inner_cell_bottom_left;
  inner_cell_bottom_left.x = inner_cell_top_left.x;
  inner_cell_bottom_left.y = inner_cell_bottom_right.y;

  int inner_cell_top_left_arena =
      arena[inner_cell_top_left.y][inner_cell_top_left.x];
  int inner_cell_bottom_right_arena =
      arena[inner_cell_bottom_right.y][inner_cell_bottom_right.x];
  int inner_cell_top_right_arena =
      arena[inner_cell_top_right.y][inner_cell_top_right.x];
  int inner_cell_bottom_left_arena =
      arena[inner_cell_bottom_left.y][inner_cell_bottom_left.x];

  Coord current_cell_top_left;
  current_cell_top_left.x =
      (player.position.x - (int)HALF_PLAYER_SIZE) / CELL_SIZE;
  current_cell_top_left.y =
      (player.position.y - (int)HALF_PLAYER_SIZE) / CELL_SIZE;

  Coord current_cell_bottom_right;
  current_cell_bottom_right.x =
      (player.position.x - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;
  current_cell_bottom_right.y =
      (player.position.y - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;

  Coord current_cell_top_right;
  current_cell_top_right.x = current_cell_bottom_right.x;
  current_cell_top_right.y = current_cell_top_left.y;

  Coord current_cell_bottom_left;
  current_cell_bottom_left.x = current_cell_top_left.x;
  current_cell_bottom_left.y = current_cell_bottom_right.y;

  int current_cell_top_left_arena =
      arena[current_cell_top_left.y][current_cell_top_left.x];
  int current_cell_bottom_right_arena =
      arena[current_cell_bottom_right.y][current_cell_bottom_right.x];
  int current_cell_top_right_arena =
      arena[current_cell_top_right.y][current_cell_top_right.x];
  int current_cell_bottom_left_arena =
      arena[current_cell_bottom_left.y][current_cell_bottom_left.x];

  bool every_inner_corner_in_bomb =
      (inner_cell_top_left_arena == inner_cell_bottom_right_arena) &&
      (inner_cell_top_right_arena == inner_cell_bottom_left_arena) &&
      (inner_cell_top_right_arena == BOMB);
  bool every_outer_corner_in_bomb =
      (outer_cell_top_left_arena == outer_cell_bottom_right_arena) &&
      (outer_cell_top_right_arena == outer_cell_bottom_left_arena) &&
      (outer_cell_top_right_arena == BOMB);
  bool every_inner_part_same_as_outer_part =
      (inner_cell_top_left_arena == outer_cell_top_left_arena) &&
      (inner_cell_bottom_right_arena == outer_cell_bottom_right_arena) &&
      (inner_cell_top_right_arena == outer_cell_top_right_arena) &&
      (inner_cell_bottom_left_arena == outer_cell_bottom_left_arena);
  bool every_outer_part_same_as_current_part =
      (current_cell_top_left_arena == outer_cell_top_left_arena) &&
      (current_cell_bottom_right_arena == outer_cell_bottom_right_arena) &&
      (current_cell_top_right_arena == outer_cell_top_right_arena) &&
      (current_cell_bottom_left_arena == outer_cell_bottom_left_arena);
  bool outer_valid_side = (outer_cell_top_left_arena == OPENED ||
                           outer_cell_top_left_arena == BOMB) &&
                          (outer_cell_bottom_right_arena == OPENED ||
                           outer_cell_bottom_right_arena == BOMB) &&
                          (outer_cell_top_right_arena == OPENED ||
                           outer_cell_top_right_arena == BOMB) &&
                          (outer_cell_bottom_left_arena == OPENED ||
                           outer_cell_bottom_left_arena == BOMB);

  bool is_every_bomb_planted_by_player =
      isBombPlantedByPlayer(outer_cell_top_left, player.id) &&
      isBombPlantedByPlayer(outer_cell_bottom_right, player.id) &&
      isBombPlantedByPlayer(outer_cell_top_right, player.id) &&
      isBombPlantedByPlayer(outer_cell_bottom_left, player.id);

  bool every_outer_corner_in_own_bomb =
      every_outer_corner_in_bomb && is_every_bomb_planted_by_player;

  if (outer_valid_side &&
      !(every_inner_corner_in_bomb || every_outer_corner_in_bomb ||
        every_inner_part_same_as_outer_part)) {
    return every_outer_part_same_as_current_part;
  }

  if (every_inner_corner_in_bomb && outer_valid_side &&
      every_inner_part_same_as_outer_part) {
    if (!every_outer_corner_in_own_bomb) {
      return false;
    }
  }
  return (every_inner_corner_in_bomb && outer_valid_side) ||
         every_outer_corner_in_own_bomb || every_inner_part_same_as_outer_part;
}

void action(Player *player, actions act) {
  Coord new_position = player->position;

  switch (act) {
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

  if (canPlayerWalk(*player, new_position)) {
    if (player->newBombCoordPtr != NULL) {
      Coord bombCell;
      bombCell.x = player->newBombCoordPtr->x;
      bombCell.y = player->newBombCoordPtr->y;

      int offset = 1;
      Coord cell_top_left;
      cell_top_left.x = (new_position.x - (int)HALF_PLAYER_SIZE) / CELL_SIZE;
      cell_top_left.y = (new_position.y - (int)HALF_PLAYER_SIZE) / CELL_SIZE;

      Coord cell_bottom_right;
      cell_bottom_right.x =
          (new_position.x - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;
      cell_bottom_right.y =
          (new_position.y - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;

      Coord cell_top_right;
      cell_top_right.x = cell_bottom_right.x;
      cell_top_right.y = cell_top_left.y;

      Coord cell_bottom_left;
      cell_bottom_left.x = cell_top_left.x;
      cell_bottom_left.y = cell_bottom_right.y;

      bool top_left_still_on_bomb =
          (bombCell.x == cell_top_left.x && bombCell.y == cell_top_left.y);
      bool bottom_right_still_on_bomb = (bombCell.x == cell_bottom_right.x &&
                                         bombCell.y == cell_bottom_right.y);

      bool top_right_still_on_bomb =
          (bombCell.x == cell_top_right.x && bombCell.y == cell_top_right.y);
      bool bottom_left_still_on_bomb = (bombCell.x == cell_bottom_left.x &&
                                        bombCell.y == cell_bottom_left.y);

      if (!(bottom_right_still_on_bomb || top_left_still_on_bomb ||
            top_right_still_on_bomb || bottom_left_still_on_bomb)) {
        player->newBombCoordPtr = NULL;
      }
    }

    player->position = new_position;
  }
}

bool isAnyCornerOfPlayerInCell(Player player, Coord cell) {
  int offset = 1;
  Coord cell_top_left = {
      (player.position.x - (int)HALF_PLAYER_SIZE) / CELL_SIZE,
      (player.position.y - (int)HALF_PLAYER_SIZE) / CELL_SIZE};

  Coord cell_bottom_right = {
      (player.position.x - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE,
      (player.position.y - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE};

  Coord cell_top_right = {cell_bottom_right.x, cell_top_left.y};
  Coord cell_bottom_left = {cell_top_left.x, cell_bottom_right.y};

  return coordEquals(cell, cell_top_left) ||
         coordEquals(cell, cell_bottom_right) ||
         coordEquals(cell, cell_top_right) ||
         coordEquals(cell, cell_bottom_left);
}
