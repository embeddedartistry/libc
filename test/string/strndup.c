/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "string_tests.h"
#include <stdlib.h>
#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static void strndup_test(void** state)
{
	const char* base = "this is a base string woo!";
	char* dup;

	dup = strndup(base, 3);
	assert_ptr_not_equal(dup, NULL);
	assert_int_equal(strlen(dup), 3);
	assert_int_equal(strncmp(dup, base, strlen(dup)), 0);
	free(dup);

	dup = strndup(base, strlen(base));
	assert_ptr_not_equal(dup, NULL);
	assert_int_equal(strlen(dup), 26);
	assert_int_equal(strncmp(dup, base, strlen(base)), 0);
	free(dup);

	dup = strndup(base, strlen(base) + 10);
	assert_ptr_not_equal(dup, NULL);
	assert_int_equal(strlen(dup), 26);
	assert_int_equal(strncmp(dup, base, strlen(base)), 0);
	free(dup);

	dup = strndup(NULL, 10);
	assert_ptr_equal(dup, NULL);

	dup = strndup(base, SIZE_MAX);
	assert_ptr_not_equal(dup, NULL);
	assert_int_equal(strlen(dup), 26);
	assert_int_equal(strncmp(dup, base, strlen(base)), 0);
	free(dup);
}

#pragma mark - Public Functions -

int strndup_tests(void)
{
	const struct CMUnitTest strndup_tests[] = {
		cmocka_unit_test(strndup_test),
	};

	return cmocka_run_group_tests(strndup_tests, NULL, NULL);
}
