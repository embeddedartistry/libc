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

static void strncmp_test(void** state)
{
	// Check if strncmp compares past n
	assert_int_equal(strncmp("abcd", "abce", 3), 0);

	// Check if strncmp fails to compare n-1st byte
	assert_int_equal(!!strncmp("abc", "abd", 3), 1);
}

#pragma mark - Public Functions -

int strncmp_tests(void)
{
	const struct CMUnitTest strncmp_tests[] = {
		cmocka_unit_test(strncmp_test),
	};

	return cmocka_run_group_tests(strncmp_tests, NULL, NULL);
}
