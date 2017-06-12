/* ------------------------------------------------------------------
 * abejas.c
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

#include "abejas.h"
#include "funcion.h"
#include <stdlib.h>

/**
 * @file abejas.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the Artificial bee definitions 
 * for a final project for the "Combinatorial Optimization 
 * Heuristics" class.
 *
 * En este archivo de c, implementamos las estructuras y 
 * las funciones que tendran nuestras abjeas artificiales 
 * para la ejecucion del ABC.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/abejas-tetris
 *
 */

/**
 * Creamos en memoria una abeja nueva y iniciamos tu tablero 
 * y la funcion con el valor del @tablero.
 *
 */
ABEJA* init_abeja(TABLERO* tablero)
{
  ABEJA *abeja = malloc(sizeof(ABEJA));
  abeja->solucion = tablero;
  abeja->funcion = waggle_dance(tablero);
  return abeja;
}

/**
 * La busqueda de caminos a polem es en realidad 
 * encontrar una solucion al tablero actual de la abeja.
 * @see busca_solucion_actual
 *
 */
double busca_fuente_alimento(ABEJA *abeja)
{
  busca_solucion_actual(abeja->solucion);
  abeja->funcion = waggle_dance(abeja->solucion);
  return abeja->funcion;
}

/**
 * Al cambiar el @tablero de la @abeja, tambien hay que
 * realizar la nueva modificacion a la @funcion de la 
 * abeja.
 *
 */
void set_tablero_abeja(TABLERO* tablero, ABEJA *abeja)
{
  abeja->solucion = tablero;
  abeja->funcion = waggle_dance(tablero);
} //Fin de abejas.c
