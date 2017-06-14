/* ------------------------------------------------------------------
 * abc.h
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
 * ------------------------------------------------------------------
 */
#ifndef ABC_H
#define ABC_H

#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include "abejas.h"
#include "dump.h"
#include "funcion.h"
#include "tablero.h"

/**
 * @file abc.h
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the Artificial bee colony algorithm 
 * for a final project for the "Combinatorial Optimization 
 * Heuristics" class.
 *
 * En este archivo se define la unica funcion que dara vida al 
 * algoritmo de la colonia de abejas.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/abejas-tetris
 *
 */

/**
 * @brief - Artificial bee colony algorithm.
 *
 * Artificial bee colony algorithm o colonia de abejas.
 * Esta funcion ejecuta un set del juego completo de tetris,
 * teniendo como objetivo la optimizacion de ganar la mayoria
 * de puntos evitando perder y mantendiendo el tablero lo
 * mas limpio posible.
 * @param tablero_pointer - Es la posicion se encuentra el tablero.
 * @param empleadas - Es el numero de abejas que viviran.
 * @param distancia - Es la "distancia" en tiempo que recorreran.
 * @param lag - Para ver si lo ejecuta lento o no.
 *
 */
void ABC(TABLERO **tablero_pointer, int empleadas, int distancia, bool lag);

#endif //Fin de abc.h
