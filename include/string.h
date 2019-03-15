#ifndef STRING_H_
#define STRING_H_

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <stddef.h>
#include <stdint.h>

#pragma mark - memory -

/**
 * @brief Compares the first n characters of the two objects pointed to by s1 and s2.
 *
 * Compares the first n characters of the objects pointed to by s1 and s2.
 * The comparison is done lexicographically.
 *
 * The behavior is undefined if access occurs beyond the end of either object pointed to by s1 and
 * s2. The behavior is undefined if either s1 or s2 is a null pointer.
 *
 * @param s1 pointers to the objects to compare
 * @param s2 pointers to the objects to compare
 * @param n the number of bytes to examine
 * @return Negative value if s1 appears before s2 in lexicographical order.
 *         Zero if s1 and s2 compare equal, or if n is zero.
 *         Positive value if s1 appears after s2 in lexicographical order.
 * */
int memcmp(const void* s1, const void* s2, size_t n);

/**
 * @brief Copies the value c into each of the first n characters of the object pointed to by dest.
 *
 * Copies the value c (after conversion to unsigned char as if by (unsigned char)c ) into each of
 * the first n characters of the object pointed to by dest.
 *
 *  The behavior is undefined if access occurs beyond the end of the dest array.
 *  The behavior is undefined if dest is a null pointer.
 *
 * @param dest pointer to the object to fill
 * @param c fill byte
 * @param n number of bytes to fill
 * @return A copy of dest
 * */
void* memset(void* dest, int c, size_t n);

/**
 * @brief Copies n characters from the object pointed to by src to the object pointed to by dest.
 *
 * Copies n characters from the object pointed to by src to the object pointed to by dest.
 * Both objects are interpreted as arrays of unsigned char.
 *
 * The behavior is undefined if access occurs beyond the end of the dest array.
 * If the objects overlap (which is a violation of the restrict contract) (since C99), the behavior
 * is undefined. The behavior is undefined if either dest or src is a null pointer.
 *
 * @param dest pointer to the object to copy to
 * @param src pointer to the object to copy from
 * @param n number of bytes to copy
 * @return a copy of dest
 * */
void* memcpy(void* __restrict dest, const void* __restrict src, size_t n);

/**
 * @brief Copies n characters from the object pointed to by src to the object pointed to by dest.
 *
 * Copies n characters from the object pointed to by src to the object pointed to by dest.
 * Both objects are interpreted as arrays of unsigned char.
 *
 *  The behavior is undefined if access occurs beyond the end of the dest array.
 *  The behavior is undefined if either dest or src is a null pointer.
 *
 * @param dest pointer to the object to copy to
 * @param src pointer to the object to copy from
 * @param n number of bytes to copy
 * @return a copy of dest
 * */
void* memmove(void* dest, const void* src, size_t n);

/**
 * @brief Finds the first occurrence of c in the initial n characters of the object pointed to by s
 *
 * Finds the first occurrence of c (after conversion to unsigned char as if by (unsigned char)c )
 * in the initial n characters (each interpreted as unsigned char) of the object pointed to by s.
 *
 * The behavior is undefined if access occurs beyond the end of the array (s) searched.
 * The behavior is undefined if s is a null pointer.
 *
 * @param s pointer to the object to be examined
 * @param c character to search for
 * @param n max number of characters to examine
 * @return a copy of dest
 * */
void* memchr(const void* s, int c, size_t n);

/**
 * @brief Find substring s in memory area l.
 *
 * Finds the start of the first occurrence of the substring s of length s_len in the memory area l
 * of length l_len.
 *
 * The behavior is undefined if access occurs beyond the end of the array (s) searched.
 * The behavior is undefined if s is a null pointer.
 *
 * @param l pointer to the object to be examined
 * @param l_len number of characters to examine
 * @param s the substring to search for
 * @param s_len number of characters to examine
 * @return  a pointer to the beginning of the substring, or NULL if the substring is not found.
 * */
void* memmem(const void* l, size_t l_len, const void* s, size_t s_len);

#pragma mark - string -

/**
 * @brief Returns the length of the given null-terminated byte string.
 *
 * Returns the length of the given null-terminated byte string, that is,
 * the number of characters in a character array whose first element is
 * pointed to by str up to and not including the first null character.
 *
 *  The behavior is undefined if str is not a pointer to a null-terminated byte string.
 *
 * @param str pointer to the null-terminated byte string to be examined
 * @return The length of the null-terminated byte string str.
 * */
size_t strlen(const char* str);

/**
 * @brief Returns the length of the given null-terminated byte string.
 *
 * Same as @sa strlen, except that the function returns zero if str is a null pointer
 * and returns maxlen if the null character was not found in the first maxlen bytes of str.
 *
 * The behavior is undefined if str points to a character array which lacks the null character
 * and the size of that character array < maxlen; in other words, an erroneous value of maxlen does
 * not expose impending buffer overflow.
 *
 * @param str pointer to the null-terminated byte string to be examined
 * @param maxlen maximum number of characters to examine
 * @return  The length of the null-terminated byte string str on success, zero if str is a null
 * pointer, maxlen if the null character was not found.
 * */
size_t strnlen(const char* str, size_t maxlen);

/**
 * @brief Copies the null-terminated byte string pointed to by src to the character array whose
 * first element is pointed to by dest.
 *
 * Copies the null-terminated byte string pointed to by src, including the null terminator,
 * to the character array whose first element is pointed to by dest. It may clobber the rest
 * of the destination array with unspecified values and that the following errors are detected
 * at runtime and call the currently installed constraint handler function:
 * The behavior is undefined if the dest array is not large enough.
 * The behavior is undefined if the strings overlap.
 * The behavior is undefined if either dest is not a pointer to a character array or src is not a
 * pointer to a null-terminated byte string. The behavior is undefined if the size of the character
 * array pointed to by dest <= strlen(src, destsz)
 *
 * @param dst pointer to the character array to write to
 * @param src pointer to the null-terminated byte string to copy from
 * @return a copy of dest
 * */
char* strcpy(char* __restrict dst, const char* __restrict src);

/**
 * @brief  Copies at most maxlen characters of the character array pointed to by src to character
 * array pointed to by dest.
 *
 * Copies at most maxlen characters of the character array pointed to by src (including the
 * terminating null character, but not any of the characters that follow the null character) to
 * character array pointed to by dest. If maxlen is reached before the entire array src was copied,
 * the resulting character array is not null-terminated. If, after copying the terminating null
 * character from src, maxlen is not reached, additional null characters are written to dest until
 * the total of maxlen characters have been written.
 *
 * The behavior is undefined if the character arrays overlap, if either dest or src is not a pointer
 * to a character array (including if dest or src is a null pointer), if the size of the array
 * pointed to by dest is less than maxlen, or if the size of the array pointed to by src is less
 * than maxlen and it does not contain a null character.
 *
 * @param dst pointer to the character array to copy to
 * @param src pointer to the character array to copy from
 * @param maxlen maximum number of characters to copy
 * @return a copy of dest
 * */
char* strncpy(char* __restrict dst, const char* __restrict src, size_t maxlen);

/**
 * @brief Finds the first occurrence of the substring  in the string
 *
 * Finds the first occurrence of the null-terminated byte string pointed to by substring in the
 * null-terminated byte string pointed to by string. The terminating null characters are not
 * compared.
 *
 * The behavior is undefined if either stirng or substring is not a pointer to a null-terminated
 * byte string.
 *
 * @param string pointer to the null-terminated byte string to examine
 * @param substring pointer to the null-terminated byte string to search for
 * @return Pointer to the first character of the found substring in string, or NULL if no such
 * substring is found. If substring points to an empty string, string is returned.
 * */
char* strstr(const char* string, const char* substring);

/**
 * @brief Finds the first occurrence of find in the initial slen characters of the object pointed to
 * by s
 *
 * Locates the first occurrence of the null-terminated string find in the string s,
 * where not more than slen characters are searched. Characters that appear after a `\0' character
 * are not searched.
 *
 * The behavior is undefined if either find or s is not a pointer to a null-terminated byte string.
 *
 * @param s pointer to the null-terminated byte string to examine
 * @param find pointer to the null-terminated byte string to search for
 * @param slen maxinum number of characters to search for
 * @return If find is an empty string, s is returned; if find occurs nowhere in s, NULL is returned;
 *         otherwise a pointer to the first character of the first occurrence of find is returned.
 * */
char* strnstr(const char* s, const char* find, size_t slen);

/**
 * @brief Compares two null-terminated byte strings lexicographically.
 *
 * Compares two null-terminated byte strings lexicographically.
 *
 * The behavior is undefined if s1 or s2 are not pointers to null-terminated byte strings.
 *
 * @param s1 pointers to the null-terminated byte strings to compare
 * @param s2 pointers to the null-terminated byte strings to compare
 * @return Negative value if s1 appears before s2 in lexicographical order.
 *         Zero if s1 and s2 compare equal, or if n is zero.
 *         Positive value if s1 appears after s2 in lexicographical order.
 * */
int strcmp(const char* s1, const char* s2);

/**
 * @brief Compares at most n characters of two possibly null-terminated arrays.
 *
 * Compares at most count characters of two possibly null-terminated arrays.
 * The comparison is done lexicographically.
 *
 * The behavior is undefined when access occurs past the end of either array s1 or s2.
 * The behavior is undefined when either s1 or s2 is the null pointer.
 *
 * @param s1 pointers to the null-terminated byte strings to compare
 * @param s2 pointers to the null-terminated byte strings to compare
 * @param n maximum number of characters to compare
 * @return Negative value if s1 appears before s2 in lexicographical order.
 *         Zero if s1 and s2 compare equal, or if n is zero.
 *         Positive value if s1 appears after s2 in lexicographical order.
 * */
int strncmp(const char* s1, const char* s2, size_t n);

/**
 * @brief Duplicate the passed in string str.
 *
 * Returns a pointer to a new string which is a duplicate of the string str.
 * Memory for the new string is obtained with malloc(3), and can be freed with free(3).
 *
 * @param str a pointer to a string to duplicate
 * @return a pointer to the duplicated string on success. NULL if insufficient memory was available,
 * with errno set to indicate cause of error.
 * */
char* strdup(const char* str);

/**
 * @brief Duplicate n bytes of the passed in string str.
 *
 * strndup is similar to @sa strdup, but copies at most n bytes.
 * If str is longer than n, only n bytes are copied, and a terminating null byte ('\0') is added.
 *
 * @param str a pointer to a string to duplicate
 * @param n maximum number of bytes to copy
 * @return a pointer to the duplicated string on success. NULL if insufficient memory was available,
 * with errno set to indicate cause of error.
 * */
char* strndup(const char* str, size_t n);

/**
 * @brief Finds the first occurrence of c in the null-terminated byte string pointed to by s.
 *
 * Finds the first occurrence of c (after conversion to char as if by (char)c ) in the
 * null-terminated byte string pointed to by s (each character interpreted as unsigned char). The
 * terminating null character is considered to be a part of the string and can be found when
 * searching for '\0'.
 *
 * The behavior is undefined if s is not a pointer to a null-terminated byte string.
 *
 * @param s pointer to the null-terminated byte string to be analyzed
 * @param c character to search for
 * @return a pointer to the found character in s, or null pointer if no such character is found.
 * */
char* strchr(const char* s, int c);

/**
 * @brief Finds the last occurrence of c in the null-terminated byte string pointed to by s.
 *
 * Finds the last occurrence of c (after conversion to char as if by (char)c ) in the
 * null-terminated byte string pointed to by s (each character interpreted as unsigned char). The
 * terminating null character is considered to be a part of the string and can be found when
 * searching for '\0'.
 *
 * The behavior is undefined if s is not a pointer to a null-terminated byte string.
 *
 * @param s pointer to the null-terminated byte string to be analyzed
 * @param c character to search for
 * @return a pointer to the found character in s, or null pointer if no such character is found.
 * */
char* strrchr(const char* s, int c);

/**
 * @brief Appends a copy of the null-terminated byte string pointed to
 *        by src to the end of the null-terminated byte string pointed to by dest.
 *
 * Appends a copy of the null-terminated byte string pointed to by src to the end of
 * the null-terminated byte string pointed to by dest. The character src[0] replaces
 * the null terminator at the end of dest. The resulting byte string is null-terminated.
 *
 * The behavior is undefined if the destination array is not large enough for the contents
 * of both src and dest and the terminating null character.
 * The behavior is undefined if the strings overlap.
 * The behavior is undefined if either dest or src is not a pointer to a null-terminated byte
 * string.
 *
 * @param dst pointer to the null-terminated byte string to append to
 * @param src pointer to the null-terminated byte string to copy from
 * @return a copy of dest
 * */
char* strcat(char* __restrict dst, const char* __restrict src);

/**
 * @brief Appends at most maxlen characters from the character array pointed to by src,
 *        to the end of the null-terminated byte string pointed to by dest.
 *
 * Appends at most count characters from the character array pointed to by src,
 * stopping if the null character is found, to the end of the null-terminated byte string pointed to
 * by dest. The character src[0] replaces the null terminator at the end of dest. The terminating
 * null character is always appended in the end (so the maximum number of bytes the function may
 * write is maxlen+1).
 *
 * The behavior is undefined if the destination array is not large enough for the contents
 * of both src and dest and the terminating null character.
 * The behavior is undefined if the strings overlap.
 * The behavior is undefined if either dest or src is not a pointer to a null-terminated byte
 * string.
 *
 * @param dst pointer to the null-terminated byte string to append to
 * @param src pointer to the null-terminated byte string to copy from
 * @param maxlen maximum number of characters to copy
 * @return a copy of dest
 * */
char* strncat(char* __restrict dst, const char* __restrict src, size_t maxlen);

/**
 * @brief  Finds the next token in a null-terminated byte string pointed to by s.
 *
 *  Finds the next token in a null-terminated byte string pointed to by s.
 *  The separator characters are identified by null-terminated byte string pointed to by delim.
 *  This function is designed to be called multiples times to obtain successive tokens from the same
 * string.
 *
 *  - If s != NULL, the call is treated as the first call to strtok for this particular string.
 *    The function searches for the first character which is not contained in delim.
 *
 *  The behavior is undefined if either s or delim is not a pointer to a null-terminated byte
 * string.
 *
 * @param s pointer to the null-terminated byte string to tokenize
 * @param delim pointer to the null-terminated byte string identifying delimiters
 * @return Returns pointer to the beginning of the next token or NULL if there are no more tokens.
 * */
char* strtok(char* s, const char* delim);

// TODO: documentation
size_t strxfrm(char* __restrict, const char* __restrict, size_t);
size_t strcspn(const char*, const char*);
size_t strspn(const char*, const char*);
char* strpbrk(const char*, const char*);
int strcoll(const char*, const char*);
char* strerror(int);
int strerror_r(int, char*, size_t);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif /* STRING_H_ */
