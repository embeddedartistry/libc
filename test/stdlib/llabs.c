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

static void llabs_test(void** state)
{
	assert_int_equal(llabs(0), 0);
	assert_int_equal(llabs(1), 1);
	assert_int_equal(llabs(-1), 1);
	assert_int_equal(llabs(LLONG_MAX), LLONG_MAX);
	assert_int_equal(llabs(-LLONG_MAX), LLONG_MAX);
	assert_int_equal(llabs(LLONG_MIN), LLONG_MIN);

	// We add one to prevent an overflow with -LLONG_MIN. We expect it to be LLONG_MAX.
	assert_int_equal(llabs(-(LLONG_MIN + 1)), (LLONG_MAX));
}

#pragma mark - Public Functions -

int llabs_tests(void)
{
	const struct CMUnitTest llabs_tests[] = {cmocka_unit_test(llabs_test)};

	return cmocka_run_group_tests(llabs_tests, NULL, NULL);
}
