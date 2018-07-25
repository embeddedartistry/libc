#ifndef CTYPE_H_
#define CTYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks if the given character is an alphanumeric character.
 *
 * Checks if the given character is an alphanumeric character using the default locale.
 *	The following characters are alphanumeric:
 *		- digits (0123456789)
 *		- uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
 *		- lowercase letters (abcdefghijklmnopqrstuvwxyz)
 *
 *   The behavior is undefined if the value of ch is not representable as unsigned char and is not
 *equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is an alphanumeric character, 0 otherwise.
 * */
int isalnum(int ch);

/**
 * @brief Checks if the given character is an alphabetic character.
 *
 * Checks if the given character is an alphabetic character, i.e. either an uppercase letter
 *	(ABCDEFGHIJKLMNOPQRSTUVWXYZ), or a lowercase letter (abcdefghijklmnopqrstuvwxyz)
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 *equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is an alphabetic character, zero otherwise.
 * */
int isalpha(int ch);

/**
 * @brief Checks if a given character is  a 7-bit US-ASCII character.
 *
 * Checks if a given character 7-bit unsigned char value that fits into the ASCII character set.
 *	which is any character between 0 and  0x7f inclusive.
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 *equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if ch is a 7-bit US-ASCII character code, zero otherwise.
 * */
int isascii(int ch);

/**
 * @brief Checks if the given character is a blank character.
 *
 * Checks if the given character is a blank character using the default locale.
 * 	The following characters classified as blank:
 *		- space (0x20)
 *		- horizontal tab (0x09)
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 *equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is a blank character, zero otherwise.
 * */
int isblank(int ch);

/**
 * @brief Checks if the given character is a control character.
 *
 * Checks if the given character is a control character.
 * 	The following are examples of control character:
 *		- codes (0x00-0x1F) and (0x7F)
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 *equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is a control character, zero otherwise.
 * */
int iscntrl(int ch);

/**
 * @brief Checks if the given character is a numeric character.
 *
 * Checks if the given character is a numeric character (0123456789).
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 * equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is a numeric character, zero otherwise.
 * */
int isdigit(int ch);

/**
 * @brief Checks if the given character has a graphical representation.
 *
 * Checks if the given character has a graphical representation using the default locale.
 * 	The following characters are graphical:
 *		- number (0123456789)
 *		- uppercase letter (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
 *		- letter (abcdefghijklmnopqrstuvwxyz)
 *		- punctuation character (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 *equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character has a graphical representation character, zero otherwise.
 * */
int isgraph(int ch);

/**
 * @brief Checks if the given character is classified as a lowercase character.
 *
 * Checks if the given character is classified as a lowercase character using the default local.
 * islower returns true only for the lowercase letters (abcdefghijklmnopqrstuvwxyz). If islower
 * returns true, it is guaranteed that \sa iscntrl, \sa isdigit, \sa ispunct, \sa isspace will
 * return false for the same character in the same default locale.
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 * equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is a lowercase letter, zero otherwise.
 * */
int islower(int ch);

/**
 * @brief Checks if the given character can be printed.
 *
 * Checks if the given character can be printed using the default locale.
 * 	The following characters are printable:
 *		- number (0123456789)
 *		- uppercase letter (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
 *		- letter (abcdefghijklmnopqrstuvwxyz)
 *		- punctuation character (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)
 *		- space (0x20)
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 *equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character can be printed, zero otherwise.
 * */
int isprint(int ch);

/**
 * @brief Checks if the given character is a punctuation character.
 *
 * Checks if the given character is a punctuation character using the default local.
 * 	The following characters are classified as punctuation character:
 *		 - (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 *equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is a punctuation character, zero otherwise.
 * */
int ispunct(int ch);

/**
 * @brief Checks if the given character is a whitespace character.
 *
 * Checks if the given character is a whitespace character.
 * 	The following are examples of a whitespace character:
 *		- space (0x20)
 *		- feed (0x0c)
 *		- line feed (0x0a)
 *		- carriage return (0x0d)
 *		- horizontal tab (0x09)
 *		- vertical tab (0x0b)
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 *equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is a whitespace character, zero otherwise.
 * */
int isspace(int ch);

/**
 * @brief Checks if the given character is an uppercase character
 *
 * Checks if the given character is an uppercase character using the default local.
 * isupper returns true only for the uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ). If isupper
 * returns true, it is guaranteed that \sa iscntrl, \sa isdigit, \sa ispunct, \sa isspace will
 * return false for the same character in the same default locale.
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 * equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is an uppercase letter, zero otherwise.
 * */
int isupper(int ch);

/**
 * @brief Checks if the given character is a hexadecimal numeric character.
 *
 * Checks if the given character is a hexadecimal numeric character (0123456789).
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 * equal to EOF.
 *
 * @param ch The character to classify
 * @return Non-zero value if the character is an hexadecimal numeric character, zero otherwise.
 * */
int isxdigit(int ch);

/**
 * @brief Converts the given character to lowercase.
 *
 * Converts the given character to lowercase according to the character
 * conversion rules defined by the default local, i.e. the following uppercase letters
 * (ABCDEFGHIJKLMNOPQRSTUVWXYZ) are replaced with respective lowercase letters
 * (abcdefghijklmnopqrstuvwxyz).
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 * equal to EOF.
 *
 * @param ch character to be converted.
 * @return Lowercase version of ch or unmodified ch if no lowercase version is listed in the default
 * locale.
 * */
int tolower(int ch);

/**
 * @brief Converts the given character to lowercase.
 *
 * Converts the given character to lowercase according to the character
 * conversion rules defined by the default local, i.e. the following lowercase letters
 * (abcdefghijklmnopqrstuvwxyz) are replaced with respective uppercase letters
 * (ABCDEFGHIJKLMNOPQRSTUVWXYZ).
 *
 * The behavior is undefined if the value of ch is not representable as unsigned char and is not
 * equal to EOF.
 *
 * @param ch character to be converted.
 * @return Uppercase version of ch or unmodified ch if no uppercase version is listed in the default
 * locale.
 * */
int toupper(int ch);

/**
 * @brief Converts the given character to ASCII.
 *
 * Converts the given character to  a 7-bit unsigned char value that fits into the ASCII character
 * set.
 *
 * @param ch character to be converted.
 * @return The value returned is that of the converted letter, or ch if the conversion was not
 * possible.
 * */
int toascii(int ch);

#ifdef __cplusplus
}
#endif

#endif // CTYPE_H_
