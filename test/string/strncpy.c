/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "string_tests.h"
#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static void strncpy_test(void** state)
{
	char b[32];
	b[16] = 'a';
	b[17] = 'b';
	b[18] = 'c';
	b[19] = 0;

	// Check return values
	assert_ptr_equal(memset(b, 'x', sizeof b), b);
	assert_ptr_equal(strncpy(b, "abc", sizeof b - 1), b);

	// Check if strncpy fails to zero-pad dest
	assert_int_equal(memcmp(b, "abc\0\0\0\0", 8), 0);

	// Check if strncpy overruns buffer when n > strlen(src)
	assert_int_not_equal(b[sizeof b - 1], 0);

	b[3] = 'x';
	b[4] = 0;
	strncpy(b, "abc", 3);

	// Check if strncpy fails to copy last byte
	assert_int_equal(b[2], 'c');

	// Check if strncpy overruns buffer to null-terminate
	assert_int_equal(b[3], 'x');
}

#pragma mark - Public Functions -

int strncpy_tests(void)
{
	const struct CMUnitTest strncpy_tests[] = {
		cmocka_unit_test(strncpy_test),
	};

	return cmocka_run_group_tests(strncpy_tests, NULL, NULL);
}
