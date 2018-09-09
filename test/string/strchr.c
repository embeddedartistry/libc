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

#pragma mark - Definitions -

static void strchr_test(void** state)
{
	char b[32];
	strcpy(b, "aaababccdd0001122223");
	assert_ptr_equal(b + 3, strchr(b, 'b'));
}

#pragma mark - Public Functions -

int strchr_tests(void)
{
	const struct CMUnitTest strchr_tests[] = {
		cmocka_unit_test(strchr_test),
	};

	return cmocka_run_group_tests(strchr_tests, NULL, NULL);
}
