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

#include <string.h>
#include "fribidi.h"

extern FriBidiCharType FriBidiPropertyBlock0000[256];
extern FriBidiCharType *FriBidiPropertyBlocks[256];

FriBidiChar
fribidi_cap_rtl_to_unicode_c (guchar ch)
{
  return ch;
}

guchar
fribidi_unicode_to_cap_rtl_c (FriBidiChar uch)
{
  if (uch <= 0x7f)
    return uch;
  else
    return (guchar) "¿";
}

gint
fribidi_cap_rtl_to_unicode (guchar *s, FriBidiChar *us)
{
  gint i, j, len;

  len = strlen (s);
  j = 0;
  for (i = 0; i < len; i++)
    {
      guchar ch;

      ch = s[i];
      if (ch == '_')
	{
	  switch (ch = s[++i])
	    {
	    case '>':
	      us[j++] = UNI_LRM;
	      break;
	    case '<':
	      us[j++] = UNI_RLM;
	      break;
	    case 'l':
	      us[j++] = UNI_LRE;
	      break;
	    case 'r':
	      us[j++] = UNI_RLE;
	      break;
	    case 'o':
	      us[j++] = UNI_PDF;
	      break;
	    case 'L':
	      us[j++] = UNI_LRO;
	      break;
	    case 'R':
	      us[j++] = UNI_RLO;
	      break;
	    case '_':
	      us[j++] = '_';
	      break;
	    default:
	      us[j++] = '_';
	      i--;
	      break;
	    }
	}
      else
	us[j++] = s[i];
    }

  return j;
}

gint
fribidi_unicode_to_cap_rtl (FriBidiChar *us, gint length, guchar *s)
{
  gint i, j;

  j = 0;
  for (i = 0; i < length; i++)
    {
      FriBidiChar ch = us[i];
      if (!FRIBIDI_IS_EXPLICIT (fribidi_get_type (ch)) && ch != '_'
	  && ch != UNI_LRM && ch != UNI_RLM)
	{
	  if (ch < 256)
	    s[j++] = ch;
	  else
	    s[j++] = '¿';
	}
      else
	{
	  s[j++] = '_';
	  switch (ch)
	    {
	    case UNI_LRM:
	      s[j++] = '>';
	      break;
	    case UNI_RLM:
	      s[j++] = '<';
	      break;
	    case UNI_LRE:
	      s[j++] = 'l';
	      break;
	    case UNI_RLE:
	      s[j++] = 'r';
	      break;
	    case UNI_PDF:
	      s[j++] = 'o';
	      break;
	    case UNI_LRO:
	      s[j++] = 'L';
	      break;
	    case UNI_RLO:
	      s[j++] = 'R';
	      break;
	    case '_':
	      s[j++] = '_';
	      break;
	    default:
	      j--;
	      if (ch < 256)
		s[j++] = ch;
	      else
		s[j++] = '¿';
	      break;
	    }
	}
    }
  s[j] = 0;

  return j;
}

guchar *
fribidi_char_set_desc_cap_rtl (void)
{
  return
    "CapRTL is a character set for testing with the reference\n" \
    "implementation, with explicit marks escape strings, and\n" \
    "the property that contains all unicode character types in\n" \
    "ASCII range 0-127.\n" \
    "\n"
    "CapRTL's character types:\n"
    "  * 0x00    ON    * 0x01 ^A ON    * 0x02 ^B ON    * 0x03 ^C ON    \n"
    "  * 0x04 ^D LTR   * 0x05 ^E RTL   * 0x06 ^F ON    * 0x07 ^G ON    \n"
    "  * 0x08 ^H ON    * 0x09 ^I ON    * 0x0a ^J ON    * 0x0b ^K ON    \n"
    "  * 0x0c ^L ON    * 0x0d ^M BS    * 0x0e ^N RLO   * 0x0f ^O RLE   \n"
    "  * 0x10 ^P LRO   * 0x11 ^Q LRE   * 0x12 ^R PDF   * 0x13 ^S WS    \n"
    "  * 0x14 ^T ON    * 0x15 ^U ON    * 0x16 ^V ON    * 0x17 ^W ON    \n"
    "  * 0x18 ^X ON    * 0x19 ^Y ON    * 0x1a ^Z ON    * 0x1b    ON    \n"
    "  * 0x1c    ON    * 0x1d    ON    * 0x1e    ON    * 0x1f    ON    \n"
    "  * 0x20    WS    * 0x21 !  ON    * 0x22 \"  ON    * 0x23 #  ON    \n"
    "  * 0x24 $  ET    * 0x25 %  ON    * 0x26 &  ON    * 0x27 '  ON    \n"
    "  * 0x28 (  ON    * 0x29 )  ON    * 0x2a *  ON    * 0x2b +  ET    \n"
    "  * 0x2c ,  CS    * 0x2d -  ON    * 0x2e .  ES    * 0x2f /  ES    \n"
    "  * 0x30 0  EN    * 0x31 1  EN    * 0x32 2  EN    * 0x33 3  EN    \n"
    "  * 0x34 4  EN    * 0x35 5  EN    * 0x36 6  AN    * 0x37 7  AN    \n"
    "  * 0x38 8  AN    * 0x39 9  AN    * 0x3a :  CS    * 0x3b ;  ON    \n"
    "  * 0x3c <  ON    * 0x3d =  ON    * 0x3e >  ON    * 0x3f ?  ON    \n"
    "  * 0x40 @  RTL   * 0x41 A  AL    * 0x42 B  AL    * 0x43 C  AL    \n"
    "  * 0x44 D  AL    * 0x45 E  AL    * 0x46 F  AL    * 0x47 G  RTL   \n"
    "  * 0x48 H  RTL   * 0x49 I  RTL   * 0x4a J  RTL   * 0x4b K  RTL   \n"
    "  * 0x4c L  RTL   * 0x4d M  RTL   * 0x4e N  RTL   * 0x4f O  RTL   \n"
    "  * 0x50 P  RTL   * 0x51 Q  RTL   * 0x52 R  RTL   * 0x53 S  RTL   \n"
    "  * 0x54 T  RTL   * 0x55 U  RTL   * 0x56 V  RTL   * 0x57 W  RTL   \n"
    "  * 0x58 X  RTL   * 0x59 Y  RTL   * 0x5a Z  RTL   * 0x5b [  ON    \n"
    "  * 0x5c \\  BS    * 0x5d ]  ON    * 0x5e ^  ON    * 0x5f _  ON    \n"
    "  * 0x60 `  NSM   * 0x61 a  LTR   * 0x62 b  LTR   * 0x63 c  LTR   \n"
    "  * 0x64 d  LTR   * 0x65 e  LTR   * 0x66 f  LTR   * 0x67 g  LTR   \n"
    "  * 0x68 h  LTR   * 0x69 i  LTR   * 0x6a j  LTR   * 0x6b k  LTR   \n"
    "  * 0x6c l  LTR   * 0x6d m  LTR   * 0x6e n  LTR   * 0x6f o  LTR   \n"
    "  * 0x70 p  LTR   * 0x71 q  LTR   * 0x72 r  LTR   * 0x73 s  LTR   \n"
    "  * 0x74 t  LTR   * 0x75 u  LTR   * 0x76 v  LTR   * 0x77 w  LTR   \n"
    "  * 0x78 x  LTR   * 0x79 y  LTR   * 0x7a z  LTR   * 0x7b {  ON    \n"
    "  * 0x7c |  SS    * 0x7d }  ON    * 0x7e ~  WS    * 0x7f    ON    \n"
    "\n"
    "Escape sequences:\n"
    "  Character `_' is used to escape explicit marks. The list is:\n"
    "    * _>  LRM\n"
    "    * _<  RLM\n"
    "    * _l  LRE\n"
    "    * _r  RLE\n"
    "    * _o  PDF\n"
    "    * _L  LRO\n" "    * _R  RLO\n" "    * __  `_' itself\n" "\n";
}

#define WS FRIBIDI_PROP_TYPE_WS
#define BS FRIBIDI_PROP_TYPE_BS
#define EO FRIBIDI_PROP_TYPE_EO
#define CTL FRIBIDI_PROP_TYPE_CTL
#define LRE FRIBIDI_PROP_TYPE_LRE
#define RLE FRIBIDI_PROP_TYPE_RLE
#define ES FRIBIDI_PROP_TYPE_ES
#define LRO FRIBIDI_PROP_TYPE_LRO
#define RLO FRIBIDI_PROP_TYPE_RLO
#define AL FRIBIDI_PROP_TYPE_AL
#define SS FRIBIDI_PROP_TYPE_SS
#define ET FRIBIDI_PROP_TYPE_ET
#define NSM FRIBIDI_PROP_TYPE_NSM
#define LTR FRIBIDI_PROP_TYPE_LTR
#define ON FRIBIDI_PROP_TYPE_ON
#define AN FRIBIDI_PROP_TYPE_AN
#define BN FRIBIDI_PROP_TYPE_BN
#define RTL FRIBIDI_PROP_TYPE_RTL
#define CS FRIBIDI_PROP_TYPE_CS
#define PDF FRIBIDI_PROP_TYPE_PDF
#define EN FRIBIDI_PROP_TYPE_EN

FriBidiPropCharType FriBidiPropertyBlockCapRTL[256] = {
  /* CapRTL charset table. */
  ON, ON, ON, ON, LTR, RTL, ON, ON, ON, ON, ON, ON, ON, BS, RLO, RLE,	/*00-0f */
  LRO, LRE, PDF, WS, ON, ON, ON, ON, ON, ON, ON, ON, ON, ON, ON, ON,	/*10-1f */
  WS, ON, ON, ON, ET, ON, ON, ON, ON, ON, ON, ET, CS, ON, ES, ES,	/*20-2f */
  EN, EN, EN, EN, EN, EN, AN, AN, AN, AN, CS, ON, ON, ON, ON, ON,	/*30-3f */
  RTL, AL, AL, AL, AL, AL, AL, RTL, RTL, RTL, RTL, RTL, RTL, RTL, RTL, RTL,	/*40-4f */
  RTL, RTL, RTL, RTL, RTL, RTL, RTL, RTL, RTL, RTL, RTL, ON, BS, ON, ON, ON,	/*50-5f */
  NSM, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,	/*60-6f */
  LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, ON, SS, ON, WS, ON,	/*70-7f */
  /* These are not needed for the CapRTL charset, only to fill the table. */
  BN, BN, BN, BN, BN, BS, BN, BN, BN, BN, BN, BN, BN, BN, BN, BN,
  BN, BN, BN, BN, BN, BN, BN, BN, BN, BN, BN, BN, BN, BN, BN, BN,
  CS, ON, ET, ET, ET, ET, ON, ON, ON, ON, LTR, ON, ON, ON, ON, ON,
  ET, ET, EN, EN, ON, LTR, ON, ON, ON, EN, LTR, ON, ON, ON, ON, ON,
  LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
  LTR,
  LTR, LTR, LTR, LTR, LTR, LTR, LTR, ON, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
  LTR,
  LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
  LTR,
  LTR, LTR, LTR, LTR, LTR, LTR, LTR, ON, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
  LTR,
};

#undef WS
#undef BS
#undef EO
#undef CTL
#undef LRE
#undef RLE
#undef ES
#undef LRO
#undef RLO
#undef AL
#undef SS
#undef ET
#undef NSM
#undef LTR
#undef ON
#undef AN
#undef BN
#undef RTL
#undef CS
#undef PDF
#undef EN

gboolean
fribidi_char_set_enter_cap_rtl (void)
{
  FriBidiPropertyBlocks[0] = FriBidiPropertyBlockCapRTL;
  return TRUE;
}

gboolean
fribidi_char_set_leave_cap_rtl (void)
{
  FriBidiPropertyBlocks[0] = FriBidiPropertyBlock0000;
  return TRUE;
}
