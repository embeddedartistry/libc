// Pulled from musl libc, locale support removed

#include <ctype.h>

int isdigit(int c)
{
	return (unsigned)c-'0' < 10;
}
