/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "ctype_tests.h"
#include <ctype.h>
#include <limits.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static void good_input(void** state)
{
	for(int i = 0; i < 0x80; i++)
	{
		assert_int_equal(toascii(i), i);
	}
}

static void bad_input(void** state)
{
	for(int i = 0x80; i < 0xFF; i++)
	{
		assert_int_equal(toascii(i), (i & 0x7F));
	}

	// Remaining integers spot check
	assert_int_equal(toascii(1024), (1024 & 0x7F));
	assert_int_equal(toascii(15185), (15185 & 0x7F));
	assert_int_equal(toascii(1808303), (1808303 & 0x7F));
	assert_int_equal(toascii(INT_MAX), (INT_MAX & 0x7F));
	assert_int_equal(toascii(-1), (-1 & 0x7F));
	assert_int_equal(toascii(-100), (-100 & 0x7F));
	assert_int_equal(toascii(-INT_MAX), (-INT_MAX & 0x7F));
}

int toascii_tests(void)
{
	const struct CMUnitTest toascii_tests[] = {
		cmocka_unit_test(good_input),
		cmocka_unit_test(bad_input),
	};

	return cmocka_run_group_tests(toascii_tests, NULL, NULL);
}
