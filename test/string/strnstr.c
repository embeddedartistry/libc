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

static void strnstr_test(void** state)
{
	(void)state;
	char buf[10] = "man tees";

	char* r = strnstr(buf, "tees", 10);
	assert_string_equal(r, "tees");
}

static void strnstr_test_null(void** state)
{
	(void)state;
	char buf[10] = "man tees";

	char* r = strnstr(buf, "te", 5);
	assert_null(r);
}

#pragma mark - Public Functions -

int strnstr_tests(void)
{
	const struct CMUnitTest strnstr_tests[] = {
		cmocka_unit_test(strnstr_test),
		cmocka_unit_test(strnstr_test_null),
	};

	return cmocka_run_group_tests(strnstr_tests, NULL, NULL);
}
