AC_INIT([libgcm], [0.1.0])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE

LT_INIT

AC_PROG_CC_C99

PKG_CHECK_MODULES([json_c], [json-c])
PKG_CHECK_MODULES([libcurl], [libcurl])

AC_OUTPUT([Makefile src/libgcm.pc])
