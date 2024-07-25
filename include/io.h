#ifndef _IO_H_
#define _IO_H_

#include "consts.h"
#include "helpers.h"
#include "player.h"
#include "structs.h"

extern bool input_buffer[256];

void handleInput();
void keyboard(unsigned char key, UNUSED int x, UNUSED int y);
void keyboardUp(unsigned char key, UNUSED int x, UNUSED int y);
void idle();

#endif
