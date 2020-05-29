
int getchar(void){
    char c;
    sys_read(1,&c, 1);
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
    return cant;
}

int putchar(char c){
    return sys_write(1, &c, 1);
}

int puts(const char* str){
    int cant = strlen(str);
    return sys_write(1, str, cant);
}