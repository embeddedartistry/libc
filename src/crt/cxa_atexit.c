#include <stdlib.h>

__attribute__((weak)) int __cxa_atexit(void (*function)(void*), void* arg, void* d)
{
	(void)function;
	(void)arg;
	(void)d;

	// EA libc does not exit on baremetal systems
	return 0;
}

// We aren't using shared libraries, so __dso_handle can be set to NULL
void* __dso_handle = NULL;
