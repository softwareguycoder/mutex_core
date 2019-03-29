
#ifndef __MUTEX_CORE_STDAFX_H__
#define __MUTEX_CORE_STDAFX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef OK
#define OK		0		// Code to return to the operating system to indicate successful program termination
#endif // OK

#ifndef ERROR
#define ERROR	-1		// Code to return to the operating system to indicate an error condition
#endif // ERROR

// Boolean "data type"
typedef enum {
	FALSE, TRUE
} BOOL;

#endif /* __MUTEX_CORE_STDAFX_H__ */
