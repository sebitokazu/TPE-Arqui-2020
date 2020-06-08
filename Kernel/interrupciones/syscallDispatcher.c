#include "syscallDispatcher.h"
#include <stdint.h>
#include "../include/video_driver.h"
#include "../include/keyboardDriver.h"
#include "interrupts.h"
#include "../include/RTC.h"
#include "../include/registers.h"
#include "../include/programs.h"

#define NULL 0

#define SYSCALLS_COUNT 13


int (*syscall[SYSCALLS_COUNT])(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t) = {};

int syscall_write(uint64_t fd, uint64_t str, uint64_t count, uint64_t x, uint64_t y, uint64_t r9)
{
    char *str_c = (char*)str;
    if (fd == 1)
    {
        if (str_c == NULL)
        {
            return 0;
        }
        else
        {
            return printString(str_c, count,x,y);
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

int syscall_print_rect(uint64_t width, uint64_t height, uint64_t x, uint64_t y, uint64_t r8, uint64_t r9)
{
    return printRect(width, height, x, y);
}

int syscall_screen_width(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
    return getScreenSize()[0];
}

int syscall_screen_height(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
    return getScreenSize()[1];
}

int syscall_time(uint64_t date_buf, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    int *date_c = (int*)date_buf;
    date_c[0] = getRTCSeconds();
    date_c[1] = getRTCMinutes();
    date_c[2] = getRTCHours();
    date_c[3] = getRTCWeekday();
    date_c[4] = getRTCDay();
    date_c[5] = getRTCMonth();
    date_c[6] = getRTCYear();
    return 0;
}

int syscall_create_program(uint64_t id, uint64_t Xi, uint64_t Xf, uint64_t Yi, uint64_t Yf, uint64_t ptr)
{
    return createProgram(id, Xi, Xf, Yi, Yf,ptr);
}

int syscall_change_program(uint64_t id, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    return changeProgram(id);
}

int syscall_clear(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
    clearScreen();
    return 0;
}

int syscall_keyboard_status(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
    return getSpecialKeysStatus();
}

int syscall_get_registers(uint64_t reg_buf, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
    return getRegistersSnap((uint64_t *)reg_buf);
}


int syscall_scroll(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
    scrollUp();
    return 0;
}


int syscall_graphic_info(uint64_t ch_height_buf, uint64_t ch_width_buf, uint64_t spacing_buf, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    getGraphicsInfo((int *)ch_height_buf, (int *)ch_width_buf, (int *)spacing_buf);
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
    syscall[6] = syscall_create_program;
    syscall[7] = syscall_change_program;
    syscall[8] = syscall_clear;
    syscall[9] = syscall_keyboard_status;
    syscall[10] = syscall_get_registers;
    syscall[11] = syscall_scroll;
    syscall[12] = syscall_graphic_info;
}

int syscallDispatcher(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    if (rax < 0 || rax >= SYSCALLS_COUNT)
    {
        return -1; //TODO Error
    }
    int res = (syscall[rax])(rdi, rsi, rdx, rcx, r8, r9);
    return res;
}