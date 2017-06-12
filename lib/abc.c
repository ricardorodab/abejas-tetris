#include "abc.h"
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "funcion.h"

#define FUTURO_COTA 50
#define INFINITO -1*INFINITY

void ABC(TABLERO **tablero_pointer,int empleadas)
{
  int i,futuro;
  TABLERO *tablero = *tablero_pointer;
  double funcion = INFINITO;
  //Inicializacion de la colmena.
  ABEJA *abejas_empleadas[empleadas];
  for(i = 0; i < empleadas; i++)
    abejas_empleadas[i] = init_abeja(copy_tablero(tablero));
  //Hasta que ganemos o perdamos.
  bool game_over = false;
  while(!game_over) {
    double fun_temp;
    ABEJA *waggle_dance;
    for(i = 0; i < empleadas; i++) {
      for(futuro = 0; futuro < FUTURO_COTA; futuro++) {
	fun_temp = busca_fuente_alimento(abejas_empleadas[i]);      
	if(fun_temp > funcion){
	  funcion = fun_temp;
	  waggle_dance = abejas_empleadas[i];
	}
      }
      funcion = waggle_dance->funcion;
    }
    //funcion = INFINITO;
    //Para cada abeja empleada ahora buscan sobre este tablero
    //la manera de acomodar esta pieza en distintas locaciones
    //dentro de un rango definido.
    *(tablero_pointer) = waggle_dance->solucion;
    //imprime_tablero(waggle_dance->solucion);
    tablero = waggle_dance->solucion;
    siguiente_turno_tablero(tablero);
    for(i = 0; i < empleadas; i++)
      set_tablero_abeja(copy_tablero(tablero),abejas_empleadas[i]);
    //imprime_tablero(tablero);
    printf("Fun=%f\n",waggle_dance->funcion);
    //printf("atrapados=%f\n",cuenta_atrapados(waggle_dance->solucion));
    usleep(50000);
  }
}
