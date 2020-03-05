/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "string_tests.h"
#include <stdint.h>
#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static void strnlen_test(void** state)
{
	assert_int_equal(strnlen("", 1), 0);
	assert_int_equal(strnlen("a", 1), 1);
	assert_int_equal(strnlen("a", 2), 1);
	assert_int_equal(strnlen("ab", 1), 1);
	assert_int_equal(strnlen("ab", SIZE_MAX), 2);
	assert_int_equal(strnlen("ab", (size_t)-2), 2);
	assert_int_equal(strnlen("ab", 0), 0);
}

#pragma mark - Public Functions -

int strnlen_tests(void)
{
	const struct CMUnitTest strnlen_tests[] = {
		cmocka_unit_test(strnlen_test),
	};

	return cmocka_run_group_tests(strnlen_tests, NULL, NULL);
}
