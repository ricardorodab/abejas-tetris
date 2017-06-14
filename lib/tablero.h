/*-------------------------------------------------------------------
 * tablero.h
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

#ifndef TABLERO_H
#define TABLERO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lock.h"
#include "pieza.h"

/**
 * @file tablero.h
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the struct and funtions to simulate Tetris
 * board for the "Combinatorial Optimization Heuristics" class. 
 *
 * En este archivo definimos la estructura tablero y junto a 
 * la firma de funciones que se hacen uso de las estructuras y
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
 * @brief La estructura TABLERO contiene datos basicos de el.
 *
 * Usamos esta estructura para mantener unidos los datos que contiene
 * un juego como piezas, actual.
 *
 */

typedef struct tablero {
  int alto; /**< Es el alto del tablero. */
  int ancho; /**< Es el ancho del tablero. */
  int size; /**< Es la cantidad de piezas que posee el tablero. */
  int max_size; /**< Es el maximo nuero de piezas que puede tener. */
  int num_piezas_totales; /**< Es el numero de piezas jugadas. */
  int piezas_actuales; /**< Es el numero de piezas jugadas actual. */
  int num_tetris; /**< Es el numero de tetris que ha hecho. */
  bool game_over; /**< Nos dice si el tablero termino y perdio. */
  PIEZA ***piezas; /**< Es el arreglo[][] de pointer a piezas. */
  PIEZA *actual; /**< Es la pieza actual que se juega. */
} TABLERO;

/**
 * @brief
 *
 *
 * @param alto -
 * @param ancho -
 * @return
 *
 */
TABLERO* init_tablero(int alto, int ancho);

/**
 * @brief
 *
 *
 * @param tablero -
 * @return
 */
TABLERO* copy_tablero(TABLERO *tablero);

/**
 * @brief
 *
 *
 * @param tablero -
 *
 */
void free_tablero(TABLERO *tablero);

/**
 * @brief
 *
 *
 * @param tablero -
 *
 */
void crear_pieza_tablero(TABLERO *tablero);

/**
 * @brief
 *
 *
 * @param tablero -
 * @param pieza -
 *
 */
void agrega_pieza_tablero(TABLERO *tablero, PIEZA *pieza);

/**
 * @brief
 *
 *
 * @param tablero -
 * @param pieza -
 *
 */
void borra_pieza_tablero(TABLERO *tablero, PIEZA *pieza);

/**
 * @brief
 *
 *
 * @param tablero -
 * @param pieza -
 * @return
 *
 */
bool mover_pieza_tablero(TABLERO *tablero, PIEZA *pieza);

/**
 * @brief
 *
 *
 * @param tablero -
 * @param pieza -
 * @return
 *
 */
bool rotar_pieza_tablero(TABLERO *tablero, PIEZA *pieza);

/**
 * @brief
 *
 *
 * @param tablero -
 * @param pieza -
 * @return
 *
 */
bool mover_izquierda_tablero(TABLERO *tablero, PIEZA *pieza);

/**
 * @brief
 *
 *
 * @param tablero -
 * @param pieza -
 * @return
 *
 */
bool mover_derecha_tablero(TABLERO *tablero, PIEZA *pieza);

/**
 * @brief
 *
 *
 * @param tablero -
 *
 */
void busca_solucion_actual(TABLERO *tablero);

/**
 * @brief
 *
 *
 * @param tablero -
 * @param l -
 *
 */
void tetris_nivel(TABLERO *tablero, int l);

/**
 * @brief
 *
 *
 * @param tablero -
 *
 */
void tetris(TABLERO *tablero);

/**
 * @brief
 *
 *
 * @param tablero -
 * @param pieza -
 *
 */
void set_pieza_nueva(TABLERO *tablero, PIEZA *pieza);

/**
 * @brief
 *
 *
 * @param tablero -
 * @param x -
 * @param y -
 * @return 
 *
 */
PIEZA* get_pieza(TABLERO *tablero, int x, int y);

/**
 * @brief
 *
 *
 * @param tablero -
 *
 */
void siguiente_turno_tablero(TABLERO *tablero);

/**
 * @brief
 *
 *
 * @param tablero -
 *
 */
void imprime_tablero(TABLERO *tablero);

#endif //Fin de tablero.h
