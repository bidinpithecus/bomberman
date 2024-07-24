#include "../include/bomb.h"

Bomb bombs[MAX_BOMBS];
int bombCount = 0;

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
