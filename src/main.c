#include "../include/consts.h"
#include "../include/helpers.h"
#include "../include/rendering.h"

int arena[NUM_ROWS][NUM_COLS];

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
