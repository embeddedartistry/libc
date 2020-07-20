/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "string_tests.h"
#include <stdint.h>
#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#pragma mark - Definitions -

#define N(s, sub)                  \
	{                              \
		const char* p = s;         \
		char* q = strstr(p, sub);  \
		assert_ptr_equal(q, NULL); \
	}

#define T(s, sub, n)                                      \
	{                                                     \
		const char* p = s;                                \
		char* q = strstr(p, sub);                         \
		assert_ptr_not_equal(q, NULL);                    \
		assert_int_equal((intptr_t)(q - p), (intptr_t)n); \
	}

static void strstr_test(void** state)
{
	N("", "a")
	N("a", "aa")
	N("a", "b")
	N("aa", "ab")
	N("aa", "aaa")
	N("abba", "aba")
	N("abc abc", "abcd")
	N("0-1-2-3-4-5-6-7-8-9", "-3-4-56-7-8-")
	N("0-1-2-3-4-5-6-7-8-9", "-3-4-5+6-7-8-")
	N("_ _ _\xff_ _ _", "_\x7f_")
	N("_ _ _\x7f_ _ _", "_\xff_")

	T("", "", 0)
	T("abcd", "", 0)
	T("abcd", "a", 0)
	T("abcd", "b", 1)
	T("abcd", "c", 2)
	T("abcd", "d", 3)
	T("abcd", "ab", 0)
	T("abcd", "bc", 1)
	T("abcd", "cd", 2)
	T("ababa", "baba", 1)
	T("ababab", "babab", 1)
	T("abababa", "bababa", 1)
	T("abababab", "bababab", 1)
	T("ababababa", "babababa", 1)
	T("abbababab", "bababa", 2)
	T("abbababab", "ababab", 3)
	T("abacabcabcab", "abcabcab", 4)
	T("nanabanabanana", "aba", 3)
	T("nanabanabanana", "ban", 4)
	T("nanabanabanana", "anab", 1)
	T("nanabanabanana", "banana", 8)
	T("_ _\xff_ _", "_\xff_", 2)
}

#pragma mark - Public Functions -

int strstr_tests(void)
{
	const struct CMUnitTest strstr_tests[] = {
		cmocka_unit_test(strstr_test),
	};

	return cmocka_run_group_tests(strstr_tests, NULL, NULL);
}
