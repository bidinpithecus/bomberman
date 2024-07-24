#include "../include/consts.h"
#include "../include/helpers.h"
#include "../include/rendering.h"
#include "../include/structs.h"
#include <GL/freeglut_std.h>

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

// Fix hitbox - Done (maybe)
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

  if (isPositionAnOpenCell(new_position) ||
      canPlayerWalkThroughBomb(*player, new_position)) {
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

bool isPlayerAbleToPlantBomb(Player player) {
  if (isPositionAnOpenCell(player.position) && player.numOfBombsToPlant > 0) {
    return true;
  }

  return false;
}

// Fix hitbox -- Done (maybe)
bool isPositionAnOpenCell(Coord position) {
  int offset = 1;
  Coord cell_top_left;
  cell_top_left.x = (position.x - (int)HALF_PLAYER_SIZE) / CELL_SIZE;
  cell_top_left.y = (position.y - (int)HALF_PLAYER_SIZE) / CELL_SIZE;

  Coord cell_bottom_right;
  cell_bottom_right.x =
      (position.x - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;
  cell_bottom_right.y =
      (position.y - offset + (int)HALF_PLAYER_SIZE) / CELL_SIZE;

  Coord cell_top_right;
  cell_top_right.x = cell_bottom_right.x;
  cell_top_right.y = cell_top_left.y;

  Coord cell_bottom_left;
  cell_bottom_left.x = cell_top_left.x;
  cell_bottom_left.y = cell_bottom_right.y;

  return (arena[cell_top_left.y][cell_top_left.x] ==
          arena[cell_bottom_right.y][cell_bottom_right.x]) &&
         (arena[cell_top_right.y][cell_top_right.x] ==
          arena[cell_bottom_left.y][cell_bottom_left.x]) &&
         (arena[cell_bottom_right.y][cell_bottom_right.x] == OPENED);
}

// Fix hitbox -- Done (maybe)
bool canPlayerWalkThroughBomb(Player player, Coord new_position) {
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

bool isBombPlantedByPlayer(Coord cell, int playerId) {
  for (int i = 0; i < bombCount; i++) {
    if (bombs[i].cell.x == cell.x && bombs[i].cell.y == cell.y &&
        bombs[i].playerId == playerId) {
      return true;
    }
  }
  return false;
}

void explodeBomb(Bomb *bomb) {
  int coord_count = 0;
  Coord *explosion_coords = NULL;

  for (int dx = -bomb->radius; dx <= bomb->radius; dx++) {
    for (int dy = -bomb->radius; dy <= bomb->radius; dy++) {
      if (dx == 0 || dy == 0) {
        coord_count += 1;
      }
    }
  }

  explosion_coords = calloc(coord_count, sizeof(Coord));

  int i = 0;
  for (int dx = -bomb->radius; dx <= bomb->radius; dx++) {
    for (int dy = -bomb->radius; dy <= bomb->radius; dy++) {
      if (dx == 0 || dy == 0) {
        Coord cell = {bomb->cell.x + dx, bomb->cell.y + dy};
        explosion_coords[i++] = cell;
      }
    }
  }

  for (int i = 0; i < coord_count; i++) {
    Coord cell = {explosion_coords[i].x, explosion_coords[i].y};
    if (cell.x == bomb->cell.x && cell.y == bomb->cell.y) {
      arena[cell.y][cell.x] = OPENED;
      Player *player = getPlayerById(bomb->playerId);

      if (player != NULL) {
        player->numOfBombsPlanted -= 1;
        player->numOfBombsToPlant += 1;
      }
    } else {
      applyExplosionEffects(cell);
    }
  }

  int index = bomb - bombs;
  for (int i = index; i < bombCount; i++) {
    bombs[i] = bombs[i + 1];
  }
  bombCount -= 1;
  // playExplosionSound();
  // createExplosionAnimation(bomb.cell);
  glutPostRedisplay();
}

void applyExplosionEffects(Coord affectedCell) {
  if (arena[affectedCell.y][affectedCell.x] == BREAKABLE_WALL) {
    arena[affectedCell.y][affectedCell.x] = OPENED;
  } else if (arena[affectedCell.y][affectedCell.x] == BOMB) {
    Bomb *bomb = getBombByCell(affectedCell);

    if (bomb != NULL) {
      bomb->timer = 0;
    }
  }
}

Bomb *getBombByCell(Coord cell) {
  for (int i = 0; i < bombCount; i++) {
    if (bombs[i].cell.x == cell.x && bombs[i].cell.y == cell.y) {
      return &bombs[i];
    }
  }

  return NULL;
}

Player *getPlayerById(int id) {
  if (id == 1) {
    return &player_01;
  } else if (id == 2) {
    return &player_02;
  }

  return NULL;
}

void updateBombTimers(UNUSED int value) {
  for (int i = 0; i < bombCount;) {
    bombs[i].timer -= TICK;

    if (bombs[i].timer <= 0) {
      explodeBomb(&bombs[i]);
    } else {
      i++;
    }
  }

  glutTimerFunc(TICK, updateBombTimers, 0);
}

void setup() {
  start_player_01();
  start_player_02();
  prepareArena();
}

int main(UNUSED int argc, UNUSED char **argv) {
  setup();
  glutStart();

  return 0;
}
