/* ------------------------------------------------------------------
 * tetromino.c
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

#include "tetromino.h"
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

/**
 * @file tetromino.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the openGL GUI for a final project for the
 * "Combinatorial Optimization Heuristics" class.
 *
 * Este archivo implementa las funciones que necesitan para observar
 * las fichas del juego de tetris que la heuristica de abejas juega.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/abejas-tetris
 *
 */

/**
 * Para cada caso de las figura (grados, posicion de cada bloque,
 * existencia de este mismo y si se encuentra activo o no) se 
 * pinta una posicion (x,y) en el mapa.
 *
 */
void dibuja_cuadrado(PIEZA *pieza, int dif_x, int dif_y)
{
  glColor3f(1.0f,0.0f,1.0f);
  if(pieza->activo_centro)
    glRectf(pieza->x-(dif_x),
	    pieza->y-(dif_y),
	    pieza->x-(dif_x)+1,
	    pieza->y-(dif_y)+1);
  if(pieza->bloques[0]->activo)
    glRectf(pieza->bloques[0]->x-(dif_x),
	    pieza->bloques[0]->y-(dif_y),
	    pieza->bloques[0]->x-(dif_x)+1,
	    pieza->bloques[0]->y-(dif_y)+1);
  if(pieza->bloques[1]->activo)
    glRectf(pieza->bloques[1]->x-(dif_x),
	    pieza->bloques[1]->y-(dif_y),
	    pieza->bloques[1]->x-(dif_x)+1,
	    pieza->bloques[1]->y-(dif_y)+1);
  if(pieza->bloques[2]->activo)
    glRectf(pieza->bloques[2]->x-(dif_x),
	    pieza->bloques[2]->y-(dif_y),
	    pieza->bloques[2]->x-(dif_x)+1,
	    pieza->bloques[2]->y-(dif_y)+1);
  glColor3f(1.0f,1.0f,1.0f);
}

/**
 * Para cada caso de las figura (grados, posicion de cada bloque,
 * existencia de este mismo y si se encuentra activo o no) se 
 * pinta una posicion (x,y) en el mapa.
 *
 */
void dibuja_left_gun(PIEZA *pieza, int dif_x, int dif_y)
{
  glColor3f(0.5f,0.0f,0.5f);
  if(pieza->activo_centro)
    glRectf(pieza->x-(dif_x),
	    pieza->y-(dif_y),
	    pieza->x-(dif_x)+1,
	    pieza->y-(dif_y)+1);
  if(pieza->orientacion == 0){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else if(pieza->orientacion == 90){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else if(pieza->orientacion == 180){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else{
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }
  glColor3f(1.0f,1.0f,1.0f);
}

/**
 * Para cada caso de las figura (grados, posicion de cada bloque,
 * existencia de este mismo y si se encuentra activo o no) se 
 * pinta una posicion (x,y) en el mapa.
 *
 */
void dibuja_right_gun(PIEZA *pieza, int dif_x, int dif_y)
{
  glColor3f(0.0f,0.5f,0.5f);
  if(pieza->activo_centro)
    glRectf(pieza->x-(dif_x),
	    pieza->y-(dif_y),
	    pieza->x-(dif_x)+1,
	    pieza->y-(dif_y)+1);
  if(pieza->orientacion == 0){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else if(pieza->orientacion == 90){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else if(pieza->orientacion == 180){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else{
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }
  glColor3f(1.0f,1.0f,1.0f);
}

/**
 * Para cada caso de las figura (grados, posicion de cada bloque,
 * existencia de este mismo y si se encuentra activo o no) se 
 * pinta una posicion (x,y) en el mapa.
 *
 */
void dibuja_left_snake(PIEZA *pieza, int dif_x, int dif_y)
{
  glColor3f(0.6f,0.4f,0.3f);
  if(pieza->activo_centro)
    glRectf(pieza->x-(dif_x)
	    ,pieza->y-(dif_y)
	    ,pieza->x-(dif_x)+1
	    ,pieza->y-(dif_y)+1);  
  if(pieza->orientacion == 0 || pieza->orientacion == 180){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else{
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }
  glColor3f(1.0f,1.0f,1.0f);
}

/**
 * Para cada caso de las figura (grados, posicion de cada bloque,
 * existencia de este mismo y si se encuentra activo o no) se 
 * pinta una posicion (x,y) en el mapa.
 *
 */
void dibuja_right_snake(PIEZA *pieza, int dif_x, int dif_y)
{
  glColor3f(0.0f,0.9f,0.0f);
  if(pieza->activo_centro)
    glRectf(pieza->x-(dif_x),
	    pieza->y-(dif_y),
	    pieza->x-(dif_x)+1,
	    pieza->y-(dif_y)+1);
  if(pieza->orientacion == 0 || pieza->orientacion == 180){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else{
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }
  glColor3f(1.0f,1.0f,1.0f);
}

/**
 * Para cada caso de las figura (grados, posicion de cada bloque,
 * existencia de este mismo y si se encuentra activo o no) se 
 * pinta una posicion (x,y) en el mapa.
 *
 */
void dibuja_i(PIEZA *pieza, int dif_x, int dif_y)
{
  glColor3f(0.0f,0.0f,1.0f);
  if(pieza->activo_centro)
    glRectf(pieza->x-(dif_x),
	    pieza->y-(dif_y),
	    pieza->x-(dif_x)+1,
	    pieza->y-(dif_y)+1);
  if(pieza->orientacion == 0 || pieza->orientacion == 180){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else{
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }
  glColor3f(1.0f,1.0f,1.0f);
}

/**
 * Para cada caso de las figura (grados, posicion de cada bloque,
 * existencia de este mismo y si se encuentra activo o no) se 
 * pinta una posicion (x,y) en el mapa.
 *
 */
void dibuja_t(PIEZA *pieza, int dif_x, int dif_y)
{
  glColor3f(1.0f,0.0f,0.0f);
  if(pieza->activo_centro)
    glRectf(pieza->x-(dif_x),
	    pieza->y-(dif_y),
	    pieza->x-(dif_x)+1,
	    pieza->y-(dif_y)+1);
  if(pieza->orientacion == 0){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else if(pieza->orientacion == 90){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else if(pieza->orientacion == 180){
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }else{
    if(pieza->bloques[0]->activo)
      glRectf(pieza->bloques[0]->x-(dif_x),
	      pieza->bloques[0]->y-(dif_y),
	      pieza->bloques[0]->x-(dif_x)+1,
	      pieza->bloques[0]->y-(dif_y)+1);
    if(pieza->bloques[1]->activo)
      glRectf(pieza->bloques[1]->x-(dif_x),
	      pieza->bloques[1]->y-(dif_y),
	      pieza->bloques[1]->x-(dif_x)+1,
	      pieza->bloques[1]->y-(dif_y)+1);
    if(pieza->bloques[2]->activo)
      glRectf(pieza->bloques[2]->x-(dif_x),
	      pieza->bloques[2]->y-(dif_y),
	      pieza->bloques[2]->x-(dif_x)+1,
	      pieza->bloques[2]->y-(dif_y)+1);
  }
  glColor3f(1.0f,1.0f,1.0f);
} //Fin de tetromino.c
