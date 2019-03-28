///////////////////////////////////////////////////////////////////////////////
// mutex_core.c: Defines a standardized API for working with pthread mutex
// objects

#include "stdafx.h"
#include "mutex_core.h"

///////////////////////////////////////////////////////////////////////////////
// FreeMutex: Internal function for freeing malloc'd mutex handles.  This
// function is not exposed in the header file for this library, as it is
// meant for internal use only.

/**
 * @brief Internal (i.e., will not be put in the mutex.h header file) method
 * for freeing malloc'd mutex handles.
 * @param hMutex The handle to be freed.
 */
void _FreeMutex(HMUTEX hMutex) {
	if (INVALID_HANDLE_VALUE == hMutex) {
		// If we have an invalid handle (i.e., NULL pointer), then there is nothing to do.
		return;
	}

	// The HMUTEX handle type is just a typedef of pthread_mutex_t*
	// However, to work with the pthread functions, we need to view it
	// as such.
	pthread_mutex_t* pMutex = (pthread_mutex_t*) hMutex;

	free(pMutex);
	pMutex = NULL;
	hMutex = INVALID_HANDLE_VALUE;
}

///////////////////////////////////////////////////////////////////////////////
// CreateMutex: Creates a new mutex object using the pthread routines and then,
// if successful, returns a HMUTEX handle to the newly-created mutex. The new
// mutex also is initialized by the pthread_mutex_init routine.  malloc() is used
// to allocate the memory for the new mutex.

/**
 * @brief Creates a mutex object, and returns a handle to it.  Returns INVALID_HANDLE_VALUE
 if an error occurred.
 * @remarks This function also initializes the new mutex handle with a call to
 * pthread_mutex_init before it returns the HMUTEX handle.
 */
HMUTEX CreateMutex() {
	pthread_mutex_t* pMutex = (pthread_mutex_t*) malloc(
			sizeof(pthread_mutex_t));
	if (pMutex == NULL) {
		return INVALID_HANDLE_VALUE;
	}

	// Call pthread_mutex_init.  This version of CreateMutex just passes a
	// mutex handle for the function to initialize with NULL for the attributes.
	int nResult = pthread_mutex_init(pMutex, NULL);
	if (OK != nResult) {
		// Cleanup the mutex handle if necessary
		if (pMutex != NULL) {
			_FreeMutex((HMUTEX) pMutex);
		}

		return INVALID_HANDLE_VALUE;
	}

	return (HMUTEX) pMutex;	// a HMUTEX is a typedef of pthread_mutex_t*
}

///////////////////////////////////////////////////////////////////////////////
// DestroyMutex: Releases the resources associated with the specified mutex
// back to the operating system.  Attempts to call free() on the memory occupied
// by the mutex as well.

/**
 * @brief Releases resources associated with the specified mutex back to the operating system.
 * @remarks NOTE: For every call to CreateMutex, there must also be a call to DestroyMutex.
 */
void DestroyMutex(HMUTEX hMutex) {
	if (INVALID_HANDLE_VALUE == hMutex) {
		// If we have an invalid handle (i.e., NULL pointer), then there is nothing to do.
		return;
	}

	int nResult = pthread_mutex_destroy((pthread_mutex_t*) hMutex);
	if (OK != nResult) {
		return;
	}

	_FreeMutex(hMutex);
}

///////////////////////////////////////////////////////////////////////////////
// LockMutex: Attempts to obtain a mutually-exclusive lock on the mutex with the
// handle specified.  Does not return to the caller until either the lock has been
// obtained or an error has occurred.

/**
 * @brief Locks the mutex with the handle specified.  Does nothing if the handle
 * is INVALID_HANDLE_VALUE.
 * @param hMutex Handle of type HMUTEX (see stdafx.h) that refers to the mutex you want
 * to obtain a lock for.
 * @returns TRUE (nonzero) if a lock was successfully obtained; FALSE (zero) if a problem occurred.
 */
BOOL LockMutex(HMUTEX hMutex) {
	if (hMutex == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	int nResult = pthread_mutex_lock(hMutex);
	if (OK != nResult) {
		return FALSE;
	}
	return TRUE; 	// Succeeded
}

///////////////////////////////////////////////////////////////////////////////
// UnlockMutex: Attempts to release any existing mutually-exclusive lock which
// may be being held by the current thread.

/**
 * @brief Releases any existing locks on the mutex referred to by the handle specified. Does
 * nothing if the handle is INVALID_HANDLE_VALUE.
 * @param hMutex Mutex handle of type HMUTEX (see stdafx.h) that refers to the mutex you want
 * to release the lock on.
 * @returns TRUE if we successfully released the lock; FALSE if a problem occurred.
 */
BOOL UnlockMutex(HMUTEX hMutex) {
	if (hMutex == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	// Attempt to unlock the mutex provided and report to the user if the attempt does not work.

	int nResult = pthread_mutex_unlock((pthread_mutex_t*) hMutex);
	if (OK != nResult) {
		return FALSE;
	}

	// Done with execution.

	return TRUE; 	// Succeeded
}

