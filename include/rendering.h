#ifndef _RENDERING_H_
#define _RENDERING_H_

#include "consts.h"
#include "io.h"
#include <GL/glut.h>

void drawArena();
void drawPlayer(Player player);
void displayInit();
void displayEnd();
void drawScene();
void display();
void glutStart();

#endif
