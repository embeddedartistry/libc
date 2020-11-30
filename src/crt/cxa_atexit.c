#include <stdlib.h>

int __cxa_atexit(void (*function)(void*), void* arg, void* dso);

/// Embedded Artistry libc does not exit on baremetal systems, so this function does nothing.
__attribute__((weak)) int __cxa_atexit(void (*function)(void*), void* arg, void* dso)
{
	(void)function;
	(void)arg;
	(void)dso;

	return 0;
}

// We aren't using shared libraries, so __dso_handle can be set to NULL
void* __dso_handle = NULL;
