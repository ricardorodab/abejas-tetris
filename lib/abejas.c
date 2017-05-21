#include "abejas.h"
#include "funcion.h"
#include <stdlib.h>

ABEJA* init_abeja(BEE_TYPE tipo, TABLERO* tablero)
{
  ABEJA *abeja = malloc(sizeof(ABEJA));
  abeja->tipo = tipo;
  abeja->solucion = tablero;
  abeja->funcion = funcion_costo(tablero);
  //abeja->funcion
}
