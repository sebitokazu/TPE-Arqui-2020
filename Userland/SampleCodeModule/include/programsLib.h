/*
 *  Para crear programas y cambiar el programa activo
 *  Avisa a kernel que se va a definir un espacio en pantalla (ventana)  
 */

#ifndef _PROGRAMS_LIB_H_
#define _PROGRAMS_LIB_H_

#include <stdint.h>

int create_program(int id, int Xi, int Xf, int Yi, int Yf,uint64_t ptr);
int change_program(int id);

#endif