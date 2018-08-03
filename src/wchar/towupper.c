#include "_towcase.h"

wint_t towupper(wint_t wc)
{
	return (unsigned)wc < 128 ? toupper(wc) : __towcase(wc, 0);
}
