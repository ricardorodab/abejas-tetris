#include "funcion.h"
#include "math.h"
#include <stdio.h>
// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)



double funcion_costo(TABLERO *tablero)
{
  double cateto_adyacente = carga(tablero);
  double hipotenusa = sqrt(pow(cateto_adyacente,2) +
			   pow(tablero->num_piezas_totales,2));
  double grados = cateto_adyacente/hipotenusa;
  double radiales = degreesToRadians(grados);
  printf("π/2=%f\n",M_PI/2);
  double arcoseno = acos(radiales);  
  return fabs(arcoseno);
}

double carga(TABLERO *tablero)
{
  double max_piezas = tablero->ancho*tablero->alto;
  double piezas_actuales = tablero->piezas_actuales;
  return (piezas_actuales/max_piezas); //Es la carga
}
