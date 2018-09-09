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
	assert_int_not_equal(isspace(' '), 0);
	assert_int_not_equal(isspace('\n'), 0);
	assert_int_not_equal(isspace('\t'), 0);
	assert_int_not_equal(isspace(11), 0);
	assert_int_not_equal(isspace(12), 0);
	assert_int_not_equal(isspace(13), 0);
}

static void bad_input(void** state)
{
	// 9 represents '\t'
	for(int i = 0; i < 9; i++)
	{
		assert_int_equal(isspace(i), 0);
	}

	// 32 represents ' '
	for(int i = 16; i < 32; i++)
	{
		assert_int_equal(isspace(i), 0);
	}

	for(int i = 33; i < 0x80; i++)
	{
		assert_int_equal(isspace(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(isspace(129), 0);
	assert_int_equal(isspace(1024), 0);
	assert_int_equal(isspace(15185), 0);
	assert_int_equal(isspace(1808303), 0);
	assert_int_equal(isspace(INT_MAX), 0);
	assert_int_equal(isspace(-1), 0);
	assert_int_equal(isspace(-100), 0);
	assert_int_equal(isspace(-INT_MAX), 0);
}

int isspace_tests(void)
{
	const struct CMUnitTest isspace_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(isspace_tests, NULL, NULL);
}
