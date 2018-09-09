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
		assert_int_not_equal(isalnum(c), 0);
	}
	for(char c = 'A'; c <= 'Z'; c++)
	{
		assert_int_not_equal(isalnum(c), 0);
	}
	for(char c = '0'; c <= '9'; c++)
	{
		assert_int_not_equal(isalnum(c), 0);
	}
}

static void bad_input(void** state)
{
	// 48 represents '0'
	for(int i = 0; i < 48; i++)
	{
		assert_int_equal(isalnum(i), 0);
	}

	// 65 represents 'A'
	for(int i = 58; i < 65; i++)
	{
		assert_int_equal(isalnum(i), 0);
	}

	// 97 represents 'a'
	for(int i = 91; i < 97; i++)
	{
		assert_int_equal(isalnum(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(isalnum(123), 0);
	assert_int_equal(isalnum(1024), 0);
	assert_int_equal(isalnum(15185), 0);
	assert_int_equal(isalnum(1808303), 0);
	assert_int_equal(isalnum(INT_MAX), 0);
	assert_int_equal(isalnum(-1), 0);
	assert_int_equal(isalnum(-100), 0);
	assert_int_equal(isalnum(-INT_MAX), 0);
}

int isalnum_tests(void)
{
	const struct CMUnitTest isalnum_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(isalnum_tests, NULL, NULL);
}
