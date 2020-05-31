/* sampleCodeModule.c */
#include "include/stdio.h"
#include "graphicslib.h"

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

int main(char** env_var) {
	//All the following code may be removed
	*v = 'X';
	*(v+1) = 0x74;
	draw_rect(2, 768, 1024/2, 0);
	putchar('>');
	putchar(env_var[0][1]);
	puts(env_var[0]);
	char *buf = 0;
	buf = "Funciona";
	puts(buf);
	char *input="";
	int cant = scanf("%s", input);
	putchar('\n');
	putchar('>');
	puts(input);
	putchar('f');
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;


	return 0xDEADBEEF;
}