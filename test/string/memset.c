/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "string_tests.h"
#include <limits.h>
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

#define N 400

#pragma mark - Declarations -

static char buf[N];
static char buf2[N];

#pragma mark - Private Functions -

static char* aligned(void* p)
{
	return (char*)(((intptr_t)p + 63) & -64);
}

static void test_align(int align, size_t len)
{
	char* s = aligned(buf + 64) + align;
	char* want = aligned(buf2 + 64) + align;
	char* p;
	int i;

	assert_false(len + 64 > (size_t)(buf + N - s));
	assert_false(len + 64 > (size_t)(buf2 + N - want));

	for(i = 0; i < N; i++)
	{
		buf[i] = buf2[i] = ' ';
	}

	for(i = 0; i < (int)len; i++)
	{
		want[i] = '#';
	}

	p = memset(s, '#', len);

	assert_ptr_equal(p, s);

	for(i = -64; i < (int)len + 64; i++)
	{
		assert_int_equal(s[i], want[i]);
	}
}

static void memset_aligned_test(void** state)
{
	for(int i = 0; i < 16; i++)
	{
		for(size_t j = 0; j < 200; j++)
		{
			test_align(i, j);
		}
	}
}

static void check_input_(char c, void** state)
{
	memset(buf, c, 10);
	for(int i = 0; i < 10; i++)
	{
		assert_int_equal(buf[i], c);
	}
}

static void check_input(void** state)
{
	check_input_('c', state);
	check_input_(0, state);
	check_input_(-1, state);
	check_input_((char)INT_MAX, state);
	check_input_((char)-INT_MAX, state);
	check_input_((char)0xab, state);
}

#pragma mark - Public Functions -

int memset_tests(void)
{
	const struct CMUnitTest memset_tests[] = {
		cmocka_unit_test(memset_aligned_test),
		cmocka_unit_test(check_input),
	};

	return cmocka_run_group_tests(memset_tests, NULL, NULL);
}
