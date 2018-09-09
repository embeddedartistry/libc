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

static void strcpy_test(void** state)
{
	char b[32];
	char* s;
	b[16] = 'a';
	b[17] = 'b';
	b[18] = 'c';
	b[19] = 0;

	s = strcpy(b, b + 16);
	assert_ptr_equal(s, b);
	assert_int_equal(strcmp(s, "abc"), 0);

	s = strcpy(b + 1, b + 16);
	assert_ptr_equal(s, b + 1);
	assert_int_equal(strcmp(s, "abc"), 0);

	s = strcpy(b + 2, b + 16);
	assert_ptr_equal(s, b + 2);
	assert_int_equal(strcmp(s, "abc"), 0);

	s = strcpy(b + 3, b + 16);
	assert_ptr_equal(s, b + 3);
	assert_int_equal(strcmp(s, "abc"), 0);

	s = strcpy(b + 1, b + 17);
	assert_ptr_equal(s, b + 1);
	assert_int_equal(strcmp(s, "bc"), 0);

	s = strcpy(b + 2, b + 18);
	assert_ptr_equal(s, b + 2);
	assert_int_equal(strcmp(s, "c"), 0);

	s = strcpy(b + 3, b + 19);
	assert_ptr_equal(s, b + 3);
	assert_int_equal(strcmp(s, ""), 0);
}

#pragma mark - Public Functions -

int strcpy_tests(void)
{
	const struct CMUnitTest strcpy_tests[] = {
		cmocka_unit_test(strcpy_test),
	};

	return cmocka_run_group_tests(strcpy_tests, NULL, NULL);
}
