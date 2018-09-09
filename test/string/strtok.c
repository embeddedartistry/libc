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

static void strtok_test(void** state)
{
	char b[32];
	char* s;

	strcpy(b, "abc   123; xyz; foo");

	s = strtok(b, " ");
	assert_ptr_equal(s, b);
	assert_int_equal(strcmp(s, "abc"), 0);

	s = strtok(NULL, ";");
	assert_ptr_equal(s, b + 4);
	assert_int_equal(strcmp(s, "  123"), 0);

	s = strtok(NULL, " ;");
	assert_ptr_equal(s, b + 11);
	assert_int_equal(strcmp(s, "xyz"), 0);

	s = strtok(NULL, " ;");
	assert_ptr_equal(s, b + 16);
	assert_int_equal(strcmp(s, "foo"), 0);
}

#pragma mark - Public Functions -

int strtok_tests(void)
{
	const struct CMUnitTest strtok_tests[] = {
		cmocka_unit_test(strtok_test),
	};

	return cmocka_run_group_tests(strtok_tests, NULL, NULL);
}
