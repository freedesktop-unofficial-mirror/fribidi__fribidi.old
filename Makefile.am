noinst_PROGRAMS = fribidi_benchmark

INCLUDES = $(GLIB_CFLAGS)

lib_LTLIBRARIES = libfribidi.la

libfribidi_la_SOURCES = \
	fribidi.c	    \
	fribidi_tables.i    \
	fribidi_types.c     \
	fribidi_char_sets.c \
	fribidi_char_sets_utf8.c       \
	fribidi_char_sets_cap_rtl.c    \
	fribidi_char_sets_iso8859_6.c  \
	fribidi_char_sets_iso8859_8.c  \
	fribidi_char_sets_cp1255.c     \
	fribidi_char_sets_cp1256.c     \
	fribidi_char_sets_isiri_3342.c \
	fribidi_get_type.c             \
	fribidi_utils.c

libfribidi_la_LIBADD = $(GLIB_LIBS)

libfribidiincdir = $(includedir)/fribidi

libfribidiincdir = $(includedir)/fribidi
libfribidiinc_HEADERS = \
	fribidi.h \
	fribidi_char_sets_utf8.h       \
	fribidi_char_sets_cap_rtl.h    \
	fribidi_char_sets_iso8859_6.h  \
	fribidi_char_sets_iso8859_8.h  \
	fribidi_char_sets_cp1255.h     \
	fribidi_char_sets_cp1256.h     \
	fribidi_char_sets_isiri_3342.h \
	fribidi_char_sets.h \
	fribidi_types.h

EXTRA_DIST = \
        unidata/CreateGetType.pl \
	tests/test-CapRTL \
	tests/test-explicit \
	tests/test-hebrew \
	tests/test-CapRTL.reference \
	tests/test-explicit.reference \
	tests/test-hebrew.reference \
	run.tests \
	ANNOUNCE \
	acinclude.m4 \
        fribidi_mini_glib.h \
	fribidi_mini_glib.c \
        Makefile.noglib


fribidi_benchmark_SOURCES = fribidi_benchmark.c
fribidi_benchmark_LDADD = libfribidi.la $(GLIB_LIBS)

bin_PROGRAMS = fribidi
fribidi_SOURCES = fribidi_main.c
fribidi_LDADD = libfribidi.la $(GLIB_LIBS)

tests/test-CapRTL.reference: fribidi tests/test-CapRTL 
	mkdir -p tests
	./fribidi --fill --showinput --charset CapRTL $(top_srcdir)/tests/test-CapRTL > \
	$(top_srcdir)/tests/test-CapRTL.reference

tests/test-explicit.reference: fribidi tests/test-explicit 
	./fribidi --fill --showinput --charset CapRTL $(top_srcdir)/tests/test-explicit > \
	$(top_srcdir)/tests/test-explicit.reference

tests/test-hebrew.reference: fribidi tests/test-hebrew
	./fribidi --fill --showinput --charset ISO8859-8 $(top_srcdir)/tests/test-hebrew > \
	$(top_srcdir)/tests/test-hebrew.reference

test: fribidi
	./run.tests

TESTS = run.tests

bin_SCRIPTS = fribidi-config
