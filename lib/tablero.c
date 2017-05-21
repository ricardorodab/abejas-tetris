#include "tablero.h"
#include <stdio.h>
#include <stdlib.h>

TABLERO* init_tablero(int ancho, int alto)
{
  TABLERO *tablero = malloc(sizeof(TABLERO));
  tablero->alto = alto;
  tablero->ancho = ancho;  
  tablero->size = 0;
  tablero->num_piezas_totales = 0;
  tablero->piezas_actuales = 0;
  tablero->actual = malloc(sizeof(PIEZA*));
  tablero->actual = NULL;
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

TABLERO* copy_tablero(TABLERO *tablero)
{
  TABLERO *tablero_nuevo = malloc(sizeof(TABLERO));
  tablero_nuevo->alto = tablero->alto;
  tablero_nuevo->num_piezas_totales = tablero->num_piezas_totales;
  tablero_nuevo->ancho = tablero->ancho;
  tablero_nuevo->piezas_actuales = tablero->piezas_actuales;
  tablero_nuevo->size = tablero->size;
  tablero_nuevo->actual = malloc(sizeof(PIEZA*));
  tablero_nuevo->actual = tablero->actual;
  tablero_nuevo->max_size = tablero->max_size;
  tablero_nuevo->piezas = malloc((tablero->ancho+1)*sizeof(PIEZA***));
  int i, j;
  for(i = 0; i < tablero->ancho+1; i++)
    tablero_nuevo->piezas[i] = malloc((tablero->alto+1)*sizeof(PIEZA**));
  for(i = 0; i < tablero->ancho+1; i++)
    for(j = 0; j < tablero->alto+1; j++)
      tablero_nuevo->piezas[i][j] = tablero->piezas[i][j];
  return tablero_nuevo;
}

void free_tablero(TABLERO *tablero)
{
  int i;
  for(i = 0; i < tablero->ancho+1; i++)
    free(tablero->piezas[i]);
  free(tablero->actual);
  free(tablero->piezas);
  free(tablero);
}

void crear_pieza_tablero(TABLERO *tablero)
{
  PIEZA *nueva = init_pieza(tablero->size,rand()%7);
  set_punto_pieza(nueva,tablero->alto/2-2,tablero->ancho-3);
  agrega_pieza_tablero(tablero,nueva);
}

void agrega_pieza_tablero(TABLERO *tablero, PIEZA *pieza)
{
  tablero->size++;
  tablero->num_piezas_totales++;
  tablero->piezas_actuales += 4;
  if(tablero->size == tablero->max_size)
    {
      printf("Tamanio maximo alcanzado\n");
      exit(1);
    }
  tablero->piezas[pieza->x][pieza->y] = pieza;  
  int i;
  for(i = 0; i < 3; i++){
    tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = pieza;
  }
  if(tablero->actual != NULL)
    tablero->actual->fija = true;
  tablero->actual = pieza;
}

void borra_pieza_tablero(TABLERO *tablero, PIEZA *pieza)
{
  tablero->size--;
  int i;
  for(i = 0; i < 3; i++){
    if(tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] == pieza)
      tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = NULL;    
  }
  if(tablero->piezas[pieza->x][pieza->y] == pieza)
    tablero->piezas[pieza->x][pieza->y] = NULL;
  free_pieza(pieza);
}

bool mover_pieza_tablero(TABLERO *tablero, PIEZA *pieza)
{
  int i;
  if(pieza->fija == true)
    return false;
  for(i = 0; i < 3; i++){
    if(pieza->bloques[i]->y <= 0 ||
       pieza->bloques[i]->y >= tablero->alto){
      return false;
    }
  }
  if(pieza->y <= 0 || pieza-> x < 0 || pieza->y >= tablero->alto ||
     pieza->x >= tablero->ancho){
    return false;
  }
  deja_caer_pieza(pieza);
  for(i = 0; i < 3; i++)
    if(tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] != NULL)
      if(tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] != pieza)
	{
	  levanta_pieza(pieza);
	  return false;
	}
  if(tablero->piezas[pieza->x][pieza->y] != NULL)
    if(tablero->piezas[pieza->x][pieza->y] != pieza)
      {
	levanta_pieza(pieza);
	return false;
      }
  levanta_pieza(pieza);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = NULL;
  tablero->piezas[pieza->x][pieza->y] = NULL;
  deja_caer_pieza(pieza);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = pieza;
    tablero->piezas[pieza->x][pieza->y] = pieza;
  return true;
}

bool rotar_pieza_tablero(TABLERO *tablero, PIEZA *pieza)
{
  int i;
  if(pieza->fija == true)
    return false;
  rotar_pieza(pieza);
  if(pieza->bloques[i]->y <= 0 || pieza->bloques[i]->x <= 0 ||
       pieza->bloques[i]->y >= tablero->alto ||
       pieza->bloques[i]->x >= tablero->ancho-1){
    rota_pieza(pieza,(pieza->orientacion-90)%360);
    return false;
  }
  if(pieza->y <= 0 || pieza-> x <= 0 || pieza->y >= tablero->alto ||
     pieza->x >= tablero->ancho-1){
    rota_pieza(pieza,(pieza->orientacion-90)%360);
    return false;
  }
  for(i = 0; i < 3; i++)
    if(tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] != NULL)
      if(tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] != pieza)
	{
	  rota_pieza(pieza,(pieza->orientacion-90)%360);
	  return false;
	}
  if(tablero->piezas[pieza->x][pieza->y] != NULL)
    if(tablero->piezas[pieza->x][pieza->y] != pieza)
      {
	rota_pieza(pieza,(pieza->orientacion-90)%360);
	return false;
      }
  rota_pieza(pieza,(pieza->orientacion-90)%360);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = NULL;
  tablero->piezas[pieza->x][pieza->y] = NULL;
  rotar_pieza(pieza);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = pieza;
  tablero->piezas[pieza->x][pieza->y] = pieza;
  return true;
}

bool mover_izquierda_tablero(TABLERO *tablero, PIEZA *pieza)
{
  int i;
  if(pieza->fija == true)
    return false;
  for(i = 0; i < 3; i++){
    if(pieza->bloques[i]->x <= 0){
      return false;
    }
  }
  if(pieza-> x <= 0){
    return false;
  }
  actualiza_posicion_pieza(pieza,pieza->x-1,pieza->y);
  for(i = 0; i < 3; i++)
    if(tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] != NULL)
      if(tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] != pieza)
	{
	  actualiza_posicion_pieza(pieza,pieza->x+1,pieza->y);
	  return false;
	}
  if(tablero->piezas[pieza->x][pieza->y] != NULL)
    if(tablero->piezas[pieza->x][pieza->y] != pieza)
      {
	actualiza_posicion_pieza(pieza,pieza->x+1,pieza->y);
	return false;
      }
  actualiza_posicion_pieza(pieza,pieza->x+1,pieza->y);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = NULL;
  tablero->piezas[pieza->x][pieza->y] = NULL;
  actualiza_posicion_pieza(pieza,pieza->x-1,pieza->y);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = pieza;
    tablero->piezas[pieza->x][pieza->y] = pieza;
  return true;
}

bool mover_derecha_tablero(TABLERO *tablero, PIEZA *pieza)
{
  int i;
  if(pieza->fija == true)
    return false;
  for(i = 0; i < 3; i++){
    if(pieza->bloques[i]->x >= tablero->ancho-1){
      return false;
    }
  }
  if(pieza->x >= tablero->ancho-1){
    return false;
  }
  actualiza_posicion_pieza(pieza,pieza->x+1,pieza->y);
  for(i = 0; i < 3; i++)
    if(tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] != NULL)
      if(tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] != pieza)
	{
	  actualiza_posicion_pieza(pieza,pieza->x-1,pieza->y);
	  return false;
	}
  if(tablero->piezas[pieza->x][pieza->y] != NULL)
    if(tablero->piezas[pieza->x][pieza->y] != pieza)
      {
	actualiza_posicion_pieza(pieza,pieza->x-1,pieza->y);
	return false;
      }
  actualiza_posicion_pieza(pieza,pieza->x-1,pieza->y);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = NULL;
  tablero->piezas[pieza->x][pieza->y] = NULL;
  actualiza_posicion_pieza(pieza,pieza->x+1,pieza->y);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x][pieza->bloques[i]->y] = pieza;
  tablero->piezas[pieza->x][pieza->y] = pieza;
  return true;
}

void busca_solucion_actual(TABLERO *tablero)
{
  bool fija = false;
  mover_pieza_tablero(tablero,tablero->actual);
  while(!fija){
    if(rand()%2 == 0)
      rotar_pieza_tablero(tablero,tablero->actual);
    int r = rand()%2;
    if(r == 0)
      mover_izquierda_tablero(tablero,tablero->actual);
    else if(r == 1)
      mover_derecha_tablero(tablero,tablero->actual);
    if(rand()%2 == 0)
      fija = !(mover_pieza_tablero(tablero,tablero->actual));
  }
}

/**
 *
 */
void tetris_nivel(TABLERO *tablero,int l)
{
  int i,j;
  for(i = l; i < tablero->alto; i++){
    for(j = 0; j < tablero->ancho; j++){
      PIEZA *antes = tablero->piezas[j][i];
      tablero->piezas[j][i] = NULL;
      tablero->piezas[j][i] = tablero->piezas[j][i+1];      
      if(antes != NULL)
	if(borra_bloque_pieza(antes,j,i)){
	  tablero->piezas_actuales--;
	  borra_pieza_tablero(tablero,antes);
	}
      if(tablero->piezas[j][i] != NULL)
	bajar_bloque_pieza(tablero->piezas[j][i],j,i);
    }
  }
}

void tetris(TABLERO *tablero)
{
  int i,j;
  j = tablero->alto-1;
  bool bandera = true;
  while(j >= 0){
    bandera = true;
    for(i = 0; i < tablero->ancho; i++){
      if(tablero->piezas[i][j] == NULL){
	bandera = false;
	break;
      }
    }
    if(bandera)
      tetris_nivel(tablero,j);
    j--;
  }
}

PIEZA* get_pieza(TABLERO *tablero, int x, int y)
{
  return tablero->piezas[x][y];
}
