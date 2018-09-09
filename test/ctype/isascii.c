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
	for(int i = 0; i < 0x7F; i++)
	{
		assert_int_not_equal(isascii(i), 0);
	}
}

static void bad_input(void** state)
{
	// Remaining integers spot check
	assert_int_equal(isascii(0x80), 0);
	assert_int_equal(isascii(0x100), 0);
	assert_int_equal(isascii(1024), 0);
	assert_int_equal(isascii(15185), 0);
	assert_int_equal(isascii(1808303), 0);
	assert_int_equal(isascii(INT_MAX), 0);
	assert_int_equal(isascii(-1), 0);
	assert_int_equal(isascii(-100), 0);
	assert_int_equal(isascii(-INT_MAX), 0);
}

int isascii_tests(void)
{
	const struct CMUnitTest isascii_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(isascii_tests, NULL, NULL);
}
