#include <video_driver.h>
#include <font.h>

static struct vbe_mode_info_structure* screen_info = 0x5C00;

static uint8_t red = 0xFF, blue = 0xFF, green = 0xFF;
static int scale = 1;

const int WIDTH = 1024;
const int HEIGHT = 768;

static int currentColor = 0xFFFFFF;
static int current_x, current_y;

//HEIGHT / (CHAR_HEIGHT+SPACING) = 64
static int cursorLastPosInRow[64] = {0};

static void backspace();
int printCharLoc(int x, int y, char c);


void initVideo()
{
    current_x = 0;
    current_y = 0;

    ///printCursorPosition();
}

static char* getPixelDataByPosition(int x,int y){
    return screen_info->framebuffer + y * screen_info->pitch + (x * (screen_info->bpp / 8));
    //return screen_info->framebuffer + (x + y * screen_info->width) * 3;
}


void setColor(uint8_t r, uint8_t g, uint8_t b){
    red = r;
    green = g;
    blue = b;
}

int printPixel(char* pos){
    //char* pos = getPixelDataByPosition(x,y);
    pos[0] = currentColor & (int)0xFF; //azul
    pos[1] = (currentColor >> 8) & (int)0xFF; //verde
    pos[2] = currentColor>>16; //rojo
}

int printColorPixel(char* pos, uint32_t rgb){
    pos[0] = rgb & (uint32_t)0xFF;  //azul
    pos[1] = ( rgb >> 8 ) & (uint32_t) 0xFF; //verde
    pos[2] = rgb>>16;   //rojo
}

int printChar(char c){
    printCharLoc(current_x, current_y, c);
}

int printCharLoc(int x, int y, char c){
    if (c == '\n')
    {
        //clearCursorPosition();
        printNewLine();
    }
    else if (c == '\b')
    {
        backspace();
    }
    else
    {
        for (int i = 0; i < CHAR_HEIGHT; i++)
        {
            for (int j = 0; j < CHAR_WIDTH; j++)
            {
                if (font8x8_basic[c][i] & (1 << j))
                {
                    printRect(scale, scale, (x + j) * scale, (y + i) * scale);
                }else{
                    printColorRect(scale, scale, (x + j) * scale, (y + i) * scale,BLACK);
                }
            }
        }
        current_x += CHAR_WIDTH;
        if (current_x >= WIDTH)
            printNewLine();
    }
   // printCursorPosition();
}

int printString(char* str,int cant){
    int i = cant;
    while (i > 0 && *str != '\0')
    {
        printCharLoc(current_x, current_y, *str++);
        i--;
    }
    return cant - i;
}

void set_cursor_position(int x, int y){
    current_x = x;
    current_y = y;
}

void printNewLine(){
    cursorLastPosInRow[current_y % (CHAR_WIDTH + SPACING)] = current_x;
    current_x = 0;
    current_y += (CHAR_WIDTH + SPACING) * scale;
}

void clearScreen()
{
    char *pos = screen_info->framebuffer;
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        printColorPixel(pos + i * 3, 0);
    }
    current_x = 0;
    current_y = 0;
    //printCursorPosition();
}

void backspace(){
    //clearCursorPosition();
    if(current_x>0){
        current_x -= CHAR_WIDTH;
    }
    else
    {
        if(current_y!=0){
            current_y -= (CHAR_WIDTH + SPACING);
            current_x = cursorLastPosInRow[current_y % (CHAR_WIDTH + SPACING)];
        }
    }
}

void printCursorPosition()
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printColorRect(scale, scale, (current_x + j) * scale, (current_y + i) * scale, WHITE);
        }
    }
}

void clearCursorPosition(){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printColorRect(scale, scale, (current_x + j) * scale, (current_y + i) * scale,BLACK);
        }
    }
}

int printColorRect(int width, int height, int x, int y, int rgb){
    char *pos = getPixelDataByPosition(x, y);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printColorPixel(pos + j * 3,rgb);
        }
        pos += screen_info->pitch;
    }
}

int printRect(int width, int height, int x, int y)
{
    if(x >= WIDTH || y >= HEIGHT)
        return -1;
    char *pos = getPixelDataByPosition(x, y);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width;j++){
            printPixel(pos + j*3);
        }
        pos += screen_info->pitch;
    }

    return 0;
}
