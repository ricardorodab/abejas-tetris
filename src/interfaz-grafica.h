#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

TABLERO *tablero_principal;
double ancho;
double alto;
//Valor entre 
double zoom;

void myInit(char *progname);
void print(double x, double y,double z, char *string);
void myReshape (int width, int height);
void myDisplay(void);
void myKeyboard (unsigned char key, int x, int y);
void visual_main(int argc, char** argv, TABLERO *tablero, double zoom_p);
#endif
