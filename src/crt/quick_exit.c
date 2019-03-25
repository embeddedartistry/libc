#include <stdlib.h>

__attribute__((weak, noreturn)) void quick_exit(int rc)
{
	_Exit(rc);
}
