#include "include/registers.h"
#include "include/video_driver.h"
#include "include/string.h"

#define REGISTERS_COUNT 19

static uint64_t regs_snap[REGISTERS_COUNT] = {0};
const char *REGISTERS[REGISTERS_COUNT] = {"IP:","CS:","RFLAGS:","RSP:","R15:", "R14:", "R13:", "R12:", "R11:", "R10:", "R9:", "R8:", "RSI:", "RDI:",
                             "RBP:", "RDX:", "RCX:", "RBX:", "RAX:"};
static char *reg = "0x00000000";

/*
    Guarda el snap de los registros
*/
void snap_register(uint64_t *rsp, uint64_t *ip)
{
    int i,j;
    for (i = 0; i < 4; i++)
    {
        regs_snap[i] = ip[i];
    }
    for (j = 0; j < 15; j++)
    {
        regs_snap[j + i] = rsp[j];
    }
}
/* Asigna a ptr, el array con los valores de los registros, en el orden
    IP,CS,FLAGS,RSP,R15,R14,R13,R12,R11,R10,R9,R8,RSI,RDI,RBP,RDX,RCX,RBX,RAX
    Retorna la cantidad de registros del array
*/
int getRegistersSnap(uint64_t *ptr)
{
    for (int i = 0; i < REGISTERS_COUNT;i++){
        ptr[i] = regs_snap[i];
    }
        return REGISTERS_COUNT;
}
/*
 *  Para imprimir el estado de registros de forma interna en el kernel ante una excepcion 
 */
int printSnapRegisters(){
    for (int i = 0; i < REGISTERS_COUNT;i++){
        if (i % 5 == 0)
            printNewLine();
        uintToBase2(regs_snap[i], reg, 16);
        printStringKernel(REGISTERS[i], 8);
        printStringKernel(reg, 11);
        printStringKernel(" - ", 4);
    }
    return REGISTERS_COUNT/5 + (REGISTERS_COUNT%5 != 0);
}