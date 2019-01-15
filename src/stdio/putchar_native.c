#include <printf.h>
#include <stdio.h>

extern long write(int, const char*, unsigned long);

void _putchar(char ch)
{
	(void)write(1, &ch, 1);
}
