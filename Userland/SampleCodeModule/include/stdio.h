#ifndef _MY_STDIO_H_
#define _MY_STDIO_H_

#define CHANGEWINDOW -1

int getchar(void);
int putchar(char c, int x_cursor, int y_cursor);
int puts(const char *str, int x_cursor, int y_cursor);
int putsNum(int num, int x_cursor, int y_cursor);
int getCtrlState();

#endif