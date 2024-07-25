#ifndef _COORD_H_
#define _COORD_H_

#include "consts.h"
#include "structs.h"
#include <stdbool.h>

bool isPositionAnOpenCell(Coord position);
bool coordEquals(Coord coord_1, Coord coord_2);

#endif
