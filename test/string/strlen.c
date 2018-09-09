/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "string_tests.h"
#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

static void strlen_test(void** state)
{
	assert_int_equal(strlen(""), 0);
	assert_int_equal(strlen("a"), 1);
	assert_int_equal(strlen("ab"), 2);
	assert_int_equal(strlen("abasildjfaskjdf;askdfuoisudfoiajsdfaf"), 37);
}

#pragma mark - Public Functions -

int strlen_tests(void)
{
	const struct CMUnitTest strlen_tests[] = {
		cmocka_unit_test(strlen_test),
	};

	return cmocka_run_group_tests(strlen_tests, NULL, NULL);
}
