#include "_towcase.h"
#include <ctype.h>

wint_t towupper(wint_t wc)
{
	return (wint_t)(wc < 128 ? toupper((int)wc) : __towcase((wchar_t)wc, 0));
}
