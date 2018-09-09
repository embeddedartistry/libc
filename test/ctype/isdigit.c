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
	for(char c = '0'; c <= '9'; c++)
	{
		assert_int_not_equal(isdigit(c), 0);
	}
}

static void bad_input(void** state)
{
	// 48 represents '0'
	for(int i = 0; i < 48; i++)
	{
		assert_int_equal(isdigit(i), 0);
	}

	for(int i = 58; i < 0x80; i++)
	{
		assert_int_equal(isdigit(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(isdigit(123), 0);
	assert_int_equal(isdigit(1024), 0);
	assert_int_equal(isdigit(15185), 0);
	assert_int_equal(isdigit(1808303), 0);
	assert_int_equal(isdigit(INT_MAX), 0);
	assert_int_equal(isdigit(-1), 0);
	assert_int_equal(isdigit(-100), 0);
	assert_int_equal(isdigit(-INT_MAX), 0);
}

int isdigit_tests(void)
{
	const struct CMUnitTest isdigit_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(isdigit_tests, NULL, NULL);
}
