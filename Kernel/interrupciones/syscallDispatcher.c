#include <syscalls.h>
#include <stdint.h>
#include <video_driver.h>
#include <syscallDispatcher.h>
#include <keyboardDriver.h>
#include <interrupts.h>

#define SYSCALLS_COUNT 2

int syscall_write(uint64_t fd, char* str, uint64_t count, uint64_t rcx, uint64_t r8, uint64_t r9);
int syscall_read(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

int (*syscall[SYSCALLS_COUNT])(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = {syscall_read, syscall_write};

int syscall_write(uint64_t fd, char* str, uint64_t count, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    if(fd == 1){
        if (str == -1)
        {
            return 0;
        }
        else
        {
            return printString(str, count);
        }
    }
    else
    {
        return 0;
    }
}

int syscall_read(uint64_t fd, uint64_t buffer, uint64_t count, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    int cant = 0;
    char *buf = (char *)buffer;
    if (fd == 1)
    {
        while (cant < count)
        {
            while (isBufferEmpty())
                _hlt();
            char c = getBufferChar();
            buf[cant++] = c;
        }
        return cant;
    }
    else
    {
        return 0;
    }
}

void setup_syscalls()
{
    //syscall[1] = syscall_write;
}

int syscallDispatcher(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    if (rax < 0 || rax > SYSCALLS_COUNT)
    {
        return -1; //TODO Error
    }
    int res = (syscall[rax])(rdi, rsi, rdx, rcx, r8, r9);
    return res;
}