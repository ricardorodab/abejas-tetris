#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([ProyectoFinal], [0.1], [ricardo_rodab@ciencias.unam.mx])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([lib/pieza.c])
# Checks for programs.
#LT_INIT
AC_PROG_CC
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PROG_RANLIB
# Checks for libraries.
AC_PROG_INSTALL
PKG_CHECK_MODULES(GLIB, glib-2.0)
AC_CHECK_LIB([glut], [glutInit])
AC_CHECK_LIB([freeglut], [glutInit])
AC_CHECK_LIB(GLEW, glewInit, have_glew=yes, have_glew=no, $GLUT_LIBS)
# Checks for header files.

AC_CHECK_HEADER([GL/glew.h], [], have_glew=no)

if test "x$have_glew" = "xyes"; then
	GLEW_LIBS="-lGLEW $GL_LIBS"
	AC_DEFINE(HAVE_GLEW, 1, [defined if the GL Extension Wrangler GLEW library is available])
else
	GLEW_LIBS="$GL_LIBS"
	AC_MSG_WARN([GL Extension Wrangler library not found.  Get it from http://glew.sourceforge.net])
fi
AC_SUBST(GLEW_LIBS)

if test "x$no_gl" != "xyes"; then
	AC_DEFINE(HAVE_GL, 1, [defined if OpenGL is available])
fi

if test x$have_glew = xyes -a x$no_glut != xyes; then
	HAVE_FULLGL="yes"
else
	HAVE_FULLGL="no"
fi


case "$host" in
        *-*-mingw*|*-*-cygwin*)
                AC_DEFINE(PLATFORM_WIN32, 1, [Platform is Win32])
                opengl_LIBS="-lunsupported_platform"
                PLATFORM_STRING="Win32"
                ;;
        *-*-linux*)
                AC_DEFINE(PLATFORM_LINUX, 1, [Platform is Linux])
                opengl_LIBS="-lGL -lGLU -lglut"
                PLATFORM_STRING="Linux"
                ;;
        *-*-darwin*)
                AC_DEFINE(PLATFORM_APPLE, 1, [Platform is Apple])
                opengl_LIBS="-framework AGL -framework OpenGL -framework GLUT"
                PLATFORM_STRING="Apple"
                ;;
        *)
                AC_MSG_WARN([*** Please add $host to configure.ac checks!])
                ;;
esac
AC_SUBST(opengl_LIBS)


#Esto es lo que hizo Canek para gtk, probablemente lo usare:
#PKG_CHECK_MODULES(GLIB_COMPILE_RESOURCES, glib-compile-resources)
# PKG_CHECK_MODULES(EJEMPLO, [ gtk+-3.0 ])
#AC_SUBST(EJEMPLO_CFLAGS)
#AC_SUBST(EJEMPLO_LIBS)


# Checks for typedefs, structures, and compiler characteristics.


# Checks for library functions.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
