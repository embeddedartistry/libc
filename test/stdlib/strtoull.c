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

static void strtoull_test(void** state)
{
	const char* s;
	char* c;

	if(sizeof(long long) == 8)
	{
		assert_int_equal(strtoull(s = "18446744073709551616", &c, 0), 18446744073709551615ULL);
		assert_int_equal(c - s, 20);

		// Check negative values
		assert_int_equal(strtoull(s = "-1", &c, 0), -1ULL);
		assert_int_equal(c - s, 2);
		assert_int_equal(strtoull(s = "-2", &c, 0), -2ULL);
		assert_int_equal(c - s, 2);
		assert_int_equal(strtoull(s = "-9223372036854775808", &c, 0), -9223372036854775808ULL);
		assert_int_equal(c - s, 20);
		assert_int_equal(strtoull(s = "-9223372036854775809", &c, 0), -9223372036854775809ULL);
		assert_int_equal(c - s, 20);

		// Check negative overflow
		assert_int_equal(strtoull(s = "-18446744073709551616", &c, 0), 18446744073709551615ULL);
		assert_int_equal(c - s, 21);
	}
	else
	{
		assert_false("sizeof(long long) not implmented!\n");
	}
}

#pragma mark - Public Functions -

int strtoull_tests(void)
{
	const struct CMUnitTest strtoull_tests[] = {cmocka_unit_test(strtoull_test)};

	return cmocka_run_group_tests(strtoull_tests, NULL, NULL);
}
