/* ------------------------------------------------------------------
 * interfaz-grafica.c
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
#include "tablero.h"
#include "interfaz-grafica.h"
#include "tetromino.h"

/**
 * @file interfaz-grafica.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the body for openGL GUI functions
 * for a final project for the
 * "Combinatorial Optimization Heuristics" class.
 *
 * Este archivo implementa las funciones que necesitamos para observar
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
 *
 * Inicializa el modo de diplay mientras que le da tamanio a la
 * ventana y su posicion en la pantalla. 
 *
 */
void myInit(char *progname)
{
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(900, 600);
  ancho = 900;
  alto = 600;
  glutInitWindowPosition(100, 100);
  glutCreateWindow(progname);
  glClearColor(0.0, 0.0, 0.2, 0.0);
}

/**
 * Codigo de para imprimir texto: 
 * @see https://www.opengl.org/discussion_boards/showthread.php/169189-Printing-Text
 * 
 */
void print(double x, double y,double z, char *string)
{
  //set the position of the text in the window using the x and y coordinates                                                                                   
  glRasterPos3f(x-.7,y+2.5,z);
  //get the length of the string to display                                                                                                                    
  int len = (int)strlen(string);
  //loop to display character by character                                                                                                                     
  for (int i = 0; i < len; i++)
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
    }
}

/**
 *
 * Esta funcion horrible dibuja la cuadricula como Turing nos
 * da a entender.
 *
 */
void dibuja_cuadro(double h, double w)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_LINES);
  glColor3f(1.0f,1.0f,1.0f); // White (RGB)
  for(float x = -1*(tablero_principal->ancho/2); x <= (tablero_principal->ancho/2); x += 1 )
    {      
      glVertex3f(x, -1*(tablero_principal->alto/2), 0.0f);
      glVertex3f(x, (float)(tablero_principal->alto/2), 0.0f);
    }
  for( float y = -1*(tablero_principal->alto/2); y <= (tablero_principal->alto/2); y += 1 )
    {
      glVertex3f(-1*(tablero_principal->ancho/2), y, 0.0f);
      glVertex3f((float)(tablero_principal->ancho/2), y, 0.0f);
    }
  glEnd();
}

/**
 * @brief Funcion que dibuja cada pieza de tetris.
 * 
 * Depediendo del tipo de cada pieza de tetris dibuja cada pieza
 * con sus coordenadas en el tablero actual global.
 * @param pieza - Es la pieza actual que se desea dibujar.
 *
 */
void dibuja_pieza(PIEZA *pieza){
  switch(pieza->tipo){
  case Sq:
    dibuja_cuadrado(pieza,
		    tablero_principal->ancho/2,
		    tablero_principal->alto/2);
    break;
  case LG:
    dibuja_left_gun(pieza,
		    tablero_principal->ancho/2,
		    tablero_principal->alto/2);
    break;
  case RG:
    dibuja_right_gun(pieza,
		     tablero_principal->ancho/2,
		     tablero_principal->alto/2);
    break;
  case LS:
    dibuja_left_snake(pieza,
		      tablero_principal->ancho/2,
		      tablero_principal->alto/2);
    break;
  case RS:
    dibuja_right_snake(pieza,
		       tablero_principal->ancho/2,
		       tablero_principal->alto/2);
    break;
  case I:
    dibuja_i(pieza,
	     tablero_principal->ancho/2,
	     tablero_principal->alto/2);
    break;
  case T:
    dibuja_t(pieza,
	     tablero_principal->ancho/2,
	     tablero_principal->alto/2);
    break;
  default:
    break;
  }
}

/**
 * @brief Funcion que dibuja todas las piezas de tetris.
 * 
 * Dado el tablero actual global, dibujara todas las piezas
 * que el tablero posee.
 *
 */
void dibuja_figuras(void)
{
  int i, j;
  for(i = 0; i < tablero_principal->ancho; i++){
    for(j = 0; j < tablero_principal->alto; j++){
      if(tablero_principal->piezas[i][j] != NULL){
	dibuja_pieza(tablero_principal->piezas[i][j]);
      }
    }
  }
}

/**
 * Solo debe cambiar la perspectiva dependiendo del tamanio.
 */
void reshape (int width, int height)
{
  //glutReshapeWindow(ancho,alto);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)width/(double)height, 1, 1000.0);
  glViewport(0, 0, width, height);
}

/**
 * Limpiamos el buffer y cargamos la matriz identidad.
 * Modificamos el zoom de la vista de la cuadricula.
 * Dibujamos las figuras y cambiamos los buffers antes de repintar.
 *
 */
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  int size = tablero_principal->max_size;
  double por = zoom*log2(size); 
  gluLookAt(0.0f, 0.0f, (float)por, 0.0f, 0.0f,0.0f,0.0f, 5.f, 0.5f);
  tablero_principal = *tablero_principal_pointer;
  dibuja_cuadro(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
  dibuja_figuras();
  glutSwapBuffers();
  if(!game_over)
    glutPostRedisplay();
}

/**
 * @brief Dejamos caer a la pieza
 *
 * Para acelerar el juego dejamos caer la pieza donde queramos.
 *
 */
void deja_caer(void)
{
  bool valor = true;
  while(valor)
     valor = mover_pieza_tablero(tablero_principal,tablero_principal->actual);
}

/**
 * Revisamos los casos Exit - salimos.
 * Espacio - Dejar caer la pieza.
 *
 */
void myKeyboard (unsigned char key, int x, int y)
{  
  switch (key) {
  case 27:
    exit(0);
    break;
  case 32:    
    deja_caer();
    break;
  default:    
    break;
  }
}

/**
 * @brief Le da comportamiento a la entrada (flechas).
 *
 * Cada que se presiona una flecha ocurre un evento.
 * @param key - Es la flecha que es presionada.
 * @param x - Es la tecla x que corresponde a la posicion del evento.
 * @param y - Es la tecla y que corresponde a la posicion del evento.
 *
 */
void specialKeyInput(int key, int x, int y)
{
   if (key == GLUT_KEY_RIGHT)
     {
       mover_derecha_tablero(tablero_principal,
			     tablero_principal->actual);
     }
   if (key == GLUT_KEY_LEFT)
     {
       mover_izquierda_tablero(tablero_principal,
			     tablero_principal->actual);
     }
   if (key == GLUT_KEY_UP)
     {
       rotar_pieza_tablero(tablero_principal,tablero_principal->actual);
     }
   if (key == GLUT_KEY_DOWN)
     {
       rotar_pieza_tablero(tablero_principal,tablero_principal->actual);
     }
}

/**
 * Modifica la variable de @game_over.
 */
void end_visual_main(void)
{
  game_over = true;
}

/**
 * Instanciamos a las variablesp principales como
 * @game_over o @tablero_principal para despues entrar en un ciclo
 * potencialmente infinito para seguir dibujando el tablero.
 *
 */
void visual_main(int argc, char** argv, TABLERO **tablero, double zoom_p)
{
  game_over = false;
  tablero_principal_pointer = tablero;
  tablero_principal = *tablero;
  zoom = zoom_p;
  glutInit(&argc, argv); 
  myInit("Tetris & Abejas");
  glutKeyboardFunc(myKeyboard);
  glutSpecialFunc(specialKeyInput);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMainLoop();
} //Fin de interfaz-grafica.c
