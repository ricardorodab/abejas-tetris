#ifndef ABEJAS_H
#define ABEJAS_H

#include "tablero.h"

typedef struct abeja {
  double funcion;
  TABLERO *solucion;
} ABEJA;

ABEJA* init_abeja(TABLERO *tablero);
double busca_fuente_alimento(ABEJA *abeja);
void set_tablero_abeja(TABLERO* tablero, ABEJA *abeja);
#endif
