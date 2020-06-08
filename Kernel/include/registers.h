#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include <stdint.h>

void snap_register(uint64_t *rsp, uint64_t *ip);
int printSnapRegisters();
int getRegistersSnap(uint64_t *ptr);

#endif