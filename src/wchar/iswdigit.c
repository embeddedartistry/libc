#include <wctype.h>

int iswdigit(wint_t wc)
{
	return (unsigned)wc - '0' < 10;
}
