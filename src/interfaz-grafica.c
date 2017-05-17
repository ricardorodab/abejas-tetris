#include <stdio.h>
#include <GL/glew.h>
#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif
#include <OpenGL/gl3.h>
#define __gl_h_
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tablero.h"
#include "interfaz-grafica.h"
#include "tetromino.h"

/* Función para las configuraciones iniciales. */
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

/* Codigo de para imprimir texto: https://www.opengl.org/discussion_boards/showthread.php/169189-Printing-Text */
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


void dibuja_cuadro(double w, double h)
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
  /*for(float x = w*-1; x < glutGet(GLUT_WINDOW_WIDTH); x += 0.5 )
    {glVertex3f(x, -1*h, 0.0f);
    glVertex3f(x, (float)(glutGet(GLUT_WINDOW_WIDTH)), 0.0f);
    }for( float y = h*-1; y < glutGet(GLUT_WINDOW_HEIGHT); y += 0.5 )
    {glVertex3f(-1*w, y, 0.0f);
    glVertex3f((float)(glutGet(GLUT_WINDOW_HEIGHT)), y, 0.0f);}*/ 
  glEnd();
}

void dibuja_pieza(PIEZA *pieza){
  switch(pieza->tipo){
  case Sq:
    dibuja_cuadrado(pieza);
    break;
  case LG:
    dibuja_left_gun(pieza);
    break;
  case RG:
    dibuja_right_gun(pieza);
    break;
  case LS:
    dibuja_left_snake(pieza);
    break;
  case RS:
    dibuja_right_snake(pieza);
    break;
  case I:
    dibuja_i(pieza);
    break;
  case T:
    dibuja_t(pieza);
    break;
  default:
    break;
  }
}

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
  //glutPostRedisplay();
}

/* Función para poder volver a dibujar con algún cambio. */
void reshape (int width, int height)
{
  //glutReshapeWindow(ancho,alto);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)width/(double)height, 1, 1000.0);
  glViewport(0, 0, width, height);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  int size = tablero_principal->max_size;
  double por = zoom*log2(size); 
  gluLookAt(0.0f, 0.0f, (float)por, 0.0f, 0.0f,0.0f,0.0f, 5.f, 0.5f);
  dibuja_cuadro(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
  dibuja_figuras();
  glutSwapBuffers();
  glutPostRedisplay ();
}

void myKeyboard (unsigned char key, int x, int y)
{
  switch (key) {
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}
void specialKeyInput(int key, int x, int y)
{
   if (key == GLUT_KEY_RIGHT)
     {
     }
   if (key == GLUT_KEY_LEFT)
     {
     }
   if (key == GLUT_KEY_UP)
     {
     }
   if (key == GLUT_KEY_DOWN)
     {
       glutPostRedisplay ();
     }
}


void visual_main(int argc, char** argv, TABLERO *tablero, double zoom_p)
{  
  tablero_principal = tablero;
  zoom = zoom_p;
  glutInit(&argc, argv); 
  myInit("Tetris & Abejas");
  glutKeyboardFunc(myKeyboard);
  glutSpecialFunc(specialKeyInput);
  //glutSpecialFunc(specialKeyInput);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMainLoop();






  
}
