#include <printf.h>
#include <stdio.h>

int putchar(int c)
{
	putchar_((char)c);
	return c;
}
