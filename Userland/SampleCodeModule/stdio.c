#include "include/stdio.h"
#include "include/libasm.h"

int getchar(void){
    char c;
    read(1,&c, 1);
    return c;
}

int scanf(char* fmt, char* buff){
    char c = 0;
    int cant = 0;
    c = getchar();
    while (c != '\n')
    {
        buff[cant++] = c;
        putchar(c);
        c = getchar();
    }
    buff[cant] = '\0';
    return cant;
}

int putchar(char c){
    return write(1, &c, 1);
}

int puts(char* str){
    int cant = strlen(str);
    return write(1, str, cant);
}

int strlen(char* str){
    int c = 0;
    while(*str!=0){
        c++;
        str++;
    }
    return c;
}