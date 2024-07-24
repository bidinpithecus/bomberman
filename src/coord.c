#include "../include/coord.h"

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
