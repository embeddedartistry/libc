#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include <time.h>

char* asctime(const struct tm* tm)
{
	static char buf[26];
	return asctime_r(tm, buf);
}
