#include <string.h>

char* strpbrk(const char* s, const char* b)
{
	s += strcspn(s, b);
	return *s ? (char*)(uintptr_t)s : 0;
}
