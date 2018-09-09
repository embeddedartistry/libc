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
	for(int c = 0x21; c < 0x7F; c++)
	{
		assert_int_not_equal(isgraph(c), 0);
	}
}

static void bad_input(void** state)
{
	for(int i = 0; i < 0x21; i++)
	{
		assert_int_equal(isgraph(i), 0);
	}

	// Remaining integers spot check
	assert_int_equal(isgraph(127), 0);
	assert_int_equal(isgraph(129), 0);
	assert_int_equal(isgraph(1024), 0);
	assert_int_equal(isgraph(15185), 0);
	assert_int_equal(isgraph(1808303), 0);
	assert_int_equal(isgraph(INT_MAX), 0);
	assert_int_equal(isgraph(-1), 0);
	assert_int_equal(isgraph(-100), 0);
	assert_int_equal(isgraph(-INT_MAX), 0);
}

int isgraph_tests(void)
{
	const struct CMUnitTest isgraph_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(isgraph_tests, NULL, NULL);
}
