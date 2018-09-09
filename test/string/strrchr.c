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

static void strrchr_test(void** state)
{
	char b[32];
	strcpy(b, "aaababccdd0001122223");
	assert_ptr_equal(b + 5, strrchr(b, 'b'));
}

#pragma mark - Public Functions -

int strrchr_tests(void)
{
	const struct CMUnitTest strrchr_tests[] = {
		cmocka_unit_test(strrchr_test),
	};

	return cmocka_run_group_tests(strrchr_tests, NULL, NULL);
}
