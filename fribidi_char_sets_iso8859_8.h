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
#ifndef FRIBIDI_CHAR_SETS_ISO8859_8_H
#define FRIBIDI_CHAR_SETS_ISO8859_8_H

#include "fribidi.h"

#define fribidi_char_set_name_iso8859_8 "ISO8859-8"
#define fribidi_char_set_title_iso8859_8 "ISO 8859-8 (Hebrew)"
#define fribidi_char_set_desc_iso8859_8 NULL
#define fribidi_char_set_enter_iso8859_8 NULL
#define fribidi_char_set_leave_iso8859_8 NULL

FriBidiChar fribidi_iso8859_8_to_unicode_c (guchar ch);
gint fribidi_iso8859_8_to_unicode (guchar * s,
				   /* Output */
				   FriBidiChar * us);
guchar fribidi_unicode_to_iso8859_8_c (FriBidiChar uch);
gint fribidi_unicode_to_iso8859_8 (FriBidiChar * us, gint length,
				   /* Output */
				   guchar * s);

#endif /* FRIBIDI_CHAR_SETS_ISO8859_8_H */
