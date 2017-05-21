#ifndef ABEJAS_H
#define ABEJAS_H

#include "tablero.h"

typedef enum tipo_abeja {
  EMPLEADA,
  DESCANSA,
  EXPLORA } BEE_TYPE;

typedef struct abeja {
  BEE_TYPE tipo;
  double funcion;
  TABLERO *solucion;
} ABEJA;

ABEJA* init_abeja(BEE_TYPE tipo,TABLERO *tablero);
  
#endif
