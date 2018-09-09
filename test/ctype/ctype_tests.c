/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */
#include "ctype_tests.h"
#include <stdlib.h>
#include <tests.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

int ctype_tests(void)
{
	int overall_result = 0;

	if(0 != isalnum_tests())
	{
		overall_result = -1;
	}

	if(0 != isalpha_tests())
	{
		overall_result = -1;
	}

	if(0 != isascii_tests())
	{
		overall_result = -1;
	}

	if(0 != isblank_tests())
	{
		overall_result = -1;
	}

	if(0 != isdigit_tests())
	{
		overall_result = -1;
	}

	if(0 != isgraph_tests())
	{
		overall_result = -1;
	}

	if(0 != iscntrl_tests())
	{
		overall_result = -1;
	}

	if(0 != islower_tests())
	{
		overall_result = -1;
	}

	if(0 != ispunct_tests())
	{
		overall_result = -1;
	}

	if(0 != isspace_tests())
	{
		overall_result = -1;
	}

	if(0 != isupper_tests())
	{
		overall_result = -1;
	}

	if(0 != isxdigit_tests())
	{
		overall_result = -1;
	}

	if(0 != toascii_tests())
	{
		overall_result = -1;
	}

	if(0 != tolower_tests())
	{
		overall_result = -1;
	}

	if(0 != toupper_tests())
	{
		overall_result = -1;
	}

	if(0 != isprint_tests())
	{
		overall_result = -1;
	}

	return overall_result;
}
