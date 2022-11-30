/**
 * @file kernelconfig.h
 * @author James Carr
 * @date 02/03/2022
 * @brief Configuration settings for SimpleOS Kernel.
 * 
 */

#ifndef SIMPLEOS_KERNELCONFIG_H
#define SIMPLEOS_KERNELCONFIG_H

#define SIMPLEOS_MAX_INTERRUPTS 512

#define KERNEL_CODE_SELECTOR 0x8   // CODE_SEG in kernel.asm
#define KERNEL_DATA_SELECTOR 0x10   // DATA_SEG in kernel.asm

// (1024 * 1024) * 100mb = 104857600
// 104857600 / 4096 = 25600 table entries.
// 100Mb Heap Size (Fixed for now)
#define KERNEL_HEAP_SIZE_BYTES 104857600
#define KERNEL_HEAP_BLOCK_SIZE 4096
#define KERNEL_HEAP_ADDRESS 0x01000000
#define KERNEL_HEAP_TABLE_ADDRESS 0x00007E00 // 480.5 KiB Usable memory only. Ends at 0x0007FFFF

#define HDD_SECTOR_SIZE 512

#define MAX_DIRECTORY_PATH 512

#endif
