/*-------------------------------------------------------------------
 * pieza.c
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

#include "pieza.h"

/**
 * @file pieza.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the struct and funtions to simulate Tetris
 * pieces for the "Combinatorial Optimization Heuristics" class. 
 *
 * En este archivo implementamos las funciones pieza y junto a 
 * la firma de funciones que se hacen uso de las estructuras y
 * manejo de las estructuras definidas como PIEZA, su manejo en 
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
PIEZA* init_pieza(int id, FORMA tipo)
{
  PIEZA *pieza = malloc(sizeof(PIEZA)); 
  pieza->id = id;
  pieza->tipo = tipo;
  pieza-> orientacion = 0;
  pieza->x = 0;
  pieza->y = 0;
  pieza->activo_centro = true;
  pieza->fija = false;
  int i;
  pieza->bloques = malloc(sizeof(PUNTO*)*3);
  for(i = 0; i < 3; i++) {
    pieza->bloques[i] = malloc(sizeof(PUNTO));
    pieza->bloques[i]->x = 0;
    pieza->bloques[i]->y = 0;
    pieza->bloques[i]->activo = true;
  }
  return pieza;
}

/**
 *
 */
PIEZA* copy_pieza(PIEZA *pieza)
{
  if(pieza == NULL)
    return NULL;
  PIEZA *pieza_nueva = malloc(sizeof(PIEZA)); 
  pieza_nueva->id = pieza->id;
  pieza_nueva->tipo = pieza->tipo;
  pieza_nueva-> orientacion = pieza->orientacion;
  pieza_nueva->x = pieza->x;
  pieza_nueva->y = pieza->y;
  pieza_nueva->activo_centro = pieza->activo_centro;
  pieza_nueva->fija = pieza->fija;
  int i;
  pieza_nueva->bloques = malloc(sizeof(PUNTO*)*3);
  for(i = 0; i < 3; i++){
    pieza_nueva->bloques[i] = malloc(sizeof(PUNTO));
    pieza_nueva->bloques[i]->x = pieza->bloques[i]->x;
    pieza_nueva->bloques[i]->y = pieza->bloques[i]->y;
    pieza_nueva->bloques[i]->activo = pieza->bloques[i]->activo;
  }
  return pieza_nueva;
}

/**
 *
 */
void free_pieza(PIEZA *pieza)
{
  if(pieza == NULL)
    return;
  pthread_mutex_lock(&lock_pieza);
  int i;
  for(i = 0; i < 3; i++)
    free(pieza->bloques[i]);
  free(pieza->bloques);
  free(pieza);
  pthread_mutex_unlock(&lock_pieza);
}

/**
 *
 */
void set_x_pieza(PIEZA *pieza, int x)
{
  pieza->x = x;
}

/**
 *
 */
void set_y_pieza(PIEZA *pieza, int y)
{
  pieza->y = y;
}


/**
 *
 */
void actualiza_cuadrado(PIEZA *pieza)
{
  pieza->bloques[0]->x = pieza->x+1;
  pieza->bloques[0]->y = pieza->y;
  pieza->bloques[1]->x = pieza->x;
  pieza->bloques[1]->y = pieza->y+1;
  pieza->bloques[2]->x = pieza->x+1;
  pieza->bloques[2]->y = pieza->y+1;
  
}

/**
 *
 */
void actualiza_left_gun(PIEZA *pieza)
{
 if(pieza->orientacion == 0){
    pieza->bloques[0]->x = pieza->x;
    pieza->bloques[0]->y = pieza->y+1;
    pieza->bloques[1]->x = pieza->x;
    pieza->bloques[1]->y = pieza->y-1;
    pieza->bloques[2]->x = pieza->x-1;
    pieza->bloques[2]->y = pieza->y-1;    
  }else if(pieza->orientacion == 90){
    pieza->bloques[0]->x = pieza->x+1;
    pieza->bloques[0]->y = pieza->y;
    pieza->bloques[1]->x = pieza->x-1;
    pieza->bloques[1]->y = pieza->y;
    pieza->bloques[2]->x = pieza->x-1;
    pieza->bloques[2]->y = pieza->y+1;
  }else if(pieza->orientacion == 180){
    pieza->bloques[0]->x = pieza->x;
    pieza->bloques[0]->y = pieza->y+1;
    pieza->bloques[1]->x = pieza->x;
    pieza->bloques[1]->y = pieza->y-1;
    pieza->bloques[2]->x = pieza->x+1;
    pieza->bloques[2]->y = pieza->y+1;    
  }else{
    pieza->bloques[0]->x = pieza->x+1;
    pieza->bloques[0]->y = pieza->y;
    pieza->bloques[1]->x = pieza->x-1;
    pieza->bloques[1]->y = pieza->y;
    pieza->bloques[2]->x = pieza->x+1;
    pieza->bloques[2]->y = pieza->y-1;
  }
}

/**
 *
 */
void actualiza_right_gun(PIEZA *pieza)
{
  if(pieza->orientacion == 0){
    pieza->bloques[0]->x = pieza->x;
    pieza->bloques[0]->y = pieza->y+1;
    pieza->bloques[1]->x = pieza->x;
    pieza->bloques[1]->y = pieza->y-1;
    pieza->bloques[2]->x = pieza->x+1;
    pieza->bloques[2]->y = pieza->y-1;    
  }else if(pieza->orientacion == 90){
    pieza->bloques[0]->x = pieza->x+1;
    pieza->bloques[0]->y = pieza->y;
    pieza->bloques[1]->x = pieza->x-1;
    pieza->bloques[1]->y = pieza->y;
    pieza->bloques[2]->x = pieza->x-1;
    pieza->bloques[2]->y = pieza->y-1;
  }else if(pieza->orientacion == 180){
    pieza->bloques[0]->x = pieza->x;
    pieza->bloques[0]->y = pieza->y+1;
    pieza->bloques[1]->x = pieza->x;
    pieza->bloques[1]->y = pieza->y-1;
    pieza->bloques[2]->x = pieza->x-1;
    pieza->bloques[2]->y = pieza->y+1;
  }else{
    pieza->bloques[0]->x = pieza->x+1;
    pieza->bloques[0]->y = pieza->y;
    pieza->bloques[1]->x = pieza->x-1;
    pieza->bloques[1]->y = pieza->y;
    pieza->bloques[2]->x = pieza->x+1;
    pieza->bloques[2]->y = pieza->y+1;     
  }
}

/**
 *
 */
void actualiza_left_snake(PIEZA *pieza)
{
  if(pieza->orientacion == 0 || pieza->orientacion == 180){
    pieza->bloques[0]->x = pieza->x;
    pieza->bloques[0]->y = pieza->y+1;
    pieza->bloques[1]->x = pieza->x-1;
    pieza->bloques[1]->y = pieza->y;
    pieza->bloques[2]->x = pieza->x-1;
    pieza->bloques[2]->y = pieza->y-1;   
  }else{
    pieza->bloques[0]->x = pieza->x+1;
    pieza->bloques[0]->y = pieza->y;
    pieza->bloques[1]->x = pieza->x;
    pieza->bloques[1]->y = pieza->y+1;
    pieza->bloques[2]->x = pieza->x-1;
    pieza->bloques[2]->y = pieza->y+1;  
  }
}

/**
 *
 */
void actualiza_right_snake(PIEZA *pieza)
{
  if(pieza->orientacion == 0 || pieza->orientacion == 180){
    pieza->bloques[0]->x = pieza->x;
    pieza->bloques[0]->y = pieza->y-1;
    pieza->bloques[1]->x = pieza->x-1;
    pieza->bloques[1]->y = pieza->y;
    pieza->bloques[2]->x = pieza->x-1;
    pieza->bloques[2]->y = pieza->y+1;    
  }else{
    pieza->bloques[0]->x = pieza->x-1;
    pieza->bloques[0]->y = pieza->y;
    pieza->bloques[1]->x = pieza->x;
    pieza->bloques[1]->y = pieza->y+1;
    pieza->bloques[2]->x = pieza->x+1;
    pieza->bloques[2]->y = pieza->y+1;  
  }
}

/**
 *
 */
void actualiza_i(PIEZA *pieza)
{
  if(pieza->orientacion == 0 || pieza->orientacion == 180){
    pieza->bloques[0]->x = pieza->x-1;
    pieza->bloques[0]->y = pieza->y;
    pieza->bloques[1]->x = pieza->x+1;
    pieza->bloques[1]->y = pieza->y;
    pieza->bloques[2]->x = pieza->x+2;
    pieza->bloques[2]->y = pieza->y;    
 }else{
    pieza->bloques[0]->x = pieza->x;
    pieza->bloques[0]->y = pieza->y-1;
    pieza->bloques[1]->x = pieza->x;
    pieza->bloques[1]->y = pieza->y+1;
    pieza->bloques[2]->x = pieza->x;
    pieza->bloques[2]->y = pieza->y+2;  
  }
}

/**
 *
 */
void actualiza_t(PIEZA *pieza)
{
  if(pieza->orientacion == 0){
    pieza->bloques[0]->x = pieza->x-1;
    pieza->bloques[0]->y = pieza->y;
    pieza->bloques[1]->x = pieza->x+1;
    pieza->bloques[1]->y = pieza->y;
    pieza->bloques[2]->x = pieza->x;
    pieza->bloques[2]->y = pieza->y-1;  
  }else if(pieza->orientacion == 90){
    pieza->bloques[0]->x = pieza->x;
    pieza->bloques[0]->y = pieza->y-1;
    pieza->bloques[1]->x = pieza->x;
    pieza->bloques[1]->y = pieza->y+1;
    pieza->bloques[2]->x = pieza->x-1;
    pieza->bloques[2]->y = pieza->y;    
  }else if(pieza->orientacion == 180){
    pieza->bloques[0]->x = pieza->x-1;
    pieza->bloques[0]->y = pieza->y;
    pieza->bloques[1]->x = pieza->x+1;
    pieza->bloques[1]->y = pieza->y;
    pieza->bloques[2]->x = pieza->x;
    pieza->bloques[2]->y = pieza->y+1;    
  }else{
    pieza->bloques[0]->x = pieza->x;
    pieza->bloques[0]->y = pieza->y-1;
    pieza->bloques[1]->x = pieza->x;
    pieza->bloques[1]->y = pieza->y+1;
    pieza->bloques[2]->x = pieza->x+1;
    pieza->bloques[2]->y = pieza->y;
  }
}

/**
 *
 */
void actualiza_bloques(PIEZA *pieza)
{
    switch(pieza->tipo){
  case Sq:
    actualiza_cuadrado(pieza);
    break;
  case LG:
    actualiza_left_gun(pieza);
    break;
  case RG:
    actualiza_right_gun(pieza);
    break;
  case LS:
    actualiza_left_snake(pieza);
    break;
  case RS:
    actualiza_right_snake(pieza);
    break;
  case I:
    actualiza_i(pieza);
    break;
  case T:
    actualiza_t(pieza);
    break;
  default:
    break;
  }
}

/**
 *
 */
void set_punto_pieza(PIEZA *pieza, int x, int y)
{
  set_x_pieza(pieza,x);
  set_y_pieza(pieza,y);
  actualiza_bloques(pieza);
}

/**
 *
 */
void rotar_pieza(PIEZA *pieza)
{
  pieza->orientacion = ((pieza->orientacion+90) % 360);
  actualiza_bloques(pieza);
}

/**
 *
 */
void rota_pieza(PIEZA *pieza,int grado)
{
  pieza->orientacion = grado;
  actualiza_bloques(pieza);
}

/**
 *
 */
void actualiza_posicion_pieza(PIEZA *pieza, int x, int y)
{
  pieza->x = x;
  pieza->y = y;
  actualiza_bloques(pieza);
}

/**
 *
 */
void deja_caer_pieza(PIEZA *pieza)
{
  actualiza_posicion_pieza(pieza,pieza->x,pieza->y-1);
}

/**
 *
 */
void levanta_pieza(PIEZA *pieza)
{
  actualiza_posicion_pieza(pieza,pieza->x,pieza->y+1);
}

/**
 *
 */
bool borra_bloque_pieza(PIEZA *pieza, int x, int y)
{
  if(pieza->x == x && pieza->y == y){
    pieza->activo_centro = false;
  }else if(pieza->bloques[0]->x == x && pieza->bloques[0]->y == y){
    pieza->bloques[0]->activo = false;
  }else if(pieza->bloques[1]->x == x && pieza->bloques[1]->y == y){
    pieza->bloques[1]->activo = false;
  }else if(pieza->bloques[2]->x == x && pieza->bloques[2]->y == y){
    pieza->bloques[2]->activo = false;
  }
  if(!pieza->activo_centro &&
     !pieza->bloques[0]->activo &&
     !pieza->bloques[1]->activo &&
     !pieza->bloques[2]->activo)    
    return true;
  return false;     
}

/**
 *
 */
void bajar_bloque_pieza(PIEZA *pieza, int x, int y)
{
  if(pieza->x == x && pieza->y == y+1){
    pieza->y = y;
  }else if(pieza->bloques[0]->x == x &&
	   pieza->bloques[0]->y == y+1 &&
	   pieza->bloques[0]->activo){
    pieza->bloques[0]->y = y;
  }else if(pieza->bloques[1]->x == x &&
	   pieza->bloques[1]->y == y+1 &&
	   pieza->bloques[1]->activo){
    pieza->bloques[1]->y = y;
  }else if(pieza->bloques[2]->x == x &&
	   pieza->bloques[2]->y == y+1 &&
	   pieza->bloques[2]->activo){
    pieza->bloques[2]->y = y;
  }
} //Fin de pieza.c
