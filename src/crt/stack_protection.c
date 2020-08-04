#include <crt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef STACK_CHK_GUARD_VALUE
#if UINTPTR_MAX == UINT32_MAX
#define STACK_CHK_GUARD_VALUE 0xa5f3cc8d
#else
#define STACK_CHK_GUARD_VALUE 0xdeadbeefa55a8572
#endif
#endif

#ifdef DISABLE_STACK_CHK_GUARD_RUNTIME_CONFIG
__attribute__((weak)) uintptr_t __stack_chk_guard = STACK_CHK_GUARD_VALUE;
#else
/** Stack check guard variable
 *
 * The value of this variable is used as a stack canary to detect
 * whether an overflow has occurred.
 */
__attribute__((weak)) uintptr_t __stack_chk_guard = 0;

/*
 * Stack protection *must* be disabled for this function. In the case of
 * -fstack-protector-all, this function will fail the check because it
 * changes the value of __stack_chk_guard.
 */
static void __attribute__((constructor, no_stack_protector)) __construct_stk_chk_guard()
{
	if(__stack_chk_guard == 0)
	{
		__stack_chk_guard = __stack_chk_guard_init();
	}
}

__attribute__((weak)) uintptr_t __stack_chk_guard_init(void)
{
	return STACK_CHK_GUARD_VALUE;
}
#endif // ! DISABLE_STACK_CHK_GUARD_RUNTIME_CONFIG

__attribute__((weak, noreturn)) void __stack_chk_fail(void)
{
	printf("Stack overflow detected! Aborting program.\n");
	abort();
}
