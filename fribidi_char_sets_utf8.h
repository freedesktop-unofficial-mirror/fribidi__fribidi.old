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
#ifndef FRIBIDI_CHAR_SETS_UTF8_H
#define FRIBIDI_CHAR_SETS_UTF8_H

#include "fribidi.h"

#define fribidi_char_set_name_utf8 "UTF-8"
#define fribidi_char_set_title_utf8 "UTF-8 (Unicode)"
#define fribidi_char_set_desc_utf8 NULL
#define fribidi_char_set_enter_utf8 NULL
#define fribidi_char_set_leave_utf8 NULL

gint fribidi_unicode_to_utf8 (FriBidiChar *us, gint length,
			      /* Output */
			      gchar *s);

/* warning: the length of output string may exceed the length of the input */
/* the length of the string is returned */
gint fribidi_utf8_to_unicode (gchar *s,
			      /* Output */
			      FriBidiChar *us);

/* the following added by Omer Zak <omerz@actcom.co.il> Sept 2000.
   The following functions do the same thing, but have better-defined
   interfaces. */

/* Returns TRUE if the entire UTF8 string was converted without errors. */
gboolean fribidi_utf8_to_unicode_p (	/* Input */
				     /* UTF8 string */
				     gchar *in_utf8_str,
				     /* Length of UTF8 string in octets */
				     guint in_utf8_length,
				     /* Buffer for Unicode translation */
				     FriBidiChar *unicode_buffer,
				     /* Length of Unicode buffer in Unicode characters */
				     guint unicode_buffer_length,
				     /* Outputs */
				     /* Actual number of UTF8 octets translated */
				     guint *out_utf8_consumed_length_p,
				     /* Actual number of Unicode characters used in the Unicode buffer. */
				     guint
				     *out_actual_unicode_buffer_length_p);

/* Returns TRUE if the outputs are valid, even if the entire Unicode string
 * was not converted. */
gboolean fribidi_unicode_to_utf8_p (	/* Input */
				     /* Unicode string */
				     FriBidiChar *in_unicode_str,
				     /* Unicode string length in Unicode characters */
				     guint in_unicode_length,
				     /* Buffer for UTF8 translation */
				     gchar *utf8_buffer,
				     /* Length of UTF8 buffer */
				     guint utf8_buffer_length,
				     /* Outputs */
				     /* Actual number of Unicode characters translated */
				     guint *out_uni_consumed_length_p,
				     /* Actual number of bytes used in the UTF8 buffer */
				     guint *out_actual_utf8_buffer_length_p);

#endif /* FRIBIDI_CHAR_SETS_UTF8_H */
