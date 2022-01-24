#include <stdint.h>
#include <stdio.h>
#include <string.h>

void stack_overflows_here();
uintptr_t __stack_chk_guard_init();

const char* buffer_long = "This is a long long string";

uintptr_t __stack_chk_guard_init()
{
	return 0xbeeffeeda5a5a5a5;
}

void stack_overflows_here()
{
	char buffer_short[20];

	strcpy(buffer_short, buffer_long);

	printf("Overflow case run.\n");
}

int main(void)
{
	extern uintptr_t __stack_chk_guard;
	printf("Running stack overflow test program. Canary value: 0x%p\n", (void*)__stack_chk_guard);

	stack_overflows_here();

	return 0;
}
