/* Generate fully random tests. */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int lev = 0, len = 0, minlen;

void
letter ()
{

  char rl = (rand () % 2 ? 'a' : 'A');
  int i, j = rand () % 5;

  len += j;

  for (i = 0; i < j; i++)
    putchar (rl + rand () % 26);

}

void
number ()
{

  int i, j = rand () % 5;

  len += j;

  switch (rand () % 16)
    {
    case 10:
      putchar ('[');
      break;
    case 11:
      putchar (']');
      break;
    case 12:
      putchar ('{');
      break;
    case 13:
      putchar ('}');
      break;
    case 14:
      putchar ('(');
      break;
    case 15:
      putchar (')');
      break;

    default:
      for (i = 0; i < j; i++)
	putchar ('0' + rand () % 6);
      break;
    }

}

void
gen ()
{

  int f = 1;

  while (f)
    switch (rand () % 12)
      {
      case 0:
	len += 2;
	printf ("_R");
	gen ();
	printf ("_o");
	break;
      case 1:
	len += 2;
	printf ("_r");
	gen ();
	printf ("_o");
	break;
      case 2:
	len += 2;
	printf ("_L");
	gen ();
	printf ("_o");
	break;
      case 3:
	len += 2;
	printf ("_l");
	gen ();
	printf ("_o");
	break;

      case 4:
	len++;
	letter ();
	letter ();
	printf (" ");
	break;
      case 5:
	number ();
	break;
      case 6:
	len++;
	printf (" ");
	break;

      default:
	letter ();
	if (len << lev > minlen)
	  f = 0;
	break;
      }

}

int
main (int argc, char **argv)
{

  if (argv[1])
    minlen = atoi (argv[1]);
  else
    minlen = 1;
  srand ((int) (time) (NULL));
  gen ();
  printf ("\n");

}
