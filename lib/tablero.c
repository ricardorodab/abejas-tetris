#include "tablero.h"
#include <stdio.h>
#include <stdlib.h>

TABLERO* init_tablero(int alto, int ancho)
{
  TABLERO *tablero = malloc(sizeof(TABLERO));
  tablero->alto = alto;
  tablero->ancho = ancho;
  tablero->size = 0;
  tablero->max_size = (alto*ancho)/4;
  tablero->piezas = malloc((ancho+1)*sizeof(PIEZA***));
  int i, j;
  for(i = 0; i < ancho+1; i++)
    tablero->piezas[i] = malloc((alto+1)*sizeof(PIEZA**));
  for(i = 0; i < ancho+1; i++)
    for(j = 0; j < alto+1; j++)
      tablero->piezas[i][j] = NULL;
  return tablero;
}

void free_tablero(TABLERO *tablero)
{
  int i;
  for(i = 0; i < tablero->ancho+1; i++)
    free(tablero->piezas[i]);
  free(tablero->piezas);
  free(tablero);
}

void agrega_pieza_tablero(TABLERO *tablero, PIEZA *pieza)
{
  tablero->size++;
  if(tablero->size == tablero->max_size)
    {
      printf("Tamanio maximo alcanzado\n");
      exit(1);
    }
  tablero->piezas[pieza->x][pieza->y] = pieza;
}

void mueve_pieza_tablero(TABLERO *tablero,PIEZA *pieza, int x, int y)
{
  tablero->piezas[pieza->x][pieza->y] = NULL;
  actualiza_posicion_pieza(pieza, x, y);
  tablero->piezas[pieza->x][pieza->y] = pieza;
}

PIEZA* get_pieza(TABLERO *tablero, int x, int y)
{
  return tablero->piezas[x][y];
}
