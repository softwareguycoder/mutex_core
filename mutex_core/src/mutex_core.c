// Mutex API

#include "stdafx.h"
#include "mutex_core.h"

/**
 * @brief Internal (i.e., will not be put in the mutex.h header file) method
 * for freeing malloc'd mutex handles.
 * @param hMutex The handle to be freed.
 */
void FreeMutex(HMUTEX hMutex) {
	log_info("In FreeMutex");

	log_info("FreeMutex: Checking whether the mutex handle passed is valid...");

	if (INVALID_HANDLE_VALUE == hMutex) {
		log_warning(
				"FreeMutex: The mutex handle passed has an invalid value; assuming it's already been deallocated.");

		log_info("FreeMutex: Done.");

		// If we have an invalid handle (i.e., NULL pointer), then there is nothing to do.
		return;
	}

	log_info(
			"FreeMutex: The mutex handle passed is valid.  Freeing the memory...");

	// The HMUTEX handle type is just a typedef of pthread_mutex_t*
	// However, to work with the pthread functions, we need to view it
	// as such.
	pthread_mutex_t* pMutex = (pthread_mutex_t*) hMutex;

	free(pMutex);
	pMutex = NULL;
	hMutex = INVALID_HANDLE_VALUE;

	log_info("FreeMutex: The mutex handle passed has been freed.");

	log_info("FreeMutex: Done.");
}

/**
 * @brief Creates a mutex object, and returns a handle to it.  Returns INVALID_HANDLE_VALUE
 if an error occurred.
 */
HMUTEX CreateMutex() {
	log_info("In CreateMutex");

	log_info(
			"CreateMutex: Attempting to allocate system memory for mutex handle...");

	pthread_mutex_t* pMutex = (pthread_mutex_t*) malloc(
			sizeof(pthread_mutex_t));
	if (pMutex == NULL) {
		log_error(
				"CreateMutex: Memory allocation of pthread_mutex_t structure failed.");

		log_info("CreateMutex: Done.");

		return INVALID_HANDLE_VALUE;
	}

	log_debug("CreateMutex: %d B of memory allocated.",
			sizeof(pthread_mutex_t));

	log_info("CreateMutex: Attempting to initialize mutex...");

	// Call pthread_mutex_init.  This version of CreateMutex just passes a
	// mutex handle for the function to initialize with NULL for the attributes.
	int nResult = pthread_mutex_init(pMutex, NULL);
	if (OK != nResult) {
		log_error("CreateMutex: Failed to allocate mutex. %s",
				strerror(nResult));

		log_info(
				"CreateMutex: Attempting to release memory occupied by the mutex handle...");

		// Cleanup the mutex handle if necessary
		if (pMutex != NULL) {
			FreeMutex((HMUTEX) pMutex);
		}

		log_info(
				"CreateMutex: Resources consumed by the mutex handle have been released baack to the operating system.");

		log_info("CreateMutex: Done.");

		return INVALID_HANDLE_VALUE;
	}

	log_debug("CreateMutex: Created mutex with handle at address %p.", pMutex);

	log_info("CreateMutex: Done.");

	return (HMUTEX) pMutex;	// a HMUTEX is a typedef of pthread_mutex_t*
}

/**
 * @brief Releases resources associated with the specified mutex back to the operating system.
 * @remarks NOTE: For every call to CreateMutex, there must also be a call to DestroyMutex.
 */
void DestroyMutex(HMUTEX hMutex) {
	log_info("In DestroyMutex");

	log_info(
			"DestroyMutex: Checking whether the mutex handle passed is valid...");

	if (INVALID_HANDLE_VALUE == hMutex) {
		log_warning(
				"DestroyMutex: The mutex handle passed is already set to an invalid value.  Nothing to do.");

		log_info("DestroyMutex: Done.");

		// If we have an invalid handle (i.e., NULL pointer), then there is nothing to do.
		return;
	}

	log_info("DestroyMutex: The mutex handle passed is still a valid value.");

	log_info(
			"DestroyMutex: Attempting to release the mutex's resources back to the operating system...");

	int nResult = pthread_mutex_destroy((pthread_mutex_t*) hMutex);
	if (OK != nResult) {
		log_error("DestroyMutex: Failed to destroy the mutex. %s",
				strerror(nResult));

		log_info("DestroyMutex: Done.");

		return;
	}

	log_info(
			"DestroyMutex: Resources for the mutex have been released back to the operating system.");

	FreeMutex(hMutex);

	log_info("DestroyMutex: Done.");
}

/**
 * @brief Locks the mutex with the handle specified.  Does nothing if the handle
 * is INVALID_HANDLE_VALUE.
 * @param hMutex Handle of type HMUTEX (see stdafx.h) that refers to the mutex you want
 * to obtain a lock for.
 */
void LockMutex(HMUTEX hMutex) {
	log_info("In LockMutex");

	log_info("LockMutex: Checking whether the mutex handle passed is valid...");

	if (hMutex == INVALID_HANDLE_VALUE) {
		log_error(
				"LockMutex: The mutex handle passed has an invalid value.  Call CreateMutex first.");

		log_info("LockMutex: Done.");

		return;
	}

	log_info(
			"LockMutex: The mutex handle is valid.  Attempting to get a lock on it...");

	int nResult = pthread_mutex_lock(hMutex);
	if (OK != nResult) {
		log_error("LockMutex: Failed to lock the mutex provided. %s",
				strerror(nResult));

		log_info("LockMutex: Done.");

		return;
	}

	log_info("LockMutex: Obtained a lock on the mutex.");

	log_info("LockMutex: Done.");
}

/**
 * @brief Releases any existing locks on the mutex referred to by the handle specified. Does
 * nothing if the handle is INVALID_HANDLE_VALUE.
 * @param hMutex Mutex handle of type HMUTEX (see stdafx.h) that refers to the mutex you want
 * to release the lock on.
 */
void UnlockMutex(HMUTEX hMutex) {
	log_info("In UnlockMutex");

	log_info(
			"UnlockMutex: Checking whether the mutex handle passed is valid...");

	if (hMutex == INVALID_HANDLE_VALUE) {
		log_error("UnlockMutex: The mutex handle is invalid.  Nothing to do.");

		log_info("UnlockMutex: Done.");

		return;
	}

	log_info(
			"UnlockMutex: The mutex handle passed is a valid value.  Attempting to release the lock on it...");

	// Attempt to unlock the mutex provided and report to the user if the attempt does not work.

	int nResult = pthread_mutex_unlock((pthread_mutex_t*) hMutex);
	if (OK != nResult) {
		log_error("UnlockMutex: Failed to unlock the mutex provided. %s",
				strerror(nResult));

		log_info("UnlockMutex: Done.");

		return;
	}

	log_info("UnlockMutex: Lock released successfully.");

	// Done with execution.

	log_info("UnlockMutex: Done.");
}

