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
	for(char c = '!'; c <= '/'; c++)
	{
		assert_int_not_equal(ispunct(c), 0);
	}

	for(char c = ':'; c <= '@'; c++)
	{
		assert_int_not_equal(ispunct(c), 0);
	}

	for(char c = '['; c <= '`'; c++)
	{
		assert_int_not_equal(ispunct(c), 0);
	}

	for(char c = '{'; c <= '~'; c++)
	{
		assert_int_not_equal(ispunct(c), 0);
	}
}

static void bad_input(void** state)
{
	for(int i = 0; i < '!'; i++)
	{
		assert_int_equal(ispunct(i), 0);
	}

	for(int i = '0'; i < '9'; i++)
	{
		assert_int_equal(ispunct(i), 0);
	}

	for(int i = 'A'; i < 'Z'; i++)
	{
		assert_int_equal(ispunct(i), 0);
	}

	for(int i = 'a'; i < 'z'; i++)
	{
		assert_int_equal(ispunct(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(ispunct(127), 0);
	assert_int_equal(ispunct(128), 0);
	assert_int_equal(ispunct(129), 0);
	assert_int_equal(ispunct(1024), 0);
	assert_int_equal(ispunct(15185), 0);
	assert_int_equal(ispunct(1808303), 0);
	assert_int_equal(ispunct(INT_MAX), 0);
	assert_int_equal(ispunct(-1), 0);
	assert_int_equal(ispunct(-100), 0);
	assert_int_equal(ispunct(-INT_MAX), 0);
}

int ispunct_tests(void)
{
	const struct CMUnitTest ispunct_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(ispunct_tests, NULL, NULL);
}
