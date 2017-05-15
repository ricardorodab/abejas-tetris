#include "pieza.h"
#include <stdlib.h>

FICHA* init_ficha(int id, FORMA tipo)
{
  FICHA *ficha = malloc(sizeof(FICHA));
  ficha->id = id;
  ficha->tipo = tipo;
  ficha-> orientacion = 0;
  ficha->x = 0;
  ficha->y = 0;
  ficha->fija = false;
  return ficha;
}

void free_ficha(FICHA *ficha)
{
  free(ficha);
}

void rotar_ficha(FICHA *ficha)
{
  ficha->orientacion = (ficha->orientacion+90) % 360;
}

void rota_ficha(FICHA *ficha,int grado)
{
  ficha->orientacion = grado;
}
