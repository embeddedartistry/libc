#include <stdlib.h>

__attribute__((weak,noreturn)) void _Exit(int ec)
{
	(void)ec;

	while(1);
}
