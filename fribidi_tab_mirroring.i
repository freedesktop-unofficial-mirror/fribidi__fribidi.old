/*
  This file was automatically created from BidiMirroring.txt, version 3.2.0
  by fribidi_create_mirroring
*/

#ifndef FRIBIDI_TAB_MIRRORING_I
#define FRIBIDI_TAB_MIRRORING_I

#include "fribidi.h"

/*
  Mirrored characters include all the characters in the Unicode list
  that have been declared as being mirrored and that have a mirrored
  equivalent.

  There are lots of characters that are designed as being mirrored
  but do not have any mirrored glyph, e.g. the sign for there exist.
  Are these used in Arabic? That is are all the mathematical signs
  that are assigned to be mirrorable actually mirrored in Arabic?
  If that is the case, we'll change the below code to include also
  characters that mirror to themself. It will then be the responsibility
  of the display engine to actually mirror these.
*/

/* *INDENT-OFF* */

static const struct
{
  FriBidiChar ch, mirrored_ch;
}
FriBidiMirroredChars[] =
{
  {0x0028, 0x0029},
  {0x0029, 0x0028},
  {0x003C, 0x003E},
  {0x003E, 0x003C},
  {0x005B, 0x005D},
  {0x005D, 0x005B},
  {0x007B, 0x007D},
  {0x007D, 0x007B},
  {0x00AB, 0x00BB},
  {0x00BB, 0x00AB},
  {0x2039, 0x203A},
  {0x203A, 0x2039},
  {0x2045, 0x2046},
  {0x2046, 0x2045},
  {0x207D, 0x207E},
  {0x207E, 0x207D},
  {0x208D, 0x208E},
  {0x208E, 0x208D},
  {0x2208, 0x220B},
  {0x2209, 0x220C},
  {0x220A, 0x220D},
  {0x220B, 0x2208},
  {0x220C, 0x2209},
  {0x220D, 0x220A},
  {0x223C, 0x223D},
  {0x223D, 0x223C},
  {0x2243, 0x22CD},
  {0x2252, 0x2253},
  {0x2253, 0x2252},
  {0x2254, 0x2255},
  {0x2255, 0x2254},
  {0x2264, 0x2265},
  {0x2265, 0x2264},
  {0x2266, 0x2267},
  {0x2267, 0x2266},
  {0x2268, 0x2269},
  {0x2269, 0x2268},
  {0x226A, 0x226B},
  {0x226B, 0x226A},
  {0x226E, 0x226F},
  {0x226F, 0x226E},
  {0x2270, 0x2271},
  {0x2271, 0x2270},
  {0x2272, 0x2273},
  {0x2273, 0x2272},
  {0x2274, 0x2275},
  {0x2275, 0x2274},
  {0x2276, 0x2277},
  {0x2277, 0x2276},
  {0x2278, 0x2279},
  {0x2279, 0x2278},
  {0x227A, 0x227B},
  {0x227B, 0x227A},
  {0x227C, 0x227D},
  {0x227D, 0x227C},
  {0x227E, 0x227F},
  {0x227F, 0x227E},
  {0x2280, 0x2281},
  {0x2281, 0x2280},
  {0x2282, 0x2283},
  {0x2283, 0x2282},
  {0x2284, 0x2285},
  {0x2285, 0x2284},
  {0x2286, 0x2287},
  {0x2287, 0x2286},
  {0x2288, 0x2289},
  {0x2289, 0x2288},
  {0x228A, 0x228B},
  {0x228B, 0x228A},
  {0x228F, 0x2290},
  {0x2290, 0x228F},
  {0x2291, 0x2292},
  {0x2292, 0x2291},
  {0x22A2, 0x22A3},
  {0x22A3, 0x22A2},
  {0x22B0, 0x22B1},
  {0x22B1, 0x22B0},
  {0x22B2, 0x22B3},
  {0x22B3, 0x22B2},
  {0x22B4, 0x22B5},
  {0x22B5, 0x22B4},
  {0x22B6, 0x22B7},
  {0x22B7, 0x22B6},
  {0x22C9, 0x22CA},
  {0x22CA, 0x22C9},
  {0x22CB, 0x22CC},
  {0x22CC, 0x22CB},
  {0x22CD, 0x2243},
  {0x22D0, 0x22D1},
  {0x22D1, 0x22D0},
  {0x22D6, 0x22D7},
  {0x22D7, 0x22D6},
  {0x22D8, 0x22D9},
  {0x22D9, 0x22D8},
  {0x22DA, 0x22DB},
  {0x22DB, 0x22DA},
  {0x22DC, 0x22DD},
  {0x22DD, 0x22DC},
  {0x22DE, 0x22DF},
  {0x22DF, 0x22DE},
  {0x22E0, 0x22E1},
  {0x22E1, 0x22E0},
  {0x22E2, 0x22E3},
  {0x22E3, 0x22E2},
  {0x22E4, 0x22E5},
  {0x22E5, 0x22E4},
  {0x22E6, 0x22E7},
  {0x22E7, 0x22E6},
  {0x22E8, 0x22E9},
  {0x22E9, 0x22E8},
  {0x22EA, 0x22EB},
  {0x22EB, 0x22EA},
  {0x22EC, 0x22ED},
  {0x22ED, 0x22EC},
  {0x22F0, 0x22F1},
  {0x22F1, 0x22F0},
  {0x2308, 0x2309},
  {0x2309, 0x2308},
  {0x230A, 0x230B},
  {0x230B, 0x230A},
  {0x2329, 0x232A},
  {0x232A, 0x2329},
  {0x3008, 0x3009},
  {0x3009, 0x3008},
  {0x300A, 0x300B},
  {0x300B, 0x300A},
  {0x300C, 0x300D},
  {0x300D, 0x300C},
  {0x300E, 0x300F},
  {0x300F, 0x300E},
  {0x3010, 0x3011},
  {0x3011, 0x3010},
  {0x3014, 0x3015},
  {0x3015, 0x3014},
  {0x3016, 0x3017},
  {0x3017, 0x3016},
  {0x3018, 0x3019},
  {0x3019, 0x3018},
  {0x301A, 0x301B},
  {0x301B, 0x301A},
} ;

/* *INDENT-ON* */

const int nFriBidiMirroredChars = 140;


#endif /* FRIBIDI_TAB_MIRRORING_I */
