#include <stddef.h>
#include <string.h>
#include "crt.h"

// TODO: move exit/ into crt
// TODO: which exit functions call libc_exit_fini?
//	exit only?

extern void _init();
extern void _fini();
extern char* __bss_start__;
extern char* __bss_end__;
extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));
extern void (*__fini_array_start []) (void) __attribute__((weak));
extern void (*__fini_array_end []) (void) __attribute__((weak));

void __libc_init_array(void)
{
	size_t count, i;

	count = (size_t)__preinit_array_end - (size_t)__preinit_array_start;
	for (i = 0; i < count; i++)
	{
		__preinit_array_start[i]();
	}

	_init();

	count = (size_t)__init_array_end - (size_t)__init_array_start;
	for (i = 0; i < count; i++)
	{
		__init_array_start[i]();
	}
}

void __libc_fini_array(void)
{
	size_t count, i;

	count = (size_t)__preinit_array_end - (size_t)__preinit_array_start;
	for (i = count - 1; i >= 0; i--)
	{
		__fini_array_start[i]();
	}

	_fini();
}

void CRTStartup(void)
{
	memset(__bss_start__, 0, (size_t)__bss_end__-(size_t)__bss_start__);

	// TODO: handle relocs?
	//__libc_init_array();
}
