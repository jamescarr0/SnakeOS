/**
 * @file memory.h
 * @author James Carr
 * @brief Declerations for memory related tasks used by ther kernel
 * @version 0.1
 * @date 2022-02-23
 * 
 */


#ifndef SIMPLEOS_MEMORY_H
#define SIMPLEOS_MEMORY_H

#include <stddef.h>

/**
 * Sets a block of memory of n bytes with the specified value.
 *
 * @param ptr Pointer to the starting address of the memory block to fill.
 * @param c Value to fill the memory block with.
 * @param size Number of bytes to set.
 * @return void pointer to the starting address.
 */
void *memset(void *ptr, int c, size_t size);

/**
 * Compares two byte sequences.
 *
 * @param s1 The first string for comparison
 * @param s2 The second string for comparison
 * @param n The total number of bytes to compare
 * @return int: greater than, equal to, or less than 0.
 */
int memcmp(const void *s1, const void *s2, size_t n);

#endif // SIMPLEOS_MEMORY_H
