/* -----------------------------------------------------------------
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
 * -----------------------------------------------------------------
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
 * @see https://github.com/ricardorodab/abejas-tetris
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "tablero.h"
#include "funcion.h"
#include "abc.h"
#include "interfaz-grafica.h"
#include "lock.h"


/**
 * @def LINEA
 *
 * Re-definimos la constante de linea que viene por default en C.
 *
 */
#define LINEA __LINE__

/**
 * @var int size_x
 * @brief Anchura.
 *
 * Variable global para marcar el tamanio de la anchura
 * del pg.
 *
 */
int size_x;
/**
 * @var int size_y
 * @brief Altura.
 *
 * Variable global para marcar el tamanio de la altura
 * del pg.
 *
 */
int size_y;

/**
 * @var int ERROR
 * @brief Variable de marcardo de error.
 *
 * Si en algun momento de la ejecucion esta variable es != 0
 * terminamos. 
 *
 */
int ERROR = 0;

/**
 * @var char *UBICACION_SEMILLAS
 * @brief ES la ubicacion en el directorio donde se encuentra nuestro semillero.
 *
 * Con esta direccion buscamos las mejores opciones que existan 
 * el desarollo de un juego de tetris.
 *
 */ 
char *UBICACION_SEMILLA;

/**
 * @var int SEMILLA
 * @brief Es la semilla que el usuario desea usar.
 * 
 * Esto es para inicializar la funcion srand que le dice
 * cual es el origen de la funcion pseudoaleatorio.
 *
 */
int SEMILLA;

/**
 * @var int SEMILLA_ITERA
 * @brief Es el numero de busquedas de semillas.
 *
 * Si deseamos buscar una buena semilla definimos la cota
 * de iteraciones que deseamos hacer.
 *
 */
int SEMILLA_ITERA;

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
 * @waring Termina el programa.
 *
 */
void main_imprime_error(char *msg,int linea)
{
  char *err = "-Linea:";
  printf("%s%s%d\n",msg,err,linea);
  exit(1);
}

/**
 * @brief Regresa el numero de semillas disponible.
 *
 * Busca dentro del semillero el numero de ',' que
 * encuentre lo que se traduce a un numero x de semillas.
 * @param num_semilla -Es la posicion de nuestra semilla en el archivo.
 * @return El numero de semillas que podemos tomar del semillero.
 */
int get_tamanio_semillero(char *ubicacion_semillas)
{
  int tamanio = 0;
  FILE *file;
  int int_file;
  char char_file[1];
  GList *l;
  file = fopen(ubicacion_semillas,"r+");
  //Revisamos si el archivo abrio bien.
  if(file == NULL){
    main_imprime_error("El archivo no existe o existe un problema al abrirlo.\n",__LINE__);
  }
  int_file = 0;
  while((int_file = fscanf(file,"%c",char_file)) != -1)
    {
      if(char_file[0] == ',')
	tamanio++;
    }
  fclose(file);
  return tamanio;
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
 * @brief Parametros de threads.
 *
 * Usamos esta estructura para mantener unidos los datos que contiene
 * el programa y necesitamos para correr la heuristica.
 *
 */
typedef struct param{
  int argc; /**< Es el id que representa el # de argumentos. */
  char **argv; /**< Son los argumentos del programa original. */
  TABLERO **tablero; /**< Es el apuntador al apuntador del tablero.*/
  int size_colonia; /**< Es el tamanio de la colonia que correremos.*/
  int distancia; /**< Es la distancia que recorrera una abeja.*/
} PARAM;

/**
 * @brief Ejecuta un pequenio recolector de basura.
 *
 * Para quitarle carga a el algoritmo, ejecutamos
 * un hilo que se encargue de liberar memoria.
 * @param thread_param - Son los argumentos como apuntador <T>.
 *
 */
void* basura(void *thread_param)
{
  PARAM *param = (PARAM*)thread_param;
  TABLERO **tablero = param->tablero;
  while(1)
    limpia();
  pthread_exit(NULL);
}

/**
 * @brief Ejecuta el solucionador del tetris.
 *
 * Ejecuta al thread que se va a encargar correr las abejas.
 * @param thread_param - Son los argumentos como apuntador <T>.
 *
 */
void* heuristica_abejas(void *thread_param)
{
  //Obtenemos los parametros del programa.
  PARAM *param = (PARAM*)thread_param;
  TABLERO **tablero = param->tablero;
  int size_colonia = param->size_colonia;
  int distancia = param->distancia;
  // Inicializamos el tablero en la primera ficha.
  siguiente_turno_tablero(*tablero);
  // Si el usuario especifica una semilla:
  if(SEMILLA > 0) {
    srand(get_semilla(UBICACION_SEMILLA,SEMILLA));
    ABC(tablero, size_colonia,distancia,true);
  }
  // Si el usuario no espeficia nada:  
  else {
    // Arreglar esto:
    int semillero = get_tamanio_semillero(UBICACION_SEMILLA);
    int i = SEMILLA_ITERA;
    int tetris = -1;
    int semilla_l = 1;
    while(--i > 0) {
      TABLERO *mejor = copy_tablero(*tablero);
      srand(time(NULL));
      int random_semilla = rand()%semillero;
      int seed = get_semilla(UBICACION_SEMILLA,random_semilla);
      srand(seed);
      ABC(tablero, size_colonia,distancia,false);
      if(tetris < (*tablero)->num_tetris) {
	tetris = (*tablero)->num_tetris;
	semilla_l = seed;
	printf("SEMILLA NUMERO = %d (%d)\n",random_semilla,seed);
      }
      TABLERO *elimina = *tablero;
      *tablero = mejor;
      agrega_basura(elimina);     
      if(i == 1) {
	srand(semilla_l);
	ABC(tablero, size_colonia, distancia, true);
	exit(0);
	break;
      }       
    }
  }
  end_visual_main();
  pthread_exit(NULL);
}

/**
 * @brief Metodo principal del programa.
 *
 * Tratamos de encontrar soluciones factibles al problema tetris..
 * @param argc - Es el numero de parametros. 
 * En este caso se espera argc > 2.
 * @param argv - Son los parametros NULL.
 * @return Un entero 0 si todo sale bien 1 en caso contrario.
 * @TODO Revisar parametros y si es mayor a uno e igual a 
 * RANDOM inicializar semilla con time(NULL).
 *
 */
int main(int argc, char** argv)
{
  //Inicializamos una variable para medir el tiempo de ejecucion:
  clock_t tic = clock();
  // Constantes de la GUI.
  int ALTO;
  int ANCHO;
  double ZOOM;
  // Constantes de experimentacion.
  int SIZE_COLONIA;
  int DISTANCIA;
  char *UBICACION_CFG;
  bool interfaz;
  // Revisamos los argumentos
  if(argc == 1) {
    interfaz = true;
    UBICACION_CFG = "./etc/config.cfg";
  }
  else if(argc == 2) {     
    if(strcmp(argv[1],"-i") == 0) {
      interfaz = false;
      UBICACION_CFG = "./etc/config.cfg";
    } else {
      UBICACION_CFG = argv[1];
    }
  }
  else {
    if(strcmp(argv[1],"-i") == 0) {
      interfaz = false;
	UBICACION_CFG = argv[2];
    }
    else if(strcmp(argv[2],"-i") == 0) {
      interfaz = false;
      UBICACION_CFG = argv[2];
    }
    else {
      interfaz = true;
      UBICACION_CFG = argv[1];
    }
  }
  // Variables para obtener las variables de configuracion.
  GKeyFile *keyfile;
  GKeyFileFlags flags;
  GError *error;
  //Leemos el archivo de configuracion:
  keyfile = g_key_file_new();
  flags = G_KEY_FILE_NONE;
  if (!g_key_file_load_from_file (keyfile,
				  UBICACION_CFG,
				  flags, &error))
    {
      printf("Error al cargar archivo de configuracion. LINEA= %d",__LINE__);
      return 1;
    }
  
  // 1. Los parametros de la GUI.
  ANCHO               = g_key_file_get_integer(keyfile,"GUI",
					       "ANCHO",NULL);
  ALTO                = g_key_file_get_integer(keyfile,"GUI",
					       "ALTO",NULL);
  ZOOM                = g_key_file_get_double(keyfile,"GUI",
					      "ZOOM",NULL);    
  // 2. Variables de experimentacion:
  SIZE_COLONIA        = g_key_file_get_integer(keyfile,"COLONIA",
					       "SIZE",NULL);
  DISTANCIA           = g_key_file_get_integer(keyfile,"COLONIA",
					       "DISTANCIA",NULL);  
  
  //Ahora asignamos a cada una de las variables sus valores del .cfg:
  // 3. Las semillas, numero elegida y la ubicacion del semillero:
  SEMILLA_ITERA     = g_key_file_get_integer(keyfile,"SEMILLA",
					     "SEMILLA_ITERA",NULL);    
  SEMILLA           = g_key_file_get_integer(keyfile,"SEMILLA",
					     "SEMILLA",NULL);    
  UBICACION_SEMILLA = g_key_file_get_string(keyfile,"SEMILLA",
					    "UBICACION",NULL);
  
  pthread_t threads[3];
  size_x = ANCHO;
  size_y = ALTO;
  double zoom_param = ZOOM;
  
  TABLERO *temp = init_tablero(size_y,size_x);
  TABLERO **tablero = &temp;
  PARAM *param = malloc(sizeof(PARAM));
  
  param->argc = argc;
  param->argv = argv;
  param->tablero = tablero;
  param->size_colonia = SIZE_COLONIA;
  param->distancia = DISTANCIA; 

  //Inicializamos el botadero:
  basurero = NULL;
  
  // Este es el lock del tablero.
  if (pthread_mutex_init(&lock, NULL) != 0 ||
      pthread_mutex_init(&lock_pieza, NULL) != 0 ||
      pthread_mutex_init(&lock_basura, NULL) != 0)
    {
      printf("\n mutex init failed\n");
      return 1;
    }
  pthread_create(&threads[0],NULL,heuristica_abejas,(void*)param);
  pthread_create(&threads[1],NULL,basura,(void*)param);
  if(interfaz)
    visual_main(argc,argv,tablero,zoom_param);
  while(1);
  //Contamos el tiempo:
  clock_t toc = clock();
  double segundos = (double)(toc - tic) / CLOCKS_PER_SEC;
  printf("Transcurrieron: %f segundos o %f minutos.\n",segundos,segundos/60);
  //pthread_join(threads[0],NULL);
  //pthread_join(threads[1],NULL);
  pthread_exit(NULL);
  pthread_mutex_destroy(&lock);
  pthread_mutex_destroy(&lock_pieza);
  pthread_mutex_destroy(&lock_basura);
  return 0; 
} //Fin de main.c

