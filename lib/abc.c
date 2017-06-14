/* ------------------------------------------------------------------
 * abc.c
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

#include "abc.h"

/**
 * @file abc.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the Artificial bee colony algorithm 
 * for a final project for the "Combinatorial Optimization 
 * Heuristics" class.
 *
 * En este archivo se implementa la unica funcion que dara vida al 
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
 * @def INFINITO
 *
 * Redefine el infinito para usarlo negativo.
 *
 */
#define INFINITO 1*INFINITY

#define COMPARADOR(x,y) (x < y)

/**
 * El algoritmo funciona de la siguiente manera:
 * 1. Inicializamos a nuestras abejas con nuestro tablero.
 * 2. Cada abeja tendra un clon de nuestro tablero inicial.
 * 3. Mientras que no hayamos perdido ejecutamos los 4,5,6,7,8 y 9.
 * 4. Cada abeja empleada sale a una @distancia propuesta.
 * 5. Busca soluciones a tu clon de tablero y sus juegos.
 * 6. Regresa y hace el baile "waggle dance" para ver si ella es
 * la "waggle bee" que guiara el tablero.
 * 7. Si su nectar (funcion) es mejor, avisa a la colmena.
 * 8. Al final la mejor "waggle bee" marca el camino y todas las
 * abejas deben copiar su camino.
 * 9. Revisamos que no hayamos perdido en el siguiente turno.
 * 10. Terminamos.
 *
 */
void ABC(TABLERO **tablero_pointer,
	 int empleadas,
	 int distancia,
	 bool lag)
{
  double fun_temp, inf_tmp;
  int i,distancia_it;
  TABLERO *tablero = *tablero_pointer;
  double funcion = INFINITO;
  //Inicializacion de la colmena.
  ABEJA *abejas_empleadas[empleadas];
  for(i = 0; i < empleadas; i++)
    abejas_empleadas[i] = init_abeja(copy_tablero(tablero));
  //Inicializamos en particular la abeja waggle.
  ABEJA *waggle_bee = init_abeja(copy_tablero(tablero));
  waggle_bee->waggle_bee = true;
  //Hasta que ganemos o perdamos.
  bool game_over = false;
  while(!game_over) {
    //Nuestro maximo local:
    inf_tmp = INFINITO;
    //Almacenamos nuestra mejor abeja local.
    ABEJA *waggle_bee_tmp;
    //Para preguntar si la abeja global cambia:
    bool cambio = false;
    
    for(i = 0; i < empleadas; i++) {
      // Hacemos que recorra cierta "distancia"
      // que en realidad es las posibilidades de la pieza.
      for(distancia_it = 0; distancia_it < distancia; distancia_it++) {
	busca_fuente_alimento(abejas_empleadas[i]);
	if(abejas_empleadas[i]->solucion->game_over)
	  break;      
	} //
	fun_temp = do_waggle_dance(abejas_empleadas[i]);
	
	if(COMPARADOR(fun_temp,inf_tmp)) {
	  inf_tmp = fun_temp;
	  waggle_bee_tmp = abejas_empleadas[i];
	}
	
	if(COMPARADOR(fun_temp,funcion)) {
	  funcion = fun_temp;
	  cambio = true;
	  waggle_bee->funcion = funcion;
	  set_tablero_abeja(copy_tablero(abejas_empleadas[i]->solucion),
			    waggle_bee);
	}
	//} //
    }
    if(!cambio) {
      set_tablero_abeja(copy_tablero(waggle_bee_tmp->solucion),
			waggle_bee);
      waggle_bee->funcion = inf_tmp;
    }
    funcion = waggle_bee->funcion;
    //Para cada abeja empleada ahora buscan sobre este tablero
    //la manera de acomodar esta pieza en distintas locaciones
    //dentro de un rango definido.
    *(tablero_pointer) = (copy_tablero(waggle_bee->solucion));
    agrega_basura(tablero); 
    tablero = (copy_tablero(waggle_bee->solucion));
    siguiente_turno_tablero(tablero);
    game_over = tablero->game_over;
    if(!game_over) {
      for(i = 0; i < empleadas; i++) 
	set_tablero_abeja(copy_tablero(tablero),abejas_empleadas[i]);
    }
    if(lag) 
      usleep(50000);
  }
  for(i = 0; i < empleadas; i++)
    free_abeja(abejas_empleadas[i]);
  free(waggle_bee);
} //Fin de abc.c
