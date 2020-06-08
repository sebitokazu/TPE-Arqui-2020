#include "include/programs.h"
#include "include/video_driver.h"

#define MAX_PROGRAMS 3 //son 2 programas + el administrador de ventanas


struct program program_list[MAX_PROGRAMS];
int index_program = 0;
int current_program_index = 0;

/*
 * Crea un programa con un id, la zona de pantalla que le corresponde, y un puntero a donde reiniciar en caso de crasheo
 */
int createProgram(int id, int Xi, int Xf, int Yi, int Yf,uint64_t ptr)
{
    if(index_program == MAX_PROGRAMS)
        return -1;
    struct program *new_pgm = &(program_list[index_program++]);
    new_pgm->id = id;
    new_pgm->Xi = Xi;
    new_pgm->Xf = Xf;
    new_pgm->Yi = Yi;
    new_pgm->Yf = Yf;
    new_pgm->start_ptr = ptr;
    return 0;
}

struct program* getCurrentProgram(){
    return &(program_list[current_program_index]);
}

int changeProgram(int id){
    if(id>MAX_PROGRAMS)
        return -1;
    current_program_index = id;
    return 0;
}

uint64_t getCurrentProgramPtr(){
    return program_list[current_program_index].start_ptr;
}