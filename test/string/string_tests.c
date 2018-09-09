/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */
#include <stdlib.h>

#include "string_tests.h"
#include <tests.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

int string_tests(void)
{
	int overall_result = 0;

	overall_result |= memcpy_tests();
	overall_result |= memset_tests();
	overall_result |= memmem_tests();
	overall_result |= memmove_tests();
	overall_result |= memcmp_tests();
	overall_result |= strcmp_tests();
	overall_result |= strcpy_tests();
	overall_result |= strdup_tests();
	overall_result |= strlen_tests();
	overall_result |= strncmp_tests();
	overall_result |= strncpy_tests();
	overall_result |= strndup_tests();
	overall_result |= strnlen_tests();
	overall_result |= strnstr_tests();
	overall_result |= strstr_tests();
	overall_result |= strchr_tests();
	overall_result |= strrchr_tests();
	overall_result |= strcat_tests();
	overall_result |= strncat_tests();
	overall_result |= strtok_tests();

	return overall_result;
}
