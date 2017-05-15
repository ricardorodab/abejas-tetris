/* -------------------------------------------------------------------
 * main.c
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
 * -------------------------------------------------------------------
 */

/**
 * @file main.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 14 May 2017
 * @brief File containing the final project for the
 * "Combinatorial Optimization Heuristics" class.
 *
 * Este programa utiliza una heuristica conocida por "Abejas"
 * sobre el famoso problema tetris. Donde buscamos la manera de
 * acomodar fichas de tetris dado un tablero.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/AceptacionUmbral
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>
#include <time.h> 
//include "conexion.h"


/**
 * @brief Linea del codigo actual.
 *
 * Re-definimos la constante de linea que viene por default en C.
 *
 */
#define LINEA __LINE__
#define QUERY1 "SELECT * FROM cities"
#define QUERY2 "SELECT * FROM connections"

/**
 * @brief Variable de marcardo de error.
 *
 * Si en algun momento de la ejecucion esta variable es != 0 terminamos. 
 *
 */
int ERROR = 0;

/**
 * @brief Una funcion simple para imprimir que hubo un error y en que linea.
 *
 * Si llega a ocurrir se debe anexar un mensaje de error que el usuario
 * pueda ver para facilitar la facil busqueda de este.
 *
 * @param msg -Es la cadena que se le mostrara al usuario.
 * @param linea -Es la linea del codigo donde ocurrio este error. 
 * @see ERROR
 * @note Esta funcion termina la ejecucion del programa.
 * @waring
 *
 */
void main_imprime_error(char *msg,int linea)
{
  char *err = "-Linea:";
  printf("%s%s%d\n",msg,err,linea);
  exit(1);
}


/**
 * @brief Buscador de un numero del archivo donde viene las semillas.
 *
 * Como nuestro programa funciona con alta probabilidad y queremos que
 * los resultados sean repetibles, usamos un semillero para reproducir
 * el procedimiento de experimentacion.
 * @param ubicacion_semilla -Es el nombre del archivo donde viene la semilla.
 * @param num_semilla -Es la posicion de nuestra semilla en el archivo.
 * @return La semilla final que se usara.
 *
 */
int get_semilla(char *ubicacion_semilla,int num_semilla)
{
  int temp_seed = 1;
  FILE *file;
  int int_file;
  char char_file[1];
  GList *l;
  char numero[128];
  if(num_semilla < 0)
    return temp_seed;
  file = fopen(ubicacion_semilla,"r+");
    //Revisamos si el archivo abrio bien.
  if(file == NULL){
    main_imprime_error("El archivo no existe o existe un problema al abrirlo.\n",__LINE__);
  }
  int_file = 0;
  while(num_semilla && ((int_file = fscanf(file,"%c",char_file)) != -1))
    {
      if(char_file[0] == ',')
	num_semilla--;
    }  
  if(int_file == -1)
    return temp_seed;
  int i = 0;
  while((int_file=fscanf(file,"%c",char_file) != -1) && char_file[0] != ',')
    {
      if(!isdigit(char_file[0]))
	break;
      numero[i++] = char_file[0];
    }
  numero[i] = '\0';
  temp_seed = atoi(numero);
  fclose(file);
  return temp_seed;
}

/**
 * @brief Manejador y parseador del archivo donde viene la muestra.
 *
 * Al requerir una muestra con la que trabajar, nuestro programa 
 * necesita almacenar esta muestra en un archivo para facilitar las
 * pruebas y experimentacion del programa.
 * @param ubicacion_muestra -Es el nombre del archivo donde viene la muestra.
 * @param muestra_size -Es el tamanio que debe contener nuestra muestra.
 * @return Un arreglo GArray con los indices de nuestras muestras.
 *
 */
GArray* lee_muestra(char *ubicacion_muestra,int *muestra_size)
{
  GArray *muestra;
  //Esto esta feo pero es rapido y facilita el parseo:
  GList *entrada = NULL;
  int linea;
  char char_file[1];
  char numero[80];
  FILE *file;
  int int_file;
  file = fopen(ubicacion_muestra,"r+");
  //Revisamos si el archivo abrio bien.
  if(file == NULL){
    main_imprime_error("El archivo no existe o existe un problema al abrirlo.\n",__LINE__);
  }
  while((int_file = fscanf(file,"%c",char_file)) != -1)
    {
      //Caso especial: Un comentario empezando por '#'
      if(char_file[0] == '#'){
	int comment_int = 0;       
	while(((comment_int = fscanf(file,"%c",char_file)) != -1)
	      && char_file[0] != '\n'){}
	if(comment_int == -1)
	  break;
      }
      char *index = malloc(sizeof(char));
      *index = char_file[0];
      entrada = g_list_append(entrada,index);
    }
  linea = 0;
  int i = 0;
  int cant_num = 0;
  //Inicializamos nuestro arreglo de muestras de tamanio *muestra_size
  muestra = g_array_sized_new (FALSE, FALSE, sizeof(gint),*muestra_size);
  GList *l;
  for(l = entrada; l != NULL; l = l->next)
    {
      char *data = (l->data);
      //Caso linea 0 -> numero de muestras:
      if(linea == 0){
	if(*data == '\n'){
	  linea++;
	  numero[i] = '\0';
	  *muestra_size = atoi(numero);
	  i = 0;
	}else if(isdigit(*data)){
	  numero[i] = *data;
	  i++;
	}	
      }else{
	if(*data == ','){
	  numero[i] = '\0';
	  int *val = malloc(sizeof(int));
	  *val = atoi(numero);
	  g_array_append_val(muestra,*val);
	  cant_num++;
	  i = 0;
	}else if(l->next == NULL){
	  numero[i] = *data;
	  numero[i+1] = '\0';	  
	  int *val = malloc(sizeof(int));
	  *val = atoi(numero);
	  g_array_append_val(muestra,*val);
	  cant_num++;
	  i = 0;
	}else if(isdigit(*data)){
	  numero[i] = *data;
	  i++;
	}
      }
    }
  if(cant_num != *muestra_size)
    main_imprime_error("No coincide el numero de muestras con estas!",
		       __LINE__);
  fclose(file);
  return muestra;
}

/**
 * @brief Metodo principal del programa.
 *
 * Tratamos de encontrar soluciones factibles al problema del viajero.
 * @param argc - Es el numero de parametros. En este caso se espera argc > 2.
 * @param argv - Son los parametros que nos daran la base de datos y banderas.
 * @return Un entero 0 si todo sale bien 1 en caso contrario.
 *
 */
int main(int argc, char** argv)
{
  //Definimos las variables que usaremos en el programa:
  GArray *muestra;
  int muestra_size;
  //A leer de externo ./etc/config.cfg:
  char *UBICACION_MUESTRA;
  char *UBICACION_SEMILLA;
  int SEMILLA;
  
  //Inicializamos una variable para medir el tiempo de ejecucion:
  clock_t tic = clock();
  //Leemos el archivo de configuracion:
  GKeyFile *keyfile;
  GKeyFileFlags flags;
  GError *error = NULL;
  keyfile = g_key_file_new ();
  flags = G_KEY_FILE_NONE;
  if (!g_key_file_load_from_file (keyfile,
				  "./etc/config.cfg",
				  flags, &error))
    {
      printf("Error al cargar archivo de configuracion. LINEA= %d",__LINE__);
      return 1;
    }
  
  //Ahora asignamos a cada una de las variables sus valores del .cfg:
  // 1. Las semillas, numero elegida y la ubicacion del semillero:
  SEMILLA             = g_key_file_get_integer(keyfile,"SEMILLA",
					       "SEMILLA",NULL);
  UBICACION_SEMILLA = g_key_file_get_string(keyfile,"SEMILLA",
					    "UBICACION",NULL);
  // 4. Por ultimo el nombre donde esta la muestra:
  UBICACION_MUESTRA = g_key_file_get_string(keyfile,"MUESTRA",
					    "UBICACION",NULL);
  //Lo primero que hacemos es inicializamos el generador de num aleatorios:
  int seed = get_semilla(UBICACION_SEMILLA,SEMILLA);
  //Inicializamos la semilla "aleatoria".
  //srand(seed);

  // AQUI TENEMOS QUE INICIALIZAR Y LEER LA MUESTRA;
  muestra = lee_muestra(UBICACION_MUESTRA,&muestra_size);
  // Creamos la ruta y aleatorizamos a la ruta.
  

  
  //Contamos el tiempo:
  clock_t toc = clock();
  double segundos = (double)(toc - tic) / CLOCKS_PER_SEC;
  printf("Transcurrieron: %f segundos o %f minutos.\n",segundos,segundos/60);
  return 0; 
} //Fin de main.c

