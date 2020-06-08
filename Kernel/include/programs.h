#ifndef _PROGRAMS_H_
#define _PROGRAMS_H_

#include <stdint.h>

/*
 * Estructura que define un programa. Contiene un id, limites en pantalla y un puntero en caso de crush
 * 
 */

struct program
{
    int id;
    int Xi;
    int Xf;
    int Yi;
    int Yf;
    uint64_t start_ptr;
};

int createProgram(int id, int Xi, int Xf, int Yi, int Yf,uint64_t ptr);
struct program *getCurrentProgram();
int changeProgram(int id);
uint64_t getCurrentProgramPtr();
void setProgramPtr(void *ptr);

#endif