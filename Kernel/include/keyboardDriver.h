#ifndef _KEYBOARD_DRIVER_H_
#define _KEYBOARD_DRIVER_H_

#include <stdint.h>

void keyboard_handler(uint64_t *rsp);
int isBufferEmpty();
char getBufferChar();
int getSpecialKeysStatus();

#endif