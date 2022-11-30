/**
 * @file heap.h
 * @author James Carr
 * @brief Declearations for creating and managing heap memory.
 * @version 0.1
 * @date 2022-03-08
 *
 * Heap Implementatoin: Consists of a directory table (an array) which describes memory blocks free
 * and memory blocks taken.  The table has a pointer to a 'data pool', which is the region of memory space
 * allocated for our heap.  The heap is block based.  Each memory address returned will be aligned to 
 * 4096 therefore, the minimum size returned will always be at least 4096 bytes.   I.e, if 50 bytes are
 * requested, 4096 will be returned.  Similalry, if 6000 bytes are requested, 8192 (4096*2) will returned.
 * 
 * The Entry Table:
 * Is an array of 1 byte entries that represent an directory in the heap.  The array (table size) is calculated
 * by taking the total heap size (100Mb) and dividing it by the block size (4096 bytes).  This equals the 
 * total number of entries needed in the array.
 * 
 * Eg, 104857600 (100Mb stack) / 4096 (block size) = 25600 entries
 * 
 * Table will be located at 0x00007E00 and ends at 0x0007FFFF.  Small area of free memory (refer to intel documentation)
 * This provides  480.5 KiB of usable memory only, our table directory is 25.6kb so this is plenty to hold our heap table.
 * 
 * If the heap is located at 0x01000000:
 * directory zero   = 0x01000000
 * directory one    = 0x01001000
 * directory two    = 0x01002000
 * ...
 * directory n - 1  = 0x073FE000
 * directory n      = 0x073FF000
 * 
 * 
 * Table Entry:
 * Each byte repesents 4096 bytes in the data pool (heap).
 * Upper 4 bits are allocation flags.
 * Lower 4 bits repesent the directory type
 * 
 *          7                                                                       0
 *          +-----------------------------------------------------------------------+
 *  Bit 7   | Has Next | Is_First | Not Used | Not Used | ET 3 | ET 2 | ET 1 | ET 0 | Bit 0
 *          +-----------------------------------------------------------------------+
 * 
 * Has Next = Set (1) if the next block is part of the allocation
 * Is First = Set (1) if this is the first directory of the allocation
 * 
 */

#ifndef SIMPLEOS_HEAP_H
#define SIMPLEOS_HEAP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "kernelconfig.h"

// Heap Block Table defines
#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00

// Bit masks for the heap blocks in the heap block table
// MSB represents the block has another block next to it.
// MSB-1 represents if the block is free to use.
#define HEAP_BLOCK_HAS_NEXT 0b10000000
#define HEAP_BLOCK_IS_FIRST 0b01000000

typedef unsigned char HBT_ENTRY_t;

/**
 * @brief Entry based heap table.
 *
 * Table contains a finite (total_entries) number of block entries
 */
typedef struct
{
    HBT_ENTRY_t *entries; // Pointer to heap block entries
    size_t total_entries; // Total Number of entries.
} heap_table_t;

/**
 * @brief The heap.
 *
 * Contains the a pointer to the heap table and the starting address
 * of the heap.
 */
typedef struct
{
    heap_table_t *heap_table; // Pointer to heap table.
    void *start_address;      // Start address of the heap
} heap_t;

/**
 * @brief Initialises and creates a new heap.
 *
 * @param heap Uninitialised heap structrue
 * @param heap_start Starting address of heap
 * @param heap_end End address of heap
 * @param table Heap table pointing to the heap entries
 * @return int
 */
int heap_create(heap_t *heap, void *heap_start_addr, void *heap_end_addr, heap_table_t *table);

/**
 * @brief
 *
 * @param heap The data pool (memory range) from which to deallocate memory.
 * @param ptr Pointer to memory space to deallocate.
 */
void heap_free(heap_t *heap, void *ptr);

/**
 * @brief
 *
 * @param heap The data pool (memory range) from which to allocate memory.
 * @param size The size in bytes of memory to allocate.
 * @return void* Pointer to the allocated memory.
 */
void *heap_malloc(heap_t *heap, size_t size);

#endif
