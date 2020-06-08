#ifndef _LIBASM_H_
#define _LIBASM_H_

#include <stdint.h>
#include "time.h"

int write(int fd, char *str, int count,int x, int y);
int read(int fd, char *buffer, uint64_t count);
int time(int* date);
int invalidopcode();
uint8_t keyboard_status();
int inforeg(uint64_t* ptr);

#endif