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

#define CALLOC_TEST_SIZE 1024

#pragma mark - Private Functions -

static void calloc_test(void** state)
{
	uint8_t* p = calloc(1, CALLOC_TEST_SIZE);

	assert_non_null(p);

	for(int i = 0; i < CALLOC_TEST_SIZE; i++)
	{
		assert_int_equal(p[i], 0);
	}

	free(p);

	p = calloc(CALLOC_TEST_SIZE, 1);
	assert_non_null(p);

	for(int i = 0; i < CALLOC_TEST_SIZE; i++)
	{
		assert_int_equal(p[i], 0);
	}

	free(p);
}

#pragma mark - Public Functions -

int calloc_tests(void)
{
	const struct CMUnitTest calloc_tests[] = {cmocka_unit_test(calloc_test)};

	return cmocka_run_group_tests(calloc_tests, NULL, NULL);
}
