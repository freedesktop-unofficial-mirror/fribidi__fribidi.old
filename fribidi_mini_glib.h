#ifndef _FRIBIDI_MINI_GLIB_H
#define _FRIBIDI_MINI_GLIB_H

#include <stdlib.h>

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
typedef signed char gint8;
typedef unsigned char guint8;
typedef signed short gint16;
typedef unsigned short guint16;
typedef signed int gint32;
typedef unsigned int guint32;

/* don't know where */
#define TRUE 1
#define FALSE 0

#define g_malloc(n) malloc(n)
#define g_new(T, n) malloc((n)*sizeof(T))
#define g_free(P) free(P)

typedef struct _GList GList;
struct _GList
{
  gpointer data;
  GList *next;
  GList *prev;
};

GList *g_list_append (GList *list, gpointer data);

#endif /* _FRIBIDI_MINI_GLIB_H */
