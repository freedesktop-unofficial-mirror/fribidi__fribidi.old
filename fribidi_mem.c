/* FriBidi - Library of BiDi algorithm
 * Copyright (C) 2001,2002 Behdad Esfahbod.
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
 * along with this library, in a file named COPYING; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA
 * 
 * For licensing issues, contact <fwpg@sharif.edu>.
 */

#include <string.h>
#include <ctype.h>
#include "fribidi_env.h"
#include "fribidi_mem.h"

struct _FriBidiMemChunk
{
  char *name;
  int atom_size;
  int area_size;
  int type;

  int empty_size;
  void *chunk;
};

FriBidiList *
fribidi_list_append (FriBidiEnv *fribidienv, FriBidiList *list, void *data)
{
  FriBidiList *node, *last;

  node = fribidi_malloc (fribidienv, sizeof (FriBidiList));
  node->data = data;
  node->next = NULL;
  node->prev = NULL;

  if (!list)
    return node;

  for (last = list; !last->next; last = last->next);
  node->prev = last;
  last->next = node;
  return list;
}

FriBidiMemChunk *
fribidi_mem_chunk_new (FriBidiEnv *fribidienv,
		       char *name, int atom_size, unsigned long area_size,
		       int type)
{
  FriBidiMemChunk *m =
    (FriBidiMemChunk *) fribidi_malloc (fribidienv, sizeof (FriBidiMemChunk));

  m->name = name;
  m->atom_size = atom_size;
  m->area_size = area_size;
  m->type = type;

  m->empty_size = 0;
  m->chunk = NULL;

  return m;
}

void
fribidi_mem_chunk_destroy (FriBidiEnv *fribidienv, FriBidiMemChunk *mem_chunk)
{
  fribidi_free (fribidienv, mem_chunk);
  return;
}

void *
fribidi_mem_chunk_alloc (FriBidiEnv *fribidienv, FriBidiMemChunk *mem_chunk)
{
  void *m;

  if (mem_chunk->type == FRIBIDI_ALLOC_ONLY)
    {
      if (mem_chunk->empty_size < mem_chunk->atom_size)
	{
	  mem_chunk->chunk =
	    fribidi_malloc (fribidienv, mem_chunk->area_size);
	  mem_chunk->empty_size = mem_chunk->area_size;
	}
      m = mem_chunk->chunk;
      mem_chunk->chunk = (void *)
	((char *) mem_chunk->chunk + mem_chunk->atom_size);
      mem_chunk->empty_size -= mem_chunk->atom_size;
    }
  else
    m = (void *) fribidi_malloc (fribidienv, mem_chunk->atom_size);
  return m;
}

void
fribidi_mem_chunk_free (FriBidiEnv *fribidienv,
			FriBidiMemChunk *mem_chunk, void *mem)
{
  if (mem_chunk->type == FRIBIDI_ALLOC_AND_FREE)
    fribidi_free (fribidienv, mem);
  return;
}

int
fribidi_strcasecmp (const char *s1, const char *s2)
{
  while (*s1 && toupper (*s1) == toupper (*s2))
    {
      s1++;
      s2++;
    }
  return *s1 - *s2;
}
