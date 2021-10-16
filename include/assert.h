#ifndef ASSERT_H_
#define ASSERT_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NDEBUG
#define assert(x) (void)0
#else
#define assert(x) ((void)((x) || (__assert_fail(#x, __FILE__, __LINE__, __func__), 0)))
#endif

#if __STDC_VERSION__ >= 201112L && !defined(__cplusplus)
#define static_assert _Static_assert
#endif

__attribute__((noreturn)) void __assert_fail(const char* expr, const char* file, unsigned int line,
											 const char* function);

#ifdef __cplusplus
}
#endif

#endif // ASSERT_H_
