#include "pieza.h"
#include <stdlib.h>

PIEZA* init_pieza(int id, FORMA tipo)
{
  PIEZA *pieza = malloc(sizeof(PIEZA));
  pieza->id = id;
  pieza->tipo = tipo;
  pieza-> orientacion = 0;
  pieza->x = 0;
  pieza->y = 0;
  pieza->fija = false;
  return pieza;
}

void free_pieza(PIEZA *pieza)
{
  free(pieza);
}

void rotar_pieza(PIEZA *pieza)
{
  pieza->orientacion = ((pieza->orientacion+90) % 360);
}

void rota_pieza(PIEZA *pieza,int grado)
{
  pieza->orientacion = grado;
}

void actualiza_posicion_pieza(PIEZA *pieza, int x, int y)
{
  pieza->x = x;
  pieza->y = y;
}
