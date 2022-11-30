/**
 * @file Source code to implement string related functions.
 * @date 22/02/2022
 * **Author:** James Carr
 * ## Role
 * Provides the kernel with string and character related functions.
 */

#include <stddef.h>
#include <stdbool.h>

#define ASCII_CHAR_0 48
#define ASCII_CHAR_9 57 

size_t strlen(const char *str) {
    /* Iterate a string and increment the length counter
     * String must be NULL terminated.
     *
     * Returns:
     * Length of NULL terminated string
     */
    size_t length = 0;
    while (*str++)
        length++;

    return length;
}

size_t strnlen(const char *str, int n) {

    int length = 0;
    while(*str++ && length < n)
        length++;
        
    return length;
}

bool is_digit(int c)
{
    if (c < 0 || c > 9)
    {
        return false;
    }
    return true;
}

int char_to_digit(const char c)
{
    return c - 48;
}
