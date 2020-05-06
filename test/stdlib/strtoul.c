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

static void strtoul_test(void** state)
{
	const char* s;
	char* c;

	assert_int_equal(strtoul("4294967295", 0, 0), 4294967295UL); // max 32bit unsigned

	if(sizeof(long) == 4)
	{
		// Check for uncaught overflows
		assert_int_equal(strtoul(s = "4294967296", &c, 0), 4294967295UL);
		assert_int_equal(c - s, 10);

		// Check negatives
		assert_int_equal(strtoul(s = "-1", &c, 0), -1UL);
		assert_int_equal(c - s, 2);
		assert_int_equal(strtoul(s = "-2", &c, 0), -2UL);
		assert_int_equal(c - s, 2);
		assert_int_equal(strtoul(s = "-2147483648", &c, 0), -2147483648UL);
		assert_int_equal(c - s, 11);
		assert_int_equal(strtoul(s = "-2147483649", &c, 0), -2147483649UL);
		assert_int_equal(c - s, 11);

		// Check negative overflow
		assert_int_equal(strtoul(s = "-4294967296", &c, 0), 4294967295UL);
		assert_int_equal(c - s, 11);
	}
	else if(sizeof(long) == 8)
	{
		// Check overflows
		assert_int_equal(strtoul(s = "18446744073709551616", &c, 0), 18446744073709551615UL);
		assert_int_equal(c - s, 20);

		// Check negative values
		assert_int_equal(strtoul(s = "-1", &c, 0), -1UL);
		assert_int_equal(c - s, 2);
		assert_int_equal(strtoul(s = "-2", &c, 0), -2UL);
		assert_int_equal(c - s, 2);
		assert_int_equal(strtoul(s = "-9223372036854775808", &c, 0), -9223372036854775808UL);
		assert_int_equal(c - s, 20);
		assert_int_equal(strtoul(s = "-9223372036854775809", &c, 0), -9223372036854775809UL);
		assert_int_equal(c - s, 20);

		// Check negative overflows
		assert_int_equal(strtoul(s = "-18446744073709551616", &c, 0), 18446744073709551615UL);
		assert_int_equal(c - s, 21);
	}
	else
	{
		assert_false("sizeof(long) not implemented!\n");
	}
}

#pragma mark - Public Functions -

int strtoul_tests(void)
{
	const struct CMUnitTest strtoul_tests[] = {cmocka_unit_test(strtoul_test)};

	return cmocka_run_group_tests(strtoul_tests, NULL, NULL);
}
