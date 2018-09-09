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

static void strdup_test(void** state)
{
	const char* base = "this is a base string woo!";
	char* dup;

	dup = strdup(base);
	assert_ptr_not_equal(dup, NULL);
	assert_int_equal(strlen(dup), 26);
	assert_int_equal(strncmp(dup, base, strlen(dup)), 0);
	free(dup);

	dup = strdup(NULL);
	assert_ptr_equal(dup, NULL);
}

#pragma mark - Public Functions -

int strdup_tests(void)
{
	const struct CMUnitTest strdup_tests[] = {
		cmocka_unit_test(strdup_test),
	};

	return cmocka_run_group_tests(strdup_tests, NULL, NULL);
}
