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
	for(char c = ' '; c < 0x7F; c++)
	{
		assert_int_not_equal(isprint(c), 0);
	}
}

static void bad_input(void** state)
{
	// 65 represents 'A'
	for(int i = 0; i < ' '; i++)
	{
		assert_int_equal(isprint(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(isprint(127), 0);
	assert_int_equal(isprint(128), 0);
	assert_int_equal(isprint(129), 0);
	assert_int_equal(isprint(1024), 0);
	assert_int_equal(isprint(15185), 0);
	assert_int_equal(isprint(1808303), 0);
	assert_int_equal(isprint(INT_MAX), 0);
	assert_int_equal(isprint(-1), 0);
	assert_int_equal(isprint(-100), 0);
	assert_int_equal(isprint(-INT_MAX), 0);
}

int isprint_tests(void)
{
	const struct CMUnitTest isprint_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(isprint_tests, NULL, NULL);
}
