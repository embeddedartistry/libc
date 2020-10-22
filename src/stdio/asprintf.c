// From musl libc

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include <stdarg.h>
#include <stdio.h>

int asprintf(char** string, const char* fmt, ...)
{
	int r;
	va_list ap;

	va_start(ap, fmt);
	r = vasprintf(string, fmt, ap);
	va_end(ap);

	return r;
}
