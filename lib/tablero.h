#ifndef TABLERO_H
#define TABLERO_H

#include <glib.h>
#include "pieza.h"

typedef struct tablero {
  int alto;
  int ancho;
  int size;
  int max_size;
  PIEZA ***piezas; 
} TABLERO;

TABLERO* init_tablero(int alto, int ancho);
void free_tablero(TABLERO *tablero);
void agrega_pieza_tablero(TABLERO *tablero, PIEZA *pieza);
void mueve_pieza_tablero(TABLERO *tablero,PIEZA *pieza, int x, int y);
PIEZA* get_pieza(TABLERO *tablero, int x, int y);

#endif
