#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma mark - Declarations -

#ifndef STACK_CHK_GUARD_VALUE
#if UINTPTR_MAX == UINT32_MAX
#define STACK_CHK_GUARD_VALUE 0xa5f3cc8d
#else
#define STACK_CHK_GUARD_VALUE 0xdeadbeefa55a857
#endif
#endif

/** Stack check guard variable
*
* The value of this variable is used as a stack canary to detect
* whether an overflow has occurred.
*/
uintptr_t __stack_chk_guard = STACK_CHK_GUARD_VALUE;

#pragma mark - Implementations -

__attribute__((weak,noreturn)) void __stack_chk_fail(void)
{
	printf("Stack overflow detected! Aborting program.\n");
	abort();
}
