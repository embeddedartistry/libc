/*
 * Copyright © 2017 Embedded Artistry LLC.
 * License: MIT. See LICENSE file for details.
 */

#include "string_tests.h"
#include <stdlib.h>
#include <string.h>

// Cmocka needs these
// clang-format off
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
// clang-format on

struct test_memmove_data
{
	char template[64];
	char buf[64];
};

static void fill_buffer(char* buf, size_t size, char start_value, char end_value)
{
	for(size_t i = 0; i < size; ++i)
	{
		buf[i] = (char)(((size_t)start_value + i) % (size_t)(end_value - start_value + 1));
	}
}

static int setup_test(void** state)
{
	struct test_memmove_data* md = malloc(sizeof(struct test_memmove_data));
	if(!md)
	{
		return -1;
	}
	fill_buffer(md->template, sizeof(md->template), 'A', 'Z');
	memcpy(md->buf, md->template, sizeof(md->buf));
	*state = md;
	return 0;
}

static int teardown_test(void** state)
{
	struct test_memmove_data* md = *state;
	free(md);
	return 0;
}

static void memmove_test_lower_to_higher(void** state)
{
	struct test_memmove_data* md = *state;
	char* p;
	size_t offset = 20;
	size_t len = sizeof(md->buf) - offset;
	p = memmove(md->buf + offset, md->buf, len);
	assert_ptr_equal(p, md->buf + offset);
	assert_memory_equal(md->buf + offset, md->template, len);
	assert_memory_equal(md->buf, md->template, offset);
	return;
}

static void memmove_test_higher_to_lower(void** state)
{
	struct test_memmove_data* md = *state;
	char* p;
	size_t offset = 20;
	size_t len = sizeof(md->buf) - offset;
	p = memmove(md->buf, md->buf + offset, len);
	assert_ptr_equal(p, md->buf);
	assert_memory_equal(md->buf, md->template + offset, len);
	assert_memory_equal(md->buf + len, md->template + len, offset);
	return;
}

static void memmove_test_zero_size(void** state)
{
	struct test_memmove_data* md = *state;
	char* p;
	size_t offset = 30;
	p = memmove(md->buf + offset, md->buf, 0);
	assert_ptr_equal(p, md->buf + offset);
	assert_memory_equal(md->buf, md->template, sizeof(md->template));
	return;
}

static void memmove_test_copy_to_itself(void** state)
{
	struct test_memmove_data* md = *state;
	char* p;
	p = memmove(md->buf, md->buf, sizeof(md->buf));
	assert_ptr_equal(p, md->buf);
	assert_memory_equal(md->buf, md->template, sizeof(md->template));
	return;
}
#pragma mark - Public Functions -

int memmove_tests(void)
{
	const struct CMUnitTest memmove_tests[] = {
		cmocka_unit_test_setup_teardown(memmove_test_lower_to_higher, setup_test, teardown_test),
		cmocka_unit_test_setup_teardown(memmove_test_higher_to_lower, setup_test, teardown_test),
		cmocka_unit_test_setup_teardown(memmove_test_zero_size, setup_test, teardown_test),
		cmocka_unit_test_setup_teardown(memmove_test_copy_to_itself, setup_test, teardown_test),
	};

	return cmocka_run_group_tests(memmove_tests, NULL, NULL);
}
