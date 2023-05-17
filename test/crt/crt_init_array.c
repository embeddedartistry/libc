
/*
 * Copyright © 2020 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "crt_tests.h"
#include <crt.h>
#include <stdbool.h>
#include <stdio.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

// Currently these tests only run on MacOS due to section/segment requirement
#ifdef __APPLE__
static volatile bool preinit_was_called = false;
static volatile bool preinit_was_not_called = true;
static volatile int init_was_called = 0;
static volatile bool init_was_not_called = true;
static volatile int fini_was_called = 0;
static volatile bool fini_was_not_called = true;

static void preinit_should_be_called(void)
{
	preinit_was_called = true;
}

static void preinit_should_not_be_called(void)
{
	preinit_was_not_called = false;
}

static void init_should_be_called(void)
{
	init_was_called = init_was_called + 1;
}

static void init_should_not_be_called(void)
{
	init_was_not_called = false;
}

static void fini_should_be_called(void)
{
	fini_was_called = fini_was_called + 1;
}

static void fini_should_not_be_called(void)
{
	fini_was_not_called = false;
}

static void (*preinit_call_list[])(void) = {preinit_should_be_called, preinit_should_not_be_called};
static void (*init_call_list[])(void) = {init_should_be_called, init_should_be_called,
										 init_should_not_be_called};
static void (*fini_call_list[])(void) = {fini_should_be_called, fini_should_be_called,
										 fini_should_be_called, fini_should_not_be_called};

__attribute__((section("__DATA,.preinit_array"))) void (**__preinit_array_start)(void) =
	preinit_call_list;
__attribute__((section("__DATA,.preinit_array"))) void (**__preinit_array_end)(void) =
	&preinit_call_list[1];
__attribute__((section("__DATA,.init_array"))) void (**__init_array_start)(void) = init_call_list;
__attribute__((section("__DATA,.init_array"))) void (**__init_array_end)(void) = &init_call_list[2];
__attribute__((section("__DATA,.fini_array"))) void (**__fini_array_start)(void) = fini_call_list;
__attribute__((section("__DATA,.fini_array"))) void (**__fini_array_end)(void) = &fini_call_list[3];

static void check_crt_init_routines(void** state)
{
	__libc_init_array();

	assert_true(preinit_was_called);
	assert_true(preinit_was_not_called);
	assert_int_equal(init_was_called, 2);
	assert_true(init_was_not_called);
}

static void check_crt_fini_routines(void** state)
{
	__libc_fini_array();

	assert_int_equal(fini_was_called, 3);
	assert_true(fini_was_not_called);
}
#endif

int crt_array_test_suite(void)
{
	const struct CMUnitTest crt_tests[] = {
#ifdef __APPLE__
		cmocka_unit_test(check_crt_init_routines),
		cmocka_unit_test(check_crt_fini_routines),
#endif
	};

	return cmocka_run_group_tests(crt_tests, NULL, NULL);
}
