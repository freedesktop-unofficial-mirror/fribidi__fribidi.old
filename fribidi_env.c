/* fribidi_env.c - FriBidi environment management
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


/*======================================================================
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
 *----------------------------------------------------------------------*/

#include <stdlib.h>

#include "fribidi_env.h"

/*======================================================================
 *  Initialize a FriBidiEnv structure.  Must be called before any
 *  other use of the structure.
 *
 *  It initializes the doubly-linked list of memory chunks and the flags.
 *----------------------------------------------------------------------*/

void
init_fribidienv (FriBidiEnv *fribidienv, FriBidiFlags aFlags)
{
  VALIDATE_FRIBIDIENV (fribidienv);
  fribidienv->iAllocatedMemoryChunks = NULL;
  fribidienv->iFlags = aFlags;
  /* fribidienv->iReserved3 = NULL; */
}

/*======================================================================
 * Free all memory linked to this FriBidiEnv instance.
 * After calling this procedure, the instance is legally initialized,
 * so there is no need for a separate init_fribidienv() call (but it
 * does not harm).
 *----------------------------------------------------------------------*/
void
destroy_fribidienv (FriBidiEnv *fribidienv)
{
  FriBidiMemChunkPrefix *lChunkPtr;
  FriBidiMemChunkPrefix *lChunkNext;

  VALIDATE_FRIBIDIENV (fribidienv);

  lChunkPtr = fribidienv->iAllocatedMemoryChunks;
  while (NULL != lChunkPtr)
    {
      lChunkNext = (FriBidiMemChunkPrefix *) (lChunkPtr->iNext);
      free (lChunkPtr);
      lChunkPtr = lChunkNext;
    }
  fribidienv->iAllocatedMemoryChunks = NULL;
}


/*======================================================================
 * Allocate memory and link it to this FriBidiEnv instance.
 * This function may throw an Out-Of-Memory exception in
 * environments, which support exceptions.
 *----------------------------------------------------------------------*/
void *
fribidi_malloc (FriBidiEnv *fribidienv, int size)
{
  FriBidiMemChunkPrefix *lChunk_ptr;
  FriBidiMemChunkPrefix *lNextChunk_ptr;

  VALIDATE_FRIBIDIENV (fribidienv);

  lChunk_ptr =
    (FriBidiMemChunkPrefix *) malloc (sizeof (FriBidiMemChunkPrefix) + size);
  if (NULL == lChunk_ptr)
    {
      FRIBIDI_OOM_ACTION;
    }

  /* Before:
   * fribidienv->iAllocatedMemoryChunks points at lNextChunk_ptr.
   * if (NULL != lNextChunk_Ptr):
   *   lNextChunk_ptr->iNext points at something.
   *   lNextChunk_ptr->iPrev points back at fribidienv.
   *
   * After:
   * fribidienv->iAllocatedMemoryChunks points at lChunk_ptr.
   * if (NULL != lNextChunk_Ptr):
   *   lNextChunk_ptr->iNext unchanged.
   *   lNextChunk_ptr->iPrev points at lChunk_ptr.
   * lChunk_ptr->iNext points at lNextChunk_ptr.
   * lChunk_ptr->iPrev points back at fribidienv.
   */

  lNextChunk_ptr = fribidienv->iAllocatedMemoryChunks;
  fribidienv->iAllocatedMemoryChunks = lChunk_ptr;
  if (NULL != lNextChunk_ptr)
    {
      lNextChunk_ptr->iPrev = lChunk_ptr;
    }
  lChunk_ptr->iNext = lNextChunk_ptr;
  lChunk_ptr->iPrev = (FriBidiMemChunkPrefix *) fribidienv;

  return ((void *) (&lChunk_ptr[1]));
}

/*======================================================================
 * Unlink the memory chunk pointed at by ptr from this
 * FriBidiEnv instance and free it.
 * If the memory chunk is not properly linked, then panic.
 *----------------------------------------------------------------------*/
void
fribidi_free (FriBidiEnv *fribidienv, void *ptr)
{
  FriBidiMemChunkPrefix *lChunk_ptr;
  FriBidiMemChunkPrefix *lNextChunk_ptr;
  FriBidiMemChunkPrefix *lPrevChunk_ptr;

  /* VALIDATE_FRIBIDIENV(fribidienv); */
  /* At normal operation (i.e. not when debugging the memory management
   * subsystem), fribidienv is not used in this implementation of
   * fribidi_free().
   */

  if (NULL == ptr)
    return;

  lChunk_ptr = (FriBidiMemChunkPrefix *)
    (((char *) ptr) - sizeof (FriBidiMemChunkPrefix));

  lNextChunk_ptr = (FriBidiMemChunkPrefix *) (lChunk_ptr->iNext);
  lPrevChunk_ptr = (FriBidiMemChunkPrefix *) (lChunk_ptr->iPrev);

  /* assert (NULL != lPrevChunk_ptr); */

  /* Remove the current memory chunk from the doubly-linked list. */
  lPrevChunk_ptr->iNext = lNextChunk_ptr;
  if (NULL != lNextChunk_ptr)
    {
      lNextChunk_ptr->iPrev = lPrevChunk_ptr;
    }

  free (lChunk_ptr);
}




/*======================================================================
 *  fribidi_mirroring_status() returns whether mirroring is on or off,
 *  default is on.
 *----------------------------------------------------------------------*/
fribidi_boolean
fribidi_mirroring_status (FriBidiEnv *fbenv)
{
  VALIDATE_FRIBIDIENV (fbenv);

  return (0 !=
	  (fbenv->
	   iFlags & FRIBIDIENV_MIRRORING_MODE) ? FRIBIDI_TRUE :
	  FRIBIDI_FALSE);
}

/*======================================================================
 *  fribidi_set_mirroring() sets mirroring on or off.
 *----------------------------------------------------------------------*/
void
fribidi_set_mirroring (FriBidiEnv *fbenv, fribidi_boolean mirror)
{
  VALIDATE_FRIBIDIENV (fbenv);

  if (FRIBIDI_FALSE != mirror)
    {
      fbenv->iFlags |= FRIBIDIENV_MIRRORING_MODE;
    }
  else
    {
      fbenv->iFlags &= (~FRIBIDIENV_MIRRORING_MODE);
    }
}

/*======================================================================
 *  fribidi_reorder_nsm_status() returns whether reordering of nsm
 *  sequences is on or off, default is off.
 *----------------------------------------------------------------------*/
fribidi_boolean
fribidi_reorder_nsm_status (FriBidiEnv *fbenv)
{
  VALIDATE_FRIBIDIENV (fbenv);

  return (0 !=
	  (fbenv->
	   iFlags & FRIBIDIENV_REORDER_NSM_MODE) ? FRIBIDI_TRUE :
	  FRIBIDI_FALSE);
}

/*======================================================================
 *  fribidi_set_reorder_nsm() sets reordering of nsm sequences on or off.
 *----------------------------------------------------------------------*/
void
fribidi_set_reorder_nsm (FriBidiEnv *fbenv, fribidi_boolean reorder)
{
  VALIDATE_FRIBIDIENV (fbenv);

  if (FRIBIDI_FALSE != reorder)
    {
      fbenv->iFlags |= FRIBIDIENV_REORDER_NSM_MODE;
    }
  else
    {
      fbenv->iFlags &= (~FRIBIDIENV_REORDER_NSM_MODE);
    }
}

/*======================================================================
 *  fribidi_debug_status() returns whether debugging is on or off,
 *  default is off.
 *----------------------------------------------------------------------*/
fribidi_boolean
fribidi_debug_status (FriBidiEnv *fbenv)
{
#ifdef DEBUG
  VALIDATE_FRIBIDIENV (fbenv);

  return (0 !=
	  (fbenv->
	   iFlags & FRIBIDIENV_DEBUG_MODE) ? FRIBIDI_TRUE : FRIBIDI_FALSE);
#else /* DEBUG */
  return FRIBIDI_FALSE;
#endif /* DEBUG */
}

/*======================================================================
 *  fribidi_set_debug() turn on or off debugging, default is off.
 *  if the library was compiled without DEBUG option, this function
 *  returns FRIBIDI_FALSE.
 *----------------------------------------------------------------------*/
fribidi_boolean
fribidi_set_debug (FriBidiEnv *fbenv, fribidi_boolean debug)
{
#ifdef DEBUG
  VALIDATE_FRIBIDIENV (fbenv);

  if (FRIBIDI_FALSE != debug)
    {
      fbenv->iFlags |= FRIBIDIENV_DEBUG_MODE;
    }
  else
    {
      fbenv->iFlags &= (~FRIBIDIENV_DEBUG_MODE);
    }
  return debug;
#else /* DEBUG */
  return FRIBIDI_FALSE;
#endif /* DEBUG */
}


/*======================================================================
 *  For environments with global FriBidiEnv instance.
 *----------------------------------------------------------------------*/
#ifdef GLOBAL_FRIBIDIENV
FriBidiEnv fribidi_global_env = { NULL, FRIBIDIENV_DEFAULT_SETTINGS };
/* fribidi_global_env needs no explicit initialization. */
#endif /* GLOBAL_FRIBIDIENV */


/* End of fribidi_env.c */
