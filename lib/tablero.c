/*-------------------------------------------------------------------
 * tablero.c
 * version 1.0
 * Copyright (C) 2017  Jose Ricardo Rodriguez Abreu.
 * Facultad de Ciencias,
 * Universidad Nacional Autonoma de Mexico, Mexico.
 *
 * Este programa es software libre; se puede redistribuir
 * y/o modificar en los terminos establecidos por la
 * Licencia Publica General de GNU tal como fue publicada
 * por la Free Software Foundation en la version 2 o
 * superior.
 *
 * Este programa es distribuido con la esperanza de que
 * resulte de utilidad, pero SIN GARANTIA ALGUNA; de hecho
 * sin la garantia implicita de COMERCIALIZACION o
 * ADECUACION PARA PROPOSITOS PARTICULARES. Vease la
 * Licencia Publica General de GNU para mayores detalles.
 *
 * Con este programa se debe haber recibido una copia de la
 * Licencia Publica General de GNU, de no ser asi, visite el
 * siguiente URL:
 * http://www.gnu.org/licenses/gpl.html
 * o escriba a la Free Software Foundation Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * -------------------------------------------------------------------
 */

#include "tablero.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * @file tablero.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the struct and funtions to simulate Tetris
 * board for the "Combinatorial Optimization Heuristics" class. 
 *
 * En este archivo implementamos la estructura tablero y junto a 
 * las funciones que se hacen uso de las estructuras y
 * manejo de las estructuras definidas como TABLERO, su manejo en 
 * memoria y la de los atributos que constituye su estructura.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/AceptacionUmbral
 *
 */

/**
 *
 */
TABLERO* init_tablero(int ancho, int alto)
{
  TABLERO *tablero = malloc(sizeof(TABLERO));
  tablero->alto = alto;
  tablero->ancho = ancho;  
  tablero->size = 0;
  tablero->num_piezas_totales = 0;
  tablero->piezas_actuales = 0;
  tablero->game_over = false;
  tablero->actual = malloc(sizeof(PIEZA*));
  tablero->actual = NULL;
  tablero->num_tetris = 0; 
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

/**
 *
 */
TABLERO* copy_tablero(TABLERO *tablero)
{
  TABLERO *tablero_nuevo = malloc(sizeof(TABLERO));
  tablero_nuevo->alto = tablero->alto;
  tablero_nuevo->num_piezas_totales = tablero->num_piezas_totales;
  tablero_nuevo->ancho = tablero->ancho;
  tablero_nuevo->piezas_actuales = tablero->piezas_actuales;
  tablero_nuevo->size = tablero->size;
  tablero_nuevo->num_tetris = tablero->num_tetris;
  tablero_nuevo->game_over = tablero->game_over;
  tablero_nuevo->actual = malloc(sizeof(PIEZA*));
  int actual_x = tablero->actual->x;
  int actual_y = tablero->actual->y;
  tablero_nuevo->max_size = tablero->max_size;
  tablero_nuevo->piezas = malloc((tablero->ancho+1)*sizeof(PIEZA***));
  int i, j, k;
  for(i = 0; i < tablero->ancho+1; i++)
    tablero_nuevo->piezas[i] =
      malloc((tablero->alto+1)*sizeof(PIEZA**));

  for(i = 0; i < tablero->ancho+1; i++) 
    for(j = 0; j < tablero->alto+1; j++)
      tablero_nuevo->piezas[i][j] = NULL;
  
  for(i = 0; i < tablero->ancho+1; i++) {
    for(j = 0; j < tablero->alto+1; j++) {
      if(tablero_nuevo->piezas[i][j] == NULL) {
	PIEZA *copiada = copy_pieza(tablero->piezas[i][j]);
	tablero_nuevo->piezas[i][j] = copiada;
	if(copiada != NULL)
	for(k = 0; k < 3; k++)
	    if(copiada->bloques[k]->activo)
	      tablero_nuevo->piezas
		[copiada->bloques[k]->x]
		[copiada->bloques[k]->y] = copiada;	
      }
    }
  }
  tablero_nuevo->actual = tablero_nuevo->piezas[actual_x][actual_y];
  return tablero_nuevo;
}

/**
 *
 */
void free_tablero(TABLERO *tablero)
{
  int i;
  for(i = 0; i < tablero->ancho+1; i++)
    free(tablero->piezas[i]);
  free(tablero->actual);
  free(tablero->piezas);
  free(tablero);
}

/**
 *
 */
void crear_pieza_tablero(TABLERO *tablero)
{
  PIEZA *nueva = init_pieza(tablero->size,rand()%7);
  set_punto_pieza(nueva,tablero->alto/2-2,tablero->ancho-3);
  agrega_pieza_tablero(tablero,nueva);
}

/**
 *
 */
void agrega_pieza_tablero(TABLERO *tablero, PIEZA *pieza)
{
  int i;
  if(tablero->piezas[pieza->x][pieza->y] != NULL) {
    tablero->game_over = true;
    return;
  }
  for(i = 0; i < 3; i++) {
    if(tablero->piezas[pieza->bloques[i]->x]
       [pieza->bloques[i]->y] != NULL) {
      tablero->game_over = true;
      return;
    }
  }
  tetris(tablero);
  tablero->size++;
  tablero->num_piezas_totales++;
  tablero->piezas_actuales += 4;
  if(tablero->size == tablero->max_size)
    {
      printf("Tamanio maximo alcanzado\n");
      //exit(1);
      tablero->game_over = true;
      return;
    }
  tablero->piezas[pieza->x][pieza->y] = pieza;  
  for(i = 0; i < 3; i++){
    tablero->piezas[pieza->bloques[i]->x]
      [pieza->bloques[i]->y] = pieza;
  }
  if(tablero->actual != NULL)
    tablero->actual->fija = true;
  tablero->actual = pieza;
}

/**
 *
 */
void borra_pieza_tablero(TABLERO *tablero, PIEZA *pieza)
{
  tablero->size--;
  int i;
  for(i = 0; i < 3; i++){
    if(tablero->piezas[pieza->bloques[i]->x]
       [pieza->bloques[i]->y] == pieza)
      tablero->piezas[pieza->bloques[i]->x]
	[pieza->bloques[i]->y] = NULL;    
  }
  if(tablero->piezas[pieza->x][pieza->y] == pieza)
    tablero->piezas[pieza->x][pieza->y] = NULL;
  free_pieza(pieza);
}

/**
 *
 */
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
    if(tablero->piezas[pieza->bloques[i]->x]
       [pieza->bloques[i]->y] != NULL)
      if(tablero->piezas[pieza->bloques[i]->x]
	 [pieza->bloques[i]->y] != pieza)
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
    tablero->piezas[pieza->bloques[i]->x]
      [pieza->bloques[i]->y] = NULL;
  tablero->piezas[pieza->x][pieza->y] = NULL;
  deja_caer_pieza(pieza);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x]
      [pieza->bloques[i]->y] = pieza;
    tablero->piezas[pieza->x][pieza->y] = pieza;
  return true;
}

/**
 *
 */
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
    if(tablero->piezas[pieza->bloques[i]->x]
       [pieza->bloques[i]->y] != NULL)
      if(tablero->piezas[pieza->bloques[i]->x]
	 [pieza->bloques[i]->y] != pieza)
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
    tablero->piezas[pieza->bloques[i]->x]
      [pieza->bloques[i]->y] = NULL;
  tablero->piezas[pieza->x][pieza->y] = NULL;
  rotar_pieza(pieza);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x]
      [pieza->bloques[i]->y] = pieza;
  tablero->piezas[pieza->x][pieza->y] = pieza;
  return true;
}

/**
 *
 */
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
    if(tablero->piezas[pieza->bloques[i]->x]
       [pieza->bloques[i]->y] != NULL)
      if(tablero->piezas[pieza->bloques[i]->x]
	 [pieza->bloques[i]->y] != pieza)
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
    tablero->piezas[pieza->bloques[i]->x]
      [pieza->bloques[i]->y] = NULL;
  tablero->piezas[pieza->x][pieza->y] = NULL;
  actualiza_posicion_pieza(pieza,pieza->x-1,pieza->y);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x]
      [pieza->bloques[i]->y] = pieza;
    tablero->piezas[pieza->x][pieza->y] = pieza;
  return true;
}

/**
 *
 */
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
    if(tablero->piezas[pieza->bloques[i]->x]
       [pieza->bloques[i]->y] != NULL)
      if(tablero->piezas[pieza->bloques[i]->x]
	 [pieza->bloques[i]->y] != pieza)
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
    tablero->piezas[pieza->bloques[i]->x]
      [pieza->bloques[i]->y] = NULL;
  tablero->piezas[pieza->x][pieza->y] = NULL;
  actualiza_posicion_pieza(pieza,pieza->x+1,pieza->y);
  for(i = 0; i < 3; i++)
    tablero->piezas[pieza->bloques[i]->x]
      [pieza->bloques[i]->y] = pieza;
  tablero->piezas[pieza->x][pieza->y] = pieza;
  return true;
}

/**
 *
 */
void busca_solucion_actual(TABLERO *tablero)
{
  bool fija = false;
  int lugares = rand()%tablero->ancho;
  int i = 0;
  if(rand()%2 == 0) {
    while(i++ < lugares)
      mover_izquierda_tablero(tablero,tablero->actual);
  }
  else {
    while(i++ < lugares)
      mover_derecha_tablero(tablero,tablero->actual);
  }
  while(!fija) {
    if(rand()%2 == 0)
      rotar_pieza_tablero(tablero,tablero->actual);
    if(rand()%2 == 0) {
      fija = !(mover_pieza_tablero(tablero,tablero->actual));
    }
  }
}

/**
 *
 */
void tetris_nivel(TABLERO *tablero,int l)
{
  int i,j;
  tablero->num_tetris++;
  for(i = l; i < tablero->alto; i++){
    for(j = 0; j < tablero->ancho; j++){
      PIEZA *antes = tablero->piezas[j][i];
      tablero->piezas[j][i] = NULL;
      tablero->piezas[j][i] = tablero->piezas[j][i+1];      
      if(antes != NULL){
	if(borra_bloque_pieza(antes,j,i)){
	  borra_pieza_tablero(tablero,antes);
	}
      }
      if(tablero->piezas[j][i] != NULL)
	bajar_bloque_pieza(tablero->piezas[j][i],j,i);
    }
  }
}

/**
 *
 */
void tetris(TABLERO *tablero)
{
  //
  int i,j;
  j = 0;
  bool bandera = true;
  while(j < tablero->alto-1){
    bandera = true;
    for(i = 0; i < tablero->ancho; i++){
      if(tablero->piezas[i][j] == NULL){
	bandera = false;
	break;
      }
    }
    if(bandera){
      tablero->piezas_actuales -= i-1;
      tetris_nivel(tablero,j);
      j--;
    }
    j++;
  }
}

/**
 *
 */
void set_pieza_nueva(TABLERO *tablero, PIEZA *pieza)
{
  if(pieza->tipo == I) {
    set_punto_pieza(pieza,(tablero->ancho/2)-1,tablero->alto-3);
  }
  else {
    set_punto_pieza(pieza,(tablero->ancho/2)-1,tablero->alto-2);
  }
}

/**
 *
 */
PIEZA* get_pieza(TABLERO *tablero, int x, int y)
{
  return tablero->piezas[x][y];
}

/**
 *
 */
void siguiente_turno_tablero(TABLERO *tablero)
{
  FORMA forma_random = rand() % 7;
  PIEZA *temp = init_pieza(tablero->num_piezas_totales+1,
			   forma_random);
  set_pieza_nueva(tablero,temp);
  agrega_pieza_tablero(tablero,temp);
}

/**
 *
 */
void imprime_tablero(TABLERO *tablero)
{
  int i,j;
  for(i = tablero->alto; i >= 0; i--) {
    for(j = 0; j < tablero->ancho; j++) {
      if(tablero->piezas[j][i] == NULL)
	printf("□");
      else
	printf("■");
    }
    printf("\n");
  }
  printf("\n\n");
} //Fin de tablero.c
