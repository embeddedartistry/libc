#include <ctype.h>
#include <wctype.h>

int iswblank(wint_t wc)
{
	return isblank(wc);
}
