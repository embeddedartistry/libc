#include <stdlib.h>

__attribute__((weak)) int atexit(void (*function)(void))
{
	(void)function;
	// EA libc does not exit on bare metal systems
	return 0;
}
