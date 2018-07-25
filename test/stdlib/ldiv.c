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

static void ldiv_test(void** state)
{
#warning ldiv tests not implemented
}

#pragma mark - Public Functions -

int ldiv_tests(void)
{
	const struct CMUnitTest ldiv_tests[] = {cmocka_unit_test(ldiv_test)};

	return cmocka_run_group_tests(ldiv_tests, NULL, NULL);
}
