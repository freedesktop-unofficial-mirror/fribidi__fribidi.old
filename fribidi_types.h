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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef FRIBIDI_TYPES_H
#define FRIBIDI_TYPES_H

#include <glib.h>

typedef guint32 FriBidiChar;

/* Define some bit masks, that character types are based on, each one has
   only one bit on. */
static enum
{
  FRIBIDI_MASK_RTL       = 0x00000001,  /* Is right to left */
  FRIBIDI_MASK_ARABIC    = 0x00000002,  /* Is arabic */

  /* Each char can be only one of the three following. */
  FRIBIDI_MASK_STRONG    = 0x00000010,  /* Is strong */
  FRIBIDI_MASK_WEAK      = 0x00000020,  /* Is weak */
  FRIBIDI_MASK_NEUTRAL   = 0x00000040,  /* Is neutral */
  FRIBIDI_MASK_SENTINEL  = 0x00000080,  /* Is sentinel: SOT, EOT */
  /* Sentinels are not valid chars, just identify the start and end of strings. */

  /* Each char can be only one of the five following. */
  FRIBIDI_MASK_LETTER    = 0x00000100,  /* Is letter: L, R, AL */
  FRIBIDI_MASK_NUMBER    = 0x00000200,  /* Is number: EN, AN */
  FRIBIDI_MASK_NUMSEPTER = 0x00000400,  /* Is number separator or terminator: ES, ET, CS */
  FRIBIDI_MASK_SPACE     = 0x00000800,  /* Is space: BN, BS, SS, WS */
  FRIBIDI_MASK_EXPLICIT  = 0x00001000,  /* Is expilict mark: LRE, RLE, LRO, RLO, PDF */

  /* Can be on only if FRIBIDI_MASK_SPACE is also on. */
  FRIBIDI_MASK_SEPARATOR = 0x00002000,  /* Is test separator: BS, SS */

  /* Can be on only if FRIBIDI_MASK_EXPLICIT is also on. */
  FRIBIDI_MASK_OVERRIDE  = 0x00004000,  /* Is explicit override: LRO, RLO */

  /* Can be on for SOT and EOT sentinels only, not a valid char if is on. */

  /* The following must be to make types pairwise different, some of them can
     be removed but are here because of efficiency (make queries faster). */

  FRIBIDI_MASK_ES        = 0x00010000,
  FRIBIDI_MASK_ET        = 0x00020000,
  FRIBIDI_MASK_CS        = 0x00040000,

  FRIBIDI_MASK_NSM       = 0x00080000,
  FRIBIDI_MASK_BN        = 0x00100000,

  FRIBIDI_MASK_BS        = 0x00200000,
  FRIBIDI_MASK_SS        = 0x00400000,
  FRIBIDI_MASK_WS        = 0x00800000,
} FRIBIDI_MASK;

typedef enum
{
  FRIBIDI_TYPE_LTR = /* Strong left to right */
    FRIBIDI_MASK_STRONG + FRIBIDI_MASK_LETTER,
  FRIBIDI_TYPE_RTL = /* Right to left characters */
    FRIBIDI_MASK_STRONG + FRIBIDI_MASK_LETTER +
    FRIBIDI_MASK_RTL,
  FRIBIDI_TYPE_AL  = /* Arabic characters */
    FRIBIDI_MASK_STRONG + FRIBIDI_MASK_LETTER +
    FRIBIDI_MASK_RTL + FRIBIDI_MASK_ARABIC,
  FRIBIDI_TYPE_LRE = /* Left-To-Right embedding */
    FRIBIDI_MASK_STRONG + FRIBIDI_MASK_EXPLICIT,
  FRIBIDI_TYPE_RLE = /* Right-To-Left embedding */
    FRIBIDI_MASK_STRONG + FRIBIDI_MASK_EXPLICIT +
    FRIBIDI_MASK_RTL,
  FRIBIDI_TYPE_LRO = /* Left-To-Right override */
    FRIBIDI_MASK_STRONG + FRIBIDI_MASK_EXPLICIT +
    FRIBIDI_MASK_OVERRIDE,
  FRIBIDI_TYPE_RLO = /* Right-To-Left override */
    FRIBIDI_MASK_STRONG + FRIBIDI_MASK_EXPLICIT +
    FRIBIDI_MASK_RTL + FRIBIDI_MASK_OVERRIDE,

  FRIBIDI_TYPE_PDF = /* Pop directional override */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_EXPLICIT,
  FRIBIDI_TYPE_EN  = /* European digit */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_NUMBER,
  FRIBIDI_TYPE_AN  = /* Arabic digit */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_NUMBER +
    FRIBIDI_MASK_ARABIC,
  FRIBIDI_TYPE_ES  = /* European number separator */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_NUMSEPTER +
    FRIBIDI_MASK_ES,
  FRIBIDI_TYPE_ET  = /* European number terminator */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_NUMSEPTER +
    FRIBIDI_MASK_ET,
  FRIBIDI_TYPE_CS  = /* Common Separator */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_NUMSEPTER +
    FRIBIDI_MASK_CS,
  FRIBIDI_TYPE_NSM = /* Non spacing mark */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_NSM,
  FRIBIDI_TYPE_BN  = /* Boundary neutral */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_SPACE +
    FRIBIDI_MASK_BN,

  FRIBIDI_TYPE_BS  = /* Block separator */
    FRIBIDI_MASK_NEUTRAL + FRIBIDI_MASK_SPACE +
    FRIBIDI_MASK_SEPARATOR + FRIBIDI_MASK_BS,
  FRIBIDI_TYPE_SS  = /* Segment separator */
    FRIBIDI_MASK_NEUTRAL + FRIBIDI_MASK_SPACE +
    FRIBIDI_MASK_SEPARATOR + FRIBIDI_MASK_SS,
  FRIBIDI_TYPE_WS  = /* Whitespace */
    FRIBIDI_MASK_NEUTRAL + FRIBIDI_MASK_SPACE +
    FRIBIDI_MASK_WS,
  FRIBIDI_TYPE_ON  = /* Other Neutral */
    FRIBIDI_MASK_NEUTRAL,

  /* The following are used to identify the paragraph direction,
     types L, R, N are not used internally anymore, and recommended to use
     LTR, RTL and ON instead, didn't removed because of compatability. */
  FRIBIDI_TYPE_L   = FRIBIDI_TYPE_LTR,
  FRIBIDI_TYPE_R   = FRIBIDI_TYPE_RTL,
  FRIBIDI_TYPE_N   = FRIBIDI_TYPE_ON,
  FRIBIDI_TYPE_WL  = /* Weak left to right */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_LETTER,    
  FRIBIDI_TYPE_WR  = /* Weak right to left */
    FRIBIDI_MASK_WEAK + FRIBIDI_MASK_LETTER +
    FRIBIDI_MASK_RTL,

  /* The following are only used internally */
  FRIBIDI_TYPE_SOT = /* Start of text */
    FRIBIDI_MASK_SENTINEL,
  FRIBIDI_TYPE_EOT = /* End of text */
    FRIBIDI_MASK_SENTINEL + FRIBIDI_MASK_RTL,
} FriBidiCharType;

/* Defining macros for needed queries, It is fully dependent on the 
   implementation of FriBidiCharType. */
   
/* Return the direction of the level number, FRIBIDI_TYPE_LTR for even and
   FRIBIDI_TYPE_RTL for odds. */
#define LEVEL_TO_DIR(lev) (FRIBIDI_TYPE_LTR | (lev & 1))

/* Return the minimum level of the direction, 0 for FRIBIDI_TYPE_LTR and
   1 for FRIBIDI_TYPE_RTL and FRIBIDI_TYPE_AL. */
#define DIR_TO_LEVEL(dir) (dir & 1)
  
/* Is right to left? */
#define IS_RTL(p)      ((P) & FRIBIDI_MASK_RTL)
/* Is arabic? */
#define IS_ARABIC(p)   ((p) & FRIBIDI_MASK_ARABIC)

/* Is strong? */
#define IS_STRONG(p)   ((p) & FRIBIDI_MASK_STRONG)
/* Is weak? */
#define IS_WEAK(p)     ((p) & FRIBIDI_MASK_WEAK)
/* Is neutral? */
#define IS_NEUTRAL(p)  ((p) & FRIBIDI_MASK_NEUTRAL)
/* Is sentinel? */
#define IS_SENTINEL(p) ((p) & FRIBIDI_MASK_SENTINEL)

/* Is letter: L, R, AL? */
#define IS_LETTER(p)   ((p) & FRIBIDI_MASK_LETTER)
/* Is number: EN, AN? */
#define IS_NUMBER(p)   ((p) & FRIBIDI_MASK_NUMBER)
/* Is number separator or terminator: ES, ET, CS? */
#define IS_NUMBER_SEPARATOR_OR_TERMINATOR(p) \
                       ((p) & FRIBIDI_MASK_NUMSEPTER)
/* Is space: BN, BS, SS, WS? */
#define IS_SPACE(p)    ((p) & FRIBIDI_MASK_SPACE)
/* Is explicit mark: LRE, RLE, LRO, RLO, PDF? */
#define IS_EXPLICIT(p) ((p) & FRIBIDI_MASK_EXPLICIT)

/* Is test separator: BS, SS? */
#define IS_SEPARATOR(p) ((p) & FRIBIDI_MASK_SEPARATOR)

/* Is explicit override: LRO, RLO? */
#define IS_OVERRIDE(p) ((p) & FRIBIDI_MASK_OVERRIDE)

/* Some more: */

/* Is left to right letter: LTR? */
#define IS_LTR_LETTER(p) \
    ((p) & (FRIBIDI_MASK_LETTER | FRIBIDI_MASK_RTL) == FRIBIDI_MASK_LETTER)

/* Is right to left letter: RTL, AL? */
#define IS_RTL_LETTER(p) \
    ((p) & (FRIBIDI_MASK_LETTER | FRIBIDI_MASK_RTL) == \
    (FRIBIDI_MASK_LETTER | FRIBIDI_MASK_RTL))

/* Is ES or CS: ES, CS? */
#define IS_ES_OR_CS(p) \
    ((p) & (FRIBIDI_MASK_ES | FRIBIDI_MASK_CS))

/* Is explicit or BN: LRE, RLE, LRO, RLO, PDF, BN? */
#define IS_EXPLICIT_OR_BN(p) \
    ((p) & (FRIBIDI_MASK_EXPLICIT | FRIBIDI_MASK_BN))
    
/* Is explicit or separator or BN or WS: LRE, RLE, LRO, RLO, PDF, BS, SS, BN, WS? */
#define IS_EXPLICIT_OR_SEPARATOR_OR_BN_OR_WS(p) \
    ((p) & (FRIBIDI_MASK_EXPLICIT | FRIBIDI_MASK_SEPARATOR | \
            FRIBIDI_MASK_BN | FRIBIDI_MASK_WS))

/* Define some conversions. */

/* Change numbers:EN, AN  to RTL. */
#define CHANGE_NUMBER_TO_RTL(p) \
    (IS_NUMBER(p) ? FRIBIDI_TYPE_RTL : (p))

/* Override status of an explicit mark: LRO->LTR, RLO->RTL, otherwise->ON. */
#define EXPLICIT_TO_OVERRIDE_DIR(p) \
    (IS_EXPLICIT(p) ? LEVEL_TO_DIR(DIR_TO_LEVEL(p)) : FRIBIDI_TYPE_ON)


#ifdef DEBUG
char char_from_type[] = {
  'L', 'R', 'l', 'r', '1', 'w', 'w', '9', 'w', 'P', 'S', '_', 'A',
  '.', '+', '+', '+', '+', '-', 'n', '?',
  'b', '?', '>', '<', 'n', 'e', '?', '?'
};
#endif

/* The following type is used by fribidi_utils */
typedef struct {
  int length;
  void *attribute;
} FriBidiRunType;

/* The following should be configuration parameters, once I can
   figure out how to make configure set them... */
#ifndef FRIBIDI_MAX_STRING_LENGTH
#define FRIBIDI_MAX_STRING_LENGTH 65535
#endif

#endif
