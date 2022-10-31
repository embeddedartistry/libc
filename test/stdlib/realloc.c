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
#include <string.h>
#include <cmocka.h>
// clang-format on

#define CALLOC_TEST_SIZE 1024

#pragma mark - Private Functions -

static void realloc_test_larger(void** state)
{
	uint8_t* p = calloc(CALLOC_TEST_SIZE, 1);
	assert_non_null(p);
	memset(p, 42, CALLOC_TEST_SIZE * 1);
	p = realloc(p, CALLOC_TEST_SIZE * 2);
	assert_non_null(p);
	for(int i = 0; i < CALLOC_TEST_SIZE; i++)
	{
		assert_true(p[i] == 42);
	}
}

static void realloc_test_smaller(void** state)
{
	uint8_t* p = calloc(CALLOC_TEST_SIZE, 1);
	assert_non_null(p);
	memset(p, 42, CALLOC_TEST_SIZE * 1);
	p = realloc(p, CALLOC_TEST_SIZE / 2);
	assert_non_null(p);
	for(int i = 0; i < CALLOC_TEST_SIZE / 2; i++)
	{
		assert_true(p[i] == 42);
	}
}
#pragma mark - Public Functions -

int realloc_tests(void)
{
	const struct CMUnitTest realloc_tests[] = {cmocka_unit_test(realloc_test_larger),
											   cmocka_unit_test(realloc_test_smaller)};

	return cmocka_run_group_tests(realloc_tests, NULL, NULL);
}
