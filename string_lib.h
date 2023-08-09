#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char*   data;
    size_t  length;
    size_t  capacity;
} string;


/**
 * @brief Initializes a new string with the specified raw C-string.
 *
 * This function allocates memory for the new string and copies the contents of the 
 * provided C-string into it. It also sets the length and capacity of the new string.
 *
 * @param raw_str The raw C-string to initialize the new string with.
 * @return A pointer to the newly initialized string. Returns NULL if memory
 * allocation fails.
 * 
 * @note The caller is responsible for freeing the memory of the string 
 * using the string_free() function.
 */
string* string_init(const char* raw_str);


/**
 * @brief Frees the memory occupied by the given string.
 *
 * This function releases the memory allocated for both the string's metadata 
 * and its data. After this function call, the pointer to the string and its 
 * data should not be used.
 *
 * @param str A pointer to the string to be freed. If the pointer is NULL, 
 * the function has no effect.
 * 
 * @note After calling this function, any further access to the string or its
 * data is undefined behavior.
 */
void string_free(string* str);


/**
 * @brief Reserves memory for the string to accommodate a specified capacity.
 *
 * This function attempts to allocate memory to ensure that the string can 
 * store up to `new_capacity` characters without further reallocation. If 
 * `new_capacity` is less than or equal to the current capacity, the function 
 * does nothing and returns true.
 *
 * @param str A pointer to the string for which memory should be reserved.
 * @param new_capacity The desired capacity in characters. This does not 
 * include the null terminator.
 * 
 * @return Returns true if the reservation was successful or if no action 
 * was taken (because the current capacity is sufficient). Returns false 
 * if memory allocation failed.
 * 
 * @note If memory allocation fails, the original string remains unchanged.
 */
bool string_reserve(string* str, size_t new_capacity);

/**
 * @brief Appends the contents of the source string to the destination string.
 *
 * This function attempts to concatenate the given source string to the end
 * of the destination string. If the current capacity of the destination string
 * is insufficient to hold the combined result, it reallocates memory to accommodate
 * the concatenated string.
 *
 * @param dest A pointer to the destination string to which the source string 
 * will be appended.
 * @param source The string to be appended to the destination string. It should
 * be null-terminated.
 * 
 * @return Returns true if the concatenation was successful. Returns false 
 * if memory allocation for resizing the destination string failed.
 * 
 * @note If memory allocation fails, the original destination string remains unchanged.
 */
bool string_concat(string* dest, const char* source);

/**
 * @brief Checks if all characters in the given string are digits.
 *
 * This function iterates through each character of the input string
 * and checks if every character is a digit (0-9).
 *
 * @param str A pointer to the string whose characters are to be checked.
 * 
 * @return Returns true if all characters in the string are digits. 
 * Returns false if any character in the string is not a digit or if the string is empty.
 * 
 * @note This function does not check for signs (+/-) or decimal points. 
 * Only characters 0-9 are considered digits.
 */
bool string_isdigit(const string* str);

/**
 * @brief Counts the occurrences of a specified character in a given string.
 *
 * This function iterates through each character of the input string
 * and counts how many times the specified character appears.
 *
 * @param str A pointer to the string in which occurrences of the character are to be counted.
 * @param char_to_count The character whose occurrences are to be counted.
 * 
 * @return Returns the number of times the specified character appears in the string. 
 * Returns 0 if the character does not appear or if the string is empty.
 * 
 * @note This function performs a case-sensitive count. To perform a case-insensitive count,
 * consider converting the entire string and the character to a common case (e.g., lower) before calling.
 */
int string_count_char(const string* str, char char_to_count);


/**
 * @brief Extracts a substring from the given string between specified indices.
 *
 * This function returns a new string that contains the characters of the original string
 * starting from `start_index` up to, but not including, `end_index`. If the specified 
 * indices are out of bounds or if `start_index` is greater than or equal to `end_index`,
 * the function returns NULL.
 *
 * @param str A pointer to the original string from which the substring is to be extracted.
 * @param start_index The starting index (inclusive) of the substring.
 * @param end_index The ending index (exclusive) of the substring.
 * 
 * @return Returns a pointer to a new string containing the extracted substring. 
 * The caller is responsible for freeing the memory allocated for this new string using `string_free()`.
 * Returns NULL if the extraction is not possible due to invalid indices.
 * 
 * @note Indices are zero-based, i.e., the first character of the string is at index 0.
 */
string* string_substr(const string* str, size_t start_index, size_t end_index);

/**
 * @brief Creates a deep copy of the given string.
 *
 * This function returns a new string that contains the exact characters of the original string.
 * Both the structure and the underlying character data are copied, ensuring that the original
 * and the copied string are completely independent of each other.
 *
 * @param str A pointer to the original string that needs to be copied.
 * 
 * @return Returns a pointer to a new string that is a deep copy of the original string. 
 * The caller is responsible for freeing the memory allocated for this new string using `string_free()`.
 * Returns NULL if the memory allocation for the copy fails.
 */
string* string_copy(const string* str);

/**
 * @brief Checks if the 'needle' string is present in the 'haystack' string.
 *
 * This function searches for the first occurrence of the substring 'needle' in the string 'haystack'.
 * If 'needle' is found, the function returns a pointer to the beginning of the first occurrence of 'needle'.
 * Otherwise, it returns NULL.
 *
 * @param haystack A pointer to the string in which the search is to be performed.
 * @param needle A pointer to the string for which we are searching in the 'haystack'.
 * 
 * @return Returns a pointer to the beginning of the first occurrence of 'needle' in 'haystack',
 * or NULL if 'needle' is not found.
 */
char* string_contains(const string* haystack, char* needle);

/**
 * @brief Compares two strings for equality.
 *
 * This function compares the strings 's1' and 's2'. It behaves similarly to the standard `strcmp` function.
 *
 * @param s1 A pointer to the first string to be compared.
 * @param s2 A pointer to the second string to be compared.
 * 
 * @return Returns an integer less than, equal to, or greater than zero if 's1' is found, respectively,
 * to be less than, to match, or be greater than 's2'.
 */
int string_compare(const string* s1, const string* s2);

/**
 * @brief Removes leading and trailing whitespace from a string.
 *
 * This function trims whitespace characters (like spaces, tabs, and newlines) from the beginning and end 
 * of the string 'str'. The length of 'str' is updated after trimming, and the trimmed content is stored 
 * back in 'str->data'.
 *
 * @param str A pointer to the string to be trimmed.
 *
 * @note This function modifies the input string in-place.
 */
void string_trim(string* str);

/**
 * @brief Converts all the characters of a string to lowercase.
 *
 * This function iterates through each character of the string 'str' and converts 
 * it to lowercase using the standard 'tolower' function. The transformation is 
 * done in-place, meaning the original string 'str' is modified directly.
 *
 * @param str A pointer to the string to be converted to lowercase.
 *
 * @note This function modifies the input string in-place.
 */
void string_tolower(string* str);

/**
 * @brief Converts all the characters of a string to uppercase.
 *
 * This function iterates through each character of the string 'str' and converts 
 * it to uppercase using the standard 'toupper' function. The transformation is 
 * done in-place, meaning the original string 'str' is modified directly.
 *
 * @param str A pointer to the string to be converted to uppercase.
 *
 * @note This function modifies the input string in-place.
 */
void string_toupper(string* str);



#endif // STRING_LIB_H
