/*
 * Libreria para interactuar con el driver de video
 * 
 */
#ifndef _SCR_DRAW_H_
#define _SCR_DRAW_H_

int draw_rect(int width, int height, int x, int y);
int get_screen_height();
int get_screen_width();
int clear_screen();
int scroll();
int graphics_info(int *ch_height, int *ch_width, int *spacing);

#endif