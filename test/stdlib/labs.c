/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "stdlib_tests.h"
#include <limits.h>
#include <stdlib.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#pragma mark - Private Functions -

static void labs_test(void** state)
{
	assert_int_equal(labs(0), 0);
	assert_int_equal(labs(1), 1);
	assert_int_equal(labs(-1), 1);
	assert_int_equal(labs(LONG_MAX), LONG_MAX);
	assert_int_equal(labs(-LONG_MAX), LONG_MAX);
	assert_int_equal(labs(LONG_MIN), LONG_MIN);

	// We add one to prevent an overflow with -LONG_MIN. We expect it to be LONG_MAX.
	assert_int_equal(labs(-(LONG_MIN + 1)), (LONG_MAX));
}

#pragma mark - Public Functions -

int labs_tests(void)
{
	const struct CMUnitTest labs_tests[] = {cmocka_unit_test(labs_test)};

	return cmocka_run_group_tests(labs_tests, NULL, NULL);
}
