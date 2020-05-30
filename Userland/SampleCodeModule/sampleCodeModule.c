/* sampleCodeModule.c */
#include "include/libasm.h"

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

extern int write(int fd, char *str, int count);
extern int read(int fd, char *buffer, uint64_t count);

int main() {
	//All the following code may be removed
	*v = 'X';
	*(v+1) = 0x74;

	char *buf = "Tommy";
	int cant = write(1, buf, 3);
	write(1, buf, cant+2);

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;


	return 0xDEADBEEF;
}