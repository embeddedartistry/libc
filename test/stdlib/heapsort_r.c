/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "stdlib_tests.h"
#include <stdlib.h>
#include <string.h>
#include <test/test.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#pragma mark - Declarations -
static void* input_thunk = 0xDEADBEEF;
/* 26 items -- even */
static const char* s[] = {"Bob",	"Alice", "John",   "Ceres",	  "Helga",	 "Drepper", "Emeralda",
						  "Zoran",	"Momo",	 "Frank",  "Pema",	  "Xavier",	 "Yeva",	"Gedun",
						  "Irina",	"Nono",	 "Wiener", "Vincent", "Tsering", "Karnica", "Lulu",
						  "Quincy", "Osama", "Riley",  "Ursula",  "Sam"};
static const char* s_sorted[] = {
	"Alice", "Bob",		"Ceres",  "Drepper", "Emeralda", "Frank",  "Gedun", "Helga",  "Irina",
	"John",	 "Karnica", "Lulu",	  "Momo",	 "Nono",	 "Osama",  "Pema",	"Quincy", "Riley",
	"Sam",	 "Tsering", "Ursula", "Vincent", "Wiener",	 "Xavier", "Yeva",	"Zoran"};

/* 23 items -- odd, prime */
static int n[] = {879045, 394,	99405644, 33434, 232323, 4334,	  5454,	 343,
				  45545,  454,	324,	  22,	 34344,	 233,	  45345, 343,
				  848405, 3434, 3434344,  3535,	 93994,	 2230404, 4334};
static int n_sorted[] = {22,	233,	324,	343,	343,	 394,	  454,	   3434,
						 3535,	4334,	4334,	5454,	33434,	 34344,	  45345,   45545,
						 93994, 232323, 848405, 879045, 2230404, 3434344, 99405644};

#pragma mark - Private Sorting Functions -

static int scmp(void* thunk, const void* a, const void* b)
{
	return strcmp(*(char* const*)a, *(char* const*)b);
}

static int icmp(void* thunk, const void* a, const void* b)
{
	return *(const int*)a - *(const int*)b;
}

static int ccmp(void* thunk, const void* a, const void* b)
{
	return *(const char*)a - *(const char*)b;
}

static int cmp64(void* thunk, const void* a, const void* b)
{
	const uint64_t *ua = a, *ub = b;
	return *ua < *ub ? -1 : *ua != *ub;
}

static int icmp_thunk_check(void* thunk, const void* a, const void* b)
{
	assert_ptr_equal(thunk, input_thunk);
	return *(const int*)a - *(const int*)b;
}

static void heapsort_r_int_test_thunk_not_null(void** state)
{
	void* thunk = input_thunk;
	size_t len = sizeof(n) / sizeof(*n);

	heapsort_r(s, len, sizeof(*n), thunk, icmp_thunk_check);

	for(size_t i = 0; i < len; i++)
	{
		assert_int_equal(strcmp(s[i], s_sorted[i]), 0);
	}
}

#pragma mark - Private Test Functions -

static void heapsort_r_string_test(void** state)
{
	void* thunk = NULL; // unused in these examples, but we want to test API
	size_t len = sizeof(s) / sizeof(*s);

	heapsort_r(s, len, sizeof(*s), thunk, scmp);

	for(size_t i = 0; i < len; i++)
	{
		assert_int_equal(strcmp(s[i], s_sorted[i]), 0);
	}
}

static void heapsort_r_int_test(void** state)
{
	void* thunk = NULL; // unused in these examples, but we want to test API
	size_t len = sizeof(n) / sizeof(*n);
	heapsort_r(n, len, sizeof(*n), thunk, icmp);

	for(size_t i = 0; i < len; i++)
	{
		assert_int_equal(n[i], n_sorted[i]);
	}
}

static void char_test(const char* a, const char* a_sorted, void** state)
{
	void* thunk = NULL; // unused in these examples, but we want to test API
	size_t len = strlen(a);
	char* p = malloc(len + 1);
	strcpy(p, a);

	heapsort_r(p, len, 1, thunk, ccmp);
	assert_int_equal(memcmp(p, a_sorted, len + 1), 0);

	free(p);
}

static void heapsort_r_char_test(void** state)
{
	char_test("", "", state);
	char_test("1", "1", state);
	char_test("11", "11", state);
	char_test("12", "12", state);
	char_test("21", "12", state);
	char_test("111", "111", state);
	char_test("211", "112", state);
	char_test("121", "112", state);
	char_test("112", "112", state);
	char_test("221", "122", state);
	char_test("212", "122", state);
	char_test("122", "122", state);
	char_test("123", "123", state);
	char_test("132", "123", state);
	char_test("213", "123", state);
	char_test("231", "123", state);
	char_test("321", "123", state);
	char_test("312", "123", state);
	char_test("1423", "1234", state);
	char_test("51342", "12345", state);
	char_test("261435", "123456", state);
	char_test("4517263", "1234567", state);
	char_test("37245618", "12345678", state);
	char_test("812436597", "123456789", state);
	char_test("987654321", "123456789", state);
	char_test("321321321", "111222333", state);
	char_test("49735862185236174", "11223344556677889", state);
}

static void uint64_gen(uint64_t* p, uint64_t* p_sorted, size_t num)
{
	uint64_t r = 0;
	test_randseed(num);
	for(size_t i = 0; i < num; i++)
	{
		r += test_randn(20);
		p[i] = r;
	}
	memcpy(p_sorted, p, num * sizeof *p);
	test_shuffle(p, num);
}

static void uint64_test(uint64_t* a, uint64_t* a_sorted, size_t len, void** state)
{
	void* thunk = NULL; // unused in these examples, but we want to test API
	heapsort_r(a, len, sizeof(*a), thunk, cmp64);
	for(size_t i = 0; i < len; i++)
	{
		assert_int_equal(a[i], a_sorted[i]);
	}
}

static void heapsort_r_uint64_test(void** state)
{
	size_t start = 1023;
	size_t end = 1027;

	for(size_t i = start; i < end; i++)
	{
		uint64_t p[end], p_sorted[end];
		uint64_gen(p, p_sorted, i);
		uint64_test(p, p_sorted, i, state);
	}
}

#pragma mark - Public Functions -

int heapsort_r_tests(void)
{
	const struct CMUnitTest heapsort_r_tests[] = {
		cmocka_unit_test(heapsort_r_string_test),
		cmocka_unit_test(heapsort_r_int_test_thunk_not_null),
		cmocka_unit_test(heapsort_r_char_test),
		cmocka_unit_test(heapsort_r_int_test),
		cmocka_unit_test(heapsort_r_uint64_test),
	};

	return cmocka_run_group_tests(heapsort_r_tests, NULL, NULL);
}
