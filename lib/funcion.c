#include "funcion.h"
#include "math.h"
#include <stdio.h>
// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

#define hipotenusa(x,y) (sqrt(pow(x,2)+pow(y,2)))
#define hipotenusa_tres(x,y,z) (sqrt(pow(x,2)+pow(y,2)+por(z,2)))

double carga(TABLERO *tablero)
{
  double max_piezas = tablero->ancho*tablero->alto;
  double piezas_actuales = tablero->piezas_actuales;
  return (piezas_actuales/max_piezas); //Es la carga
}

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

double probabilidad_tetris(TABLERO *tablero, int j)
{
  double ancho = tablero->alto;
  int i;
  double proba = 0;
  for(i = 0; i < tablero->ancho; i++) {
    if(atrapado(tablero,i,j))
      return probabilidad_tetris(tablero,++j);
    if(tablero->piezas[i][j] != NULL) 
      proba++;
  }
  if(proba == 0)
    return 0;
  return proba;
}


double funcion_costo(TABLERO *tablero)
{
  double atrapados = cuenta_atrapados(tablero);
  double fun = (tablero->ancho*tablero->alto)-atrapados+(10*tablero->num_tetris)+probabilidad_tetris(tablero,0);
  //printf("atrapados=%f\n",fun);
  return fun;
}

/*double carga_niveles(TABLERO *tablero)
{
  double ancho = tablero->alto;
  int i;
  double ocupados = 0;
  for(i = 0; i < tablero->ancho; i++) {
    if(tablero->piezas[i][0] != NULL) 
      ocupados++;
  }
  if(ocupados == 0)
    return 0;
  return ocupados;
}

double funcion_costo(TABLERO *tablero)
{
  printf("Carga=%f\n",carga_niveles(tablero));
  return carga_niveles(tablero);
  }


double funcion_costo(TABLERO *tablero)
{
  double cateto_adyacente = carga(tablero);
  double hipotenusa = sqrt(pow(cateto_adyacente,2) +
			   pow(tablero->num_piezas_totales,2));
  double grados = cateto_adyacente/hipotenusa;
  double radiales = degreesToRadians(grados);
  double arcoseno = acos(radiales);
  printf("π/2-F=%f\n",M_PI/2-fabs(arcoseno));
  return M_PI/2-fabs(arcoseno);//+tablero->num_piezas_totales;
  }
*/
