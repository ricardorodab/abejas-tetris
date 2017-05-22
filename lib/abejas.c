#include "abejas.h"
#include "funcion.h"
#include <stdlib.h>

ABEJA* init_abeja(TABLERO* tablero)
{
  ABEJA *abeja = malloc(sizeof(ABEJA));
  abeja->solucion = tablero;
  abeja->funcion = funcion_costo(tablero);
  return abeja;
}

double busca_fuente_alimento(ABEJA *abeja)
{
  //Hacer que la abejas empleadas hagan algo.

  //
  abeja->funcion = funcion_costo(abeja->solucion);
  return abeja->funcion;
}
