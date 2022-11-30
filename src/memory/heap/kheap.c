/**
 * @file kheap.c
 * @author James Carr
 * @brief
 * @version 0.1
 * @date 2022-03-08
 *
 * Kernel space only. Memory allocation functions.
 */

#include "kheap.h"
#include "heap.h"
#include "stdio.h"
#include "memory.h"

heap_t kernel_heap;
heap_table_t kernel_heap_table;

// Create and initialise a kernel heap.
void kheap_init()
{
    // Total Number of block entries the heap will manage. 
    // Eg.. 104857600 (100Mb stack) / 4096 (block size) = 25600 bytes
    int total_table_entries = KERNEL_HEAP_SIZE_BYTES / KERNEL_HEAP_BLOCK_SIZE;

    // Store the heap table at the specified memory address
    // Our entries are 25600 with a 100mb stack so this memory space must be large enough to accomodate the table.
    kernel_heap_table.entries = (HBT_ENTRY_t *)KERNEL_HEAP_TABLE_ADDRESS;
    kernel_heap_table.total_entries = total_table_entries;

    // End of the heap.
    int *heap_end = (void *) KERNEL_HEAP_ADDRESS + KERNEL_HEAP_SIZE_BYTES;

    int res = heap_create(&kernel_heap, (void *) KERNEL_HEAP_ADDRESS, heap_end, &kernel_heap_table);
    if (res < 0) 
    {
        print("Kernel Panic TODO: Failed to init and create heap!\n", red);
    }
}

// Allocate number of bytes for the kernel heap.
void *kmalloc(size_t size)
{
    return heap_malloc(&kernel_heap, size);
}

// Malloc and memset.  Allocate memory and set to zero.
void *kzalloc(size_t size)
{
    void *p = kmalloc(size);
    if(!p) return NULL;

    memset(p, 0x00, size);
    return p;
}

// Free previously allocated kernel memory.
void kfree(void *ptr)
{
    heap_free(&kernel_heap, ptr);
}
