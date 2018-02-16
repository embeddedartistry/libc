/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */
#include <stdlib.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka/cmocka.h>
// clang-format on

extern int isalnum_tests(void);
extern int isalpha_tests(void);
extern int isascii_tests(void);
extern int isblank_tests(void);
extern int isdigit_tests(void);
extern int isgraph_tests(void);
extern int iscntrl_tests(void);
extern int islower_tests(void);
extern int ispunct_tests(void);
extern int isspace_tests(void);
extern int isupper_tests(void);
extern int isxdigit_tests(void);
extern int toascii_tests(void);
extern int tolower_tests(void);
extern int toupper_tests(void);
extern int isprint_tests(void);

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
