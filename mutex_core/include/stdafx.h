#ifndef __MUTEX_CORE_STDAFX_H__
#define __MUTEX_CORE_STDAFX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

#include <../../api_core/api_core/include/api_core.h>
#include <../../common_core/common_core/include/common_core.h>

#ifndef OK
#define OK		0		// Code to return to the operating system to indicate successful program termination
#endif // OK

#ifndef ERROR
#define ERROR	-1		// Code to return to the operating system to indicate an error condition
#endif // ERROR

#endif /* __MUTEX_CORE_STDAFX_H__ */
