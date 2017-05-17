#include "tetromino.h"
#include <GL/glew.h>
#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif
#include <OpenGL/gl3.h>
#define __gl_h_
#include <GL/freeglut.h>
#include <GL/glut.h>


void dibuja_cuadrado(PIEZA *pieza)
{
glColor3f(1.0f,0.0f,1.0f);
glRectf(pieza->x,pieza->y,pieza->x+1,pieza->y+1);
glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+2);
glRectf(pieza->x,pieza->y+1,pieza->x+2,pieza->y+2);
glRectf(pieza->x+1,pieza->y+1,pieza->x+2,pieza->y+2);
glColor3f(1.0f,1.0f,1.0f);
}
#include <stdio.h>
void dibuja_left_gun(PIEZA *pieza)
{
glColor3f(1.0f,0.2f,0.5f);
glRectf(pieza->x,pieza->y,pieza->x+1,pieza->y+1);
printf("%d\n",pieza->orientacion);
if(pieza->orientacion == 0){
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x,pieza->y-1,pieza->x+1,pieza->y);
glRectf(pieza->x-1,pieza->y-1,pieza->x,pieza->y);
}else if(pieza->orientacion == 90){
glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+1);
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
glRectf(pieza->x-1,pieza->y+1,pieza->x,pieza->y+2);
}else if(pieza->orientacion == 180){
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x,pieza->y-1,pieza->x+1,pieza->y);
glRectf(pieza->x+1,pieza->y+1,pieza->x+2,pieza->y+2);
}else{
glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+1);
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
glRectf(pieza->x+1,pieza->y-1,pieza->x+2,pieza->y);
}
glColor3f(1.0f,1.0f,1.0f);
}

void dibuja_right_gun(PIEZA *pieza)
{
glColor3f(1.0f,0.2f,0.5f);
glRectf(pieza->x,pieza->y,pieza->x+1,pieza->y+1);
printf("%d\n",pieza->orientacion);
if(pieza->orientacion == 0){
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x,pieza->y-1,pieza->x+1,pieza->y);
glRectf(pieza->x+1,pieza->y-1,pieza->x+2,pieza->y);
}else if(pieza->orientacion == 90){
glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+1);
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
glRectf(pieza->x-1,pieza->y-1,pieza->x,pieza->y);
}else if(pieza->orientacion == 180){
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x,pieza->y-1,pieza->x+1,pieza->y);
glRectf(pieza->x-1,pieza->y+1,pieza->x,pieza->y+2);
}else{
glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+1);
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
glRectf(pieza->x+1,pieza->y+1,pieza->x+2,pieza->y+2);
}
glColor3f(1.0f,1.0f,1.0f);
}

void dibuja_left_snake(PIEZA *pieza)
{
glColor3f(1.0f,0.2f,0.5f);
glRectf(pieza->x,pieza->y,pieza->x+1,pieza->y+1);
if(pieza->orientacion == 0 || pieza->orientacion == 180){
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
glRectf(pieza->x-1,pieza->y-1,pieza->x,pieza->y);
}else{
glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+1);
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x-1,pieza->y+1,pieza->x,pieza->y+2);
}
glColor3f(1.0f,1.0f,1.0f);
}

void dibuja_right_snake(PIEZA *pieza)
{
glColor3f(1.0f,0.2f,0.5f);
glRectf(pieza->x,pieza->y,pieza->x+1,pieza->y+1);
if(pieza->orientacion == 0 || pieza->orientacion == 180){
glRectf(pieza->x,pieza->y-1,pieza->x+1,pieza->y);
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
glRectf(pieza->x-1,pieza->y+1,pieza->x,pieza->y+2);
}else{
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x+1,pieza->y+1,pieza->x+2,pieza->y+2);
}
glColor3f(1.0f,1.0f,1.0f);
}

void dibuja_i(PIEZA *pieza)
{
glColor3f(1.0f,0.2f,0.5f);
glRectf(pieza->x,pieza->y,pieza->x+1,pieza->y+1);
if(pieza->orientacion == 0 || pieza->orientacion == 180){
  glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
  glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+1);
  glRectf(pieza->x+2,pieza->y,pieza->x+3,pieza->y+1);
 }else{
glRectf(pieza->x,pieza->y-1,pieza->x+1,pieza->y);
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x,pieza->y+2,pieza->x+1,pieza->y+3);
}
glColor3f(1.0f,1.0f,1.0f);
}

void dibuja_t(PIEZA *pieza)
{
glColor3f(1.0f,0.2f,0.5f);
glRectf(pieza->x,pieza->y,pieza->x+1,pieza->y+1);
if(pieza->orientacion == 0){
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+1);
glRectf(pieza->x,pieza->y-1,pieza->x+1,pieza->y);
}else if(pieza->orientacion == 90){
glRectf(pieza->x,pieza->y-1,pieza->x+1,pieza->y);
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
}else if(pieza->orientacion == 180){
glRectf(pieza->x-1,pieza->y,pieza->x,pieza->y+1);
glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+1);
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
}else{
glRectf(pieza->x,pieza->y-1,pieza->x+1,pieza->y);
glRectf(pieza->x,pieza->y+1,pieza->x+1,pieza->y+2);
glRectf(pieza->x+1,pieza->y,pieza->x+2,pieza->y+1);
}
glColor3f(1.0f,1.0f,1.0f);
}

