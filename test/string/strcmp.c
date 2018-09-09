/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "string_tests.h"
#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static void strcmp_test(void** state)
{
	const char* s = "abc 123";

	assert_int_equal(strcmp("abc", "abc"), 0);
	assert_int_not_equal(strcmp(s, "abc"), 0);
	assert_int_not_equal(strcmp("abc", s), 0);
	assert_int_not_equal(strcmp("abc", NULL), 0);
	assert_int_not_equal(strcmp(NULL, "abc"), 0);

	// Check that two NULL strings will match
	assert_int_equal(strcmp(NULL, NULL), 0);

	// Check directionality of return
	assert_int_equal(!!(strcmp(s, "abc") > 0), 1);
	assert_int_equal(!!(strcmp("abc", s) < 0), 1);
}

#pragma mark - Public Functions -

int strcmp_tests(void)
{
	const struct CMUnitTest strcmp_tests[] = {
		cmocka_unit_test(strcmp_test),
	};

	return cmocka_run_group_tests(strcmp_tests, NULL, NULL);
}
