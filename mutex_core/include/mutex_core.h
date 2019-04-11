/*
 * mutex.h
 *
 *  Created on: Jan 8, 2019
 *      Author: bhart
 */

#ifndef __MUTEX_CORE_H__
#define __MUTEX_CORE_H__

#include "stdafx.h"

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE NULL
#endif //INVALID_HANDLE_VALUE

// Handle to a mutex -- really just a pointer to a pthread_mutex_t structure instance
typedef pthread_mutex_t *HMUTEX;

// API for mutex use

/**
 * @brief Creates a mutex object, and returns a handle to it.  Returns INVALID_HANDLE_VALUE
 if an error occurred.
 */
HMUTEX CreateMutex();

/**
 * @brief Releases resources associated with the specified mutex back to the operating system.
 */
void DestroyMutex(HMUTEX hMutex);

/**
 * @brief Locks the mutex with the handle specified.  Does nothing if the handle
 * is INVALID_HANDLE_VALUE.
 * @param hMutex Handle of type HMUTEX (see stdafx.h) that refers to the mutex you want
 * to obtain a lock for.
 * @returns TRUE (nonzero) if a lock was successfully obtained; FALSE (zero) if a problem occurred.
 */
BOOL LockMutex(HMUTEX hMutex);

/**
 * @brief Releases any existing locks on the mutex referred to by the handle specified. Does
 * nothing if the handle is INVALID_HANDLE_VALUE.
 * @param hMutex Mutex handle of type HMUTEX (see stdafx.h) that refers to the mutex you want
 * to release the lock on.
 * @returns TRUE if we successfully released the lock; FALSE if a problem occurred.
 */
BOOL UnlockMutex(HMUTEX hMutex);

#endif /* __MUTEX_CORE_H__ */
