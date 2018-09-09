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
	for(char c = 'a'; c <= 'f'; c++)
	{
		assert_int_not_equal(isxdigit(c), 0);
	}
	for(char c = 'A'; c <= 'F'; c++)
	{
		assert_int_not_equal(isxdigit(c), 0);
	}
	for(char c = '0'; c <= '9'; c++)
	{
		assert_int_not_equal(isxdigit(c), 0);
	}
}

static void bad_input(void** state)
{
	// 48 represents '9'
	for(int i = 0; i < 48; i++)
	{
		assert_int_equal(isxdigit(i), 0);
	}

	// 65 represents 'A'
	for(int i = 58; i < 65; i++)
	{
		assert_int_equal(isxdigit(i), 0);
	}

	// 97 represents 'a'
	for(int i = 71; i < 97; i++)
	{
		assert_int_equal(isxdigit(i), 0);
	}

	for(int i = 103; i < 0x80; i++)
	{
		assert_int_equal(isxdigit(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(isxdigit(129), 0);
	assert_int_equal(isxdigit(1024), 0);
	assert_int_equal(isxdigit(15185), 0);
	assert_int_equal(isxdigit(1808303), 0);
	assert_int_equal(isxdigit(INT_MAX), 0);
	assert_int_equal(isxdigit(-1), 0);
	assert_int_equal(isxdigit(-100), 0);
	assert_int_equal(isxdigit(-INT_MAX), 0);
}

int isxdigit_tests(void)
{
	const struct CMUnitTest isxdigit_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(isxdigit_tests, NULL, NULL);
}
