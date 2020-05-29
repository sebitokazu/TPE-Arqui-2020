#include <keyboardDriver.h>
#include <video_driver.h>


const char scancodes[58][2]=
        {    
            {0,0},{0,0},{'1','!'},{'2','@'},{'3','#'},{'4','$'},{'5','%'},{'6','^'},{'7','&'},{'8','*'},{'9','('},{'0',')'},{'-','_'},{'=','+'},/*BACKS*/{'\b','\b'},
            /*TAB*/{0,0},{'q','Q'},{'w','W'},{'e','E'},{'r','R'},{'t','T'},{'y','Y'},{'u','U'},{'i','I'},{'o','O'},{'p','P'},{'[','{'},{']','}'},/*NL*/{'\n','\n'},
            /*CTRL*/{0,0},{'a','A'},{'s','S'},{'d','D'},{'f','F'},{'g','G'},{'h','H'},{'j','J'},{'k','K'},{'l','L'},{';',';'},{'\'','\"'},{'`','~'},/*LSHIFT*/{0,0},{'\\','|'},
            {'z','Z'} ,{'x','X'},{'c','C'},{'v','V'},{'b','B'},{'n','N'},{'m','M'},{',','<'},{'.','>'},{'/','?'},/*RSHIFT*/{0,0},{0,0},/*LALT*/{0,0},{' ',' '}
        };
#define BUFFER_LENGTH 150
static char buffer[BUFFER_LENGTH];
static unsigned int buffer_pos = 0;
static unsigned int read_pos = 0;

static int capsLock = 0, leftShift = 0, rightShift = 0;

void keyboard_handler(){
    //int capsLock = 0;
    //int keypressed = getKey();
    write_key();
}

void write_key(){
    char value;
    int keypressed = getKey();
    switch (keypressed)
    {
    case 0x3A:
        capsLock = 1 - capsLock;
        break;
    case 0x2A:
        leftShift = 1;
        break;
    case 0xAA:
        leftShift = 0;
        break;
    case 0x36:
        rightShift = 1;
        break;
    case 0xB6:
        rightShift = 0;
        break;
    default:
        break;
    }

    if (keypressed > 0x80)
    {
        value = 0;
    }
    else
    {
        if (isLetter(keypressed))
        {
            value = scancodes[keypressed][(leftShift | rightShift) ^ capsLock];
        }
        else
        {
            value = scancodes[keypressed][leftShift | rightShift];
        }
    }

    if (value != 0){
        buffer[buffer_pos++] = value;
        if(buffer_pos == BUFFER_LENGTH)
            buffer_pos = 0;
        //printChar(value);
    }
}

char getBufferChar(){
    char c = buffer[read_pos++];
    if (read_pos == BUFFER_LENGTH)
        read_pos = 0;
    return c;
}

int isBufferEmpty(){
    return read_pos == buffer_pos;
}

char key_pooling(){
    while (1)
    {
        if (hasKey())
        {
            write_key();
        }
    }
}

int isLetter(int code){
    if((code>=0x10 && code <= 0x19)|| (code >=0x1E && code <= 0x26) || (code >= 0x2C && code <= 0x32))
        return 1;
    else
        return 0;
}