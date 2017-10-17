/*
* Copyright © 2017 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka/cmocka.h>
// clang-format on

static void strnstr_test(void** state)
{
#warning "strnstr tests need to be implemented"
	return;
}

#pragma mark - Public Functions -

int strnstr_tests(void)
{
	const struct CMUnitTest strnstr_tests[] = {
		cmocka_unit_test(strnstr_test),
	};

	return cmocka_run_group_tests(strnstr_tests, NULL, NULL);
}
