#include <stdlib.h>

__attribute__((weak, noreturn)) void abort(void)
{
	_Exit(127);
}
