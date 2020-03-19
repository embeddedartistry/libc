// Imported from musl Libc

#include "strchrnul.h"
#include <limits.h>
#include <stdint.h>
#include <string.h>

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1 / UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX / 2 + 1))
#define HASZERO(x) (((x)-ONES) & ~(x)&HIGHS)

char* __strchrnul(const char* s, int c)
{
	const size_t* w;
	size_t k;
	c = (unsigned char)c;

	if(!c)
	{
		return (char*)(uintptr_t)s + strlen(s);
	}

	for(; (uintptr_t)s % ALIGN; s++)
	{
		if(!*s || *(const unsigned char*)s == c)
		{
			return (char*)(uintptr_t)s;
		}
	}

	k = ONES * (unsigned long)c;

	for(w = (const void*)s; !HASZERO(*w) && !HASZERO(*w ^ k); w++)
	{
		;
	}
	for(s = (const void*)w; *s && *(const unsigned char*)s != c; s++)
	{
		;
	}

	return (char*)(uintptr_t)s;
}
