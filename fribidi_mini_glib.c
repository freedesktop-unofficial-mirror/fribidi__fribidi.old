#include "fribidi_mini_glib.h"

GList* g_list_append            (GList          *list,
                                 gpointer        data)
{
  GList *node, *last;

  node = malloc(sizeof(GList));
  node->data = data;
  node->next = NULL;
  node->prev = NULL;

  if (!list) return node;

  for (last=list; !last->next; last=last->next);
  node->prev=last;
  last->next=node;
  return list;
}
