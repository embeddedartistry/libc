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

static void strtoll_test(void** state)
{
	const char* s;
	char* c;

	if(sizeof(long long) == 8)
	{
		assert_int_equal(strtoll(s = "9223372036854775808", &c, 0), 9223372036854775807LL);
		assert_int_equal(c - s, 19);
		assert_int_equal(strtoll(s = "-9223372036854775809", &c, 0), -9223372036854775807LL - 1);
		assert_int_equal(c - s, 20);
	}
	else
	{
		assert_false("sizeof(long long) not implmented!\n");
	}

	// Run some basic checks
	assert_int_equal(strtoll("z", 0, 36), 35);
	assert_int_equal(strtoll("00010010001101000101011001111000", 0, 2), 0x12345678);
	assert_int_equal(strtoll(s = "0F5F", &c, 16), 0x0f5f);

	assert_int_equal(strtoll(s = "0xz", &c, 16), 0);
	assert_int_equal(c - s, 0);

	assert_int_equal(strtoll(s = "0x1234", &c, 16), 0x1234);
	assert_int_equal(c - s, 6);

	c = NULL;
	assert_int_equal(strtoll(s = "123", &c, 37), 0);
	assert_int_equal(c - s, 0);

	assert_int_equal(strtoll(s = "  15437", &c, 8), 015437);
	assert_int_equal(c - s, 7);

	assert_int_equal(strtoll(s = "  1", &c, 0), 1);
	assert_int_equal(c - s, 3);
}

#pragma mark - Public Functions -

int strtoll_tests(void)
{
	const struct CMUnitTest strtoll_tests[] = {cmocka_unit_test(strtoll_test)};

	return cmocka_run_group_tests(strtoll_tests, NULL, NULL);
}
