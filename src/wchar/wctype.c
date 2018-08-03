#include <string.h>
#include <wctype.h>

wctype_t wctype(const char* s)
{
	wctype_t i;
	const char* p;
	/* order must match! */
	static const char names[] = "alnum\0"
								"alpha\0"
								"blank\0"
								"cntrl\0"
								"digit\0"
								"graph\0"
								"lower\0"
								"print\0"
								"punct\0"
								"space\0"
								"upper\0"
								"xdigit";
	for(i = 1, p = names; *p; i++, p += 6)
	{
		if(*s == *p && !strcmp(s, p))
		{
			return i;
		}
	}
	return 0;
}
