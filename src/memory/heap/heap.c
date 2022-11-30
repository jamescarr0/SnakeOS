/**
 * @file heap.c
 * @author James Carr
 * @brief
 * @version 0.1
 * @date 2022-03-08
 *
 * TODO: Check pointer bounds to assert valid pointer address is passed.
 */

#include "heap.h"
#include "status.h"
#include "memory.h"
#include <stdbool.h>

static void heap_mark_blocks_taken(heap_t *heap, int start_block, uint32_t total_blocks)
{
    uint32_t end_block = (start_block + total_blocks) - 1;
    HBT_ENTRY_t entry = HEAP_BLOCK_TABLE_ENTRY_FREE | HEAP_BLOCK_IS_FIRST; // Mark the block as the first directory.
    if (total_blocks > 1)
    {
        entry |= HEAP_BLOCK_HAS_NEXT;
    }

    for (size_t i = start_block; i <= end_block; i++)
    {
        heap->heap_table->entries[i] = entry;
        entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
        if(i != end_block - 1)
        {   
            // Mark block as having another block.
            // i.e the memory space is spread over consecutive blocks.
            entry |= HEAP_BLOCK_HAS_NEXT; 
        }
    }
}

// Check if the block has been allocated.
static int heap_get_entry_type(HBT_ENTRY_t entry)
{   
    return entry & 0x0f; // 0x00=Free Block, 0x01=Taken Block
}

// Find consecutive blocks of memory to allocate.
static int heap_get_start_block(heap_t *heap, uint32_t total_blocks)
{
    heap_table_t *heap_table = heap->heap_table;
    int current_block = 0;
    int starting_block = -1;

    // Iterate each directory looking for consecutive free blocks of memory.
    for (size_t i = 0; i < heap_table->total_entries; i++)
    {
        if (heap_get_entry_type(heap_table->entries[i] != HEAP_BLOCK_TABLE_ENTRY_FREE))
        {
            current_block = 0;
            starting_block = -1;
            continue;
        }

        if (starting_block == -1)
        {
            starting_block = i;
        }

        if (++current_block == total_blocks)
        { // Found enough blocks to allocate.
            break;
        }
    }

    if (starting_block == -1)
    {
        // Error, no memory available.
        return -ENOMEM;
    }
    else
    {
        return starting_block;
    }
}

static void *heap_block_to_address(heap_t *heap, uint32_t block)
{
    // Calculate an aboslute memory address based off the heap starting address and
    // number of blocks to allocate.
    return heap->start_address + (block * KERNEL_HEAP_BLOCK_SIZE);
}

static void *heap_malloc_blocks(heap_t *heap, uint32_t total_blocks)
{
    void *address = 0;
    int start_block = heap_get_start_block(heap, total_blocks);
    if (start_block < 0)
    {
        return address;
    }

    address = heap_block_to_address(heap, start_block);

    heap_mark_blocks_taken(heap, start_block, total_blocks);

    return address;
}

static void heap_mark_blocks_free(heap_t *heap, int starting_block)
{
    heap_table_t *heap_table = heap->heap_table;
    HBT_ENTRY_t entry;

    for (size_t i = starting_block; i < (size_t)heap_table->total_entries ; i++)
    {
        entry = heap_table->entries[i];
        heap_table->entries[i] = HEAP_BLOCK_TABLE_ENTRY_FREE;
        if(!(entry & HEAP_BLOCK_HAS_NEXT))
        {
                // Reached the end of the block
                break;
        }
    }
    
}

// Ensure that the addresses supplied align to heap block size boundaries.
static bool _validate_heap_alignment(void *ptr)
{
    return ((unsigned int)ptr % KERNEL_HEAP_BLOCK_SIZE) == 0;
}

// Validate that start and end address are correct for the table provided
// Does the table align with the block size.
static int _validate_heap_table(void *start_addr, void *end_addr, heap_table_t *table)
{
    int res = 0;
    size_t table_size = (size_t)(end_addr - start_addr);
    size_t total_blocks = table_size / KERNEL_HEAP_BLOCK_SIZE;
    if (table->total_entries != total_blocks)
    {
        return -EINVARG;
    }
    return res;
}

static int heap_address_to_block(heap_t *heap, void *address)
{
    return ((int)address - (int)heap->start_address) / KERNEL_HEAP_BLOCK_SIZE;
}

// Align input (val) to boundary.  For example if 50 is passed
// we will return 4096.  If 4097 is requested, we shall return
// 4096 * 2.... and so on.
static uint32_t heap_align_value_to_upper(uint32_t val)
{
    if ((val % KERNEL_HEAP_BLOCK_SIZE) == 0)
    {
        return val; // Alignment is good no adjustment needed.
    }

    // Align and return a new value.
    val = (val - (val % KERNEL_HEAP_BLOCK_SIZE));
    val += KERNEL_HEAP_BLOCK_SIZE;
    return val;
}

// Create the heap.
// End address is used to validate that the blocks fit and align within the table correctly.
int heap_create(heap_t *heap, void *heap_start_addr, void *heap_end_addr, heap_table_t *table)
{
    int res = 0;

    // Check for alignment to boundaries.
    if (!_validate_heap_alignment(heap_start_addr) || !_validate_heap_alignment(heap_end_addr))
    {
        return -EINVARG;
    }

    memset(heap, 0, sizeof(heap)); // Init whole heap to zero.
    heap->start_address = heap_start_addr;
    heap->heap_table = table;

    res = _validate_heap_table(heap_start_addr, heap_end_addr, table);
    if (res < 0)
    {
        return res;
    }

    size_t table_size = sizeof(HBT_ENTRY_t) * table->total_entries;

    // Init all blocks in heap directory table to zero so the entire heap can be
    // allocated.
    memset(table->entries, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);

    return res;
}

// Free the previously allocated memory
void heap_free(heap_t *heap, void *ptr)
{
    heap_mark_blocks_free(heap, heap_address_to_block(heap, ptr));
}

void *heap_malloc(heap_t *heap, size_t size)
{   
    // Get an aligned memory size
    size_t aligned_size = heap_align_value_to_upper(size); 

    // Set the number of blocks to allocate.  Minimum size is 4096.
    uint32_t total_blocks = aligned_size / KERNEL_HEAP_BLOCK_SIZE;

    return heap_malloc_blocks(heap, total_blocks);
}