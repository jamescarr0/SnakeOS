/**
 * @file kheap.h
 * @author James Carr
 * @brief Function declerations for kernel memory allocation and deallocation.
 * @version 0.1
 * @date 2022-03-08
 * 
 * 
 * Provides prototypes for kernel memory allocation and deallocation of 
 * directory based heap memory.
 */

#ifndef SIMPLEOS_KHEAP_H
#define SIMPLEOS_KHEAP_H

#include <stddef.h>

/**
 * @brief Initialise the kernel heap.
 * 
 */
void kheap_init();

/**
 * @brief Kernel space Malloc
 * 
 * @param size Number of bytes to allocate.
 * @return void* pointer to the beginning of newly allocated memory.
 * 
 * To avoid memory leaks, the pointer must be deallocated with kfree()
 */
void *kmalloc(size_t size);

/**
 * @brief Kernel space: Allocate memory and set memory to zero
 *
 * @param size
 * @return void *pointer to allocated memory which has been set to 0.
 */
void *kzalloc(size_t size);

/**
 * @brief Kernel space: Deallocates memory space allocated by kmalloc.
 * 
 * @param ptr pointer to memory to deallocate.
 */
void kfree(void *ptr);

#endif