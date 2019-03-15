#ifndef LIMITS_H__
#define LIMITS_H__

// System Specific Limits
#include <_limits.h>

/* Support signed or unsigned plain-char */

#if '\0' - 1 > 0

/*!  Expands to the integer constant 0. Minimum value of char  */
#define CHAR_MIN 0

/*! Expands to the integer constant 255. Maximum value of char */
#define CHAR_MAX 255
#else

/*!  Expands to the integer constant -128. Minimum value of char  */
#define CHAR_MIN (-128)

/*! Expands to the integer constant 127. Maximum value of char */
#define CHAR_MAX 127
#endif

/* Some universal constants... */

/*! Expands to the integer constant 8. Number of bits in byte */
#define CHAR_BIT 8

/*! Expands to the integer constant -128. Minimum value of signed char */
#define SCHAR_MIN (-128)

/*! Expands to the integer constant 127. Maximum value of signed char */
#define SCHAR_MAX 127

/*! Expands to the integer constant 255. Maximum value of unsigned char */
#define UCHAR_MAX 255

/*! Expands to -1 - 0x7fff. Minimum value of signed short */
#define SHRT_MIN (-1 - 0x7fff)

/*! Expands to the Hex constant 0x7fff. Maximum value of signed short */
#define SHRT_MAX 0x7fff

/*! Expands to hex 0xffff. Maximum value of unsigned short */
#define USHRT_MAX 0xffff

/*! Expands to hex -1 - 0x7fffffff. Minimum value of signed int */
#define INT_MIN (-1 - 0x7fffffff)

/*! Expands to hex 0x7fffffff. Maximum value of signed int */
#define INT_MAX 0x7fffffff

/*! Expands to hex 0xffffffffU. Maximum value of unsigned int */
#define UINT_MAX 0xffffffffU

/*! Expands to  (-LONG_MAX - 1). Minimum value of signed long */
#define LONG_MIN (-LONG_MAX - 1)

/*! Expands to (2UL * LONG_MAX + 1). Maximum value of unsigned long */
#define ULONG_MAX (2UL * LONG_MAX + 1)

/*! Expands to  (-LLONG_MAX - 1). Minimum value of signed long long */
#define LLONG_MIN (-LLONG_MAX - 1)

/*! Expands to (2ULL * LLONG_MAX + 1). Maximum value of unsigned long long */
#define ULLONG_MAX (2ULL * LLONG_MAX + 1)

/*! Maximum multibyte length of a character across all locales */
#define MB_LEN_MAX 4

#endif // LIMITS_H__
