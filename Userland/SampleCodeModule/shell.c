#include "include/stdio.h"
#include "include/time.h"
#include "include/strings.h"
#include "include/cpuid.h"
#include "include/graphicslib.h"
#include "include/libasm.h"

#define MODULES 8
#define REGISTERS_COUNT 19

static int processCommand(char *cmd);
static void printReg();
static void help();
static void printTime();
static void printDate();
static void printCpuid();
static void clear();
static void newEntry();
static int scanf(char *buff);
static void printmem(const char *ptr);
static void newLine();

const char *helpDescriptions[MODULES] = {
    "time -> Imprime la hora actual",
    "date -> Imprime fecha actual",
    "cpuid -> Imprime marca y modelo del procesador",
    "diverror -> Genera una excepcion de division por 0",
    "inforeg -> Imprime el estado de los registros. Presione Alt Izq para realizar un Snap",
    "printmem ptr -> realiza un volcado de memoria de 32 bytes a partir de ptr=0x...",
    "invopcode -> Genera una excepcion de invalid opcode",
    "clear -> Clear the shell"};
const char *REGISTERS[REGISTERS_COUNT] = {"IP:", "CS:", "RFLAGS:", "RSP:", "R15:", "R14:", "R13:", "R12:", "R11:", 
                                        "R10:", "R9:", "R8:", "RSI:", "RDI:","RBP:", "RDX:", "RCX:", "RBX:", "RAX:"};
static char *reg_str = "0x00000000";
/*
    Tanto el buffer de comando como la posicion de scaneo las guardamos globales, asi si cambia de programa se puede seguir escribiendo donde estaba
*/
static char buf[50];
static int buffer_pos = 0;

static int currentX = 0;
static int currentY = 0;

static int width;
static int height;
static int is_running = 1;

int runShell(int _width, int _height)
{
    width = _width;
    height = _height;

    int cmd;
    if (is_running)
    {
        currentX = 0;
        currentY = 0;
    }
    else
    {
        is_running = 1;
    }
    if(currentX == 0){
        newEntry();
    }

    while (scanf(buf) != CHANGEWINDOW)
    {
        cmd = processCommand(buf);
        if(cmd == -1){
            puts("invalid command", currentX, currentY);
            newLine();
        }
        newEntry();
    }
    return 0;
}


static int processCommand(char *cmd){
    if (strcmp(cmd, "diverror") == 0)
    {
        int a = 4 / 0;
        return 0;
    }
    else if(strcmp(cmd, "invopcode") == 0)
    {
        invalidopcode();
        return 0;
    }
    else if(strcmp(cmd, "help") == 0)
    {
        help();
        return 0;
    }
    else if (strcmp(cmd, "cpuid") == 0)
    {
        printCpuid();
        return 0;
    }
    else if (strcmp(cmd, "clear") == 0)
    {
        clear();
        return 0;
    }
    else if (strcmp(cmd, "time") == 0)
    {
        printTime();
        return 0;
    }
    else if (strcmp(cmd, "date") == 0)
    {
        printDate();
        return 0;
    }
    else if (strcmp(cmd, "inforeg") == 0)
    {
        printReg();
        newLine();
        return 0;
    }else if (strncmp(cmd, "printmem 0x",11) == 0)
    {
        printmem(cmd + 11);
        newLine();
        return 0;
    }

        return -1;
}

static void printReg(){
    uint64_t reg[REGISTERS_COUNT]={0};
    inforeg(reg);

    for (int i = 0; i < REGISTERS_COUNT; i++)
    {
        if (i % 4 == 0)
            newLine();
        uintToBase(reg[i], reg_str, 16);
        currentX += puts(REGISTERS[i], currentX, currentY);
        currentX += puts(reg_str, currentX, currentY);
        currentX += puts(" - ", currentX, currentY);
    }
}

static void help(){
    for (int i = 0; i < MODULES; i++)
    {
        int cant = puts(helpDescriptions[i], currentX, currentY);

        if (cant >= width)
        {
                newLine();
        }
            newLine();
    }
}

static void printTime(){
    int* time = getCurrentTime();
    char *buff="00:00:00";

    for (int i = 0; i < 3; i++){
        buff[7-i*3-1] = (time[i] / 10)+'0';
        buff[7 - i*3] = (time[i] % 10) + '0';
    }
    puts(buff, currentX, currentY);
    newLine();
}

static void printDate(){
    int *time = getCurrentTime();
    char *date = "SUN 01/01/00";

    for (int i = 0; i < 3; i++)
    {
        date[i] = getDay(time[3])[i];
    }
    for (int i = 0; i < 3; i++)
    {
        date[4+i*3] = (time[i+4] / 10) + '0';
        date[4+i*3+1] = (time[i+4] % 10) + '0';
    }
    puts(date, currentX, currentY);
    newLine();
}

static void printCpuid(){
    char buff[64];
    cpuVendor(buff);
    puts(buff,currentX,currentY);
    newLine();
    if (isCpuModelPresent())
    {
        cpuModel(0x80000002, buff);
        cpuModel(0x80000003, buff + 16);
        cpuModel(0x80000004, buff + 32);
        puts(buff, currentX, currentY);
        newLine();
    }
}

static void clear(){
    clear_screen();
    currentX = 0;
    currentY = 0;
}

static void newEntry(){
    putchar('>', currentX, currentY);
    currentX++;
}

static int scanf(char *buff)
{
    char c = 0;
    c = getchar();
    while (c != '\n')
    {
        if(getCtrlState()==1 && (c == 'Q' || c=='q')){
            is_running = 0;
            return CHANGEWINDOW;
        }

        if(c != '\b'){
            if(currentX<width){
                buff[buffer_pos++] = c;
                putchar(c, currentX, currentY);
                currentX++;
            }
        }
        else
        {
            if(currentX > 1){
                buff[--buffer_pos] = '\0';
                putchar(c, currentX, currentY);
                currentX--;
            }
        }
        c = getchar();
    }
    buff[buffer_pos] = '\0';
    newLine();
    int copy_cant = buffer_pos;
    buffer_pos = 0;
    return copy_cant;
}

static void printmem(const char* ptr){
    int num_ptr = strtohex(ptr);
    if(num_ptr == -1){
        puts("Direccion incorrecta", currentX, currentY);
    }else
    {
        void *dir = num_ptr;
        char *d = (char *)dir;
        char *num="FF ";
        for (int i = 0; i < 32; i++){
            if ((i % 16 == 0) & (i != 0))
                newLine();
            num = numtoHexString(num, d[i]);
            puts(num, currentX, currentY);
            currentX += 3;
        }
    }
}

static void newLine(){
    currentX = 0;
    currentY++;
    if (currentY >= height)
    {
        scroll();
        currentY=height-1;
    }
}