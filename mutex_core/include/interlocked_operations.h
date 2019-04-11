// interlocked_operations.h - Defines symbols, functions, and global variables that
// accomplish thread-safe, atomic operations such as incrementing or decrementing
// an integer.
//

#ifndef __INTERLOCKED_OPERATIONS_H__
#define __INTERLOCKED_OPERATIONS_H__

/**
 * @brief This function releases the operating system resources consumed by the
 * atomic-operation infrastructure.
 * @remarks This function must be called exactly once by the same thread that calls
 * InitializeInterlock.  If this function is not paired with a call to InitializeInterlock,
 * a memory leak may occur.
 */
void DestroyInterlock();

/**
 * @brief Decrements the integer value referenced in a thread-safe way.
 * @param pn (Requried.) Address of the integer whose value is to be changed.
 * @remarks This function will not do anything if the InitializeInterlock
 * function has not been called exactly once during the lifetime of the
 * calling application first.
 */
void InterlockedDecrement(int* pn);

/**
 * @brief This function initializes the infrastructure for providing thread-safe operations.
 * @remarks This function must be called exactly once in the application that uses these
 * functions.  If this function is not called, then the Interlocked* functions
 * in this file will not be thread-safe.
 */
void InitializeInterlock();

/**
 * @brief Increments the integer value referenced in a thread-safe way.
 * @param pn (Required.) Address of the integer whose value is to be changed.
 * @remarks This function will not do anything if the InitializeInterlock
 * function has not been called exactly once during the lifetime of the
 * calling application first.
 */
void InterlockedIncrement(int* pn);

#endif /* __INTERLOCKED_OPERATIONS_H__ */
