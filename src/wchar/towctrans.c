#include <string.h>
#include <wctype.h>

wint_t towctrans(wint_t wc, wctrans_t trans)
{
	if(trans == (wctrans_t)1)
	{
		return towupper(wc);
	}

	if(trans == (wctrans_t)2)
	{
		return towlower(wc);
	}

	return wc;
}
