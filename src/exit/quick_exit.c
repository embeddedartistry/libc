#include <stdlib.h>
#include "exit.h"

__attribute__((weak, noreturn)) void quick_exit(int code)
{
	__funcs_on_quick_exit();
	_Exit(code);
}
