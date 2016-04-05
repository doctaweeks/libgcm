AUTOMAKE_OPTIONS = foreign subdir-objects
ACLOCAL_AMFLAGS = -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libgcm.pc
DISTCLEANFILES = $(pkgconfig_DATA)

include_HEADERS=src/libgcm.h

lib_LTLIBRARIES=libgcm.la
libgcm_la_SOURCES=src/libgcm.c
libgcm_la_LIBADD=-lcurl -ljson-c
