#include <string.h>
#include <ctype.h>
#include "fribidi_mini_glib.h"

GList *
g_list_append (GList *list, gpointer data)
{
  GList *node, *last;

  node = malloc (sizeof (GList));
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

struct _GMemChunk
{
  gchar *name;
  gint atom_size;
  gint area_size;
  gint type;

  gint empty_size;
  gpointer chunk;
};

GMemChunk *
g_mem_chunk_new (gchar *name, gint atom_size, gulong area_size, gint type)
{
  GMemChunk *m = g_new (GMemChunk, 1);

  m->name = name;
  m->atom_size = atom_size;
  m->area_size = area_size;
  m->type = type;

  m->empty_size = 0;
  m->chunk = NULL;

  return m;
}

void
g_mem_chunk_destroy (GMemChunk * mem_chunk)
{
  g_free (mem_chunk);
  return;
}

gpointer
g_mem_chunk_alloc (GMemChunk * mem_chunk)
{
  gpointer m;

  if (mem_chunk->type == G_ALLOC_ONLY)
    {
      if (mem_chunk->empty_size < mem_chunk->atom_size)
	{
	  mem_chunk->chunk = g_malloc (mem_chunk->area_size);
	  mem_chunk->empty_size = mem_chunk->area_size;
	}
      m = mem_chunk->chunk;
      mem_chunk->chunk += mem_chunk->atom_size;
      mem_chunk->empty_size -= mem_chunk->atom_size;
    }
  else
    m = (gpointer) g_malloc (mem_chunk->atom_size);
  return m;
}

void
g_mem_chunk_free (GMemChunk * mem_chunk, gpointer mem)
{
  if (mem_chunk->type == G_ALLOC_AND_FREE)
    g_free (mem);
  return;
}

gint
g_strcasecmp (const gchar *s1, const gchar *s2)
{
  while (*s1 && toupper (*s1) == toupper (*s2))
    {
      s1++;
      s2++;
    }
  return *s1 - *s2;
}
