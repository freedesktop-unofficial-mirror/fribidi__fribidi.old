
This directory contains the MSVC project files for building
fribidi. This file contains some important information regarding using
these files, so please read it from start to end :-).

The project files are set to build memory-optimized version of fribidi,
but targets are provided for speed optimized builds as well. If you are
fussy and want something half-way, you will need to build
fribidi_create_char_types.exe, use it to generate fribidi_tab_char_type_?.i
and then set the HAS_FRIBIDI_TAB_CHAR_TYPE_?_I defines accordingly (have
a look at fribidi_char_type.c).

The project files are set not to build the fribidi character set
conversion functions, since under win32 you are not likely to want
them. If you need to include them, you have to uncheck the checkbox
'Settings -> General -> Exclude file from build' for the 'Char
Sets' directory and remove FRIBIDI_NO_CHARSETS from 'Settings ->
C/C++ -> Category: Preprocessor -> Preprocessor definitions' of the
entire project.

  **************************************************************
  * IMPORTANT: if MSVC refuses to open the project files       *
  * (sometimes you get a message along the lines "this file    *
  * was not created by MSVC", other times MSVC just silently   *
  * fails), then almost certainly the files you have use       * 
  * Unix convention for ending lines with \n, rather than the  *
  * DOS convention of using \r\n. You just need to use some    *
  * tool to fix this (I use the free Programmer's File Editor, * 
  * PFE32.EXE, which makes it easy). Once you do this, MSVC    *
  * should open the files no bother.                           *
  **************************************************************

Tomas Frydrych
<tomas@frydrych.uklinux.net>
07/08/2002
