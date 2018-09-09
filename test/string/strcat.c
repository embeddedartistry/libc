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

static void strcat_test(void** state)
{
	char b[32];
	strcpy(b, "abc");
	assert_ptr_equal(strcat(b, "123456"), b);

	// Check if strcat failed to null-terminate
	assert_int_equal(b[9], 0);
	assert_int_equal(strlen(b), strlen("abc") + strlen("123456"));

	// Check if the string is correct
	assert_int_equal(strcmp(b, "abc123456"), 0);
}

#pragma mark - Public Functions -

int strcat_tests(void)
{
	const struct CMUnitTest strcat_tests[] = {
		cmocka_unit_test(strcat_test),
	};

	return cmocka_run_group_tests(strcat_tests, NULL, NULL);
}
