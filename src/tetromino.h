#ifndef TETROMINO_H
#define TETROMINO_H

#include "pieza.h"

void dibuja_cuadrado(PIEZA *pieza, int dif_x, int dif_y);
void dibuja_left_gun(PIEZA *pieza, int dif_x, int dif_y);
void dibuja_right_gun(PIEZA *pieza, int dif_x, int dif_y);
void dibuja_left_snake(PIEZA *pieza, int dif_x, int dif_y);
void dibuja_right_snake(PIEZA *pieza, int dif_x, int dif_y);
void dibuja_i(PIEZA *pieza, int dif_x, int dif_y);
void dibuja_t(PIEZA *pieza, int dif_x, int dif_y);

#endif
