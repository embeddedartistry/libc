/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "stdlib_tests.h"
#include <stdlib.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#pragma mark - Private Functions -

static void atoi_test(void** state)
{
	// Integer tests
	assert_int_equal(atoi("0"), 0);
	assert_int_equal(atoi("10"), 10);
	assert_int_equal(atoi("12345"), 12345);

	assert_int_equal(atoi("-1"), -1);
	assert_int_equal(atoi("-2147483647"), -2147483647);

	// INT_MAX
	assert_int_equal(atoi("2147483647"), 2147483647);

	// UINT_MAX
	assert_int_equal((unsigned)atoi("4294967295"), 4294967295);

	// Stop at decimal
	assert_int_equal(atoi("0.1"), 0);
	assert_int_equal(atoi("1.1"), 1);
	assert_int_equal(atoi("2147483647.1232"), 2147483647);

	// Hex doesn't work with atoi
	assert_int_equal(atoi("0xFFEE"), 0);

	// Bad input
	assert_int_equal(atoi("12-a"), 12);
	assert_int_equal(atoi("-a"), 0);
	assert_int_equal(atoi("102xxa"), 102);
	assert_int_equal(atoi("a13"), 0);
}

#pragma mark - Public Functions -

int atoi_tests(void)
{
	const struct CMUnitTest atoi_tests[] = {cmocka_unit_test(atoi_test)};

	return cmocka_run_group_tests(atoi_tests, NULL, NULL);
}
