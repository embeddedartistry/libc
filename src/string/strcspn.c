#include "strchrnul.h"
#include <stdint.h>
#include <string.h>

#define BITOP(a, b, op) \
	((a)[(size_t)(b) / (8 * sizeof *(a))] op(size_t) 1 << ((size_t)(b) % (8 * sizeof *(a))))

size_t strcspn(const char* s, const char* c)
{
	const char* a = s;
	size_t byteset[32 / sizeof(size_t)];

	if(!c[0] || !c[1])
	{
		return (uintptr_t)(__strchrnul(s, *c) - (uintptr_t)a);
	}

	memset(byteset, 0, sizeof byteset);
	for(; *c && BITOP(byteset, *(const unsigned char*)c, |=); c++)
	{
		{
			;
		}
	}
	for(; *s && !BITOP(byteset, *(const unsigned char*)s, &); s++)
	{
		{
			;
		}
	}
	return (uintptr_t)s - (uintptr_t)a;
}
