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

#include "fribidi.h"

/* The following are proposed extensions to iso-8859-8. */
#define ISO_8859_8_LRM 253
#define ISO_8859_8_RLM 254
#define ISO_8859_8_LRE 251
#define ISO_8859_8_RLE 252
#define ISO_8859_8_PDF 221
#define ISO_8859_8_LRO 219
#define ISO_8859_8_RLO 220
#define ISO_ALEF 224
#define ISO_TAV 250

#define UNI_ALEF 0x05D0
#define UNI_TAV 0x05EA

FriBidiChar fribidi_iso8859_8_to_unicode_c (guchar ch)
{
  /* optimization */
  if (ch < ISO_8859_8_LRO)
    return ch;
  else if (ch >= ISO_ALEF && ch <= ISO_TAV)
    return ch - ISO_ALEF + UNI_ALEF;
  switch (ch)
    {
    case ISO_8859_8_RLM:
      return UNI_RLM;
    case ISO_8859_8_LRM:
      return UNI_LRM;
    case ISO_8859_8_RLO:
      return UNI_RLO;
    case ISO_8859_8_LRO:
      return UNI_LRO;
    case ISO_8859_8_RLE:
      return UNI_RLE;
    case ISO_8859_8_LRE:
      return UNI_LRE;
    case ISO_8859_8_PDF:
      return UNI_PDF;
    default:
      return '?';		/* This shouldn't happen! */
    }
}

gint fribidi_iso8859_8_to_unicode (guchar * s, FriBidiChar * us)
{
  gint i;
  gint len = strlen (s);

  for (i = 0; i < len + 1; i++)
    us[i] = fribidi_iso8859_8_to_unicode_c (s[i]);

  return len;
}

guchar fribidi_unicode_to_iso8859_8_c (FriBidiChar uch)
{
  if (uch < 128)
    return uch;
  if (uch >= UNI_ALEF && uch <= UNI_TAV)
    return (guchar) (uch - UNI_ALEF + ISO_ALEF);
  switch (uch)
    {
    case UNI_RLM:
      return ISO_8859_8_RLM;
    case UNI_LRM:
      return ISO_8859_8_LRM;
    case UNI_RLO:
      return ISO_8859_8_RLO;
    case UNI_LRO:
      return ISO_8859_8_LRO;
    case UNI_RLE:
      return ISO_8859_8_RLE;
    case UNI_LRE:
      return ISO_8859_8_LRE;
    case UNI_PDF:
      return ISO_8859_8_PDF;
    }
  return '¿';
}

gint fribidi_unicode_to_iso8859_8 (FriBidiChar * us, int length, guchar * s)
{
  gint i;

  for (i = 0; i < length; i++)
    s[i] = fribidi_unicode_to_iso8859_8_c (us[i]);
  s[i] = 0;

  return length;
}
