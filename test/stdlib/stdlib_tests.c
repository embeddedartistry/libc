/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */
#include "stdlib_tests.h"
#include <stdlib.h>
#include <tests.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

int stdlib_tests(void)
{
	int overall_result = 0;

	overall_result |= abs_tests();
	overall_result |= atof_tests();
	overall_result |= atoi_tests();
	overall_result |= atol_tests();
	overall_result |= atoll_tests();
	overall_result |= bsearch_tests();
	overall_result |= calloc_tests();
	overall_result |= div_tests();
	// overall_result |= heapsort_r_tests();
	overall_result |= heapsort_tests();
	overall_result |= imaxabs_tests();
	overall_result |= imaxdiv_tests();
	overall_result |= labs_tests();
	overall_result |= ldiv_tests();
	overall_result |= llabs_tests();
	overall_result |= lldiv_tests();
	overall_result |= qsort_r_tests();
	overall_result |= qsort_tests();
	overall_result |= rand_tests();
	overall_result |= realloc_tests();
	overall_result |= strtod_tests();
	overall_result |= strtof_tests();
	overall_result |= strtol_tests();
	overall_result |= strtoll_tests();
	overall_result |= strtoul_tests();
	overall_result |= strtoull_tests();

	return overall_result;
}
