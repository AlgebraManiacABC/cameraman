#ifndef WIN_COMPAT_H
#define WIN_COMPAT_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _WIN32

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int asprintf(char ** str, const char * fmt, ...);
int vasprintf(char ** str, const char * fmt, va_list args);

#else
	#define _GNU_SOURCE
#endif

#ifdef __cplusplus
}
#endif

#endif