#ifndef _STRINGS_H_
#define _STRINGS_H_

#include <stdint.h>

int strlen(const char *str);
int strncmp(const char *str1,const char *str2, int n);
int strcmp(const char *str1, const char *str2);
char *strappend(const char *src, char *dest);
char* numtostring(char *buf, int num);
int strtohex(const char *ptr);
char *numtoHexString(char *buf, char num);
uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base);

#endif