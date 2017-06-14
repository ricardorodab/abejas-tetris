AUTOMAKE_OPTIONS =  subdir-objects
AM_CFLAGS = -g -O3 -I$(top_srcdir)/lib $(GLIB_CFLAGS) $(GLIB_LIBS) $(opengl_LIBS) $(GLEW_LIBS) -lpthread -lm
noinst_LIBRARIES = lib/libutils.a

END_LIST =

lib_libutils_a_SOURCES =    \
	lib/pieza.c	    \
	lib/pieza.h	    \
	lib/tablero.c	    \
	lib/tablero.h	    \
	lib/abejas.c	    \
	lib/abejas.h	    \
	lib/funcion.c	    \
	lib/funcion.h	    \
	lib/abc.c	    \
	lib/abc.h	    \
	lib/lock.h	    \
	lib/dump.h	    \
	lib/dump.c	    \
	$(END_LIST)

lib_libutils_a_CPPFLAGS = $(GLIB_CFLAGS)
lib_libutils_a_LDFLAGS= $(GLIB_LIBS)	

bin_PROGRAMS = src/main
src_main_LDADD = $(top_builddir)/lib/libutils.a 
src_main_CFLAGS = $(AM_CFLAGS) 
src_main_SOURCES = 		\
	src/main.c		\
	src/interfaz-grafica.h	\
	src/interfaz-grafica.c	\
	src/tetromino.h		\
	src/tetromino.c		\
	$(END_LIST)

TESTS = test/test-ciudad test/test-ruta

TESTCIUDADSOURCES = test/test-ciudad.c
TESTRUTASOURCES =test/test-ruta.c

test_test_ciudad_CFLAGS = $(AM_CFLAGS)
test_test_ciudad_LDADD = $(top_builddir)/lib/libutils.a
test_test_ruta_CFLAGS = $(AM_CFLAGS)
test_test_ruta_LDADD = $(top_builddir)/lib/libutils.a  

check_PROGRAMS = $(TESTS)

