#ifndef _LIBASM_H_
#define _LIBASM_H_

char* cpuVendor();
int sys_write(int fd, char* str, int count);
int sys_read(int fd, char *buffer, uint64_t count);

#endif