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

/* r = place to store result
 * f = function call to test (or any expression)
 * x = expected result
 * m = message to print on failure (with formats for r & x)
 **/

#pragma mark - Private Functions -

static void strtol_test(void** state)
{
	const char* s;
	char* c;

	assert_int_equal(strtol("2147483647", 0, 0), 2147483647L); // max 32-bit signed

	if(sizeof(long) == 4)
	{
		// Check for uncaught overflows
		assert_int_equal(strtol(s = "2147483648", &c, 0), 2147483647L);
		assert_int_equal(c - s, 10);
		assert_int_equal(strtol(s = "-2147483649", &c, 0), -2147483647L - 1);
		assert_int_equal(c - s, 11);
	}
	else if(sizeof(long) == 8)
	{
		// Check overflows
		assert_int_equal(strtol(s = "9223372036854775808", &c, 0), 9223372036854775807L);
		assert_int_equal(c - s, 19);
		assert_int_equal(strtol(s = "-9223372036854775809", &c, 0), -9223372036854775807L - 1);
		assert_int_equal(c - s, 20);
	}
	else
	{
		assert_false("sizeof(long) not implemented!\n");
	}

	assert_int_equal(strtol("z", 0, 36), 35);
	assert_int_equal(strtol("00010010001101000101011001111000", 0, 2), 0x12345678);
	assert_int_equal(strtol(s = "0F5F", &c, 16), 0x0f5f);

	assert_int_equal(strtol(s = "0xz", &c, 16), 0);
	assert_int_equal(c - s, 0);

	assert_int_equal(strtol(s = "0x1234", &c, 16), 0x1234);
	assert_int_equal(c - s, 6);

	c = NULL;
	assert_int_equal(strtol(s = "123", &c, 37), 0);
	assert_int_equal(c - s, 0);

	assert_int_equal(strtol(s = "  15437", &c, 8), 015437);
	assert_int_equal(c - s, 7);

	assert_int_equal(strtol(s = "  1", &c, 0), 1);
	assert_int_equal(c - s, 3);
}

#pragma mark - Public Functions -

int strtol_tests(void)
{
	const struct CMUnitTest strtol_tests[] = {cmocka_unit_test(strtol_test)};

	return cmocka_run_group_tests(strtol_tests, NULL, NULL);
}
