/* ------------------------------------------------------------------
 * abejas.h
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
#ifndef ABEJAS_H
#define ABEJAS_H

#include "tablero.h"

/**
 * @file abejas.h
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the Artificial bee definitions 
 * for a final project for the "Combinatorial Optimization 
 * Heuristics" class.
 *
 * En este archivo encabezado, definimos las estructuras y 
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
 * @brief La estructura abeja.
 * 
 * Su funcion es mantener una ruta (tablero) y una cantidad a la
 * que llamaremos "polen" que marca que tan buena es su ruta.
 *
 */
typedef struct abeja {
  double funcion; /**< Representa al polen, lo bueno de su ruta. */
  TABLERO *solucion; /**< Es la ruta que tomo la abeja. */
} ABEJA;

/**
 * @brief Inicia una nueva abeja.
 *
 * Inicializa los valores dentro de una estructura abeja.
 * @param tablero - Es la ruta de la cual la abeja parte.
 * @return Un apuntador a una estructura inicializada abeja.
 *
 */
ABEJA* init_abeja(TABLERO *tablero);

/**
 * @brief Busca nuevos origenes de "polen".
 *
 * Juega una partida dentro del tablero solucion que contiene,
 * lo que puede hacerse la analogia de que "viaja por polen".
 * @param abeja - La abeja que queremos "viaje".
 * @return El valor de la funcion que contiene el destino.
 *
 */
double busca_fuente_alimento(ABEJA *abeja);

/**
 * @brief Cambia el origen de la solucion de la abeja.
 *
 * Se le cambia el apuntador del tablero que la abeja tomara
 * para partir a realizar una nueva ruta a una nueva solucion.
 * @param tablero - Es el nuevo tablero de la abeja.
 * @param abeja - Es la abeja que deseamos modificar.
 *
 */
void set_tablero_abeja(TABLERO* tablero, ABEJA *abeja);

#endif //Fin de abejas.h
