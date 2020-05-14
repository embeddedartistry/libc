#include <stdio.h>
#include <string.h>

void stack_overflows_here();

const char* buffer_long = "This is a long long string";

void stack_overflows_here()
{
	char buffer_short[20];

	strcpy(buffer_short, buffer_long);
}

int main(void)
{
	stack_overflows_here();

	printf("This statement should not be seen\n");

	return 0;
}
