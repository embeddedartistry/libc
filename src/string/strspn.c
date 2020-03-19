#include <stdint.h>
#include <string.h>

#define BITOP(a, b, op) \
	((a)[(size_t)(b) / (8 * sizeof *(a))] op(size_t) 1 << ((size_t)(b) % (8 * sizeof *(a))))

size_t strspn(const char* s, const char* c)
{
	const char* a = s;
	size_t byteset[32 / sizeof(size_t)] = {0};

	if(!c[0])
	{
		return 0;
	}

	if(!c[1])
	{
		for(; *s == *c; s++)
		{
			;
		}

		return (uintptr_t)s - (uintptr_t)a;
	}

	for(; *c && BITOP(byteset, *(const unsigned char*)c, |=); c++)
	{
		;
	}

	for(; *s && BITOP(byteset, *(const unsigned char*)s, &); s++)
	{
		;
	}

	return (uintptr_t)s - (uintptr_t)a;
}
