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
	for(char c = 'a'; c <= 'z'; c++)
	{
		assert_int_not_equal(islower(c), 0);
	}
}

static void bad_input(void** state)
{
	// 97 represents 'a'
	for(int i = 0; i < 97; i++)
	{
		assert_int_equal(islower(i), 0);
	}

	for(int i = 123; i < 0x80; i++)
	{
		assert_int_equal(islower(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(islower(129), 0);
	assert_int_equal(islower(1024), 0);
	assert_int_equal(islower(15185), 0);
	assert_int_equal(islower(1808303), 0);
	assert_int_equal(islower(INT_MAX), 0);
	assert_int_equal(islower(-1), 0);
	assert_int_equal(islower(-100), 0);
	assert_int_equal(islower(-INT_MAX), 0);
}

int islower_tests(void)
{
	const struct CMUnitTest islower_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(islower_tests, NULL, NULL);
}
