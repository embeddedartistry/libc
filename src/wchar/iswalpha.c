#include <wctype.h>

static const unsigned char table[] = {
#include "alpha.h"
};

int iswalpha(wint_t wc)
{
	if(wc < 0x20000)
	{
		return (table[(wint_t)(table[wc >> 8] * 32) + ((wc & 255) >> 3)] >> (wc & 7)) & 1;
	}
	if(wc < 0x2fffe)
	{
		return 1;
	}
	return 0;
}
