#include "../include/io.h"
#include <GL/glut.h>

bool input_buffer[256];

void keyboard(unsigned char key, UNUSED int x, UNUSED int y) {
  input_buffer[key] = true;
}

void keyboardUp(unsigned char key, UNUSED int x, UNUSED int y) {
  input_buffer[key] = false;
}

void handleInput() {
  if (input_buffer['a'] || input_buffer['A']) {
    action(&player_01, MOVE_LEFT);
  }
  if (input_buffer['d'] || input_buffer['D']) {
    action(&player_01, MOVE_RIGHT);
  }
  if (input_buffer['w'] || input_buffer['W']) {
    action(&player_01, MOVE_UP);
  }
  if (input_buffer['s'] || input_buffer['S']) {
    action(&player_01, MOVE_DOWN);
  }
  if (input_buffer[27]) {
    // ESCAPE key
    exit(0);
  }
  if (input_buffer[32]) {
    // SPACEBAR key
    action(&player_01, PLANT_BOMB);
  }

  if (input_buffer['j'] || input_buffer['J']) {
    action(&player_02, MOVE_LEFT);
  }
  if (input_buffer['l'] || input_buffer['L']) {
    action(&player_02, MOVE_RIGHT);
  }
  if (input_buffer['i'] || input_buffer['I']) {
    action(&player_02, MOVE_UP);
  }
  if (input_buffer['k'] || input_buffer['K']) {
    action(&player_02, MOVE_DOWN);
  }
  if (input_buffer['p'] || input_buffer['P']) {
    action(&player_02, PLANT_BOMB);
  }

  glutPostRedisplay();
}

void idle() { handleInput(); }
