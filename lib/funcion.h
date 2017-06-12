/* ------------------------------------------------------------------
 * funcion.h
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
#ifndef FUNCION_H
#define FUNCION_H
#include "tablero.h"

/**
 * @file funcion.h
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the Artificial bee colony algorithm 
 * for a final project for the "Combinatorial Optimization 
 * Heuristics" class.
 *
 * En este archivo se define los criterios que deben tener
 * las buenas rutas que una @abeja tenga. El baile que realiza 
 * o tambien llamado @waggle_dance nos devuelve un valor que
 * entre mayor sea, mas atractiva es el polen.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/abejas-tetris
 *
 */

/**
 * @brief Waggle dance es es baile de las abejas.
 *
 * Esta es la funcion que nos regresa un numero que representa
 * la abundancia de polen que contiene la ruta de una abeja en
 * particular.
 * @param tablero - Es el tablero que la abeja debe tener.
 * @return Un numero que entre mayor sea, mas abundancia habra.
 *
 */
double waggle_dance(TABLERO *tablero);

#endif //Fin de funcion.h
