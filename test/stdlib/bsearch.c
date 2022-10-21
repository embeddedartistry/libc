/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "stdlib_tests.h"
#include <stdlib.h>
#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static const char* s[] = {"Bob",	"Alice", "John",   "Ceres",	  "Helga",	 "Drepper", "Emeralda",
						  "Zoran",	"Momo",	 "Frank",  "Pema",	  "Xavier",	 "Yeva",	"Gedun",
						  "Irina",	"Nono",	 "Wiener", "Vincent", "Tsering", "Karnica", "Lulu",
						  "Quincy", "Osama", "Riley",  "Ursula",  "Sam"};

static int n[] = {879045, 394,	99405644, 33434, 232323, 4334,	  5454,	 343,
				  45545,  454,	324,	  22,	 34344,	 233,	  45345, 343,
				  848405, 3434, 3434344,  3535,	 93994,	 2230404, 4334};

static int cmp64(const void* a, const void* b)
{
	const uint64_t *ua = a, *ub = b;
	return *ua < *ub ? -1 : *ua != *ub;
}

static int icmp(const void* a, const void* b)
{
	return *(const int*)a - *(const int*)b;
}

static int scmp(const void* a, const void* b)
{
	return strcmp(*(char* const*)a, *(char* const*)b);
}

static int ccmp(const void* a, const void* b)
{
	return *(const char*)a - *(const char*)b;
}

static void bsearch_string_test(void** state)
{
	const char* key = "Ceres";
	const char** res = bsearch(&key, s, sizeof s / sizeof s[0], sizeof s[0], ccmp);

	assert_string_equal(*res, "Ceres");
	assert_string_equal(*res, key);
}

static void bsearch_string_test_element_not_found(void** state)
{
	const char* key = "Hello";
	char* res = bsearch(&key, s, sizeof s / sizeof s[0], sizeof s[0], scmp);

	assert_null(res);
}

static void bsearch_int_test(void** state)
{
	int key = 3535;
	int* res = bsearch(&key, n, sizeof n / sizeof n[0], sizeof n[0], icmp);

	assert_int_equal(*res, key);
}

static void bsearch_int_test_enf(void** state) // enf : element not found
{
	int key = 5;
	int res = bsearch(&key, n, sizeof n / sizeof n[0], sizeof n[0], cmp64);

	assert_null(res);
}

#pragma mark - Private Functions -

#pragma mark - Public Functions -

int bsearch_tests(void)
{
	const struct CMUnitTest bsearch_tests[] = {
		cmocka_unit_test(bsearch_string_test),
		cmocka_unit_test(bsearch_string_test_element_not_found), cmocka_unit_test(bsearch_int_test),
		cmocka_unit_test(bsearch_int_test_enf)

	};

	return cmocka_run_group_tests(bsearch_tests, NULL, NULL);
}
