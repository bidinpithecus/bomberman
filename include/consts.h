#ifndef _CONSTS_H_
#define _CONSTS_H_

#define UNUSED __attribute__((unused))
#define UNBREAKABLE_WALL 0
#define BREAKABLE_WALL 1
#define OPENED 2
#define BOMB 4
#define PLAYER_01 5
#define PLAYER_02 6
#define PLAYER_03 7
#define PLAYER_04 8
#define NUM_ROWS 15
#define NUM_COLS 15
#define MAX_BOMBS NUM_ROWS *NUM_COLS
#define CELL_SIZE 64
#define SPEED 4
#define PLAYER_SIZE CELL_SIZE * 0.75
#define HALF_PLAYER_SIZE PLAYER_SIZE * 0.5
#define WINDOW_WIDTH NUM_COLS *CELL_SIZE
#define WINDOW_HEIGHT NUM_ROWS *CELL_SIZE
#define TICK 100

#endif
