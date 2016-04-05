AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4

include_HEADERS=src/libgcm.h

lib_LTLIBRARIES=libgcm.la
libgcm_la_SOURCES=src/libgcm.c
libgcm_la_LIBADD=-lcurl -ljson-c
