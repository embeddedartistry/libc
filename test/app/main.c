#include <crt.h>

int main();

__attribute__((weak)) int entry()
{
	CRTStartup();
	return main();
}

int main(void)
{
	while(1)
	{
		;
	}

	return 0;
}
