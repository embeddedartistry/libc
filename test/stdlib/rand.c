/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "stdlib_tests.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#pragma mark - Private Functions -

static void rand_test(void** state)
{
	const unsigned int test_seed = 12345;

	/* test if rand_r affects the seed */
	srand(test_seed);
	int rand_out = rand();

	srand(test_seed);
	unsigned int rand_r_ctx = 5732;
	rand_r(&rand_r_ctx);
	int rand_r_out = rand(); /* should be the same as before if rand_r is correct */

	assert_true(rand_out == rand_r_out);

	/* test how random `rand` really is */
	srand(time(NULL));

	const unsigned int amount = 65536; /* must be power of 2 because of mean algo */
	int values[amount];
	for(unsigned int i = 0; i < amount; i++)
	{
		values[i] = rand();
	}

	/* mean algo with O(nlog n) */
	for(unsigned int j = 2; j <= amount; j *= 2)
	{
		for(unsigned int i = 0; i < amount; i += j)
		{
			values[i] = ((long)values[i] + (long)values[i + j / 2]) / 2;
		}
	}

	/* 1.554 435 122 * 10^−26% chance of failing even if rand is sufficient */
	assert_true(values[0] - INT_MAX / 2 < 1048576);
	assert_true(values[0] - INT_MAX / 2 > -1048576);
}

#pragma mark - Public Functions -

int rand_tests(void)
{
	const struct CMUnitTest rand_tests[] = {cmocka_unit_test(rand_test)};

	return cmocka_run_group_tests(rand_tests, NULL, NULL);
}
