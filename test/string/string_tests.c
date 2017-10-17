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

extern int memcpy_tests(void);
extern int memset_tests(void);
extern int memmem_tests(void);
extern int memmove_tests(void);
extern int memcmp_tests(void);
extern int strcmp_tests(void);
extern int strcpy_tests(void);
extern int strdup_tests(void);
extern int strlen_tests(void);
extern int strncmp_tests(void);
extern int strncpy_tests(void);
extern int strndup_tests(void);
extern int strnlen_tests(void);
extern int strnstr_tests(void);
extern int strstr_tests(void);
extern int strchr_tests(void);
extern int strrchr_tests(void);
extern int strncat_tests(void);
extern int strcat_tests(void);
extern int strtok_tests(void);

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
