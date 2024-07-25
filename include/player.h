#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "bomb.h"
#include "consts.h"
#include "coord.h"
#include "structs.h"
#include <stdio.h>

void start_player_01();
void start_player_02();
Bomb plant_bomb(Player *player);
bool isPlayerAbleToPlantBomb(Player player);
bool canPlayerWalk(Player player, Coord position);
Player *getPlayerById(int id);
void action(Player *player, actions act);
bool isAnyCornerOfPlayerInCell(Player player, Coord cell);

#endif
