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

static void bsearch_test(void** state)
{
	// TODO bsearch test not implemented!
}

#pragma mark - Public Functions -

int bsearch_tests(void)
{
	const struct CMUnitTest bsearch_tests[] = {cmocka_unit_test(bsearch_test)};

	return cmocka_run_group_tests(bsearch_tests, NULL, NULL);
}
