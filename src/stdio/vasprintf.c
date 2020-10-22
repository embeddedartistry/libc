// From musl libc

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int vasprintf(char** string, const char* fmt, va_list arg_list)
{
	va_list arg_list_copy;
	va_copy(arg_list_copy, arg_list);
	int l = vsnprintf(0, 0, fmt, arg_list_copy);
	va_end(arg_list_copy);

	if(l < 0 || !(*string = malloc((size_t)l + 1U)))
	{
		return -1;
	}

	return vsnprintf(*string, (size_t)l + 1U, fmt, arg_list);
}
