#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#pragma mark - Prototypes -

void __stack_chk_fail(void);

#pragma mark - Declarations -

#ifndef STACK_CHK_GUARD_VALUE
#if UINTPTR_MAX == UINT32_MAX
#define STACK_CHK_GUARD_VALUE 0xa5f3cc8d
#else
#define STACK_CHK_GUARD_VALUE 0xdeadbeefa55a857
#endif
#endif

uintptr_t __stack_chk_guard = STACK_CHK_GUARD_VALUE;

#pragma mark - Implementations -

__attribute__((weak)) void __stack_chk_fail(void)
{
	printf("Stack overflow detected! Aborting program.\n");
	abort();
}
