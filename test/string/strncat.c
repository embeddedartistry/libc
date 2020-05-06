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

static void strncat_test(void** state)
{
	char b[32];
	strcpy(b, "abc");

	// The following tests intentionally use a length < strlen("123456")
	// To test what strncat does in such a situation
	assert_ptr_equal(strncat(b, "123456", 3), b);

	// Check if strncat failed to null-terminate
	assert_int_equal(b[6], 0);

	// Check if the string is correct
	assert_int_equal(strcmp(b, "abc123"), 0);
}

#pragma mark - Public Functions -

int strncat_tests(void)
{
	const struct CMUnitTest strncat_tests[] = {
		cmocka_unit_test(strncat_test),
	};

	return cmocka_run_group_tests(strncat_tests, NULL, NULL);
}
