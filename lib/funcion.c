/* -A-----------------------------------------------------------------
 * funcion.c
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
#include "funcion.h"
#include "math.h"
#include <stdlib.h>

/**
 * @file funcion.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the Artificial bee colony algorithm 
 * for a final project for the "Combinatorial Optimization 
 * Heuristics" class.
 *
 * En este archivo se implementan los criterios que deben tener
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
 * @def INFINITO
 *
 * Redefine el infinito para usarlo negativo.
 *
 */
#define INFINITO -1*INFINITY

/**
 * @def degreesToRadians(angleDegrees)
 *
 * Convierte de grados a radiales.
 *
 */
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

/**
 * @def radiansToDegrees(angleRadians)
 *
 * Convierte de radianes a grados.
 *
 */
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

/**
 * @def pitagoras(x,y)
 *
 * Obtenemos la raiz del cuadrado de dos numeros.
 *
 */
#define pitagoras(x,y) (sqrt(pow(x,2)+pow(y,2)))

/**
 * @def valor_abs(x,y)
 *
 * Nos regresa la diferencia entre dos numeros en positivo.
 *
 */
#define valor_abs(x,y) (x > y ? (x-y) : (y-x))

/**
 * @def mi_max(x,y)
 *
 * Nos regresa el maximo de dos numeros.
 *
 */
#define mi_max(x,y) (x > y ? x : y)

/**
 * @brief Entrega un numero que representa la horizontalidad.
 *
 * Revisa para cada columna cuanta distancia hay de entre 
 * el ultimo nivel horizontal hasta el primer bloque
 * o tetrominoide que encuentre.
 * @param tablero - Es el tablero a revisar.
 * @param columna - Es la columna particular a revisar.
 * @return Regresa la diferencia con la columna y el techo.
 *
 */
double revisa_horizontal(TABLERO *tablero, int columna)
{
  int i = tablero->ancho;
  while(i > 0 && (tablero->piezas[i][columna] == NULL ||
		  !tablero->piezas[i][columna]->fija))
    i--;
  return (double)i;
}

/**
 * @brief Regresa un numero representativo para un dato del tablero.
 *
 * Regresa un entero mayor igual a cero para representar
 * todos los posibles caminos que puede tomar la linea skyline.
 * @param tablero - Es el tablero a revisar.
 * @return Regresa un numero mayor igual a cero. Entre mas
 * horizontal este la linea superior menor sera el numero.
 */
double horizontalidad(TABLERO *tablero)
{
  if(tablero->piezas_actuales == 1)
    return 0; 
  int i;
  double horizontalidad = 0;
  for(i = 0; i < tablero->ancho; i++) 
    horizontalidad += revisa_horizontal(tablero,i);  
  horizontalidad = (horizontalidad/tablero->ancho); 
  double valor_final = 0;  
  double columna_tmp;
  double diff;
  for(i = 0; i < tablero->ancho; i++) {
    columna_tmp = revisa_horizontal(tablero,i);    
    diff = valor_abs(horizontalidad,columna_tmp);
    valor_final += diff;      
  }
  return valor_final;
}

/**
 * @brief Regresa 1 si el cuadrito se encuentra atrapado.
 *
 * Revisa que un cuadro no se encuentre atrapado en el tablero,
 * en otras palabras, revisa que exista un vecino diferente a
 * un bloque ocupado.
 * @param tablero - Es el tablero que queremos observar.
 * @param x - Es la posicion x del cuadrito.
 * @param y - Es la posicion y del cuadrito.
 * @return 1 si se encuentra atrapado y 0 en caso contrario.
 *
 */
double atrapado(TABLERO *tablero, int x, int y) {
  int max_x = tablero->ancho;
  int max_y = tablero->alto;
  if(x == max_x && y == max_y) {
    if(tablero->piezas[x][y] == NULL &&
       tablero->piezas[x-1][y] != NULL &&
       tablero->piezas[x][y-1] != NULL)
      return 1;
  }
  else if(x == max_x) {
    if(tablero->piezas[x][y] == NULL &&
       tablero->piezas[x][y+1] != NULL &&
       tablero->piezas[x-1][y] != NULL &&
       tablero->piezas[x][y-1] != NULL)
      return 1;
  }
  else if(y == max_y) {
    if(tablero->piezas[x+1][y] == NULL &&
       tablero->piezas[x][y+1] != NULL &&
       tablero->piezas[x-1][y] != NULL &&
       tablero->piezas[x][y-1] != NULL)
      return 1;
  }
  else if(x == 0 && y == 0) {
    if(tablero->piezas[x][y] == NULL &&
       tablero->piezas[x+1][y] != NULL &&
       tablero->piezas[x][y+1] != NULL)
      return 1;
  }
  else if(x == 0) {
    if(tablero->piezas[x][y] == NULL &&
       tablero->piezas[x][y+1] != NULL &&
       tablero->piezas[x][y-1] != NULL)
      return 1;
  }
  else if(y == 0) {
    if(tablero->piezas[x][y] == NULL &&
       tablero->piezas[x][y+1] != NULL &&
       tablero->piezas[x-1][y] != NULL)
      return 1;
  }
  else {
    if(tablero->piezas[x][y] == NULL &&
       tablero->piezas[x+1][y] != NULL &&
       tablero->piezas[x][y+1] != NULL &&
       tablero->piezas[x-1][y] != NULL &&
       tablero->piezas[x][y-1] != NULL)
      return 1;
  }
  return 0;
}

/**
 * @brief Revisa cuantos cuadrados atrapados hay en el tablero.
 * 
 * Cuenta la cantidad de cuadritos que poseen a todos sus vecinos
 * ocupados de bloques pero el no esta ocupado.
 * @param tablero - Es el tablero que queremos evaluar.
 * @return El numero de cuadritos de 1x1 atrapados.
 *
 */
double cuenta_atrapados(TABLERO *tablero)
{
  int i,j;
  double ocupados = 0;
  for(i = 0; i < tablero->ancho; i++) {
    for(j = 0; j < tablero->alto; j++) {      
      ocupados += atrapado(tablero,i,j);
    }
  }
  return ocupados;
}

/**
 * @brief Nos dice si existe un bloque ocupado encima.
 *
 * Con el proposito de conocer si es posible acceder a 
 * bloque, revisamos todos los bloques a partir de @y.
 * @param tablero - Es el tablero en que trabajamos.
 * @param x - Es la posicion del ancho del bloque.
 * @param y - Es la altura del bloque.
 * @return 0 si esta libre y 1 en caso contrario.
 *
 */
int cuenta_cubierta(TABLERO *tablero, int x, int y)
{
  if(tablero->piezas[x][y] != NULL)
    return 0;
  int i,j;
  for(i = tablero->alto; i >= 0; i--) {
    if(i == y)
      return 0;
    else
      if(tablero->piezas[x][i] != NULL &&
	 tablero->piezas[x][i] != tablero->actual &&
	 tablero->piezas[x][i] != tablero->piezas[x][y])
	return 1;
  }
  return 0;
}

/**
 * @brief Cuenta los bloques tapados.
 *
 * Cuenta cuantos bloques es imposible
 * acceder ya que tienen algo encima.
 * @param tablero - Es el tablero que observamos.
 * @return El numero de bloques tapados o cubiertos.
 *
 */
double cuenta_cubiertas_total(TABLERO *tablero)
{
  int i,j;
  int total = 0;  
  for(i = 0; i < tablero->alto; i++) 
    for(j = 0; j < tablero->ancho; j++)
      if(cuenta_cubierta(tablero,j,i))
	total++;
  return (double)total;
}

/**
 * @brief Un estimado de que pronto se haga un tetris.
 *
 * Revisa cuantos cuadrados hay ocupados por bloques en este
 * nivel. El nivel debe no tener cuadros atrapados y 
 * ser el mas alto posible.
 * @param tablero - Es el tablero que queremos evaluar.
 * @param j - Es el nivel actual que estamos analizando.
 * @return Un numero mayor igual a cero. Entre mas grande mejor.
 *
 */
double probabilidad_tetris(TABLERO *tablero, int j)
{
  int i;
  double proba = 0;
  for(i = 0; i < tablero->ancho; i++) {
    //if(atrapado(tablero,i,j))
    if(cuenta_cubierta(tablero,i,j))
      return probabilidad_tetris(tablero,++j);
    if(tablero->piezas[i][j] != NULL) 
      proba++;
  }
  if(proba == 0)
    return 0;
  return proba;
}

/**
 *
 * Regresa un numero que entre mayor sea mejor. Utiliza las 
 * funciones con las siguientes condiciones:
 * Le resta los @cuenta_atrapados por cierta constante -50.
 * Le resta los @horizontalidad por cierta constante -10
 * Le suma los numero de tetris realizado por constante 1000
 * Le suma la @probabilidad_tetris que pronto se haga.
 *
 */
double waggle_dance(TABLERO *tablero)
{
  //Entre menor, mejor.
  double atrapados = cuenta_atrapados(tablero);
  //Entre menor, mejor.
  double horizontal = horizontalidad(tablero);
  //Entre mayor, mejor.
  double num_tetris = tablero->num_tetris;
  //Entre mayor, mejor.
  double probabilidad = probabilidad_tetris(tablero,0);
  //Entre menor, mejor.
  double cubiertos = cuenta_cubiertas_total(tablero);
  //Factor de perder.
  double perder = tablero->game_over ? INFINITO : 0;
  //La funcion, entre mayor, mejor.
  double fun = 0;
  fun += 2.8*horizontal;
  fun += 500*atrapados;
  fun += 100*cubiertos;

  fun -= 110*probabilidad;
  fun -= 2000*num_tetris;
  return fun;
}
//Fin de funcion.c
