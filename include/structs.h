#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <stdbool.h>

typedef struct {
  int x;
  int y;
} Coord;

typedef struct {
  Coord position;
  int numOfBombsToPlant;
  int numOfBombsPlanted;
  Coord* newBombCoordPtr;
  int id;
} Player;

typedef struct {
  Coord cell;
  int timer;
  int playerId;
  int radius;
} Bomb;

typedef enum { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, PLANT_BOMB } actions;

#endif
