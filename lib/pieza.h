/* -------------------------------------------------------------------
 * pieza.h
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

/**
 * @file pieza.h
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the struct and funtions to simulate Tetris
 * pieces for the "Combinatorial Optimization Heuristics" class. 
 *
 * En este archivo definimos la estructura pieza y junto a 
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

#ifndef PIEZA_H
#define PIEZA_H
#include <stdbool.h>


typedef enum FORMA {
  Sq, //Cuadrado ▢
  LG, // Left Gun: ⅃
  RG, // Right Gun: L         _
  LS, // Left snake ----_--->  |_
  RS, // Right snake->_|
  I,  // |
  T } FORMA; // T

/**
 * @brief La estructura PIEZA contiene datos basicos de ella.
 *
 * Usamos esta estructura para mantener unidos los datos que contiene
 * una pieza como tipo, orientacion, ..., y le asignamos un id para
 * identificarla de manera univocua.
 *
 */
typedef struct pieza {
  int id;
  FORMA tipo;
  int orientacion;
  int x;
  int y;
  bool fija;
  bool estado[4];
} PIEZA;

PIEZA* init_pieza(int id, FORMA tipo);
void free_pieza(PIEZA *pieza);
void rotar_pieza(PIEZA *pieza);
void rota_pieza(PIEZA *pieza,int grado);
void actualiza_posicion_pieza(PIEZA *pieza, int x, int y);

#endif //Fin de ciudad.h
