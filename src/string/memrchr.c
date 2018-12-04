// Imported from musl Libc

#include <string.h>

void* __memrchr(const void* /*m*/ /*m*/, int /*c*/ /*c*/, size_t /*n*/ /*n*/);

void* __memrchr(const void* m, int c, size_t n)
{
	const unsigned char* s = m;
	c = (unsigned char)c;

	while(n--)
	{
		if(s[n] == c)
		{
			return (void*)(uintptr_t)(s + n);
		}
	}

	return 0;
}
