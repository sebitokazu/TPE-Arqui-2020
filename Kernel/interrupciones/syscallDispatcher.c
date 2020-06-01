#include <stdint.h>
#include <video_driver.h>
#include <syscallDispatcher.h>
#include <keyboardDriver.h>
#include <interrupts.h>
#include <RTC.h>

#define NULL 0

#define SYSCALLS_COUNT 5

int syscall_write(unsigned int fd, char* str, int count);
int syscall_read(unsigned int fd, char* buffer, int count);
int syscall_print_rect(int width, int height, int x, int y);
int syscall_screen_width();
int syscall_screen_height();
int syscall_time(uint32_t* struct_tm);

int (*syscall[SYSCALLS_COUNT])(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = {};

int syscall_write(unsigned int fd, char* str, int count)
{
    if(fd == 1){
        if (str == NULL)
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

int syscall_read(unsigned int fd, char *buffer, int count)
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

int syscall_print_rect(int width, int height, int x, int y){
    return printRect(width, height, x, y);
}

int syscall_screen_width(){
    return getScreenSize()[0];
}

int syscall_screen_height(){
    return getScreenSize()[1];
}

int syscall_time(uint32_t* struct_tm){
    struct_tm[0] = getRTCSeconds();
    struct_tm[1] = getRTCMinutes();
    struct_tm[2] = getRTCHours();
    struct_tm[3] = getRTCWeekday();
    struct_tm[4] = getRTCDay();
    struct_tm[5] = getRTCMonth();
    struct_tm[6] = getRTCYear();
    return 0;
}

void setup_syscalls()
{
    syscall[0] = syscall_read;
    syscall[1] = syscall_write;
    syscall[2] = syscall_print_rect;
    syscall[3] = syscall_screen_width;
    syscall[4] = syscall_screen_height;
    syscall[5] = syscall_time;
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