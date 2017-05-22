#include "abc.h"
#include <math.h>
#include <stdbool.h>

void ABC(TABLERO *tablero,int empleadas)
{
  int i;
  //Inicializacion de la colmena.
  ABEJA *abejas_empleadas[empleadas];
  for(i = 0; i < empleadas; i++)
    abejas_empleadas[i] = init_abeja(EMPLEADA,copy_tablero(tablero));
  //Hasta que ganemos o perdamos.
  bool game_over = false;
  while(!game_over) {
    double funcion = INFINITY;
    double fun_temp;
    ABEJA *waggle_dance;
    for(i = 0; i < empleadas; i++) {
      fun_temp = busca_fuente_alimento(abejas_empleadas[i]);
      if(fun_temp < funcion){
	funcion = fun_temp;
	waggle_dance = abeja_empleada[i];
      }
    }
    
  }
}
