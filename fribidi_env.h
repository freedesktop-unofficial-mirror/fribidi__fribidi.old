/* fribidi_env.h - FriBidi environment management
 * Copyright (C) 2002 Omer Zak
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
 * For licensing issues, contact <omerz@actcom.co.il>
 */

/***********************************************************************
 * The FriBidiEnv structure encapsulates data about the environment
 * in which a particular instance of FriBidi runs.
 *
 * The structure was introduced to meet the following objectives:
 * 1. Mechanism for freeing all memory allocated by FriBidi procedures
 *    if a procedure stopped executing in middle due to any reason,
 *    such as memory allocation failure.
 *    This mechanism is necessary for using FriBidi in small-memory
 *    devices, such as devices which run the GEOS and Symbian EPOC 6
 *    operating systems.
 * 2. Avoidance of modifiable static memory variables, which are
 *    not allowed in Symbian EPOC 6 applications, and which prevent
 *    the FriBidi library from being reentrant in certain operating
 *    systems.  The structure also allows FriBidi to be used in
 *    multithreaded environments.
 * 3. Allow an application to run FriBidi under independent environments,
 *    using different settings in each environment.
 *
 * Every FriBidi function requires a pointer to FriBidiEnv as its first
 * argument.
 **********************************************************************/

#ifndef FRIBIDI_ENV_H
#define FRIBIDI_ENV_H

#include "fribidi_mem.h"

/* One of the following must be #defined. */
#define GLOBAL_FRIBIDIENV
/* #define VERIFY_NO_GLOBAL_FRIBIDIENV    */
/* #define NO_FRIBIDIENV_VALIDATION       */


/* Define to be the appropriate action for your environment. */
#define FRIBIDI_OOM_ACTION return(NULL)


#ifdef __cplusplus
extern "C"
{
#endif

/*======================================================================
 *  Memory Management Structure
 *----------------------------------------------------------------------*/

/***********************************************************************
 * The following structure is needed unless fribidi_malloc() and
 * fribidi_free() are #define'd to be the same as the operating system
 * provided malloc() and free() procedures.
 *
 * Each dynamically-allocated memory chunk is prefixed with two
 * pointers.
 * The chunk is added to a doubly-linked list.
 * When its time to be deleted comes, it is deleted from whatever
 * position it is in the doubly-linked list.
 *
 * The head of the list is in a FriBidiEnv structure instance, and it
 * is mapped in such a way that fribidi_free() does not have to distinguish
 * between it and a memory chunk in middle of the doubly-linked list.
 **********************************************************************/

  typedef struct _FriBidiMemChunkPrefix FriBidiMemChunkPrefix;

  struct _FriBidiMemChunkPrefix
  {
    FriBidiMemChunkPrefix *iNext;
    /* must be first item in the chunk prefix, so that the
     * fribidi_free() can handle the list head without checking
     * for special cases.
     */
    FriBidiMemChunkPrefix *iPrev;
    /* Points at either FriBidiMemChunkPrefix or at
     * FriBidiEnv.
     */
  };


/*======================================================================
 *  FriBidiEnv Structure Declaration
 *----------------------------------------------------------------------*/

/* The truth is that uint16 is enough for the number of flags
 * currently defined.
 * But we want to keep all FriBidiEnv fields word-aligned.
 */
  typedef uint32 FriBidiFlags;

/* The following is defined in fribidi_mem.h, must be defined
 * there due to forward references.
 */
/* typedef struct _FriBidiEnv FriBidiEnv; */

  struct _FriBidiEnv
  {
    FriBidiMemChunkPrefix *iAllocatedMemoryChunks;
    /* Pointer to doubly-linked list of allocated memory chunks.
     * Must be the first item in the structure, so that the
     * fribidi_free() can handle list head without checking for
     * special cases.
     */
    FriBidiFlags iFlags;
    /* The flags will define:
     * - Debug mode
     * - Mirroring
     * - L3 rule on/off
     * - remove BiDi marks on/off
     * - Arabic joining on/off
     * - Ligaturing on/off
     * They will be set and cleared by inlined access procedures.
     */

    /* The following are reserved for future expansion without breaking
     * binary compatibility of existing software.
     */
    uint32 iReserved1;
    uint32 iReserved2;
    void *iReserved3;		/* If necessary, will point at extension to FriBidiEnv. */
  };

/*======================================================================
 *  Initialize a FriBidiEnv structure.  Must be called before any
 *  other use of the structure.
 *
 *  It initializes the doubly-linked list of memory chunks and the flags.
 *----------------------------------------------------------------------*/
  void init_fribidienv (FriBidiEnv * fribidienv, FriBidiFlags aFlags);


/*======================================================================
 * Free all memory linked to this FriBidiEnv instance.
 * After calling this procedure, the instance is legally initialized,
 * so there is no need for a separate init_fribidienv() call (but it
 * does not harm).
 *----------------------------------------------------------------------*/
  void destroy_fribidienv (FriBidiEnv * fribidienv);


/*======================================================================
 * Allocate memory and link it to this FriBidiEnv instance.
 * This function may throw an Out-Of-Memory exception in
 * environments, which support exceptions.
 *----------------------------------------------------------------------*/
  void *fribidi_malloc (FriBidiEnv * fribidienv, size_t size);


/*======================================================================
 * Unlink the memory chunk pointed at by ptr from this
 * FriBidiEnv instance and free it.
 * If the memory chunk is not properly linked, then panic.
 *----------------------------------------------------------------------*/
  void fribidi_free (FriBidiEnv * fribidienv, void *ptr);


/*====================================================================*/

/* Flag definitions.
 *
 * When initializing a FriBidiEnv instance, OR together the constants
 * corresponding to the flags which you want to set.
 */
#define FRIBIDIENV_DEBUG_MODE		0x0001
#define FRIBIDIENV_MIRRORING_MODE	0x0002
#define FRIBIDIENV_REORDER_NSM_MODE	0x0004
#define FRIBIDIENV_REMOVE_MARKS_MODE	0x0008
#define FRIBIDIENV_ARABIC_JOINING_MODE	0x0010
#define FRIBIDIENV_LIGATURING_MODE	0x0020


/* Use FRIBIDIENV_DEFAULT_SETTINGS as a shorthand to frequently-used
 * defaults for the flags.
 */
#define FRIBIDIENV_DEFAULT_SETTINGS (FRIBIDIENV_MIRRORING_MODE | 0)


/*======================================================================
 *  fribidi_mirroring_status() returns whether mirroring is on or off,
 *  default is on.
 *----------------------------------------------------------------------*/
  boolean fribidi_mirroring_status (FriBidiEnv * fbenv);

/*======================================================================
 *  fribidi_set_mirroring() sets mirroring on or off.
 *----------------------------------------------------------------------*/
  void fribidi_set_mirroring (FriBidiEnv * fbenv, boolean mirror);

/*======================================================================
 *  fribidi_reorder_nsm_status() returns whether reordering of nsm
 *  sequences is on or off, default is off.
 *----------------------------------------------------------------------*/
  boolean fribidi_reorder_nsm_status (FriBidiEnv * fbenv);

/*======================================================================
 *  fribidi_set_reorder_nsm() sets reordering of nsm sequences on or off.
 *----------------------------------------------------------------------*/
  void fribidi_set_reorder_nsm (FriBidiEnv * fbenv, boolean reorder);

/*======================================================================
 *  fribidi_debug_status() returns whether debugging is on or off,
 *  default is off.  Returns false if fribidi is not compiled with debug
 *  enabled.
 *----------------------------------------------------------------------*/
  boolean fribidi_debug_status (FriBidiEnv * fbenv);

/*======================================================================
 *  fribidi_set_debug() turn on or off debugging, default is off.
 *  if the library was compiled without DEBUG option, this function
 *  returns FALSE.
 *----------------------------------------------------------------------*/
  boolean fribidi_set_debug (FriBidiEnv * fbenv, boolean debug);

/*======================================================================
 *  Management of various styles of defining and using FriBidiEnv.
 *----------------------------------------------------------------------*/

/*======================================================================
 *  For environments with global FriBidiEnv instance.
 *----------------------------------------------------------------------*/
#ifdef GLOBAL_FRIBIDIENV
#define VALIDATE_FRIBIDIENV(env) if ((env) == NULL) (env) = &(fribidi_global_env)

  extern FriBidiEnv fribidi_global_env;
#endif				/* GLOBAL_FRIBIDIENV */


/*======================================================================
 *  For environments with disallow global variables.
 *----------------------------------------------------------------------*/
#ifdef VERIFY_NO_GLOBAL_FRIBIDIENV
#define VALIDATE_FRIBIDIENV(env)  if ((env) == NULL) Panic()
#endif				/* VERIFY_NO_GLOBAL_FRIBIDIENV */


/*======================================================================
 *  For environments which need speed/code size optimization.
 *----------------------------------------------------------------------*/
#ifdef NO_FRIBIDIENV_VALIDATION
#define VALIDATE_FRIBIDIENV(env) while (0) {}
  /* Null definition, for environments, which guarantee valid
     ** environments, and need the efficiency.
   */
#endif				/* NO_FRIBIDIENV_VALIDATION */

#ifdef	__cplusplus
}
#endif

#endif				/* FRIBIDI_ENV_H */

/* End of fribidi_env.h */
