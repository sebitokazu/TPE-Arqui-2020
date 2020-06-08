#include "../include/video_driver.h"
#include "../include/registers.h"
#include "../include/programs.h"
#include "../include/keyboardDriver.h"

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE_ID 6


static void zero_division(uint64_t* rsp);
static void invalid_opcode();
static void printError(const char *msg, uint64_t *rsp, uint64_t *ip);
extern void _hlt();

void exceptionDispatcher(int exception, uint64_t *rsp)
{
	switch (exception){
	case ZERO_EXCEPTION_ID:
		zero_division(rsp);
		break;
	case INVALID_OPCODE_ID:
		invalid_opcode(rsp);
		break;
	default:
		break;
	}
}

static void zero_division(uint64_t* rsp) {
	printError("Zero Division", rsp, rsp+15);
	rsp[15] = getCurrentProgramPtr();
}

static void invalid_opcode(uint64_t *rsp)
{
	printError("Invalid Opcode", rsp, rsp+15);
	rsp[15] = getCurrentProgramPtr();
}
/*
 *	Imprime el error de la excepcion correspondiente y los valores de los registros
 */
static void printError(const char *msg, uint64_t *rsp, uint64_t *ip){
	printNewLine();
	printStringKernel(msg, 15);
	snap_register(rsp, ip);
	printSnapRegisters();
	printNewLine();
	printStringKernel("Presionar 'c' para continuar", 30);
	char c = 0;
	while (c != 'c')
	{
		while (isBufferEmpty())
			_hlt();
		c = getBufferChar();
	}
	clearScreen();
}