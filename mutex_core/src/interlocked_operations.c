// interlocked_operations.c - Contains the implementations of functions and
// global variables that facilitate atomic, thread-safe operations, such as
// incrementing and/or decrementing an integer.
//

#include "stdafx.h"
#include "mutex_core.h"

#include "interlocked_operations.h"

///////////////////////////////////////////////////////////////////////////////
// Global variables

// Internal mutex for interlocked decrement and increment of ints
HMUTEX g_hInterlockMutex;

///////////////////////////////////////////////////////////////////////////////
// DestroyInterlock function

void DestroyInterlock() {
	if (INVALID_HANDLE_VALUE == g_hInterlockMutex) {
		return;	// Nothing to do.
	}

	DestroyMutex(g_hInterlockMutex);
}

///////////////////////////////////////////////////////////////////////////////
// InterlockedDecrement function

void InterlockedDecrement(int* pn) {
	if (pn == NULL) {
		return;
	}

	if (INVALID_HANDLE_VALUE == g_hInterlockMutex) {
		return;
	}

	LockMutex(g_hInterlockMutex);

	(*pn)--;

	UnlockMutex(g_hInterlockMutex);
}

///////////////////////////////////////////////////////////////////////////////
// InterlockedIncrement function

void InterlockedIncrement(int* pn) {
	if (pn == NULL) {
		return;
	}

	if (INVALID_HANDLE_VALUE == g_hInterlockMutex) {
		return;
	}

	LockMutex(g_hInterlockMutex);

	(*pn)++;

	UnlockMutex(g_hInterlockMutex);
}

///////////////////////////////////////////////////////////////////////////////
// InitializeInterlock function

void InitializeInterlock() {
	if (INVALID_HANDLE_VALUE != g_hInterlockMutex) {
		return;		// Nothing to do.
	}

	g_hInterlockMutex = CreateMutex();
}
