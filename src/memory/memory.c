/**
 * @file memory.c
 * @author James Carr
 * @date 23/02/2022
 * @brief Source code for kernel memory function implementations.
 *
 * Implementations for memory related tasks used by the kernel
 *
 */

#include "memory.h"

/* Implementation of the C memset function */
void *memset(void *ptr, int c, size_t size)
{
    char *pC = (char *)ptr;

    for (size_t i = 0; i < size; i++)
        pC[i] = c;

    return ptr;
}

/* Compares two byte sequences.  Looking at the first n bytes will return at int less than,
equal to, or greter than 0 depending on wether s1 is less than, greather than or equal to s2*/
int memcmp(const void *s1, const void *s2, size_t n)
{
    const char *c1 = s1;
    const char *c2 = s2;

    for( ; n-- ; c1++, c2++) 
    {
        if(*c1 != *c2)
        {
            return(c1 - c2);
        }
    }
    return 0;
}