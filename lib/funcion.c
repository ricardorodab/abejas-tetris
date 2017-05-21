#include "funcion.h"
#include "math.h"

// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)



double funcion_costo(TABLERO *tablero)
{
  double max_piezas = tablero->ancho*tablero->alto;
  double piezas_actuales = tablero->piezas_actuales;
  double cateto_adyacente = piezas_actuales/max_piezas; //Es la carga
  double hipotenusa = sqrt(pow(cateto_adyacente,2) +
			   pow(tablero->num_piezas_totales,2));
  
  double grados = cateto_adyacente/hipotenusa;
  double radiales = degreesToRadians(grados);
  double arcoseno = acos(radiales);
  return fabs(arcoseno);
}
