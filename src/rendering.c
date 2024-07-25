#include "../include/rendering.h"

int argc;
char **argv;

void displayInit() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void displayEnd() { glutSwapBuffers(); }

void drawScene() {
  drawArena();
  drawPlayer(player_01);
  drawPlayer(player_02);
}

void display() {
  displayInit();
  drawScene();
  displayEnd();
}

void drawArena() {
  int x0;
  int y0;
  int i;
  int j;
  for (i = 0; i < NUM_ROWS; i++) {
    for (j = 0; j < NUM_COLS; j++) {
      x0 = i * CELL_SIZE;
      y0 = j * CELL_SIZE;
      if (arena[j][i] == UNBREAKABLE_WALL) {
        glColor3f(0.9f, 0.9f, 0.9f);
      } else if (arena[j][i] == BREAKABLE_WALL) {
        glColor3f(0.5f, 0.5f, 0.5f);
      } else if (arena[j][i] == OPENED) {
        glColor3f(0.0f, 0.7f, 0.0f);
      } else if (arena[j][i] == BOMB) {
        glColor3f(0.0f, 0.0f, 0.0f);
      } else {
        glColor3f(0.0f, 1.0f, 1.0f);
      }
      glBegin(GL_QUADS);
      glVertex2i(x0 + 1, y0 + 1);
      glVertex2i(x0 + 1, CELL_SIZE + y0 - 1);
      glVertex2i(CELL_SIZE + x0 - 1, CELL_SIZE + y0 - 1);
      glVertex2i(CELL_SIZE + x0 - 1, y0 + 1);
      glEnd();
    }
  }
}

void drawPlayer(Player player) {
  if (player.life > 0) {
    if (player.id == 1) {
      glColor3f(1.0f, 0.0f, 0.0f);
    } else if (player.id == 2) {
      glColor3f(0.0f, 0.0f, 1.0f);
    }
    glBegin(GL_QUADS);
    glVertex2i(player.position.x - HALF_PLAYER_SIZE,
               player.position.y - HALF_PLAYER_SIZE);
    glVertex2i(player.position.x + HALF_PLAYER_SIZE,
               player.position.y - HALF_PLAYER_SIZE);
    glVertex2i(player.position.x + HALF_PLAYER_SIZE,
               player.position.y + HALF_PLAYER_SIZE);
    glVertex2i(player.position.x - HALF_PLAYER_SIZE,
               player.position.y + HALF_PLAYER_SIZE);
    glEnd();
  }
}

void glutStart() {
  glutInit(&argc, argv);
  glutTimerFunc(100, updateBombTimers, 0);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Bomberman");
  glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
  gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();
}
