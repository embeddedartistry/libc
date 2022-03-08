/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

// CMocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#include <tests.h>

int main(void)
{
	int overall_result = 0;

	overall_result |= ctype_tests();
	overall_result |= string_tests();
	overall_result |= stdlib_tests();
#ifdef ENABLE_CRT_TESTING
	overall_result |= crt_tests();
#endif

	return overall_result;
}
