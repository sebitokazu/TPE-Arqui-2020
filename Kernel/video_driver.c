#include "include/video_driver.h"
#include "include/font.h"
#include "include/programs.h"
#include "include/lib.h"

#define WIDTH 1024
#define HEIGHT 768

static int backspace();
static void printColorRect(int width, int height, int x, int y, int rgb);
static int printChar(int x, int y, char c);
static void printPixel(char *pos);
static void printColorPixel(char *pos, uint32_t rgb);

static struct vbe_mode_info_structure *screen_info = (struct vbe_mode_info_structure *)0x5C00;

//escala de los char (sin usar)
static int scale = 1;


int screenSize[2] = {WIDTH, HEIGHT};

static int currentColor = WHITE;

//se guardan las ultimas posiciones x e y, por si el kernel tiene que imprimir en la pantalla actual (Ej. excepcion)
static int current_x=0, current_y=0;

static struct program *current_program = 0;

/*
 * Devuelve el tamaño de un char en pantalla y el espaciado entre lineas
 */
void getGraphicsInfo(int *ch_height, int *ch_width, int *spacing)
{
    *ch_height = CHAR_HEIGHT;
    *ch_width = CHAR_WIDTH;
    *spacing = SPACING;
}

int *getScreenSize()
{
    return screenSize;
}

char* getPixelDataByPosition(int x,int y){
    return screen_info->framebuffer + (x + y * screen_info->width) * 3;
}

static void printPixel(char* pos){
    pos[0] = currentColor & (int)0xFF; //azul
    pos[1] = (currentColor >> 8) & (int)0xFF; //verde
    pos[2] = currentColor>>16; //rojo
}

static void printColorPixel(char* pos, uint32_t rgb){
    pos[0] = rgb & (uint32_t)0xFF;  //azul
    pos[1] = ( rgb >> 8 ) & (uint32_t) 0xFF; //verde
    pos[2] = rgb>>16;   //rojo
}

/*
 * Dibuja un cuadrado de width*height en (x,y) del color actual en caso de que sea en los limites de la pantalla actual
 */
int printRect(int width, int height, int x, int y)
{
    current_program = getCurrentProgram();
    if (x >= current_program->Xf || y >= current_program->Yf)
    {
        return -1;
    }
    char *pos = getPixelDataByPosition(x, y);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printPixel(pos + j * 3);
        }
        pos += screen_info->pitch;
    }

    return 0;
}

static void printColorRect(int width, int height, int x, int y, int rgb)
{
    char *pos = getPixelDataByPosition(x, y);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printColorPixel(pos + j * 3, rgb);
        }
        pos += screen_info->pitch;
    }
}

static int printChar(int x, int y, char c){
    if (c == '\n')
    {
         printNewLine();
    }
    else if (c == '\b')
    {
        return backspace();
    }
    else
    {
        for (int i = 0; i < CHAR_HEIGHT; i++)
        {
            for (int j = 0; j < CHAR_WIDTH; j++)
            {
                if (font8x8_basic[c][i] & (1 << j))
                {
                    //Si es un 1, pintal el pixel de blanco
                    printRect(scale, scale, (x + j) * scale, (y + i) * scale);
                }else{
                    //Si es 0, pinta el pixel de negro
                    printColorRect(scale, scale, (x + j) * scale, (y + i) * scale,BLACK);
                }
            }
        }
        current_x += CHAR_WIDTH;
        if (current_x + CHAR_WIDTH >= current_program->Xf){
            printNewLine();
        }
    }
}

/*
 *  Funcion para que el kernel pueda imprimir en la pantalla del programa actual
 */
int printStringKernel(const char* str, int cant){
    int i = cant;
    while (i > 0 && *str != '\0')
    {
        if (printChar(current_x, current_y, *str++) == -1)
        {
            return -1;
        }
        i--;
    }
    return cant - i;
}

int printString(char* str,int cant,int x, int y){
    int i = cant;
    current_program = getCurrentProgram();
    current_x = (x*CHAR_WIDTH + current_program->Xi);
    current_y = (y*(CHAR_HEIGHT+SPACING) + current_program->Yi);
    while (i > 0 && *str != '\0')
    {
        if(printChar(current_x, current_y, *str++)==-1){
            return -1;
        }
        i--;
    }
    return cant - i;
}

void printNewLine(){
    current_x = current_program->Xi;
    current_y += (CHAR_HEIGHT + SPACING);
    if (current_y + CHAR_HEIGHT >= (current_program->Yf) - (CHAR_HEIGHT + SPACING))
    {
        scrollUp();
        current_y -= (CHAR_HEIGHT + SPACING);
    }
}
/*
 * Limpia la pantalla del programa actual
 */
void clearScreen()
{
    current_program = getCurrentProgram();
    int width = current_program->Xf - current_program->Xi;
    int height = current_program->Yf - current_program->Yi;
    printColorRect(width, height, current_program->Xi, current_program->Yi,BLACK);
    current_x = current_program->Xi;
    current_y = current_program->Yi;
}
/*
 * Scrollea hacia arriba la pantalla actual mediante un copiado de bytes en frame_buffer
 */
void scrollUp(){
    char *pos;
    char *next_pos;
    for (int i = 0; i < HEIGHT; i++)
    {
        
        pos = getPixelDataByPosition(current_program->Xi, current_program->Yi + i);
        next_pos = getPixelDataByPosition(current_program->Xi, current_program->Yi + (CHAR_HEIGHT + SPACING) + i);
        memcpy(pos, next_pos, (screen_info->bpp) / 8 * (current_program->Xf - current_program->Xi));
    }
}

static int backspace(){
    if(current_x >current_program->Xi){
        current_x -= CHAR_WIDTH;
        printChar(current_x, current_y, ' ');
        return 0;
    }
    else
    {
        return -1;
    }
}