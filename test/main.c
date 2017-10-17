/*
* Copyright © 2017 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

// CMocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka/cmocka.h>
// clang-format on

extern int ctype_tests(void);
extern int string_tests(void);

int main(void)
{
	int overall_result = 0;

	// Generate JUnit results
	cmocka_set_message_output(CM_OUTPUT_XML);

	if(0 != ctype_tests())
	{
		overall_result = -1;
	}

	if(0 != string_tests())
	{
		overall_result = -1;
	}

	return overall_result;
}
