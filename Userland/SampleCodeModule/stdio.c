#include "include/stdio.h"
#include "include/libasm.h"
#include "include/strings.h"


int getchar(void){
    char c;
    read(1,&c, 1);
    return c;
}

int putchar(char c, int x_cursor, int y_cursor)
{
    return write(1, &c, 1, x_cursor,y_cursor);
}

int puts(const char *str, int x_cursor, int y_cursor)
{
    int cant = strlen(str);
    return write(1, str, cant,x_cursor, y_cursor);
}

int putsNum(int num, int x_cursor, int y_cursor)
{
    char *buf = 0;
    numtostring(buf, num);
    return puts(buf,x_cursor,y_cursor);
}

int getCtrlState(){
    int status = keyboard_status();
    status = status >> 3;
    return status;
}