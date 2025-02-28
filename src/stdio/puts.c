#include <stdio.h>

int puts(const char* str)
{
	int r = 1;

	for(const char* c = str; *c != 0; c++)
	{
		putchar((int)*c);
		r++;
	}

	if(r == 1)
	{
		return EOF;
	}

	// puts adds a newline
	putchar('\n');
	return r;
}
