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

/* the following added by Raphael Finkel <raphael@cs.uky.edu> 12/1999 */

gint fribidi_utf8_to_unicode (guchar * s, FriBidiChar * us)
/* warning: the length of input string may exceed the length of the output */
{
  int length;

  length = 0;
  while (*s)
    {
      if (*s <= 0177)		/* one byte */
	{
	  *us++ = *s++;		/* expand with 0s */
	}
      else if (*s < 0340)	/* 2 chars, such as Hebrew */
	{
	  *us++ = ((*s & 037) << 6) + (*(s + 1) & 077);
	  s += 2;
	}
      else			/* 3 chars */
	{
	  *us++ = ((*s & 017) << 12) + ((*(s + 1) & 077) << 6) +
	    (*(s + 2) & 077);
	  s += 3;
	}
      length += 1;
    }
  *us = 0;
  return (length);
}

gint fribidi_unicode_to_utf8 (FriBidiChar * us, int length, guchar * s)
/* warning: the length of output string may exceed the length of the input */
{
  gint i;
  guchar *t;

  t = s;
  for (i = 0; i < length; i++)
    {
      FriBidiChar mychar = us[i];
      if (mychar <= 0x7F)
	{			/* 7 sig bits; plain 7-bit ASCII */
	  *t++ = mychar;
	}
      else if (mychar <= 0x7FF)	/* 11 sig bits; Hebrew is in this range */
	{
	  *t++ = 0300 | (guint8) ((mychar >> 6) & 037);
	  *t++ = 0200 | (guint8) (mychar & 077);	/* lower 6 bits */
	}
      else if (mychar <= 0xFFFF)
	{			/* 16 sig bits */
	  *t++ = 0340 | (guint8) ((mychar >> 12) & 017);	/* upper 4 bits */
	  *t++ = 0200 | (guint8) ((mychar >> 6) & 077);	/* next 6 bits */
	  *t++ = 0200 | (guint8) (mychar & 077);	/* lowest 6 bits */
	}
    }
  *t = 0;

  return (t - s);
}


/* the following was added by Omer Zak <omerz@actcom.co.il> Sept 2000.
   The following functions do the same thing, but have better-defined
   interfaces. */

gboolean			/* Returns TRUE if the entire UTF8 string was converted without errors. */
  fribidi_utf8_to_unicode_p (guchar * in_utf8_str,	/* UTF8 string */
			     guint in_utf8_length,	/* Length of UTF8 string in octets */
			     FriBidiChar * unicode_buffer,	/* Buffer for Unicode translation */
			     guint unicode_buffer_length,	/* Length of Unicode buffer in
								   Unicode characters */
			     /* Outputs */
			     guint * out_utf8_consumed_length_p,
			     /* Actual number of UTF8
			        octets translated
			      */
			     guint * out_actual_unicode_buffer_length_p)
  /* Actual number of Unicode
     characters used in the
     Unicode buffer. */
{
  /* !!! To be improved using code from libutf8-0.7.3/src/mbstowcs/mbsrtowcs.c
     !!! (the library is LGPLed :-) ) */

  guint index;
  guint index_uni;

  if (NULL == in_utf8_str
      || NULL == unicode_buffer
      || NULL == out_utf8_consumed_length_p
      || NULL == out_actual_unicode_buffer_length_p)
    return (FALSE);

  /* If we are here, all outputs must have some valid values. */
  *out_utf8_consumed_length_p = 0;
  *out_actual_unicode_buffer_length_p = 0;

  for (index = 0, index_uni = 0;
       (index < in_utf8_length) && (index_uni < unicode_buffer_length);)
    {
      /* NOTE:  there is no protection against UTF8 sequences which overflow the in_utf8_str. */
      if (in_utf8_str[index] <= 0177)	/* one byte */
	{
	  unicode_buffer[index_uni++] = in_utf8_str[index++];	/* expand with 0s */
	}
      else if (in_utf8_str[index] < 0340)	/* 2 chars, such as Hebrew */
	{
	  unicode_buffer[index_uni++] = ((in_utf8_str[index] & 037) << 6)
	    + (in_utf8_str[index + 1] & 077);
	  index += 2;
	}
      else			/* 3 chars */
	{
	  unicode_buffer[index_uni++] = ((in_utf8_str[index] & 017) << 12)
	    + ((in_utf8_str[index + 1] & 077) << 6)
	    + (in_utf8_str[index + 2] & 077);
	  index += 3;
	}
    }
  *out_utf8_consumed_length_p = index;
  *out_actual_unicode_buffer_length_p = index_uni;

  return (TRUE);
}

gboolean			/* Returns TRUE if the outputs are valid, even if the entire
				   Unicode string was not converted.
				 */
  fribidi_unicode_to_utf8_p (FriBidiChar * in_unicode_str,	/* Unicode string */
			     guint in_unicode_length,	/* Unicode string length in
							   ** Unicode characters
							 */
			     guchar * utf8_buffer,	/* Buffer for UTF8 translation */
			     guint utf8_buffer_length,	/* Length of UTF8 buffer */
			     /* Outputs */
			     guint * out_uni_consumed_length_p,
			     /* Actual number of Unicode
			        ** characters translated
			      */
			     guint * out_actual_utf8_buffer_length_p)
  /* Actual number of bytes
     ** used in the UTF8 buffer.
   */
{
  guint l_utf8_buffer_fence;	/* Fence - 6 octets before end */
  guint index;
  guint index_utf8;

  if (NULL == in_unicode_str
      || NULL == utf8_buffer
      || 0 == out_uni_consumed_length_p
      || 0 == out_actual_utf8_buffer_length_p || utf8_buffer_length < 6)
    return (FALSE);

  /* If we are here, all outputs must have some valid values. */
  *out_uni_consumed_length_p = 0;
  *out_actual_utf8_buffer_length_p = 0;

  l_utf8_buffer_fence = utf8_buffer_length - 6;

  for (index = 0, index_utf8 = 0; index < in_unicode_length; index++)
    {
      FriBidiChar ucs4_char;

      if (index_utf8 > l_utf8_buffer_fence)
	{
	  break;		/* No more guaranteed room in UTF8 buffer. */
	}

      ucs4_char = in_unicode_str[index];

#define PUT_UTF8_BYTE(b) utf8_buffer[index_utf8++] = (b)

      if (ucs4_char < 0x00000080)
	{
	  PUT_UTF8_BYTE (ucs4_char & 0x0000007F);
	}
      else if (ucs4_char < 0x00000800)
	{
	  PUT_UTF8_BYTE (((ucs4_char >> 6) & 0x0000001F) | 0x000000C0);
	  PUT_UTF8_BYTE ((ucs4_char & 0x0000003F) | 0x00000080);
	}
      else if (ucs4_char < 0x00010000)
	{
	  PUT_UTF8_BYTE (((ucs4_char >> 12) & 0x0000000F) | 0x000000E0);
	  PUT_UTF8_BYTE (((ucs4_char >> 6) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE ((ucs4_char & 0x0000003F) | 0x00000080);
	}
      else if (ucs4_char < 0x00200000)
	{
	  PUT_UTF8_BYTE (((ucs4_char >> 18) & 0x00000007) | 0x000000F0);
	  PUT_UTF8_BYTE (((ucs4_char >> 12) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE (((ucs4_char >> 6) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE ((ucs4_char & 0x0000003F) | 0x00000080);
	}
      else if (ucs4_char < 0x04000000)
	{
	  PUT_UTF8_BYTE (((ucs4_char >> 24) & 0x00000003) | 0x000000F8);
	  PUT_UTF8_BYTE (((ucs4_char >> 18) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE (((ucs4_char >> 12) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE (((ucs4_char >> 6) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE ((ucs4_char & 0x0000003F) | 0x00000080);
	}
      else			/* if (ucs4_char < 0x80000000) */
	{
	  PUT_UTF8_BYTE (((ucs4_char >> 30) & 0x00000001) | 0x000000FC);
	  PUT_UTF8_BYTE (((ucs4_char >> 24) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE (((ucs4_char >> 18) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE (((ucs4_char >> 12) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE (((ucs4_char >> 6) & 0x0000003F) | 0x00000080);
	  PUT_UTF8_BYTE ((ucs4_char & 0x0000003F) | 0x00000080);
	}

#undef PUT_UTF8_BYTE

    }

  *out_uni_consumed_length_p = index;
  *out_actual_utf8_buffer_length_p = index_utf8;

  return (TRUE);
}
