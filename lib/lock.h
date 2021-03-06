/*-------------------------------------------------------------------
 * lock.h
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

#ifndef LOCK_H
#define LOCK_H

#include <pthread.h>

/**
 * @file lock.h
 * @author Jose Ricardo Rodriguez Abreu
 * @date 13 Jun 2017
 * @brief File containing the struct and funtions to simulate Tetris
 * board for the "Combinatorial Optimization Heuristics" class. 
 *
 * Definimos un objeto mutex para evitar modificar un objeto NULL.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/AceptacionUmbral
 *
 */


/**
 * @var pthread_mutex_t lock
 * @brief Lock.
 *
 * Es un objeto mutex que evita continuar la ejecucion.
 * Con el proposito de liberar memoria y dibujar la interfaz, hacemos
 * uso de este objeto para no tener Segmentation fault.
 *
 */
pthread_mutex_t lock;

/**
 * @var pthread_mutex_t lock_pieza
 * @brief Lock de las piezas.
 *
 * Es un objeto mutex que evita continuar la ejecucion.
 * Con el proposito de liberar memoria y dibujar la interfaz, hacemos
 * uso de este objeto para no tener Segmentation fault.
 *
 */
pthread_mutex_t lock_pieza;

/**
 * @var pthread_mutex_t lock_basura
 * @brief Lock de la lista basura.
 *
 * Es un objeto mutex que evita continuar la ejecucion.
 * Con el proposito de liberar memoria y dibujar la interfaz, hacemos
 * uso de este objeto para no tener Segmentation fault.
 *
 */
pthread_mutex_t lock_basura;

#endif //Fin de lock.h
