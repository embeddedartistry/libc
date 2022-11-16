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

static const char* string_set[] = {
	"Bob",	   "Alice",	  "John",	"Ceres",  "Helga", "Drepper", "Emeralda", "Zoran",	"Momo",
	"Frank",   "Pema",	  "Xavier", "Yeva",	  "Gedun", "Irina",	  "Nono",	  "Wiener", "Vincent",
	"Tsering", "Karnica", "Lulu",	"Quincy", "Osama", "Riley",	  "Ursula",	  "Sam"};

static int integer_set[] = {879045, 394,  99405644, 33434, 232323, 4334,	5454,  343,
							45545,	454,  324,		22,	   34344,  233,		45345, 343,
							848405, 3434, 3434344,	3535,  93994,  2230404, 4334};

static int cmp64(const void* a, const void* b)
{
	const uint64_t *ua = a, *ub = b;
	return *ua < *ub ? -1 : *ua != *ub;
}

static int int_cmp(const void* a, const void* b)
{
	return *(const int*)a - *(const int*)b;
}

static int string_cmp(const void* a, const void* b)
{
	return strcmp(*(char* const*)a, *(char* const*)b);
}

static void bsearch_string_test(void** state)
{
	const char* key = "Ceres";
	const char** res = bsearch(&key, string_set, sizeof(string_set) / sizeof(string_set[0]),
							   sizeof string_set[0], string_cmp);
	assert_non_null(res);
	assert_string_equal(key, *res);
}

static void bsearch_string_test_element_not_found(void** state)
{
	const char* key = "Hello";
	char* res = bsearch(&key, string_set, sizeof string_set / sizeof string_set[0],
						sizeof string_set[0], string_cmp);
	assert_null(res);
}

static void bsearch_int_test(void** state)
{
	int key = 3535;
	int* res = bsearch(&key, integer_set, sizeof integer_set / sizeof integer_set[0],
					   sizeof integer_set[0], int_cmp);
	assert_int_equal(*res, key);
}

static void bsearch_int_test_element_not_found(void** state)
{
	int key = 5;
	int* res = bsearch(&key, integer_set, sizeof integer_set / sizeof integer_set[0],
					   sizeof integer_set[0], cmp64);
	assert_null(res);
}

#pragma mark - Private Functions -

#pragma mark - Public Functions -

int bsearch_tests(void)
{
	const struct CMUnitTest bsearch_tests[] = {
		cmocka_unit_test(bsearch_string_test),
		cmocka_unit_test(bsearch_string_test_element_not_found), cmocka_unit_test(bsearch_int_test),
		cmocka_unit_test(bsearch_int_test_element_not_found)

	};

	return cmocka_run_group_tests(bsearch_tests, NULL, NULL);
}
