MAINTAINERCLEANFILES = Makefile.in configure aclocal.m4 config.h.in

noinst_PROGRAMS = fribidi_benchmark

INCLUDES = $(GLIB_CFLAGS)

lib_LTLIBRARIES = libfribidi.la

libfribidi_la_SOURCES =	\
	fribidi.c	\
	fribidi_tables.i	\
	fribidi_types.c		\
	fribidi_get_type.c	\
	fribidi_utils.c		\
	fribidi_char_sets.c	\
	fribidi_char_sets_utf8.c	\
	fribidi_char_sets_cap_rtl.c	\
	fribidi_char_sets_iso8859_6.c	\
	fribidi_char_sets_iso8859_8.c	\
	fribidi_char_sets_cp1255.c	\
	fribidi_char_sets_cp1256.c	\
	fribidi_char_sets_isiri_3342.c

libfribidi_la_LIBADD = $(GLIB_LIBS)

libfribidiincdir = $(includedir)/fribidi

libfribidiincdir = $(includedir)/fribidi
libfribidiinc_HEADERS =	\
	fribidi.h	\
	fribidi_types.h	\
	fribidi_char_sets.h	\
	fribidi_char_sets_cap_rtl.h	\
	fribidi_char_sets_cp1255.h	\
	fribidi_char_sets_cp1256.h	\
	fribidi_char_sets_isiri_3342.h	\
	fribidi_char_sets_iso8859_6.h	\
	fribidi_char_sets_iso8859_8.h	\
	fribidi_char_sets_utf8.h	\
	@NO_GLIB_HEADERS@

EXTRA_HEADERS =	\
	fribidi_mini_glib.h	\
	getopt.h

getopt_files =	\
	getopt.c	\
	getopt1.c

EXTRA_DIST =	\
	bootstrap \
	run.tests	\
	ANNOUNCE	\
	acinclude.m4	\
	Makefile.noglib	\
	fribidi_mini_glib.c	\
	unidata/CreateGetType.pl	\
	tests/test-CapRTL	\
	tests/test-CapRTL.reference	\
	tests/test-explicit	\
	tests/test-explicit.reference	\
	tests/test-hebrew	\
	tests/test-hebrew.reference

fribidi_benchmark_SOURCES = fribidi_benchmark.c
fribidi_benchmark_LDADD = libfribidi.la $(GLIB_LIBS) $(GETOPTLIB)

bin_PROGRAMS = fribidi
fribidi_SOURCES = fribidi_main.c
fribidi_LDADD = libfribidi.la $(GLIB_LIBS) $(GETOPTLIB)

unidata/BidiMirroring.txt:
	cd $(top_srcdir)/unidata &&	\
	if ! test -f BididMirroring.txt ; then	\
	    wget http://www.unicode.org/Public/UNIDATA/BidiMirroring.txt ;	\
	fi

unidata/PropList.txt:
	cd $(top_srcdir)/unidata &&	\
	if ! test -f PropList.txt ; then	\
	    wget http://www.unicode.org/Public/UNIDATA/PropList.txt ;	\
	fi

fribidi_tables.i: unidata/CreateGetType.pl	\
	unidata/BidiMirroring.txt unidata/PropList.txt
	cd $(top_srcdir)/unidata &&	\
	./CreateGetType.pl > ../fribidi_tables.i

tests/test-CapRTL.reference: fribidi tests/test-CapRTL
	./fribidi --test --charset CapRTL $(top_srcdir)/tests/test-CapRTL > \
	$(top_srcdir)/tests/test-CapRTL.reference

tests/test-explicit.reference: fribidi tests/test-explicit
	./fribidi --test --charset CapRTL $(top_srcdir)/tests/test-explicit > \
	$(top_srcdir)/tests/test-explicit.reference

tests/test-hebrew.reference: fribidi tests/test-hebrew
	./fribidi --test --charset ISO8859-8 $(top_srcdir)/tests/test-hebrew > \
	$(top_srcdir)/tests/test-hebrew.reference

test.reference : tests/test-CapRTL.reference	\
		tests/test-explicit.reference	\
		tests/test-hebrew.reference

test: fribidi
	$(top_srcdir)/run.tests

TESTS = run.tests

bin_SCRIPTS = fribidi-config

noinst_LIBRARIES = libfribidi_mini_glib.a libgetopt.a

libfribidi_mini_glib_a_SOURCES = fribidi_mini_glib.c

libgetopt_a_SOURCES = getopt.c getopt1.c
