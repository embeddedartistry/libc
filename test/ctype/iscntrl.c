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
	for(int i = 0; i < 0x20; i++)
	{
		assert_int_not_equal(iscntrl(i), 0);
	}

	assert_int_not_equal(iscntrl(0x7f), 0);
}

static void bad_input(void** state)
{
	for(int i = 0x20; i < 0x7F; i++)
	{
		assert_int_equal(iscntrl(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(iscntrl(129), 0);
	assert_int_equal(iscntrl(1024), 0);
	assert_int_equal(iscntrl(15185), 0);
	assert_int_equal(iscntrl(1808303), 0);
	assert_int_equal(iscntrl(INT_MAX), 0);
	assert_int_equal(iscntrl(-1), 0);
	assert_int_equal(iscntrl(-100), 0);
	assert_int_equal(iscntrl(-INT_MAX), 0);
}

int iscntrl_tests(void)
{
	const struct CMUnitTest iscntrl_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(iscntrl_tests, NULL, NULL);
}
