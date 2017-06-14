/*-------------------------------------------------------------------
 * dump.c
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

#include "dump.h"

/**
 * @file dump.c
 * @author Jose Ricardo Rodriguez Abreu
 * @date 13 Jun 2017
 * @brief File containing the struct and funtions to simulate Tetris
 * board for the "Combinatorial Optimization Heuristics" class. 
 *
 * Aqui se implementa todo lo que queremos vaciar.
 *
 * El programa usa el estandar de documentacion que define el uso de 
 * doxygen.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/manual/index.html
 * @see https://github.com/ricardorodab/AceptacionUmbral
 *
 */

void agrega_basura(TABLERO *tablero)
{
  pthread_mutex_lock(&lock_basura);
  basurero = g_list_append(basurero,tablero);
  pthread_mutex_unlock(&lock_basura);
}

void limpia(void)
{
  GList *l;
  pthread_mutex_lock(&lock_basura);  
  GList *copia = g_list_copy(basurero);
  basurero = NULL;
  pthread_mutex_unlock(&lock_basura);  
  for(l = copia; l != NULL; l = l->next)
    {
      free_tablero(l->data);
    }
}
