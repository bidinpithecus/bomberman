#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <stdbool.h>

typedef struct Coord {
  int x;
  int y;
} Coord;

typedef struct Bomb {
  Coord cell;
  int timer;
  int playerId;
  int radius;
} Bomb;

typedef struct Player {
  Coord position;
  int numOfBombsToPlant;
  int numOfBombsPlanted;
  Coord *newBombCoordPtr;
  int id;
} Player;

typedef enum actions {
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
  PLANT_BOMB
} actions;

extern int arena[NUM_ROWS][NUM_COLS];
extern Bomb bombs[MAX_BOMBS];
extern int bombCount;
extern Player player_01;
extern Player player_02;

#endif
