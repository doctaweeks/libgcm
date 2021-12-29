AUTOMAKE_OPTIONS = foreign subdir-objects
ACLOCAL_AMFLAGS = -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libgcm.pc
DISTCLEANFILES = $(pkgconfig_DATA)

include_HEADERS=src/libgcm.h

lib_LTLIBRARIES=libgcm.la
libgcm_la_SOURCES=src/libgcm.c
libgcm_la_CPPFLAGS=$(json_c_CFLAGS) $(libcurl_CFLAGS)
libgcm_la_LIBADD=$(json_c__LIBS) $(libcurl_LIBS)
libgcm_la_LDFLAGS=-version-info 0:0:0
