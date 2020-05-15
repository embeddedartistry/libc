#include <stdio.h>
#include <string.h>

void stack_overflows_here();

const char* buffer_long = "This is a long long string";

void stack_overflows_here()
{
	char buffer_short[20];

	strcpy(buffer_short, buffer_long);

	printf("Overflow case run.\n");
}

int main(void)
{
	printf("Running stack overflow test program.\n");

	stack_overflows_here();

	return 0;
}
