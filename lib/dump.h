/*-------------------------------------------------------------------
 * dump.h
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

#ifndef DUMP_H
#define DUMP_H

#include <unistd.h>
#include <glib.h>
#include "tablero.h"

/**
 * @file dump.h
 * @author Jose Ricardo Rodriguez Abreu
 * @date 13 Jun 2017
 * @brief File containing the struct and funtions to simulate Tetris
 * board for the "Combinatorial Optimization Heuristics" class. 
 *
 * Aqui se guardara todo lo que queremos vaciar.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/AceptacionUmbral
 *
 */


/**
 * @var GList *basurero
 * @brief Basurero.
 *
 * Es un objeto lista que evita acumular basura
 * Con el proposito de liberar memoria, hacemos
 * uso de este objeto para no tener Segmentation fault.
 *
 */
GList *basurero;

/**
 * @brief Agregamos basura a la "pila".
 *
 * Con esta funcion agregamos basura a una lista para
 * que eventualmente sea liberado el tablero que se guardo.
 *@ param tablero - Es el tablero que queremos eliminar.
 *
 */
void agrega_basura(TABLERO *tablero);

/**
 * @brief Limpia la "pila" de basura.
 *
 * Se ejecuta un @free_tablero para todos los elementos
 * actuales de la lista @basurero.
 *
 */
void limpia(void);

#endif //Fin de dump.h
