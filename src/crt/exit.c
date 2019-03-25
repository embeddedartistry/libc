#include <stdlib.h>

__attribute__((weak, noreturn)) void exit(int rc)
{
	_Exit(rc);
}
