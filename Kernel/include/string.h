#ifndef _STRING_H_
#define _STRING_H_

#include <stdint.h>

uint32_t uintToBase2(uint64_t value, char *buffer, uint32_t base);
int strlen(const char *str);

#endif