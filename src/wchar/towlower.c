#include "_towcase.h"

wint_t towlower(wint_t wc)
{
	return (unsigned)wc < 128 ? tolower(wc) : __towcase(wc, 1);
}
