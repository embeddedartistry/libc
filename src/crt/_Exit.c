#include <stdlib.h>

__attribute__((weak, noreturn)) void _Exit(int ec)
{
	// __libc_fini_array

	(void)ec;

	while(1)
	{
		;
	}
}
