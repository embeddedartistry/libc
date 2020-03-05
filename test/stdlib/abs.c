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

static void abs_test(void** state)
{
	assert_int_equal(abs(0), 0);
	assert_int_equal(abs(1), 1);
	assert_int_equal(abs(-1), 1);
	assert_int_equal(abs(INT_MAX), INT_MAX);
	assert_int_equal(abs(-INT_MAX), INT_MAX);
}

#pragma mark - Public Functions -

int abs_tests(void)
{
	const struct CMUnitTest abs_tests[] = {cmocka_unit_test(abs_test)};

	return cmocka_run_group_tests(abs_tests, NULL, NULL);
}
