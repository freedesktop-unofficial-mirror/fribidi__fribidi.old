/* FriBidi - Library of BiDi algorithm
 * Copyright (C) 1999,2000 Dov Grobgeld, and
 * Copyright (C) 2001 Behdad Esfahbod.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public  
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,  
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License  
 * along with this library, in a file named COPYING.LIB; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA
 * 
 * For licensing issues, contact <dov@imagic.weizmann.ac.il> and
 * <fwpg@sharif.edu>.
 */
#ifndef FRIBIDI_CHAR_SETS_H
#define FRIBIDI_CHAR_SETS_H

#include "fribidi.h"

#define UNI_LRM 0x200E
#define UNI_RLM 0x200F
#define UNI_LRE 0x202a
#define UNI_RLE 0x202b
#define UNI_PDF 0x202c
#define UNI_LRO 0x202d
#define UNI_RLO 0x202e

#include "fribidi_char_sets_cap_rtl.h"
#include "fribidi_char_sets_utf8.h"
#include "fribidi_char_sets_iso8859_6.h"
#include "fribidi_char_sets_iso8859_8.h"
#include "fribidi_char_sets_cp1255.h"
#include "fribidi_char_sets_cp1256.h"
#include "fribidi_char_sets_isiri_3342.h"

/* The following enum members are going to be used as array indices,
   so they must be numbered from 0, and with the fixed order,
   FRIBIDI_CHARSET_DEFAULT is the one that when a charset leaves it's
   state with fribidi_charset_leave(), it gets into DEFAULT mode,
   so it must have no initialization. */
typedef enum
{
  FRIBIDI_CHARSET_NOT_FOUND,
  FRIBIDI_CHARSET_UTF8,
  FRIBIDI_CHARSET_CAP_RTL,
  FRIBIDI_CHARSET_ISO8859_6,
  FRIBIDI_CHARSET_ISO8859_8,
  FRIBIDI_CHARSET_CP1255,
  FRIBIDI_CHARSET_CP1256,
  FRIBIDI_CHARSET_ISIRI_3342,

  FRIBIDI_CHARSET_DEFAULT = FRIBIDI_CHARSET_UTF8,
}
FriBidiCharSet;

#define FRIBIDI_CHAR_SETS_NUM 7

/* Convert the character string "s" in charset "char_set" to unicode
   string "us" and return it's length. */
gint fribidi_charset_to_unicode (FriBidiCharSet char_set, guchar * s,
				 /* output */
				 FriBidiChar * us);

/* Convert the unicode string "us" with length "length" to character
   string "s" in charset "char_set" and return it's length. */
gint fribidi_unicode_to_charset (FriBidiCharSet char_set, FriBidiChar * us,
				 gint length,
				 /* output */
				 gchar * s);

/* Return the string containing the name of the charset. */
guchar *fribidi_char_set_name (FriBidiCharSet char_set);

/* Return the string containing the title (name with a short description)
   of the charset. */
guchar *fribidi_char_set_title (FriBidiCharSet char_set);

/* Return the string containing a descreption about the charset, if any. */
guchar *fribidi_char_set_desc (FriBidiCharSet char_set);

/* Some charsets like CapRTL may need to change some fribidis tables, by
   calling this function, they can do this changes. */
gboolean fribidi_char_set_enter (FriBidiCharSet char_set);

/* Some charsets like CapRTL may need to change some fribidis tables, by
   calling this function, they can undo their changes, perhaps to enter
   another mode. */
gboolean fribidi_char_set_leave (FriBidiCharSet char_set);

/* Return the charset which name is "s". */
FriBidiCharSet
fribidi_parse_charset (guchar * s);

#endif /* FRIBIDI_CHAR_SETS_H */
