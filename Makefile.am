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
	fribidi_char_sets.h \
	fribidi_types.h

EXTRA_DIST = \
        unidata/CreateGetType.pl \
	tests/test-hebrew \
	tests/test-capital-rtl \
	run.tests \
	test.reference \
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

test.reference : tests/test-CapRTL tests/test-explicit test/test-hebrew
	./fribidi --fill --showinput --charset CapRTL tests/test-CapRTL > \
	tests/test-CapRTL.reference
	./fribidi --fill --showinput --charset CapRTL tests/test-explicit > \
	tests/test-explicit.reference
	./fribidi --fill --showinput --charset ISO8859-8 tests/test-hebrew > \
	tests/test-hebrew.reference

test : fribidi
	./run.tests

TESTS = run.tests

bin_SCRIPTS = fribidi-config
