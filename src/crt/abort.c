#include <errno.h>
#include <stdlib.h>

__attribute__((weak, noreturn)) void abort(void)
{
	_Exit(ENOTSUP);
}
