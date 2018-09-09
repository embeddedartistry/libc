/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "ctype_tests.h"
#include <ctype.h>
#include <limits.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static void good_input(void** state)
{
	for(char c = 'A'; c <= 'Z'; c++)
	{
		assert_int_equal(tolower(c), c + 32);
	}
}

static void bad_input(void** state)
{
	for(int i = 0; i < 'A'; i++)
	{
		assert_int_equal(tolower(i), i);
	}

	for(int i = 91; i < 0x80; i++)
	{
		assert_int_equal(tolower(i), i);
	}

	// Remaining integers spot check
	assert_int_equal(tolower(1024), 1024);
	assert_int_equal(tolower(15185), 15185);
	assert_int_equal(tolower(1808303), 1808303);
	assert_int_equal(tolower(INT_MAX), INT_MAX);
	assert_int_equal(tolower(-1), -1);
	assert_int_equal(tolower(-100), -100);
	assert_int_equal(tolower(-INT_MAX), -INT_MAX);
}

int tolower_tests(void)
{
	const struct CMUnitTest tolower_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(tolower_tests, NULL, NULL);
}
