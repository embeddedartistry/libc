/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "stdlib_tests.h"
#include <inttypes.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#pragma mark - Private Functions -

static void imaxdiv_test(void** state)
{
	// TODO imaxdiv not being tested
}

#pragma mark - Public Functions -

int imaxdiv_tests(void)
{
	const struct CMUnitTest imaxdiv_tests[] = {cmocka_unit_test(imaxdiv_test)};

	return cmocka_run_group_tests(imaxdiv_tests, NULL, NULL);
}
