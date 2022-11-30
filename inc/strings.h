/**
 * @file strings.h
 * @author James Carr
 * @brief String function declerations.
 * @version 0.1
 * @date 2022-02-23
 * 
 * String related functions used by the kernel.
 * 
 */

#include <stddef.h>
#include <stdbool.h>

#ifndef SIMPLEOS_STRINGS_H
#define SIMPLEOS_STRINGS_H

/**
 * @brief Return the length of a NULL terminal
 * 
 * @param str NULL terminated string 
 * @return size_t - Length of a null terminated string (decimal)
 */
size_t strlen(const char *const str);

/**
 * @brief Return the length of a NULL terminal
 * 
 * @param str NULL terminated string 
 * @param n Total number of characters to count.
 * @return size_t - Length of a null terminated string (decimal) <= n
 */
size_t strnlen(const char *str, int n);

bool is_digit(const char c);

int char_to_digit(const char c);

#endif //SIMPLEOS_STRINGS_H
