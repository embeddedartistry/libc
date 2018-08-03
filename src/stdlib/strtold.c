
#include <stdlib.h>

long double strtold(const char* __restrict nptr, char** __restrict endptr)
{
	return (long double)strtod(nptr, endptr);
}
