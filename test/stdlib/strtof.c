/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "stdlib_tests.h"
#include "test/ulpsDistance.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

#pragma mark - Definitions -

#define length(x) (sizeof(x) / sizeof *(x))

static struct
{
	const char* s;
	float f;

} t[] = {
	// 2^-149 * 0.5 - eps
	{".7006492321624085354618647916449580656401309709382578858785341419448955413429303e-45", 0},
	// 2^-149 * 0.5 + eps
	{".7006492321624085354618647916449580656401309709382578858785341419448955413429304e-45",
	 (float)0x1p-149},
	// 2^-149 * 0.5 - eps
	{".2101947696487225606385594374934874196920392912814773657635602425834686624028790e-44",
	 (float)0x1p-149},
	// 2^-149 * 0.5 + eps
	{".2101947696487225606385594374934874196920392912814773657635602425834686624028791e-44",
	 (float)0x1p-148},
	// 2^-126 + 2^-150 - eps
	{".1175494420887210724209590083408724842314472120785184615334540294131831453944281e-37",
	 0x1p-126},
	// 2^-126 + 2^-150 + eps
	{".1175494420887210724209590083408724842314472120785184615334540294131831453944282e-37",
	 0x1.000002p-126},
	// 2^128 - 2^103 - eps
	{"340282356779733661637539395458142568447.9999999999999999999", 0x1.fffffep127},
	// 2^128 - 2^103
	{"340282356779733661637539395458142568448", INFINITY},
};

#pragma mark - Private Functions -

static void strtof_test(void** state)
{
	char* p;

	for(size_t i = 0; i < length(t); i++)
	{
		int32_t distance = ulpsDistanceFloat(strtof(t[i].s, &p), t[i].f);
		assert_true(distance < 2);
	}
}

#pragma mark - Public Functions -

int strtof_tests(void)
{
	const struct CMUnitTest strtof_tests[] = {cmocka_unit_test(strtof_test)};

	return cmocka_run_group_tests(strtof_tests, NULL, NULL);
}
