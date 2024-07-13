#include <GL/glut.h>
#include "../include/io.h"

void normalButtons(unsigned char key, UNUSED int x, UNUSED int y) {
  if (key == 'a' || key == 'A') {
    action(&player_01, MOVE_LEFT);
  }
  if (key == 'd' || key == 'D') {
    action(&player_01, MOVE_RIGHT);
  }
  if (key == 'w' || key == 'W') {
    action(&player_01, MOVE_UP);
  }
  if (key == 's' || key == 'S') {
    action(&player_01, MOVE_DOWN);
  }
  if (key == 27) {
    // ESCAPE key
    exit(0);
  }
  if (key == 32) {
    // SPACEBAR key
    action(&player_01, PLANT_BOMB);
  }

  if (key == 'j' || key == 'J') {
    action(&player_02, MOVE_LEFT);
  }
  if (key == 'l' || key == 'L') {
    action(&player_02, MOVE_RIGHT);
  }
  if (key == 'i' || key == 'I') {
    action(&player_02, MOVE_UP);
  }
  if (key == 'k' || key == 'K') {
    action(&player_02, MOVE_DOWN);
  }
  if (key == 'p' || key == 'P') {
    action(&player_02, PLANT_BOMB);
  }

  glutPostRedisplay();
}
