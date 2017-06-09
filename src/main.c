/* -------------------------------------------------------------------
 * main.c
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
 * @file main.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the final project for the
 * "Combinatorial Optimization Heuristics" class.
 *
 * Este programa utiliza una heuristica conocida por "Abejas"
 * sobre el famoso problema tetris. Donde buscamos la manera de
 * acomodar fichas de tetris dado un tablero.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/AceptacionUmbral
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "tablero.h"
#include "funcion.h"
#include "abc.h"
#include "interfaz-grafica.h"


/**
 * @brief Linea del codigo actual.
 *
 * Re-definimos la constante de linea que viene por default en C.
 *
 */
#define LINEA __LINE__

int size_x;
int size_y;

/**
 * @brief Variable de marcardo de error.
 *
 * Si en algun momento de la ejecucion esta variable es != 0 terminamos. 
 *
 */
int ERROR = 0;

/**
 * @brief Una funcion simple para imprimir que hubo un error y en que linea.
 *
 * Si llega a ocurrir se debe anexar un mensaje de error que el usuario
 * pueda ver para facilitar la facil busqueda de este.
 *
 * @param msg -Es la cadena que se le mostrara al usuario.
 * @param linea -Es la linea del codigo donde ocurrio este error. 
 * @see ERROR
 * @note Esta funcion termina la ejecucion del programa.
 * @waring
 *
 */
void main_imprime_error(char *msg,int linea)
{
  char *err = "-Linea:";
  printf("%s%s%d\n",msg,err,linea);
  exit(1);
}


typedef struct param{
  int argc;
  char **argv;
  TABLERO **tablero;
  double zoom;
} PARAM;

void* heuristica_abejas(void *thread_param)
{
  PARAM *param = (PARAM*)thread_param;
  TABLERO **tablero = param->tablero;
  siguiente_turno_tablero(*tablero);
  bool stop_condition = true;
  ABC(tablero, 100);
  pthread_exit(NULL);
}

/**
 * @brief Metodo principal del programa.
 *
 * Tratamos de encontrar soluciones factibles al problema del viajero.
 * @param argc - Es el numero de parametros. En este caso se espera argc > 2.
 * @param argv - Son los parametros que nos daran la base de datos y banderas.
 * @return Un entero 0 si todo sale bien 1 en caso contrario.
 *
 */
int main(int argc, char** argv)
{
  srand(time(NULL));
  //Inicializamos una variable para medir el tiempo de ejecucion:
  clock_t tic = clock();
  pthread_t threads[2];
  size_x = 26;size_y = 36;
  //size_x = 20;size_y = 10;
  TABLERO *temp = init_tablero(size_y,size_x);
  TABLERO **tablero = &temp;
  PARAM *param = malloc(sizeof(PARAM));
  param->argc = argc;
  param->argv = argv;
  param->tablero = tablero;
  double zoom_param = 5;
  
  pthread_create(&threads[0],NULL,heuristica_abejas,(void*)param);
  visual_main(argc,argv,tablero,zoom_param);
  //Contamos el tiempo:
  clock_t toc = clock();
  double segundos = (double)(toc - tic) / CLOCKS_PER_SEC;
  printf("Transcurrieron: %f segundos o %f minutos.\n",segundos,segundos/60);
  pthread_exit(NULL);
  return 0; 
} //Fin de main.c

