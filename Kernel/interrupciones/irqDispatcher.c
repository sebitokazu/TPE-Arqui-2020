#include <time.h>
#include <stdint.h>
#include <keyboardDriver.h>

static void int_20();
static void int_21();
static void int_80();

void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0:
			int_20();
			break;
		case 1:
			int_21();
			break;
		case 128:
			int_80();
			break;
		}
	return;
}

void int_20() {
	timer_handler();
}

void int_21(){
	keyboard_handler();
}

void int_80(){
	//syscall_handler();
}