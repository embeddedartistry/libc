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

static void memmove_test(void** state)
{
	// TODO: "Memmove tests need to be implemented"
	return;
}

#pragma mark - Public Functions -

int memmove_tests(void)
{
	const struct CMUnitTest memmove_tests[] = {
		cmocka_unit_test(memmove_test),
	};

	return cmocka_run_group_tests(memmove_tests, NULL, NULL);
}
