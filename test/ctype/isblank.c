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
	assert_int_not_equal(isblank(' '), 0);
	assert_int_not_equal(isblank('\t'), 0);
}

static void bad_input(void** state)
{
	// 9 represents '\t'
	for(int i = 0; i < 9; i++)
	{
		assert_int_equal(isblank(i), 0);
	}

	// 32 represents ' '
	for(int i = 10; i < 32; i++)
	{
		assert_int_equal(isblank(i), 0);
	}

	for(int i = 33; i < 0x80; i++)
	{
		assert_int_equal(isblank(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(isblank(129), 0);
	assert_int_equal(isblank(1024), 0);
	assert_int_equal(isblank(15185), 0);
	assert_int_equal(isblank(1808303), 0);
	assert_int_equal(isblank(INT_MAX), 0);
	assert_int_equal(isblank(-1), 0);
	assert_int_equal(isblank(-100), 0);
	assert_int_equal(isblank(-INT_MAX), 0);
}

int isblank_tests(void)
{
	const struct CMUnitTest isblank_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(isblank_tests, NULL, NULL);
}
