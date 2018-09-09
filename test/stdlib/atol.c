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

static void atol_test(void** state)
{
	if(sizeof(long) == 8)
	{
		// Check bigger than 32-bit max
		assert_int_equal(atol("6442450941"), 6442450941L);
		assert_int_equal(atol("-6442450941"), -6442450941L);
	}

	// Check that atol equivalent tests pass
	// Integer tests
	assert_int_equal(atol("0"), 0);
	assert_int_equal(atol("10"), 10);
	assert_int_equal(atol("12345"), 12345);

	assert_int_equal(atol("-1"), -1);
	assert_int_equal(atol("-2147483647"), -2147483647L);

	// INT_MAX
	assert_int_equal(atol("2147483647"), 2147483647L);

	// UINT_MAX
	assert_int_equal((unsigned)atol("4294967295"), 4294967295L);

	// Stop at decimal
	assert_int_equal(atol("0.1"), 0);
	assert_int_equal(atol("1.1"), 1);
	assert_int_equal(atol("2147483647.1232"), 2147483647L);

	// Hex doesn't work with atol
	assert_int_equal(atol("0xFFEE"), 0);

	// Bad input
	assert_int_equal(atol("12-a"), 12);
	assert_int_equal(atol("-a"), 0);
	assert_int_equal(atol("102xxa"), 102);
	assert_int_equal(atol("a13"), 0);
}

#pragma mark - Public Functions -

int atol_tests(void)
{
	const struct CMUnitTest atol_tests[] = {cmocka_unit_test(atol_test)};

	return cmocka_run_group_tests(atol_tests, NULL, NULL);
}
