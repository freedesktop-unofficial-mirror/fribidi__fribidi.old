#ifndef _FRIBIDI_MINI_GLIB_H
#define _FRIBIDI_MINI_GLIB_H

#include <stdlib.h>
#include <limits.h>

typedef char gchar;
typedef short gshort;
typedef long glong;
typedef int gint;
typedef gint gboolean;

typedef unsigned char guchar;
typedef unsigned short gushort;
typedef unsigned long gulong;
typedef unsigned int guint;

typedef float gfloat;
typedef double gdouble;

typedef void *gpointer;
typedef const void *gconstpointer;

/* from glibconfig.h */

#define G_MINSHORT      SHRT_MIN
#define G_MAXSHORT      SHRT_MAX
#define G_MININT        INT_MIN
#define G_MAXINT        INT_MAX
#define G_MINLONG       LONG_MIN
#define G_MAXLONG       LONG_MAX

typedef signed char gint8;
typedef unsigned char guint8;
typedef signed short gint16;
typedef unsigned short guint16;
typedef signed int gint32;
typedef unsigned int guint32;

/* from glib.h */

#define TRUE 1
#define FALSE 0

#define g_malloc(n) malloc(n)
#define g_new(T, n) ((T*)malloc((n) * sizeof(T)))
#define g_free(P) free(P)

#undef  MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#undef  MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

typedef struct _GList GList;
struct _GList
{
  gpointer data;
  GList *next;
  GList *prev;
};

GList *g_list_append (GList *list, gpointer data);

typedef struct _GMemChunk GMemChunk;

#define G_ALLOC_ONLY      1
#define G_ALLOC_AND_FREE  2

GMemChunk *g_mem_chunk_new (gchar *name,
			    gint atom_size, gulong area_size, gint type);
void g_mem_chunk_destroy (GMemChunk * mem_chunk);
gpointer g_mem_chunk_alloc (GMemChunk * mem_chunk);
gpointer g_mem_chunk_alloc0 (GMemChunk * mem_chunk);
void g_mem_chunk_free (GMemChunk * mem_chunk, gpointer mem);

#define g_mem_chunk_create(type, pre_alloc, alloc_type) ( \
  g_mem_chunk_new (#type " mem chunks (" #pre_alloc ")", \
                   sizeof (type), \
                   sizeof (type) * (pre_alloc), \
                   (alloc_type)) \
)
#define g_chunk_new(type, chunk)        ( \
  (type *) g_mem_chunk_alloc (chunk) \
)

gint g_strcasecmp (const gchar *s1, const gchar *s2);

#endif /* _FRIBIDI_MINI_GLIB_H */
