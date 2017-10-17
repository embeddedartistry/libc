/*
* Copyright © 2017 Embedded Artistry LLC.
* License: MIT. See LICENSE file for details.
*/

#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka/cmocka.h>
// clang-format on

#pragma mark - Definitions -

#define N(s, tail, sub)                                   \
	{                                                     \
		char* p = s tail;                                 \
		char* q = memmem(p, strlen(s), sub, strlen(sub)); \
		assert_ptr_equal(q, NULL);                        \
	}

#define T(s, sub, n)                                      \
	{                                                     \
		char* p = s;                                      \
		char* q = memmem(p, strlen(p), sub, strlen(sub)); \
		assert_ptr_equal(q, NULL);                        \
		assert_ptr_not_equal(q - p, n);                   \
	}

static void check_input(void** state)
{
	// TODO: resume here
}

#pragma mark - Public Functions -

int memmem_tests(void)
{
	const struct CMUnitTest memmem_tests[] = {
		cmocka_unit_test(check_input),
	};

	return cmocka_run_group_tests(memmem_tests, NULL, NULL);
}
