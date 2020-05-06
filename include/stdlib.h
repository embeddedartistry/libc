#ifndef STDLIB_H_
#define STDLIB_H_

#include <stddef.h>
#include <stdint.h>
#include <wctype.h> //TODO: remove need for this? due to wchar_t

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#pragma mark - definitions & types -

/// Division type for integers
typedef struct
{
	int quot; /**< The quotient */
	int rem; /**< The remainder */
} div_t;

/// Division type for long integers
typedef struct
{
	long quot; /**< The quotient */
	long rem; /**< The remainder */
} ldiv_t;

/// Division type for long long integers
typedef struct
{
	long long quot; /**< The quotient */
	long long rem; /**< The remainder */
} lldiv_t;

/*! Expands to 1. Indicates program execution execution status. */
#define EXIT_FAILURE 1

/*! Expands to 0. indicates program execution execution status. */
#define EXIT_SUCCESS 0

/*! Expands to an integer constant expression equal to the maximum value returned by the function
 * @see rand() It's guaranteed that this value is at least 32767
 * */
#define RAND_MAX (0x7fffffff)

/// Length of the current locale's multi-byte character.
/// We are faking this for now, since we don't provide locale support.
#define MB_CUR_MAX sizeof(wchar_t)

#pragma mark - runtime -

// TODO

void abort(void) __attribute__((noreturn));
int atexit(void (*)(void));
void exit(int) __attribute__((noreturn));

/** TODO: CLEANUP DOC
 * Terminates the process normally by returning control to the host environment,
 * but without performing any of the regular cleanup tasks for terminating processes (as function
 * exit does). No object destructors, nor functions registered by atexit or at_quick_exit are called
 */
void _Exit(int) __attribute__((noreturn));
int at_quick_exit(void (*)(void));
void quick_exit(int) __attribute__((noreturn));
int cxa_atexit(void (*)(void*), void*, void*);

#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
// Unsupported in bare metal environments:
char* getenv(const char*);
#endif

#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
// Unsupported in bare metal environments:
int system(const char*);
#endif

#pragma mark - Multibyte APIs -

#ifndef DISABLE_UNIMPLEMENTED_LIBC_APIS
int mblen(const char*, size_t);
int mbtowc(wchar_t* __restrict, const char* __restrict, size_t);
int wctomb(char*, wchar_t);
size_t mbstowcs(wchar_t* __restrict, const char* __restrict, size_t);
size_t wcstombs(char* __restrict, const wchar_t* __restrict, size_t);
#endif

#pragma mark - ascii-to-x -

/**
 * @brief Interprets an integer value in a byte string pointed to by str.
 *
 * Interprets an integer value in a byte string pointed to by str.
 * Discards any whitespace characters until the first non-whitespace character
 * is found, then takes as many characters as possible to form a valid integer number
 * representation and converts them to an integer value.
 * The valid integer value consists of the following parts:
 *      a) (optional) plus or minus sign
 *      b) numeric digits
 *
 * @param str pointer to the null-terminated byte string to be interpreted
 * @return Integer value corresponding to the contents of str on success.
 * 	If the converted value falls out of range of corresponding return type,
 * 	the return value is undefined. If no conversion can be performed, ​0​ is returned.
 * */
int atoi(const char* str);

/**
 * @brief Interprets a Long value in a byte string pointed to by str.
 *
 * Interprets a Long value in a byte string pointed to by str.
 * Discards any whitespace characters until the first non-whitespace character
 * is found, then takes as many characters as possible to form a valid long number
 * representation and converts them to an long value.
 * The valid Long value consists of the following parts:
 *      a) (optional) plus or minus sign
 *      b) numeric digits
 *
 * @param str pointer to the null-terminated byte string to be interpreted
 * @return long value corresponding to the contents of str on success.
 * 	If the converted value falls out of range of corresponding return type,
 * 	the return value is undefined. If no conversion can be performed, ​0​ is returned.
 * */
long atol(const char* str);

/**
 * @brief Interprets a Long Long value in a byte string pointed to by str.
 *
 * Interprets a Long Long value in a byte string pointed to by str.
 * Discards any whitespace characters until the first non-whitespace character
 * is found, then takes as many characters as possible to form a valid long number
 * representation and converts them to an long long value.
 * The valid Long long value consists of the following parts:
 *      a) (optional) plus or minus sign
 *      b) numeric digits
 *
 * @param str pointer to the null-terminated byte string to be interpreted
 * @return long value corresponding to the contents of str on success.
 * 	If the converted value falls out of range of corresponding return type,
 * 	the return value is undefined. If no conversion can be performed, ​0​ is returned.
 * */
long long atoll(const char* str);

/**
 * @brief Interprets a floating-point value in a byte string pointed to by str.
 *
 * Interprets a floating-point value in a byte string pointed to by str.
 * Function discards any whitespace characters (as determined by @see isspace()
 * until first non-whitespace character is found. Then it takes as many characters
 * as possible to form a valid floating-point representation and converts them to
 * a floating-point value.
 * The valid floating-point value can be one of the following:
 *      1) decimal floating-point expression. It consists of the following parts:
 *              a) (optional) plus or minus sign
 *              b) nonempty sequence of decimal digits optionally containing
 *                  decimal-point character
 *              c) (optional) e or E followed with optional minus or plus sign
 *                  and nonempty sequence of decimal digits (defines exponent)
 *
 *
 * @param str pointer to the null-terminated byte string to be interpreted
 * @return double value corresponding to the contents of str on success.
 * 	If the converted value falls out of range of corresponding return type,
 * 	the return value is undefined. If no conversion can be performed, ​0​.0 is returned.
 * */
double atof(const char* str);

#pragma mark - str-to-x -

/**
 * @brief Interprets a floating-point value in a byte string pointed to by str.
 *
 * Interprets a floating-point value in a byte string pointed to by str.
 * Function discards any whitespace characters (as determined by @see isspace())
 * until first non-whitespace character is found. Then it takes as many characters
 * as possible to form a valid floating-point representation and converts them to
 * a floating-point value.
 * The valid floating-point value can be one of the following:
 *      a) decimal floating-point expression. It consists of the following parts:
 *          1) (optional) plus or minus sign
 *          2) nonempty sequence of decimal digits optionally containing decimal-point character
 *             (as determined by the current C locale) (defines significand)
 *          3) (optional) e or E followed with optional minus or plus sign and nonempty sequence
 *              of decimal digits (defines exponent)
 *      b) binary floating-point expression. It consists of the following parts:
 *         1) (optional) plus or minus sign
 *         2) 0x or 0X
 *      c) infinity expression. It consists of the following parts:
 *         1) (optional) plus or minus sign
 *         2) INF or INFINITY ignoring case
 *      d) not-a-number expression. It consists of the following parts:
 *         1) (optional) plus or minus sign
 *         2) NAN or NAN(char_sequence) ignoring case of the NAN part. char_sequence can only
 * contain digits, Latin letters, and underscores. The result is a quiet NaN floating-point value.
 *
 *
 *
 * The functions sets the pointer pointed to by str_end to point to the character past the last
 * character interpreted. If str_end is NULL, it is ignored.
 *
 *
 * @param str a pointer to the null-terminated byte string to be interpreted
 * @param str_end pointer to a pointer to character
 * @return Floating-point value corresponding to the contents of str on success.
 * If the converted value falls out of range of corresponding return type, range
 * error occurs and HUGE_VAL, HUGE_VALF or HUGE_VALL is returned.
 * If no conversion can be performed, ​0​ is returned.
 * */
float strtof(const char* __restrict str, char** __restrict str_end);

/**
 * @brief Interprets a floating-point value in a byte string pointed to by str.
 *
 * Interprets a floating-point value in a byte string pointed to by str.
 * Function discards any whitespace characters (as determined by @see isspace())
 * until first non-whitespace character is found. Then it takes as many characters
 * as possible to form a valid floating-point representation and converts them to
 * a floating-point value.
 * The valid floating-point value can be one of the following:
 *      a) decimal floating-point expression. It consists of the following parts:
 *          1) (optional) plus or minus sign
 *          2) nonempty sequence of decimal digits optionally containing decimal-point character
 *             (as determined by the current C locale) (defines significand)
 *          3) (optional) e or E followed with optional minus or plus sign and nonempty sequence
 *              of decimal digits (defines exponent)
 *      b) binary floating-point expression. It consists of the following parts:
 *         1) (optional) plus or minus sign
 *         2) 0x or 0X
 *      c) infinity expression. It consists of the following parts:
 *         1) (optional) plus or minus sign
 *         2) INF or INFINITY ignoring case
 *      d) not-a-number expression. It consists of the following parts:
 *         1) (optional) plus or minus sign
 *         2) NAN or NAN(char_sequence) ignoring case of the NAN part. char_sequence can only
 * contain digits, Latin letters, and underscores. The result is a quiet NaN floating-point value.
 *
 *
 *
 * The functions sets the pointer pointed to by str_end to point to the character past the last
 * character interpreted. If str_end is NULL, it is ignored.
 *
 *
 * @param str a pointer to the null-terminated byte string to be interpreted
 * @param str_end pointer to a pointer to character
 * @return Floating-point value corresponding to the contents of str on success.
 * If the converted value falls out of range of corresponding return type, range
 * error occurs and HUGE_VAL, HUGE_VALF or HUGE_VALL is returned.
 * If no conversion can be performed, ​0​ is returned.
 * */
double strtod(const char* __restrict str, char** __restrict str_end);

/**
 * @brief Interprets an long value in a byte string pointed to by str.
 *
 *
 * Interprets an long value in a byte string pointed to by str.
 * Discards any whitespace characters (as identified by calling @see isspace())
 * until the first non-whitespace character is found, then takes as many characters
 * as possible to form a valid base-n (where n=base) long number representation and
 * converts them to an long value. The valid long value consists of the following parts:
 *
 *      1) (optional) plus or minus sign
 *      2) (optional) prefix (0) indicating octal base (applies only when the base is 8 or ​0​)
 *      3) (optional) prefix (0x or 0X) indicating hexadecimal base (applies only when the base is
 * 16 or ​0​) 4)  a sequence of digits
 *
 *
 * The set of valid values for base is {0,2,3,...,36}. The set of valid digits for base-2 integers
 * is {0,1}, for base-3 integers is {0,1,2}, and so on. For bases larger than 10, valid digits
 * include alphabetic characters, starting from Aa for base-11 integer, to Zz for base-36 integer.
 * The case of the characters is ignored.
 *
 *
 * If the value of base is ​0​, the numeric base is auto-detected: if the prefix is 0, the base
 * is octal, if the prefix is 0x or 0X, the base is hexadecimal, otherwise the base is decimal.
 *
 * If the minus sign was part of the input sequence, the numeric value calculated from
 * the sequence of digits is negated as if by unary minus in the result type.
 *
 * The functions sets the pointer pointed to by str_end to point to the character past
 * the last character interpreted. If str_end is NULL, it is ignored.
 *
 * If the str is empty or does not have the expected form, no conversion is performed,
 * and (if str_end is not NULL) the value of str is stored in the object pointed to by str_end.
 *
 * @param str pointer to the null-terminated byte string to be interpreted
 * @param str_end pointer to a pointer to character.
 * @param base base of the interpreted integer value
 *
 * @return returns the result of the conversion, unless the value would underflow or overflow.
 *  If the converted value falls out of range of corresponding return type, a range error occurs
 *  (setting errno to ERANGE) and LONG_MAX, LONG_MIN, LLONG_MAX or LLONG_MIN is returned.
 *  If no conversion can be performed, ​0​ is returned.
 * */
long strtol(const char* __restrict str, char** __restrict str_end, int base);

/**
 * @brief Interprets an unsigned long value in a byte string pointed to by str.
 *
 *
 * Interprets an unsigned long value in a byte string pointed to by str.
 * Discards any whitespace characters (as identified by calling @see isspace())
 * until the first non-whitespace character is found, then takes as many characters
 * as possible to form a valid base-n (where n=base) long number representation and
 * converts them to an unsigned long value. The valid long value consists of the following parts:
 *
 *      1) (optional) plus or minus sign
 *      2) (optional) prefix (0) indicating octal base (applies only when the base is 8 or ​0​)
 *      3) (optional) prefix (0x or 0X) indicating hexadecimal base (applies only when the base is
 * 16 or ​0​) 4)  a sequence of digits
 *
 *
 * The set of valid values for base is {0,2,3,...,36}. The set of valid digits for base-2 integers
 * is {0,1}, for base-3 integers is {0,1,2}, and so on. For bases larger than 10, valid digits
 * include alphabetic characters, starting from Aa for base-11 integer, to Zz for base-36 integer.
 * The case of the characters is ignored.
 *
 *
 * If the value of base is ​0​, the numeric base is auto-detected: if the prefix is 0, the base
 * is octal, if the prefix is 0x or 0X, the base is hexadecimal, otherwise the base is decimal.
 *
 * If the minus sign was part of the input sequence, the numeric value calculated from
 * the sequence of digits is negated as if by unary minus in the result type.
 *
 *
 * If the str is empty or does not have the expected form, no conversion is performed,
 * and (if str_end is not NULL) the value of str is stored in the object pointed to by str_end.
 *
 * @param str pointer to the null-terminated byte string to be interpreted
 * @param str_end pointer to a pointer to character.
 * @param base base of the interpreted integer value
 *
 * @return returns the result of the conversion, unless the value would underflow or overflow.
 *  If the converted value falls out of range of corresponding return type, a range error occurs
 *  (setting errno to ERANGE) and LONG_MAX, LONG_MIN, LLONG_MAX or LLONG_MIN is returned.
 *  If no conversion can be performed, ​0​ is returned.
 * */
unsigned long strtoul(const char* __restrict str, char** __restrict str_end, int base);

/**
 * @brief Interprets an long long value in a byte string pointed to by str.
 *
 *
 * Interprets an long value in a byte string pointed to by str.
 * Discards any whitespace characters (as identified by calling @see isspace())
 * until the first non-whitespace character is found, then takes as many characters
 * as possible to form a valid base-n (where n=base) long number representation and
 * converts them to an long long value. The valid long value consists of the following parts:
 *
 *      1) (optional) plus or minus sign
 *      2) (optional) prefix (0) indicating octal base (applies only when the base is 8 or ​0​)
 *      3) (optional) prefix (0x or 0X) indicating hexadecimal base (applies only when the base is
 * 16 or ​0​) 4)  a sequence of digits
 *
 *
 * The set of valid values for base is {0,2,3,...,36}. The set of valid digits for base-2 integers
 * is {0,1}, for base-3 integers is {0,1,2}, and so on. For bases larger than 10, valid digits
 * include alphabetic characters, starting from Aa for base-11 integer, to Zz for base-36 integer.
 * The case of the characters is ignored.
 *
 *
 * If the value of base is ​0​, the numeric base is auto-detected: if the prefix is 0, the base
 * is octal, if the prefix is 0x or 0X, the base is hexadecimal, otherwise the base is decimal.
 *
 * If the minus sign was part of the input sequence, the numeric value calculated from
 * the sequence of digits is negated as if by unary minus in the result type.
 *
 * The functions sets the pointer pointed to by str_end to point to the character past
 * the last character interpreted. If str_end is NULL, it is ignored.
 *
 * If the str is empty or does not have the expected form, no conversion is performed,
 * and (if str_end is not NULL) the value of str is stored in the object pointed to by str_end.
 *
 * @param str pointer to the null-terminated byte string to be interpreted
 * @param str_end pointer to a pointer to character.
 * @param base base of the interpreted integer value
 *
 * @return returns the result of the conversion, unless the value would underflow or overflow.
 *  If the converted value falls out of range of corresponding return type, a range error occurs
 *  (setting errno to ERANGE) and LONG_MAX, LONG_MIN, LLONG_MAX or LLONG_MIN is returned.
 *  If no conversion can be performed, ​0​ is returned.
 * */
long long strtoll(const char* __restrict str, char** __restrict str_end, int base);

/**
 * @brief Interprets an unsigned long long value in a byte string pointed to by str.
 *
 *
 * Interprets an unsigned long long value in a byte string pointed to by str.
 * Discards any whitespace characters (as identified by calling @see isspace())
 * until the first non-whitespace character is found, then takes as many characters
 * as possible to form a valid base-n (where n=base) long number representation and
 * converts them to an unsigned long long value. The valid long value consists of the following
 * parts:
 *
 *      1) (optional) plus or minus sign
 *      2) (optional) prefix (0) indicating octal base (applies only when the base is 8 or ​0​)
 *      3) (optional) prefix (0x or 0X) indicating hexadecimal base (applies only when the base is
 * 16 or ​0​) 4)  a sequence of digits
 *
 *
 * The set of valid values for base is {0,2,3,...,36}. The set of valid digits for base-2 integers
 * is {0,1}, for base-3 integers is {0,1,2}, and so on. For bases larger than 10, valid digits
 * include alphabetic characters, starting from Aa for base-11 integer, to Zz for base-36 integer.
 * The case of the characters is ignored.
 *
 *
 * If the value of base is ​0​, the numeric base is auto-detected: if the prefix is 0, the base
 * is octal, if the prefix is 0x or 0X, the base is hexadecimal, otherwise the base is decimal.
 *
 * If the minus sign was part of the input sequence, the numeric value calculated from
 * the sequence of digits is negated as if by unary minus in the result type.
 *
 *
 * If the str is empty or does not have the expected form, no conversion is performed,
 * and (if str_end is not NULL) the value of str is stored in the object pointed to by str_end.
 *
 * @param str pointer to the null-terminated byte string to be interpreted
 * @param str_end pointer to a pointer to character.
 * @param base base of the interpreted integer value
 *
 * @return returns the result of the conversion, unless the value would underflow or overflow.
 *  If the converted value falls out of range of corresponding return type, a range error occurs
 *  (setting errno to ERANGE) and LONG_MAX, LONG_MIN, LLONG_MAX or LLONG_MIN is returned.
 *  If no conversion can be performed, ​0​ is returned.
 * */
unsigned long long strtoull(const char* __restrict str, char** __restrict str_end, int base);

// TODO:
long double strtold(const char* __restrict, char** __restrict);

#pragma mark - math -

/**
 * @brief Computes the absolute value of an integer number.
 *
 * Computes the absolute value of an integer number.
 * The behavior is undefined if the result cannot be represented by the return type.
 *
 * @param n integer value
 * @return The absolute value of n (i.e. |n|), if it is representable.
 * */
int abs(int n);

/**
 * @brief Computes the absolute value of an long number.
 *
 * Computes the absolute value of an long number.
 * The behavior is undefined if the result cannot be represented by the return type.
 *
 * @param n long value
 * @return The absolute value of n (i.e. |n|), if it is representable.
 * */
long labs(long n);

/**
 * @brief Computes the absolute value of an long long number.
 *
 * Computes the absolute value of an long long number.
 * The behavior is undefined if the result cannot be represented by the return type.
 *
 * @param n long long value
 * @return The absolute value of n (i.e. |n|), if it is representable.
 * */
long long llabs(long long n);

/**
 * @brief Computes both the quotient and the remainder of the division of the numerator x by the
 * denominator y.
 *
 * Computes both the quotient and the remainder of the division of the numerator x by the
 * denominator y.
 *
 * @param x integer values
 * @param y integer values
 *
 * @return If both the remainder and the quotient can be represented
 * as objects of the corresponding type (int, long, long long, imaxdiv_t,
 * respectively), returns both as an object of type @see div_t, @see ldiv_t, @see lldiv_t, @see
 * imaxdiv_t.
 *
 * If either the remainder or the quotient cannot be represented, the behavior is undefined.
 * */
div_t div(int x, int y);

/**
 * @brief Computes both the quotient and the remainder of the division of the numerator x by the
 * denominator y.
 *
 * Computes both the quotient and the remainder of the division of the numerator x by the
 * denominator y. Computes quotient and remainder simultaneously. The quotient is the algebraic
 * quotient with any fractional part discarded (truncated towards zero). The remainder is such that
 * quot * y + rem == x.
 *
 * Computes the quotient (the result of the expression x/y) and remainder (the result of the
 * expression x%y) simultaneously.
 *
 * @param x integer values
 * @param y integer values
 *
 * @return If both the remainder and the quotient can be represented
 * as objects of the corresponding type (int, long, long long, imaxdiv_t,
 * respectively), returns both as an object of type @see div_t, @see ldiv_t, @see lldiv_t, @see
 * imaxdiv_t.
 *
 * If either the remainder or the quotient cannot be represented, the behavior is undefined.
 * */
ldiv_t ldiv(long x, long y);

/**
 * @brief Computes both the quotient and the remainder of the division of the numerator x by the
 * denominator y.
 *
 * Computes both the quotient and the remainder of the division of the numerator x by the
 * denominator y. Computes quotient and remainder simultaneously. The quotient is the algebraic
 * quotient with any fractional part discarded (truncated towards zero). The remainder is such that
 * quot * y + rem == x.
 *
 * Computes the quotient (the result of the expression x/y) and remainder (the result of the
 * expression x%y) simultaneously.
 *
 * @param x integer values
 * @param y integer values
 *
 * @return If both the remainder and the quotient can be represented
 * as objects of the corresponding type (int, long, long long, imaxdiv_t,
 * respectively), returns both as an object of type @see div_t, @see ldiv_t, @see lldiv_t, @see
 * imaxdiv_t.
 *
 * If either the remainder or the quotient cannot be represented, the behavior is undefined.
 * */
lldiv_t lldiv(long long x, long long y);

#pragma mark - random number generation -

int rand_r(unsigned int* ctx);

/**
 * @brief Returns a pseudo-random integer value between ​0​ and @see RAND_MAX (0 and @see
 * RAND_MAX included).
 *
 * Returns a pseudo-random integer value between ​0​ and @see RAND_MAX (0 and @see RAND_MAX
 * included).
 *
 * @see srand() seeds the pseudo-random number generator used by rand.
 * If rand is used before any calls to @see srand, rand behaves as if it was seeded with @see srand.
 * Each time rand is seeded with srand, it must produce the same sequence of values.
 *
 * rand is not guaranteed to be thread-safe.
 *
 * @return Pseudo-random integer value between ​0​ and RAND_MAX, inclusive.
 * */
int rand(void);

/**
 * @brief Seeds the pseudo-random number generator used by @see rand with the value seed.
 *
 * Seeds the pseudo-random number generator used by @see rand with the value seed.
 * If rand() is used before any calls to srand, @see rand behaves as if it was seeded with srand.
 * Each time rand is seeded with the same seed, it must produce the same sequence of values.
 *
 * srand() is not guaranteed to be thread-safe.
 *
 * @param seed the seed value
 * */
void srand(unsigned seed);

#pragma mark - sorting -

/**
 * @brief Sorts the given array pointed to by vbase in ascending order.
 *
 * The heapsort() function is a modified selection sort. It sorts an array of nmemb objects,
 * the initial member of which is pointed to by vbase. The size of each object is specified by size.
 *
 * The contents of the array base are sorted in ascending order according to a comparison
 * function pointed to by compar, which requires two arguments pointing to the objects being
 * compared.
 *
 * @param vbase a pointer to the array to sort
 * @param nmemb the number of objects to sort
 * @param size the size of each object in the array
 * @param compar comparison function which returns ​a negative integer
 *  value if the first argument is less than the second,a positive integer value
 *  if the first argument is greater than the second and zero if the arguments are equal.
 *  key is passed as the first argument, an element from the array as the second.
 *  The signature of the comparison function should be equivalent to the following:
 *       int cmp(const void *a, const void *b);
 *
 * @return the value 0 if successful; otherwise the value -1 is returned and
 * the global variable errno is set to indicate the error.
 *
 * */
int heapsort(void* vbase, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

/**
 * @brief Sorts the given array pointed to by vbase in ascending order.
 *
 * It sorts an array of nmemb objects,
 * the initial member of which is pointed to by vbase. The size of each object is specified by size.
 * The heapsort_r() function behaves identically to @see heapsort(), except that it
 * takes an additional argument, thunk, which	is passed unchanged as the
 * first argument to function	pointed	to compar.  This allows	the comparison
 * function to access	additional data	without	using global variables,	and
 * thus heapsort_r() is suitable for use in functions which must be reentrant.
 * And is therefore reentrant and safe to use in threads.
 *
 * The contents of the array base are sorted in ascending order according to a comparison
 * function pointed to by compar, which requires two arguments pointing to the objects being
 * compared.
 *
 * @param vbase a pointer to the array to sort
 * @param nmemb the number of objects to sort
 * @param size the size of each object in the array
 * @param thunk additional data(variable) for compar
 * @param compar comparison function which returns ​a negative integer
 *  value if the first argument is less than the second,a positive integer value
 *  if the first argument is greater than the second and zero if the arguments are equal.
 *  key is passed as the first argument, an element from the array as the second.
 *  The signature of the comparison function should be equivalent to the following:
 *       int cmp(const void *a, const void *b);
 *
 * @return the value 0 if successful; otherwise the value -1 is returned and
 * the global variable errno is set to indicate the error.
 *
 * */
int heapsort_r(void* vbase, size_t nmemb, size_t size, void* thunk,
			   int (*compar)(void*, const void*, const void*));

/**
 * @brief Finds an element equal to element pointed to by key in an array pointed to by ptr.
 *
 *
 *
 * @param key pointer to the element to search for
 * @param ptr pointer to the array to examine
 * @param count number of element in the array
 * @param size size of each element in the array in bytes
 * @param comp comparison function which returns ​a negative integer
 *  value if the first argument is less than the second,a positive integer value
 *  if the first argument is greater than the second and zero if the arguments are equal.
 *  key is passed as the first argument, an element from the array as the second.
 *  The signature of the comparison function should be equivalent to the following:
 *       int cmp(const void *a, const void *b);
 *  The function must not modify the objects passed to it and must return consistent
 *  results when called for the same objects, regardless of their positions in the array.
 *
 * @return Pointer to an element in the array that compares equal to *key, or
 *  null pointer if such element has not been found.
 * */
void* bsearch(const void* key, const void* ptr, size_t count, size_t size,
			  int (*comp)(const void*, const void*));

/**
 * @brief Sorts the given array pointed to by ptr in ascending order.
 *
 * The qsort_r() function behaves identically to @see qsort(), except that it
 * takes an additional argument, thunk, which	is passed unchanged as the
 * first argument to function	pointed	to compar.  This allows	the comparison
 * function to access	additional data	without	using global variables,	and
 * thus qsort_r() is suitable	for use	in functions which must	be reentrant.
 * And is therefore reentrant and safe to use in threads.
 *
 * @param a pointer to the element to sort
 * @param n number of element in the array
 * @param es size of each element in the array in bytes
 * @param thunk additional data(variable) for cmp
 * @param cmp comparison function which returns ​a negative integer
 *  value if the first argument is less than the second,a positive integer value
 *  if the first argument is greater than the second and zero if the arguments are equal.
 *  key is passed as the first argument, an element from the array as the second.
 *  The signature of the comparison function should be equivalent to the following:
 *       int cmp(const void *a, const void *b);
 *  The function must not modify the objects passed to it and must return consistent
 * */
void qsort_r(void* a, size_t n, size_t es, void* thunk,
			 int (*cmp)(void*, const void*, const void*));

/**
 * @brief Sorts the given array pointed to by ptr in ascending order.
 *
 * Sorts the given array pointed to by ptr in ascending order.
 * The array contains count elements of size bytes.
 * Function pointed to by comp is used for object comparison.
 *
 * @param a pointer to the element to sort
 * @param n number of element in the array
 * @param es size of each element in the array in bytes
 * @param compar comparison function which returns ​a negative integer
 *  value if the first argument is less than the second,a positive integer value
 *  if the first argument is greater than the second and zero if the arguments are equal.
 *  key is passed as the first argument, an element from the array as the second.
 *  The signature of the comparison function should be equivalent to the following:
 *       int cmp(const void *a, const void *b);
 *  The function must not modify the objects passed to it and must return consistent
 * */
void qsort(void* a, size_t n, size_t es, int (*compar)(const void*, const void*));

#pragma mark - memory -

/**
 * @brief Allocates size bytes of uninitialized storage.
 *
 * If size is zero, the behavior is implementation defined (null pointer may be returned,
 * or some non-null pointer may be returned that may not be used to access storage, but has to be
 * passed to @see free). malloc is thread-safe: it behaves as though only accessing the memory
 * locations visible through its argument, and not any static storage.
 *
 * @param size number of bytes to allocate
 * @return On success, returns the pointer to the beginning of newly allocated memory.
 * The returned pointer must be deallocated with @see free() or @see realloc().
 * On failure, returns a null pointer.
 * */
void* malloc(size_t size);

/**
 * @brief Deallocates allocated memory space.
 *
 * Deallocates the space previously allocated by @see malloc, @see calloc, @see realloc.
 * If ptr is a null pointer, the function does nothing.
 *
 * The behavior is undefined if the value of ptr does not equal a value returned earlier
 * by @see malloc, @see calloc, @see realloc.
 *
 * The behavior is undefined if the memory area referred to by ptr has already been deallocated,
 * that is, free() or realloc has already been called with ptr as the argument and no calls to
 * malloc, calloc or realloc resulted in a pointer equal to ptr afterwards.
 *
 * The behavior is undefined if after free returns, an access is made through the pointer ptr
 * (unless another allocation function happened to result in a pointer value equal to ptr)
 *
 * @param ptr pointer to the memory to deallocate
 * */
void free(void* ptr);

/**
 * @brief Allocates memory for an array of given number objects of size
 *        and initializes all bytes in the allocated storage to zero.
 *
 * Allocates memory for an array of num objects of size size and initializes
 * all bytes in the allocated storage to zero.
 *
 * @param num number of objects
 * @param size size of the array
 * @return (None)
 * */
void* calloc(size_t num, size_t size);

/**
 * @brief Reallocates the given area of memory.
 *
 * Reallocates the given area of memory. It must be previously allocated by @see malloc,
 * @see calloc or @see realloc and not yet freed with a call to @see free or @see realloc.
 * Otherwise, the results are undefined.
 *
 * The reallocation is done by either:
 *          1) expanding or contracting the existing area pointed to by ptr, if possible.
 *             The contents of the area remain unchanged up to the lesser of the new and old sizes.
 *             If the area is expanded, the contents of the new part of the array are undefined.
 *          2) allocating a new memory block of size size bytes, copying memory area with size
 *             equal the lesser of the new and the old sizes, and freeing the old block.
 *
 * If there is not enough memory, the old memory block is not freed and null pointer is returned.
 * If ptr is NULL, the behavior is the same as calling malloc(size).
 *
 * @param ptr pointer to the memory area to be reallocated
 * @param size new size of the array
 *
 * @return pointer to new memory allocation.
 *	If `size` is zero (e.g. `realloc(ptr,0)`) then returns NULL
 * */
void* realloc(void* ptr, size_t size);

/**
 * @brief Reallocates the given area of memory.
 *
 * Reallocates the given area of memory. It must be previously allocated by @see malloc,
 * @see calloc or @see realloc and not yet freed with a call to @see free or @see realloc.
 * Otherwise, the results are undefined.
 *
 * reallocf is a FreeBSD extension to realloc that frees
 * the input pointer if an error occurrs
 *
 * This library does not handle the BSD case where `realloc(ptr,0)` frees the ptr
 *
 * @param ptr pointer to the memory area to be reallocated
 * @param size new size of the array
 *
 * @return pointer to new memory allocation.
 *	If `size` is zero (e.g. `realloc(ptr,0)`) then returns NULL
 * */
void* reallocf(void* ptr, size_t size);

#ifdef _POSIX_MEMALIGN_VISIBLE
/** Posix Memory Alignment Extension
 *
 * Generated aligned memory. This function forwards the request to aligned malloc.
 * Allocated memory must be freed with aligned_free().
 *
 * @param memptr A pointer to the pointer which will store the aligned memory. The
 *	memory must be freed with aligned_free(). memptr must not be NULL.
 * @param alignment The target alignment for the memory. Must be a power of 2.
 * @param size The size of the allocation. Must be > 0.
 *
 * @pre `memptr` is not NULL. `alignment` is power-of-2. `size` > 0.
 *
 * @returns ENOMEM if memory could not be allocated, EINVAL if alignment is not a power-of-2, and
 *	0 on successful allocation.
 */
int posix_memalign(void** memptr, size_t alignment, size_t size);
#endif

#if(defined(__ISO_C_VISIBLE) && __ISO_C_VISIBLE >= 2011) ||  \
	(defined(__STDC_VERSION) && __STDC_VERSION >= 20112L) || \
	(defined(__cplusplus) && __cplusplus >= 201103L)
/** C11 Aligned Memory Allocation
 *
 * @param align Specifies the alignment. Must be a valid alignment supported by the
 *	implementation (e.g., here - a power of 2).
 * @param size Specifies the number of bytes to allocate.
 *
 * This implementation requires you to call aligned_free() to free memory, not free().
 *
 * @return pointer to new memory allocation; NULL on failure.
 */
void* aligned_alloc(size_t align, size_t size);
#endif

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // STDLIB_H_
