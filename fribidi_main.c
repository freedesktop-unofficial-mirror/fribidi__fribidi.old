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

/*======================================================================
//  A main program for fribidi.
//----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "fribidi.h"

#define appname "fribidi"

#define MAX_STR_LEN 65000

void
die (gchar * fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);

  fprintf (stderr, "%s: ", appname);
  vfprintf (stderr, fmt, ap);
  fprintf (stderr, "Try `%s --help' for more information.\n", appname);
  exit (-1);
}

int
main (int argc, char *argv[])
{
  int argp;
  FILE *IN;
  gboolean do_pad, do_fill, do_clean, file_found, show_input;
  gboolean show_visual, show_ltov, show_vtol, show_levels, show_changes;
  gint char_set, text_width;
  guchar *bol_text, *eol_text;
  FriBidiCharType input_base_direction;

  argp = 1;
  text_width = 80;
  do_pad = TRUE;
  do_fill = FALSE;
  do_clean = FALSE;
  show_input = FALSE;
  show_visual = TRUE;
  show_ltov = FALSE;
  show_vtol = FALSE;
  show_levels = FALSE;
  show_changes = FALSE;
  char_set = FRIBIDI_CHARSET_DEFAULT;
  bol_text = NULL;
  eol_text = NULL;
  input_base_direction = FRIBIDI_TYPE_ON;
  file_found = FALSE;

#define CASE(s) if (strcmp (S_, (s)) == 0)
#define CASE2(s1, s2) if (strcmp (S_, (s1)) == 0 || strcmp (S_, (s2)) == 0)
#define NEXTARG (argp++, argp - 1 < argc ? argv[argp - 1] : "")

  /* Parse the command line */
  while (argp < argc || (argp == argc && !file_found))
    {
      gchar *S_;

      if (argp < argc)
	S_ = argv[argp++];
      else
	S_ = "-";

      if (S_[0] == '-' && S_[1])
	{
	  CASE2 ("-?", "--help")
	  {
	    gint i;

	    printf
	      ("Usage: %s [OPTION]... [FILE]...\n"
	       "A command line interface for the %s library,\n"
	       "Converts a logical string to visual.\n"
	       "\n"
	       "  -?, --help            Display this information and exit\n"
	       "  -V, --version         Display version information and exit\n"
	       "  -d, --debug           Output debug info\n"
	       "  -t, --test            Set default character set to CapRTL, turn on padding\n"
	       "      --showinput       Output the input string too\n"
	       "  -C, --charset CS      Specify character set, default is %s\n"
	       "      --charsetdesc CS  Show descreptions for character set CS, if any and exit\n"
	       "  -p, --nopad           Do not right justify RTL lines\n"
	       "  -f, --fill            Fill lines up to margin\n"
	       "  -W, --width W         Screem width for padding, default is %d\n"
	       "  -B, --bol BOL         Output string BOL before the visual string\n"
	       "  -E, --eol EOL         Output string EOL after the visual string\n"
	       "  -R, --rtl             Force base direction to RTL\n"
	       "  -L, --ltr             Force base direction to LTR\n"
	       "  -c, --clean           Remove explicit format codes in visual string\n"
	       "                        output, currently does not affect other outputs\n"
	       "      --ltov            Output Logical to Visual position map\n"
	       "      --vtol            Output Visual to Logical position map\n"
	       "      --levels          Output Embedding Levels\n"
	       "      --changes         Output information about changes between\n"
	       "                        logical and visual string (start, length)\n"
	       "      --novisual        Do not output the visual string, to be used\n"
	       "                        with --ltov, --vtol, --levels, --changes\n"
	       "  Options affect only subsequent arguments\n"
	       "\n"
	       "Output:\n"
	       "  For each line of input, output something like this:\n"
	       "    [BOL][input-str` => '][[padding space]visual-str]\n"
	       "    [\\n ltov-map][\\n vtol-map][\\n levels][\\n changes][EOL]\n"
	       "\n"
	       "Available character sets are:\n", appname, appname,
	       fribidi_char_set_name (char_set), text_width);
	    for (i = 1; i <= FRIBIDI_CHAR_SETS_NUM; i++)
	      printf ("  * %-23s%-4s%s", fribidi_char_set_title (i),
		      (fribidi_char_set_desc (i) ? "X" : ""),
		      (i & 1 ? "" : "\n"));
	    if (FRIBIDI_CHAR_SETS_NUM & 1)
	      printf ("\n");
	    printf
	      ("  X: Character set has descreptions, use --charsetdesc to see\n");
	    printf
	      ("\nReport bugs online at <http://fribidi.sourceforge.net/bugs.php>.\n");
	    exit (0);
	  }
	  CASE2 ("-V", "--version")
	  {
	    printf
	      ("%s %s\n"
	       "Copyright (C) 2001 FriBidi Project.\n"
	       "%s comes with NO WARRANTY, to the extent permitted by law.\n"
	       "You may redistribute copies of %s under the terms of\n"
	       "the GNU General Public License.\n"
	       "For more information about these matters, see the files name COPYING.\n",
	       appname, VERSION, appname, appname);
	    exit (0);
	  }
	  CASE2 ("-p", "--nopad")
	  {
	    do_pad = FALSE;
	    continue;
	  }
	  CASE2 ("-W", "--width")
	  {
	    text_width = atoi (NEXTARG);
	    continue;
	  }
	  CASE2 ("-E", "--eol")
	  {
	    eol_text = NEXTARG;
	    continue;
	  }
	  CASE2 ("-B", "--bol")
	  {
	    bol_text = NEXTARG;
	    continue;
	  }
	  CASE2 ("-R", "--rtl")
	  {
	    input_base_direction = FRIBIDI_TYPE_RTL;
	    continue;
	  }
	  CASE2 ("-L", "--ltr")
	  {
	    input_base_direction = FRIBIDI_TYPE_LTR;
	    continue;
	  }
	  CASE2 ("-f", "--fill")
	  {
	    do_fill = TRUE;
	    continue;
	  }
	  CASE2 ("-c", "--clean")
	  {
	    do_clean = TRUE;
	    continue;
	  }
	  CASE ("--showinput")
	  {
	    show_input = TRUE;
	    continue;
	  }
	  CASE ("--ltov")
	  {
	    show_ltov = TRUE;
	    continue;
	  }
	  CASE ("--vtol")
	  {
	    show_vtol = TRUE;
	    continue;
	  }
	  CASE ("--levels")
	  {
	    show_levels = TRUE;
	    continue;
	  }
	  CASE ("--changes")
	  {
	    show_changes = TRUE;
	    continue;
	  }
	  CASE2 ("-K", "--novisual")
	  {
	    show_visual = FALSE;
	    continue;
	  }
	  CASE2 ("-d", "--debug")
	  {
	    if (!fribidi_set_debug (TRUE))
	      die
		("%s lib must be compiled with DEBUG option to enable\nturn debug info on.\n",
		 PACKAGE);
	    continue;
	  }
	  CASE2 ("-t", "--test")
	  {
	    char_set = FRIBIDI_CHARSET_CAP_RTL;
	    do_pad = TRUE;
	    continue;
	  }
	  CASE2 ("-C", "--charset")
	  {
	    S_ = NEXTARG;
	    char_set = fribidi_parse_charset (S_);
	    if (!char_set)
	      die ("unrecognized charset `%s'\n", S_);
	    continue;
	  }
	  CASE ("--charsetdesc")
	  {
	    guchar *comment;

	    S_ = NEXTARG;
	    char_set = fribidi_parse_charset (S_);
	    if (!char_set)
	      die ("unrecognized character set `%s'\n", S_);
	    S_ = fribidi_char_set_name (char_set);
	    comment = fribidi_char_set_desc (char_set);
	    if (!comment)
	      die ("no description available for character set `%s'\n", S_);
	    else
	      printf ("Descriptions for character set %s:\n"
		      "\n" "%s", fribidi_char_set_title (char_set), comment);

	    exit (0);
	  }
	  die ("unrecognized option `%s'\n", S_);
	}
      else
	{
	  file_found = TRUE;

	  /* Open the infile for reading */
	  if (S_[0] == '-' && !S_[1])
	    {
	      IN = stdin;
	    }
	  else
	    {
	      IN = fopen (S_, "r");
	      if (!IN)
		{
		  fprintf (stderr, "%s: %s: No such file or directory\n",
			   appname, S_);
		  continue;
		}
	    }

	  /* Read and process input one line at a time */
	  {
	    guchar S_[MAX_STR_LEN];
	    gint padding_width;

	    if (show_input)
	      padding_width = (text_width - 10) / 2;
	    else
	      padding_width = text_width;

	    while (fgets (S_, sizeof (S_) - 1, IN))
	      {
		int len;
		char *new_line, *nl_found;
		FriBidiChar logical[FRIBIDI_MAX_STRING_LENGTH];
		FriBidiChar visual[FRIBIDI_MAX_STRING_LENGTH];
		guchar outstring[MAX_STR_LEN];
		FriBidiCharType base;
		int i, j, k;

		nl_found = "";
		S_[sizeof (S_) - 1] = 0;
		len = strlen (S_);
		/* chop */
		if (S_[len - 1] == '\n')
		  {
		    len--;
		    S_[len] = '\0';
		    new_line = "\n";
		  }
		else
		  {
		    new_line = "";
		  }

		len = fribidi_charset_to_unicode (char_set, S_, logical);

		{
		  guint16 *ltov, *vtol;
		  guint8 *levels;
		  gint new_len;

		  if (show_ltov)
		    ltov = g_new (guint16, len + 1);
		  else
		    ltov = NULL;
		  if (show_vtol)
		    vtol = g_new (guint16, len + 1);
		  else
		    vtol = NULL;
		  if (show_levels)
		    levels = g_new (guint8, len + 1);
		  else
		    levels = NULL;

		  if (show_input)
		    {
		      printf ("%-*s => ", padding_width, S_);
		    }

		  /* Create a bidi string. */
		  base = input_base_direction;
		  fribidi_log2vis (logical, len, &base,
				   /* output */
				   visual, ltov, vtol, levels);

		  new_len = len;
		  if (show_visual)
		    {
		      printf (nl_found);

		      if (bol_text)
			printf ("%s", bol_text);

		      /* Remove explicit marks, if asked for. */
		      if (do_clean)
			len = fribidi_remove_explicits (visual, len);

		      /* Convert it to something to print. */
		      new_len = fribidi_unicode_to_charset (char_set, visual,
							    len, outstring);

		      if (base == FRIBIDI_TYPE_RTL && do_pad && *outstring)
			{
			  j = strlen (outstring);
			  k = (j - 1) % padding_width + 1;
			  for (i = (j - 1) / padding_width - 1; i >= 0; i--)
			    printf ("%.*s", padding_width,
				    outstring + (i * padding_width + k));
			  printf ("%*.*s", padding_width, k, outstring);
			}
		      else
			{
			  printf ("%s", outstring);
			  if (do_fill)
			    {
			      j = strlen (outstring);
			      k = padding_width - j % padding_width;
			      if (k)
				printf ("%*s", k, "");
			    }
			}
		      if (eol_text)
			printf ("%s", eol_text);

		      nl_found = "\n";
		    }
		  if (show_ltov)
		    {
		      gint i;

		      printf (nl_found);
		      for (i = 0; i < len; i++)
			printf ("%d ", ltov[i]);
		      nl_found = "\n";
		    }
		  if (show_vtol)
		    {
		      gint i;

		      printf (nl_found);
		      for (i = 0; i < len; i++)
			printf ("%d ", vtol[i]);
		      nl_found = "\n";
		    }
		  if (show_levels)
		    {
		      gint i;

		      printf (nl_found);
		      for (i = 0; i < len; i++)
			printf ("%d ", levels[i]);
		      nl_found = "\n";
		    }
		  if (show_changes)
		    {
		      int change_start, change_len;
		      fribidi_find_string_changes (logical, len,
						   visual, new_len,
						   &change_start,
						   &change_len);
		      printf ("%sChange start[length] = %d[%d]",
			      nl_found, change_start, change_len);
		      nl_found = "\n";
		    }

		  if (show_ltov)
		    g_free (ltov);
		  if (show_vtol)
		    g_free (vtol);
		  if (show_levels)
		    g_free (levels);
		}

		if (*nl_found)
		  printf (new_line);
	      }
	  }
	}
    }
  return 0;
}
