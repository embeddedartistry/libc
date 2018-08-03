#include <string.h>
#include <wctype.h>

wctrans_t wctrans(const char* class)
{
	if(!strcmp(class, "toupper"))
	{
		return (wctrans_t)1;
	}

	if(!strcmp(class, "tolower"))
	{
		return (wctrans_t)2;
	}

	return 0;
}
