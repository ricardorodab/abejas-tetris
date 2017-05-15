#!/bin/bash

# El proposito de este script es no tener que correr continuamente
# a mano las herramientas de autotools para instalar el proyecto
# final

aclocal ;
autoconf ;

pwd ;

automake --add-missing --foreign ;
./configure ;
