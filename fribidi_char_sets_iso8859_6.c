/* FriBidi - Library of BiDi algorithm
 * Copyright (C) 1999 Dov Grobgeld
 * Copyright (C) 2001 Behdad Esfahbod
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#include "fribidi.h"

#define ISO_HAMZA 0xc1
#define ISO_SUKUN 0xf2

#define UNI_HAMZA 0x0621
#define UNI_SUKUN 0x0652

FriBidiChar
fribidi_iso8859_6_to_unicode_c (guchar ch)
{
  if (ch >= ISO_HAMZA && ch <= ISO_SUKUN)
    return ch - ISO_HAMZA + UNI_HAMZA;
  else
    return ch;
}

gint
fribidi_iso8859_6_to_unicode (guchar * s, FriBidiChar * us)
{
  gint i;
  gint len = strlen (s);

  for (i = 0; i < len + 1; i++)
    us[i] = fribidi_iso8859_6_to_unicode_c (s[i]);

  return len;
}

guchar
fribidi_unicode_to_iso8859_6_c (FriBidiChar uch)
{
  if (uch >= UNI_HAMZA && uch <= UNI_SUKUN)
    return (guchar) (uch - UNI_HAMZA + ISO_HAMZA);
  /* TODO: handle pre-composed and presentation chars */
  else if (uch < 256)
    return (guchar) uch;
  else if (uch == 0x060c)
    return (guchar) 0xac;
  else if (uch == 0x061b)
    return (guchar) 0xbb;
  else if (uch == 0x061f)
    return (guchar) 0xbf;
  else
    return '¿';
}

gint
fribidi_unicode_to_iso8859_6 (FriBidiChar * us, int length, guchar * s)
{
  gint i;

  for (i = 0; i < length; i++)
    s[i] = fribidi_unicode_to_iso8859_6_c (us[i]);
  s[i] = 0;

  return length;
}
