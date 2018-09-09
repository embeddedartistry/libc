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

static void atoll_test(void** state)
{
	// Check bigger than 32-bit max
	assert_int_equal(atoll("6442450941"), 6442450941LL);
	assert_int_equal(atoll("-6442450941"), -6442450941LL);

	// Check that atol equivalent tests pass
	// Integer tests
	assert_int_equal(atoll("0"), 0);
	assert_int_equal(atoll("10"), 10);
	assert_int_equal(atoll("12345"), 12345);

	assert_int_equal(atoll("-1"), -1);
	assert_int_equal(atoll("-2147483647"), -2147483647L);

	// INT_MAX
	assert_int_equal(atoll("2147483647"), 2147483647L);

	// UINT_MAX
	assert_int_equal((unsigned)atoll("4294967295"), 4294967295L);

	// Stop at decimal
	assert_int_equal(atoll("0.1"), 0);
	assert_int_equal(atoll("1.1"), 1);
	assert_int_equal(atoll("2147483647.1232"), 2147483647L);

	// Hex doesn't work with atol
	assert_int_equal(atoll("0xFFEE"), 0);

	// Bad input
	assert_int_equal(atoll("12-a"), 12);
	assert_int_equal(atoll("-a"), 0);
	assert_int_equal(atoll("102xxa"), 102);
	assert_int_equal(atoll("a13"), 0);
}

#pragma mark - Public Functions -

int atoll_tests(void)
{
	const struct CMUnitTest atoll_tests[] = {cmocka_unit_test(atoll_test)};

	return cmocka_run_group_tests(atoll_tests, NULL, NULL);
}
