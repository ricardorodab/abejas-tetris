/* ------------------------------------------------------------------
 * interfaz-grafica.h
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
#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

#include <stdio.h>
#include <GL/glew.h>
#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif
#define __gl_h_
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "lock.h"
#include "tablero.h"
#include "tetromino.h" 

/**
 * @file interfaz-grafica.h
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the openGL GUI for a final project for the
 * "Combinatorial Optimization Heuristics" class.
 *
 * Este archivo define las funciones que necesitamos para observar
 * las el juego de tetris que la heuristica de abejas juegs.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/abejas-tetris
 *
 */

/**
 * @var TABLERO *tablero_principal
 * @brief Tablero principal.
 *
 * Contiene la informacion principal del tablero que debemos ver.
 *
 */
TABLERO *tablero_principal;

/**
 * @var TABLERO **tablero_principal_pointer 
 * @brief El apuntador al @tablero_principal.
 *
 * Como la informacion del tablero cambia, necesitamos
 * una variable para conocer la ubicacion del nuevo tablero.
 *
 */
TABLERO **tablero_principal_pointer;

/**
 * @var double ancho
 * @brief Ancho.
 *
 * Es el ancho que nuestra cuadricula de OpenGL tendra.
 *
 */
double ancho;

/**
 * @var double alto
 * @brief Alto.
 *
 * Es la altura que nuestra cuadricula de OpenGL tendra.
 *
 */
double alto;

/**
 * @var double zoom
 * @brief Zoom.
 *
 * Es el tamanio con el que cada cuadro de la cuadricula tendra.
 *
 */
double zoom;

/**
 * @var bool game_over
 * @brief Estatus del juego.
 *
 * Es el estado actual del algoritmo y tablero.
 *
 */
bool game_over;

/**
 * @brief Inicializa la interfaz grafica. 
 *
 * Inicia los valores que debe tener un GUI en OpenGL y glut.
 * @param progname - Es el nombre del programa a ejecutar.
 *
 */
void myInit(char *progname);

/**
 * @brief Pinta texto cuando sea necesario.
 *
 * Dado coordenadas, pintar el texto en el espacio.
 * @param x - Es la coordenada x del espacio de OpenGL.
 * @param y - Es la coordenada y del espacio de OpenGL.
 * @param z - Es la coordenada z del espacio de OpenGL.
 * @param string - Es la cadena que queremos mostrar.
 *
 */
void print(double x, double y,double z, char *string);

/**
 * @brief Vuelve a pintar el espacio visual.
 *
 * Cada que se ejecute una actualizacion del espacio se debe llamar.
 * @param width - Es el ancho del espacio visual.
 * @param height - Es el largo del espacio visual.
 *
 */
void myReshape (int width, int height);

/**
 * @brief Dibuja el espacio de busqueda
 *
 * Dibuja y muestra la interfaz grafica.
 *
 */
void myDisplay(void);

/**
 * @brief Le da comportamiento a la entrada.
 *
 * Cada que se presiona una tecla ocurre un evento.
 * @param key - Es la tecla que es presionada.
 * @param x - Es la tecla x que corresponde a la posicion del evento.
 * @param y - Es la tecla y que corresponde a la posicion del evento.
 *
 */
void myKeyboard (unsigned char key, int x, int y);

/**
 * @brief Termina la ventana.
 *
 * Metodo para terminar la ejecucion del programa visual.
 * 
 */
void end_visual_main(void);

/**
 * @brief Metodo visual principal.
 *
 * Este metodo se encarga de decirle al thread visual que debe hacer.
 * @param argc - Es el numero de parametros que el usuario paso.
 * @param argv - Son los parametros del usuario.
 * @param tablero - Es el apuntador a la ubicacion del tablero.
 * @param zoom_p - Es el zoom que el usuario desea ver su tablero.
 *
 */
void visual_main(int argc, char** argv, TABLERO **tablero, double zoom_p);
#endif //Fin de interfaz-grafica.h
