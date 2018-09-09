/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "stdlib_tests.h"
#include <stdlib.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#pragma mark - Private Functions -

static void realloc_test(void** state)
{
	// TODO: realloc tests not implemented
}

#pragma mark - Public Functions -

int realloc_tests(void)
{
	const struct CMUnitTest realloc_tests[] = {cmocka_unit_test(realloc_test)};

	return cmocka_run_group_tests(realloc_tests, NULL, NULL);
}
