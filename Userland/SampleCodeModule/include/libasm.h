#ifndef _LIBASM_H_
#define _LIBASM_H_

#include <stdint.h>

int write(int fd, char *str, int count);
int read(int fd, char *buffer, uint64_t count);

#endif