#ifndef STDDEF_H_
#define STDDEF_H_

#include <_types/_ptrdiff_t.h>
#include <_types/_size_t.h>

#pragma mark - NULL -

#ifdef __cplusplus
/*! Expands to 0L (for C++). Implementation-defined null pointer constant  */
#define NULL 0L
#else

/*! Expands to ((void*)0) (not C++). Implementation-defined null pointer constant  */
#define NULL ((void*)0)
#endif

#pragma mark - offsetof -

#if __GNUC__ > 3

/*! byte offset from the beginning of a struct type to specified member  */
#define offsetof(type, member) __builtin_offsetof(type, member)
#else

/*! byte offset from the beginning of a struct type to specified member  */
#define offsetof(type, member) ((size_t)((char*)&(((type*)0)->member) - (char*)0))
#endif

#pragma mark - max_align_t -

#if(defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || \
	(defined(__cplusplus) && __cplusplus >= 201103L)

/*! A type with alignment requirement as great as any other scalar type  */
typedef long double max_align_t;
#endif

#endif // STDDEF_H_
