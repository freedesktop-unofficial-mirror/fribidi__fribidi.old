/* Generate random test data for CapRTL character set. */
/* A sequence of fully random characters. */
/* First command line parameter is the length of test in bytes, default is 10.*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int
main (int argc, char **argv)
{

  int i, j, len;
  char c;

  if (argv[1])
    len = atoi (argv[1]);
  else
    len = 10;
  srand ((int) (time) (NULL));

  for (i = 0; i < len; i++)
    {
      c = rand () % (0x80 - 0x0E) + 0x0E;
      switch (c)
	{
	case 0x60:		// rule L3 is not implemented in fribidi yet
	case 0x3C:
	case 0x5F:		// used as a escape char
	case 0x13:		// bidiref doesn't work proper with this
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1A:
	case 0x1B:
	case 0x1C:
	case 0x1D:
	case 0x1E:
	case 0x1F:
	case 0x00:
	  i--;
	  break;
	default:
	  putchar (c);
	}
    }

  printf ("\n");
}
