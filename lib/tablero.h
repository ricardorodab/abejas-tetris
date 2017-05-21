#ifndef TABLERO_H
#define TABLERO_H

#include <glib.h>
#include <stdbool.h>
#include "pieza.h"

typedef struct tablero {
  int alto;
  int ancho;
  int size;
  int max_size;
  PIEZA ***piezas;
  PIEZA *actual;
} TABLERO;

TABLERO* init_tablero(int alto, int ancho);
void free_tablero(TABLERO *tablero);
void agrega_pieza_tablero(TABLERO *tablero, PIEZA *pieza);
void borra_pieza_tablero(TABLERO *tablero, PIEZA *pieza);
bool mover_pieza_tablero(TABLERO *tablero, PIEZA *pieza);
bool rotar_pieza_tablero(TABLERO *tablero, PIEZA *pieza);
bool mover_izquierda_tablero(TABLERO *tablero, PIEZA *pieza);
bool mover_derecha_tablero(TABLERO *tablero, PIEZA *pieza);
void tetris_nivel(TABLERO *tablero, int l);
void tetris(TABLERO *tablero);
PIEZA* get_pieza(TABLERO *tablero, int x, int y);

#endif
