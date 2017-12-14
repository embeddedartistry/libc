#ifndef _CTYPE_H
#define _CTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Checks if the given character is an alphanumeric character
*
* Checks if the given character is an alphanumeric character using the default locale.
*	The following characters are alphanumeric:
*		- digits (0123456789)
*		- uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
*		- lowercase letters (abcdefghijklmnopqrstuvwxyz)
*
*   The behavior is undefined if the value of ch is not representable as unsigned char and is not equal to EOF.
*
* @param ch The character to classify
* @return Non-zero value if the character is an alphanumeric character, 0 otherwise.
*/
int isalnum(int ch);

/**
* @brief Checks if the given character is an alphabetic character
*
* Checks if the given character is an alphabetic character, i.e. either an uppercase letter
*	(ABCDEFGHIJKLMNOPQRSTUVWXYZ), or a lowercase letter (abcdefghijklmnopqrstuvwxyz)
*
* The behavior is undefined if the value of ch is not representable as unsigned char and is not equal to EOF.
*
* @param ch The character to classify
* @return Non-zero value if the character is an alphabetic character, zero otherwise.
*/
int isalpha(int ch);

int isascii(int ch);
int isblank(int ch);
int iscntrl(int ch);
int isdigit(int ch);
int isgraph(int ch);
int islower(int ch);
int isprint(int ch);
int ispunct(int ch);
int isspace(int ch);
int isupper(int ch);
int isxdigit(int ch);
int tolower(int ch);
int toupper(int ch);
int toascii(int ch);

#ifdef __cplusplus
}
#endif

#endif
