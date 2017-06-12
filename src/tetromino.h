/* ------------------------------------------------------------------
 * tetromino.h
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
#ifndef TETROMINO_H
#define TETROMINO_H

#include "pieza.h"

/**
 * @file tetromino.h
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the openGL GUI for a final project for the
 * "Combinatorial Optimization Heuristics" class.
 *
 * Este archivo define las funciones que necesitamos para observar
 * las fichas del juego de tetris que la heuristica de abejas juega.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/abejas-tetris
 *
 */

/**
 * @brief Dibuja un cuadrado en la interfaz.
 *
 * Para dibujar en la cuadricula un cuadrado llamamos esta
 * funcion con sus coordenadas.
 * @param - Es la pieza a dibujar en el tablero.
 * @param dif_x es la posicion x del primer bloque del cuadro.
 * @param dif_y es la posicion y del primer bloque del cuadro.
 *
 */
void dibuja_cuadrado(PIEZA *pieza, int dif_x, int dif_y);

/**
 * @brief Dibuja una pistola izquierda en la interfaz.
 *
 * Para dibujar en la cuadricula un cuadrado llamamos esta
 * funcion con sus coordenadas.
 * @param - Es la pieza a dibujar en el tablero.
 * @param dif_x es la posicion x del primer bloque del cuadro.
 * @param dif_y es la posicion y del primer bloque del cuadro.
 *
 */
void dibuja_left_gun(PIEZA *pieza, int dif_x, int dif_y);

/**
 * @brief Dibuja una pistola derecha en la interfaz.
 *
 * Para dibujar en la cuadricula un cuadrado llamamos esta
 * funcion con sus coordenadas.
 * @param - Es la pieza a dibujar en el tablero.
 * @param dif_x es la posicion x del primer bloque del cuadro.
 * @param dif_y es la posicion y del primer bloque del cuadro.
 *
 */
void dibuja_right_gun(PIEZA *pieza, int dif_x, int dif_y);

/**
 * @brief Dibuja una serpiente izquierda en la interfaz.
 *
 * Para dibujar en la cuadricula un cuadrado llamamos esta
 * funcion con sus coordenadas.
 * @param - Es la pieza a dibujar en el tablero.
 * @param dif_x es la posicion x del primer bloque del cuadro.
 * @param dif_y es la posicion y del primer bloque del cuadro.
 *
 */
void dibuja_left_snake(PIEZA *pieza, int dif_x, int dif_y);

/**
 * @brief Dibuja una serpiente derecha en la interfaz.
 *
 * Para dibujar en la cuadricula un cuadrado llamamos esta
 * funcion con sus coordenadas.
 * @param - Es la pieza a dibujar en el tablero.
 * @param dif_x es la posicion x del primer bloque del cuadro.
 * @param dif_y es la posicion y del primer bloque del cuadro.
 *
 */
void dibuja_right_snake(PIEZA *pieza, int dif_x, int dif_y);

/**
 * @brief Dibuja una "I" en la interfaz.
 *
 * Para dibujar en la cuadricula un cuadrado llamamos esta
 * funcion con sus coordenadas.
 * @param - Es la pieza a dibujar en el tablero.
 * @param dif_x es la posicion x del primer bloque del cuadro.
 * @param dif_y es la posicion y del primer bloque del cuadro.
 *
 */
void dibuja_i(PIEZA *pieza, int dif_x, int dif_y);

/**
 * @brief Dibuja una "T" en la interfaz.
 *
 * Para dibujar en la cuadricula un cuadrado llamamos esta
 * funcion con sus coordenadas.
 * @param - Es la pieza a dibujar en el tablero.
 * @param dif_x es la posicion x del primer bloque del cuadro.
 * @param dif_y es la posicion y del primer bloque del cuadro.
 *
 */
void dibuja_t(PIEZA *pieza, int dif_x, int dif_y);

#endif //Fin de tetronimo.h
