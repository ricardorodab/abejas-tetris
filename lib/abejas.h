#ifndef ABEJAS_H
#define ABEJAS_H

#include "tablero.h"

typedef struct abeja {
  double funcion;
  TABLERO *solucion;
} ABEJA;

ABEJA* init_abeja(BEE_TYPE tipo,TABLERO *tablero);
double busca_fuente_alimento(ABEJA *abeja);
#endif
