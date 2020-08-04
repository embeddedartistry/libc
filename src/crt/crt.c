#include "crt.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern int __bss_start__;
extern int __bss_end__;
extern void (*__preinit_array_start[])(void) __attribute__((weak));
extern void (*__preinit_array_end[])(void) __attribute__((weak));
extern void (*__init_array_start[])(void) __attribute__((weak));
extern void (*__init_array_end[])(void) __attribute__((weak));
extern void (*__fini_array_start[])(void) __attribute__((weak));
extern void (*__fini_array_end[])(void) __attribute__((weak));
extern int main();

__attribute__((weak)) int entry(void)
{
	CRTStartup();
	return main();
}

// This function may call another function which changes __stack_chk_guard
__attribute__((no_stack_protector)) void __libc_init_array(void)
{
	size_t count = (size_t)((uintptr_t)__preinit_array_end - (uintptr_t)__preinit_array_start);
	for(size_t i = 0; i < count; i++)
	{
		__preinit_array_start[i]();
	}

	count = (size_t)((uintptr_t)__init_array_end - (uintptr_t)__init_array_start);
	for(size_t i = 0; i < count; i++)
	{
		__init_array_start[i]();
	}
}

void __libc_fini_array(void)
{
	size_t count = (size_t)((uintptr_t)__fini_array_end - (uintptr_t)__fini_array_start);
	for(size_t i = count; i > 0; i--)
	{
		__fini_array_start[i-1]();
	}
}

// This function may call another function which changes __stack_chk_guard
__attribute__((no_stack_protector)) void CRTStartup(void)
{
	memset(&__bss_start__, 0, (uintptr_t)&__bss_end__ - (uintptr_t)&__bss_start__);

	__libc_init_array();

	// TODO: handle relocs?
}
