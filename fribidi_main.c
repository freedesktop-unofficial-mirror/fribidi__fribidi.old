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

/*======================================================================
//  A main program for fribidi.
//----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <getopt.h>
#include "fribidi.h"
#include "config.h"

#define appname "fribidi"
#define appversion VERSION

extern guchar *fribidi_version_info;

#define MAX_STR_LEN 65000

void
die (gchar * fmt, ...)
{
  va_list ap;
  va_start (ap, fmt);

  if (fmt)
    {
      fprintf (stderr, "%s: ", appname);
      vfprintf (stderr, fmt, ap);
    }
  fprintf (stderr, "Try `%s --help' for more information.\n", appname);
  exit (-1);
}

gboolean do_pad, do_fill, do_clean, show_input, show_visual;
gboolean show_basedir, show_ltov, show_vtol, show_levels, show_changes;
gint char_set, text_width;
guchar *bol_text, *eol_text;
FriBidiCharType input_base_direction;

void
help (void)
{
  gint i;

  printf
    ("Usage: " appname " [OPTION]... [FILE]...\n"
     "A command line interface for the " PACKAGE " library,\n"
     "Converts a logical string to visual.\n"
     "\n"
     "  -h, --help            Display this information and exit\n"
     "  -V, --version         Display version information and exit\n"
     "  -v, --verbose         Verbose mode, same as --basedir --ltov --vtol \\\n"
     "                        --levels --changes\n"
     "  -d, --debug           Output debug information\n"
     "  -t, --test            Test " PACKAGE ", same as --clean --fill --showinput\n"
     "  -c, --charset CS      Specify character set, default is %s\n"
     "  -C, --charsetdesc CS  Show descriptions for character set CS and exit\n"
     "      --caprtl          Old style: set character set to CapRTL\n"
     "      --showinput       Output the input string too\n"
     "      --nopad           Do not right justify RTL lines\n"
     "      --fill            Fill lines up to margin\n"
     "  -w, --width W         Screen width for padding, default is %d, but if \\\n"
     "                        enviroment variable COLUMNS is defined, its value \\\n"
     "                        will be used, --width overrides both of them.\n"
     "  -B, --bol BOL         Output string BOL before the visual string\n"
     "  -E, --eol EOL         Output string EOL after the visual string\n"
     "      --rtl             Force base direction to RTL\n"
     "      --ltr             Force base direction to LTR\n"
     "      --wrtl            Set base direction to RTL if no strong character found\n"
     "      --wltr            Set base direction to LTR if no strong character found \\\n"
     "                        (default)\n"
     "      --clean           Remove explicit format codes in visual string \\\n"
     "                        output, currently does not affect other outputs\n"
     "      --basedir         Output Base Direction\n"
     "      --ltov            Output Logical to Visual position map\n"
     "      --vtol            Output Visual to Logical position map\n"
     "      --levels          Output Embedding Levels\n"
     "      --changes         Output information about changes between \\\n"
     "                        logical and visual string (start, length)\n"
     "      --novisual        Do not output the visual string, to be used with \\\n"
     "                        --basedir, --ltov, --vtol, --levels, --changes\n"
     "  All string indexes are zero based\n"
     "\n"
     "Output:\n"
     "  For each line of input, output something like this:\n"
     "    [input-str` => '][BOL][[padding space]visual-str][EOL]\n"
     "    [\\n base-dir][\\n ltov-map][\\n vtol-map][\\n levels][\\n changes]\n"
     "\n"
     "Available character sets:\n", fribidi_char_set_name (char_set), text_width);
  for (i = 1; i <= FRIBIDI_CHAR_SETS_NUM; i++)
    printf ("  * %-10s: %-25s%1s\n",
	    fribidi_char_set_name (i), fribidi_char_set_title (i),
	    (fribidi_char_set_desc (i) ? "X" : ""));
  printf ("  X: Character set has descriptions, use --charsetdesc to see\n");
  printf
    ("\nReport bugs online at <http://fribidi.sourceforge.net/bugs.php>.\n");
  exit (0);
}

void
version (void)
{
  printf (appname " " appversion "\n%s", fribidi_version_info);
  exit (0);
}

int
main (int argc, char *argv[])
{
  int exit_val;
  gboolean file_found;
  char * s;
  FILE * IN;

  text_width = 80;
  do_pad = TRUE;
  do_fill = FALSE;
  do_clean = FALSE;
  show_input = FALSE;
  show_visual = TRUE;
  show_basedir = FALSE;
  show_ltov = FALSE;
  show_vtol = FALSE;
  show_levels = FALSE;
  show_changes = FALSE;
  char_set = FRIBIDI_CHARSET_DEFAULT;
  bol_text = NULL;
  eol_text = NULL;
  input_base_direction = FRIBIDI_TYPE_ON;

  if ((s = getenv ("COLUMNS")))
    {
      int i;

      i = atoi (s);
      if (i > 0)
	text_width = i;
    }


#define CHARSETDESC 257

  /* Parse the command line with getopt library */
  /* Must set argv[0], getopt uses it to generate error messages */
  argv[0] = appname;
  while (1)
    {
      int option_index = 0, c;
      static struct option long_options[] = {
	{"help", 0, 0, 'h'},
	{"version", 0, 0, 'V'},
	{"verbose", 0, 0, 'v'},
	{"debug", 0, 0, 'd'},
	{"test", 0, 0, 't'},
	{"charset", 1, 0, 'c'},
	{"charsetdesc", 1, 0, CHARSETDESC},
	{"caprtl", 0, (int *) &char_set, FRIBIDI_CHARSET_CAP_RTL},
	{"showinput", 0, &show_input, TRUE},
	{"nopad", 0, &do_pad, FALSE},
	{"fill", 0, &do_fill, TRUE},
	{"width", 1, 0, 'w'},
	{"bol", 1, 0, 'B'},
	{"eol", 1, 0, 'E'},
	{"clean", 0, &do_clean, TRUE},
	{"ltr", 0, (int *) &input_base_direction, FRIBIDI_TYPE_L},
	{"rtl", 0, (int *) &input_base_direction, FRIBIDI_TYPE_R},
	{"wltr", 0, (int *) &input_base_direction, FRIBIDI_TYPE_WL},
	{"wrtl", 0, (int *) &input_base_direction, FRIBIDI_TYPE_WR},
	{"basedir", 0, &show_basedir, TRUE},
	{"ltov", 0, &show_ltov, TRUE},
	{"vtol", 0, &show_vtol, TRUE},
	{"levels", 0, &show_levels, TRUE},
	{"changes", 0, &show_changes, TRUE},
	{"novisual", 0, &show_visual, FALSE},
	{0, 0, 0, 0}
      };

      c =
	getopt_long (argc, argv, "hVvdtc:w:B:E:", long_options,
		     &option_index);
      if (c == -1)
	break;

      switch (c)
	{
	case 0:
	  break;
	case 'h':
	  help ();
	  break;
	case 'V':
	  version ();
	  break;
	case 'v':
	  show_basedir = TRUE;
	  show_ltov = TRUE;
	  show_vtol = TRUE;
	  show_levels = TRUE;
	  show_changes = TRUE;
	  break;
	case 'w':
	  text_width = atoi (optarg);
	  if (text_width <= 0)
	    die ("invalid screen width `%s'\n", optarg);
	  break;
	case 'B':
	  bol_text = optarg;
	  break;
	case 'E':
	  eol_text = optarg;
	  break;
	case 'd':
	  if (!fribidi_set_debug (TRUE))
	    die
	      ("%s lib must be compiled with DEBUG option to enable\nturn debug info on.\n",
	       PACKAGE);
	  break;
	case 't':
	  do_fill = TRUE;
	  do_clean = TRUE;
	  show_input = TRUE;
	  break;
	case 'c':
	  char_set = fribidi_parse_charset (optarg);
	  if (!char_set)
	    die ("unrecognized character set `%s'\n", optarg);
	  break;
	case CHARSETDESC:
	  char_set = fribidi_parse_charset (optarg);
	  if (!char_set)
	    die ("unrecognized character set `%s'\n", optarg);
	  if (!fribidi_char_set_desc (char_set))
	    die ("no description available for character set `%s'\n",
		 fribidi_char_set_name (char_set));
	  else
	    printf ("Descriptions for character set %s:\n"
		    "\n" "%s", fribidi_char_set_title (char_set),
		    fribidi_char_set_desc (char_set));
	  exit (0);
	  break;
	case ':':
	case '?':
	  die (NULL);
	  break;
	default:
	  break;
	}
    }

  exit_val = 0;
  file_found = FALSE;
  while (optind < argc || !file_found)
    {
      char *S_;

      S_ = optind < argc ? argv[optind++] : "-";
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
	      fprintf (stderr, "%s: %s: no such file or directory\n",
		       appname, S_);
	      exit_val = 1;
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
	    char *new_line, *nl_found;
	    FriBidiChar logical[FRIBIDI_MAX_STRING_LENGTH];
	    FriBidiChar visual[FRIBIDI_MAX_STRING_LENGTH];
	    guchar outstring[MAX_STR_LEN];
	    FriBidiCharType base;
	    gboolean log2vis;
	    int len, i, j, k;

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
	      FriBidiStrIndex *ltov, *vtol;
	      guint8 *levels;
	      gint new_len;

	      if (show_ltov)
		ltov = g_new (FriBidiStrIndex, len + 1);
	      else
		ltov = NULL;
	      if (show_vtol)
		vtol = g_new (FriBidiStrIndex, len + 1);
	      else
		vtol = NULL;
	      if (show_levels)
		levels = g_new (guint8, len + 1);
	      else
		levels = NULL;


	      /* Create a bidi string. */
	      base = input_base_direction;
	      log2vis = fribidi_log2vis (logical, len, &base,
					 /* output */
					 visual, ltov, vtol, levels);
	      if (log2vis)
		{

		  if (show_input)
		    {
		      printf ("%-*s => ", padding_width, S_);
		    }

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

		      if (*outstring && do_pad)
			if (base == FRIBIDI_TYPE_RTL)
			  {
			    j = strlen (outstring);
			    k = (j - 1) % padding_width + 1;
			    for (i = (j - 1) / padding_width - 1; i >= 0; i--)
			      printf ("%.*s\n", padding_width,
				      outstring + (i * padding_width + k));
			    printf ("%*.*s", padding_width, k, outstring);
			  }
			else
			  {
			    j = strlen (outstring);
			    k = (j - 1) % padding_width + 1;
			    for (i = 0; i < (j - 1) / padding_width; i++)
			      printf ("%.*s\n", padding_width,
				      outstring + (i * padding_width));
			    printf ("%-*.*s", (do_fill ? padding_width : 0),
				    k, outstring + (j - k));
			  }
		      else
			printf ("%s", outstring);
		      if (eol_text)
			printf ("%s", eol_text);

		      nl_found = "\n";
		    }
		  if (show_basedir)
		    {
		      printf (nl_found);
		      printf ("Base direction: %s",
			      (FRIBIDI_DIR_TO_LEVEL (base) ? "R" : "L"));
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
		      printf ("%sChange start[length] = %d[%d]", nl_found,
			      change_start, change_len);
		      nl_found = "\n";
		    }
		}
	      else
		{
		  exit_val = 2;
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

  return exit_val;
}
