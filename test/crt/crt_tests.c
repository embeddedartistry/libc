/*
 * Copyright © 2020 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */
#include "crt_tests.h"
#include <stdlib.h>
#include <tests.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

int crt_tests(void)
{
	int overall_result = 0;

	if(0 != crt_array_test_suite())
	{
		overall_result = -1;
	}

	return overall_result;
}
