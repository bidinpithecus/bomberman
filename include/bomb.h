#ifndef _BOMB_H_
#define _BOMB_H_

#include "consts.h"
#include "player.h"
#include "structs.h"
#include <GL/glut.h>
#include <stdlib.h>

bool isBombPlantedByPlayer(Coord cell, int playerId);
void updateBombTimers(UNUSED int value);
void explodeBomb(Bomb *bomb);
void applyExplosionEffects(Coord affectedCell);
Bomb *getBombByCell(Coord cell);

#endif
