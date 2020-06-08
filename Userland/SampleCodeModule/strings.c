#include "include/strings.h"
#include "graphicslib.h"
#include "include/stdio.h"

#define TO_HEX(i) (i <= 9 ? '0' + i : 'A' - 10 + i)

int isHexDigit(char c);

int strlen(const char *str)
{
    int c = 0;
    while (*str != 0)
    {
        c++;
        str++;
    }
    return c;
}

int strncmp(const char* str1, const char* str2, int n){
    while (*str1!= '\0' && *str2 != '\0' && *str1 == *str2 && n!=0)
    {
        str1++;
        str2++;
        n--;
    }
    if(n==0)
        return 0;
    else
        return -1;
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    if (*str1 == *str2)
        return 0;
    else
        return -1;
}

char *strappend(const char *src, char *dest)
{
    char *aux = dest + strlen(dest);

    while(*src!='\0'){
        *aux++ = *src++;
    }
    *aux= '\0';
    return dest;
}

char* numtostring(char *buf, int num)
{
    int aux = num, length = 0;

    while (aux != 0)
    {
        aux /= 10;
        length++;
    }
    int resto;
    for (int i = 0; i < length; i++)
    {
        resto = num % 10;
        num = num / 10;
        resto += '0';
        buf[length - i - 1] = resto;
    }
    buf[length] = '\0';
    return buf;
}

char *numtoHexString(char *buf, char num){
    buf[0] = TO_HEX(((num & 0xF0) >> 4));
    buf[1] = TO_HEX((num & 0x0F));
    buf[2] = ' ';
    return buf;
}

int strtohex(const char* ptr){
    char *cptr = ptr;
    int ret = 0;
    int c;
    while (*cptr != 0)
    {
        if((c=isHexDigit(*cptr)) == -1)
            return -1;
        else{
            ret = (ret << 4) | (c & 0xF);
        }
        cptr++;
    }
    return ret;
}

int isHexDigit(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    else if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }
    else
    {
        return -1;
    }
}

uint32_t uintToBase(uint64_t value, char *buffer, uint32_t base)
{
    char *p = buffer;
    char *p1, *p2;
    uint32_t digits = 0;

    //Calculate characters for each digit
    do
    {
        uint32_t remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    } while (value /= base);

    // Terminate string in buffer.
    *p = 0;

    //Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return digits;
}