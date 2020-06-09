#include "include/windowsAdmin.h"
#include "include/graphicslib.h"
#include "include/programsLib.h"
#include "include/shell.h"
#include "include/calculadora.h"

#define SEPARATORWIDTH 4
#define CANTPROGRAMS 2

int programs[CANTPROGRAMS] = {1, 2};

int activeWindow = 1;

int screen_width = 0, screen_heigth = 0, char_width = 0, char_height = 0, spacing = 0;


void setupEnvironment(){
    screen_width = get_screen_width();
    screen_heigth = get_screen_height();
    graphics_info(&char_width,&char_height,&spacing);
    //este es el programa admin de pantallas, solo corre para dibujar la linea divisoria de pantalla
    create_program(0, 0, screen_width, 0, screen_heigth, &start);
    //defino el programa de la calculadora y le envio su dir de arranque
    create_program(programs[0], 0, screen_width / 2 - SEPARATORWIDTH, 0, screen_heigth, &start);
    //defino el programa de la shell y le envio su dir de arranque
    create_program(programs[1], screen_width / 2 + SEPARATORWIDTH, screen_width, 0, screen_heigth, &start);
    //para que el programa de arranque sea el admin de ventanas
    change_program(0);
    //dibujo la linea divisoria de pantalla
    draw_rect(SEPARATORWIDTH, screen_heigth, screen_width / 2, 0);
}
//cambia la vetana activa 
void changeActiveWindows(){
    activeWindow = 1 - activeWindow;
}

//devuelve la ventana activa
int getActiveWindow(){
    return activeWindow;
}

/*
 *  Los programas no se manejan internamente en pixeles, sino en cantidad de caracteres que pueden mostrar en pantalla
 */
void start(){
    int retcode = 0;
    while (1)
    {
        if(activeWindow == 0){
            change_program(programs[getActiveWindow()]);
            retcode = runCalculadora(((screen_width / 2) - SEPARATORWIDTH)/char_width, screen_heigth / (char_height + spacing));
        }
        else
        {
            change_program(programs[getActiveWindow()]);
            retcode = runShell(((screen_width / 2))/char_width, screen_heigth/(char_height+spacing));
        }
        changeActiveWindows();
        change_program(programs[getActiveWindow()]);
    }
}