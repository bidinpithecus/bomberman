#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <stdio.h>
#include "structs.h"
#include "consts.h"

void prepareArena();
void action(Player* player, actions act);
void start_player_01();
void setup();
Bomb plant_bomb(Player* player);
bool isPositionAnOpenCell(Coord position);
bool isPlayerOnOwnBombCell(Player player);
bool isPlayerAbleToPlantBomb(Player player);
bool canPlayerWalkThroughBomb(Player player, Coord position);
bool isBombPlantedByPlayer(Coord cell, int playerId);
void updateBombTimers(int value);
void explodeBomb(Bomb* bomb);
void applyExplosionEffects(Coord affectedCell);
Bomb* getBombByCell(Coord cell);
Player* getPlayerById(int id);

#endif
