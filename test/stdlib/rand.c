/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include <stdlib.h>
#include "stdlib_tests.h"

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka/cmocka.h>
// clang-format on

#pragma mark - Private Functions -

static void rand_test(void** state)
{
#warning rand tests not implemented
}

#pragma mark - Public Functions -

int rand_tests(void)
{
	const struct CMUnitTest rand_tests[] = {cmocka_unit_test(rand_test)};

	return cmocka_run_group_tests(rand_tests, NULL, NULL);
}
