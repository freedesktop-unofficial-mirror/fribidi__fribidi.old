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
 * along with this library, in a file named COPYING; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
 * Boston, MA 02111-1307, USA  
 * 
 * For licensing issues, contact <dov@imagic.weizmann.ac.il> and 
 * <fwpg@sharif.edu>. 
 */

#include "fribidi_config.h"
#ifndef FRIBIDI_NO_CHARSETS

#ifndef FRIBIDI_CHAR_SETS_CP1255_H
#define FRIBIDI_CHAR_SETS_CP1255_H

#include "fribidi.h"

#define fribidi_char_set_name_cp1255 "CP1255"
#define fribidi_char_set_title_cp1255 "CP1255 (Hebrew/Yiddish)"
#define fribidi_char_set_desc_cp1255 NULL
#define fribidi_char_set_enter_cp1255 NULL
#define fribidi_char_set_leave_cp1255 NULL

FriBidiChar fribidi_cp1255_to_unicode_c (char ch);
int fribidix_cp1255_to_unicode (char *s, int length,
				/* Output */
				FriBidiChar *us);
char fribidi_unicode_to_cp1255_c (FriBidiChar uch);
int fribidix_unicode_to_cp1255 (FriBidiChar *us, int length,
				/* Output */
				char *s);

/* Old style, just for compatibility.  do not use these. */

#define fribidi_cp1255_to_unicode(s, us)	\
	fribidix_cp1255_to_unicode(s, strlen(s), us)

#define fribidi_unicode_to_cp1255(us, length, s)	\
	fribidix_unicode_to_cp1255(us, length, s)

#endif /* FRIBIDI_CHAR_SETS_CP1255_H */

#endif
