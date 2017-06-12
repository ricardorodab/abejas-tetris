/*-------------------------------------------------------------------
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

#ifndef PIEZA_H
#define PIEZA_H
#include <stdbool.h>

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

/**
 * @brief La estructura pieza.
 * 
 * Su funcion es mantener una pieza unida y con la informacion
 * que necesitemos en su vida util dentro de un tablero.
 *
 */
typedef enum FORMA {
Sq, /**< Cuadrado ▢. */
  LG, /**< Left Gun: ⅃ . */
  RG, /**< Right Gun: L . */         
  LS, /**< Left snake. */
  RS, /**< Right snake. */
  I,  /**< Forma de |. */
  T   /**< Forma de T. */ } FORMA;

/**
 * @brief La estructura punto.
 * 
 * Su funcion es mantener una pieza ubicada por cada uno de
 * sus bloques que contienen una posicion.
 *
 */
typedef struct punto {
  int x; /**< Es el punto x. */
  int y; /**< Es el punto y. */
  bool activo; /**< Nos dice si un bloque se encuentra actvo. */
} PUNTO;

/**
 * @brief La estructura PIEZA contiene datos basicos de ella.
 *
 * Usamos esta estructura para mantener unidos los datos que contiene
 * una pieza como tipo, orientacion, ..., y le asignamos un id para
 * identificarla de manera univocua.
 *
 */
typedef struct pieza {
  int id; /**< Un id que la identifica de forma unica. */
  FORMA tipo; /**< Cada pieza debe tener una de 7 formas. */
  int orientacion; /**< La orientacion de la pieza. Existen 4. */
  int x; /**< La posicion x del centro. */
  int y; /**< La posicion y del centro. */
  bool fija; /**< Nos dice si la pieza se encuentra en juego ahora. */
  bool activo_centro; /**< Nos dice si el centro ya hizo tetris. */
  PUNTO **bloques; /**< Un arreglo de puntos para los bloques. */
} PIEZA;

/**
 * @brief 
 *
 *
 * @param id -
 * @param tipo -
 *
 */
PIEZA* init_pieza(int id, FORMA tipo);
PIEZA* copy_pieza(PIEZA *pieza);
void free_pieza(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza -
 * @param x -
 *
 */
void set_x_pieza(PIEZA *pieza, int x);

/**
 * @brief 
 *
 *
 * @param pieza -
 * @param y -
 *
 */
void set_y_pieza(PIEZA *pieza, int y);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void actualiza_cuadrado(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void actualiza_left_gun(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void actualiza_right_gun(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void actualiza_left_snake(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void actualiza_right_snake(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void actualiza_i(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void actualiza_t(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void actualiza_bloques(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza -
 * @param x -
 * @param y - 
 *
 */
void set_punto_pieza(PIEZA *pieza, int x, int y);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void rotar_pieza(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza -
 * @param grado -
 *
 */
void rota_pieza(PIEZA *pieza,int grado);

/**
 * @brief 
 *
 *
 * @param pieza -
 * @param x -
 * @param y -
 *
 */
void actualiza_posicion_pieza(PIEZA *pieza, int x, int y);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void deja_caer_pieza(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza - Es la pieza que deseamos modificar.
 *
 */
void levanta_pieza(PIEZA *pieza);

/**
 * @brief 
 *
 *
 * @param pieza -
 * @param x -
 * @param y -
 *
 */
bool borra_bloque_pieza(PIEZA *pieza, int x, int y);

/**
 * @brief 
 *
 *
 * @param pieza -
 * @param x -
 * @param y -
 *
 */
void bajar_bloque_pieza(PIEZA *pieza, int x, int y);
#endif //Fin de pieza.h
