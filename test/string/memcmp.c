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

static void memcmp_test(void** state)
{
	const char* s = "abc 123";

	assert_int_equal(memcmp("abc", "abc", 4), 0);
	assert_int_equal(memcmp(s, "abc", 3), 0);
	assert_int_equal(memcmp("abc", s, 3), 0);

	// The following tests intentionally use a length > 3
	// To test what memcmp does in such a situation
	assert_int_equal(!!(memcmp(s, "abc", 6) > 0), 1);
	assert_int_equal(!!(memcmp("abc", s, 6) < 0), 1);

	// If the compiler built-in is used, these tests will trigger a segfault
#ifndef BUILTINS_ARE_ENABLED
	// Check NULL input handling
	assert_int_not_equal(memcmp("abc", NULL, 3), 0);
	assert_int_not_equal(memcmp(NULL, "abc", 3), 0);
#endif

	// Check that two NULL strings will match
	assert_int_equal(memcmp(NULL, NULL, 0), 0);
}

#pragma mark - Public Functions -

int memcmp_tests(void)
{
	const struct CMUnitTest memcmp_tests[] = {
		cmocka_unit_test(memcmp_test),
	};

	return cmocka_run_group_tests(memcmp_tests, NULL, NULL);
}
