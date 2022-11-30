/**
 * @file idt.h
 * @author James Carr
 * @brief IDT, IDTR and data structure declerations
 * @version 0.1
 * @date 02/03/2022
 *
 */

#ifndef SIMPLEOS_IDT_H
#define SIMPLEOS_IDT_H

#include <stdint.h>
#include "kernelconfig.h"

#define IDT_INTERRUPT_GATE 0xE
#define IDT_TRAP_GATE 0xF
#define IDT_RING_3 0x3
#define PRESENT_BIT_SET 0x1
#define UNUSED 0x0

/**
 * @brief IDT Descriptor directory
 *
 * Each directory has a complex structure.
 * Offset: A 32-bit value, split in two parts. It represents the address of the directory point of the Interrupt Service Routine.
 * Selector: A Segment Selector with multiple fields which must point to a valid code segment in your GDT.
 * Gate Type: A 4-bit value which defines the type of gate this Interrupt Descriptor represents. There are five valid type values:
 * 0b0101 or 0x5: Task Gate, note that in this case, the Offset value is unused and should be set to zero.
 * 0b0110 or 0x6: 16-bit Interrupt Gate
 * 0b0111 or 0x7: 16-bit Trap Gate
 * 0b1110 or 0xE: 32-bit Interrupt Gate
 * 0b1111 or 0xF: 32-bit Trap Gate
 * DPL: A 2-bit value which defines the CPU Privilege Levels which are allowed to access this interrupt via the INT instruction. Hardware interrupts ignore this mechanism.
 * P: Present bit. Must be set (1) for the descriptor to be valid.
 *
 */
typedef struct
{
    uint16_t offset_1; // Offset bits 0...15
    uint16_t selector; // Code segment selector in GDT
    uint8_t zero;      // Unused - Set to 0
    uint8_t type_attr; // 4 bit Gate Type,
                       // 1 bit Storage Segment
                       // 2 bit Descriptor Privilege Level
                       // Present (IRQ No.) Set to Zero for Unused IRQ.
    uint16_t offset_2; // Offset 16...31
} __attribute__((packed)) idt_entry_t;

/**
 * @brief The location and size of the IDT
 *
 * The location of the IDT is kept in the IDTR (IDT register). This is loaded using
 * the LIDT assembly instruction, whose argument is an IDTR:
 * Size: One less than the size of the IDT in bytes.
 * Offset: The linear address of the Interrupt Descriptor Table (not the physical address, paging applies).
 * Note that the amount of data loaded by LIDT differs in 32-bit and 64-bit modes, Offset is 4 bytes long in 32-bit mode and 8 bytes long in 64-bit mode.
 * This is similar to the GDT, except:
 * The first directory (at zero offset) is used in the IDT.
 * There are 256 interrupt vectors (0..255), so the IDT should have 256 entries, each directory corresponding to a specific interrupt vector.
 * Although the IDT can contain more than 256 entries, they are ignored.
 * Although the IDT can contain less than 256 entries, any entries that are not present (due to this or other reasons) will generate a
 * General Protection Fault when an attempt to access them is made. Ideally the IDT should contain enough entries so that this fault
 *(which is itself an interrupt vector) can be handled.
 */
typedef struct
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idtr_t;

/**
 * @brief Load the interrupt descriptor table in the IDT register (IDTR)
 *
 * @param pIDTR pointer to the location of the IDT.
 */
static inline void lidt(idtr_t const *const pIDTR)
{
    asm("lidt %0"
        :
        : "m"(*pIDTR));
}

/**
 * @brief Create interrupt descriptors, set interrupt routines and load into the IDT register
 *
 */
void idt_init();

/**
 * @brief
 *
 * @param interrupt_number
 * @param isr_address
 * @param attributes
 *
 * Attributes For a 32 bit Gate Descriptor.
 * Bit 47       : Present bit - Must be set to 1 for descriptor to be valid.
 * Bit 46-45    : DPL (privilege/ring level)
 * Bit 44       : Unused
 * Bit 43-40    : Gate Type
 */
void idt_set(const int interrupt_number, const void *const isr_address, uint8_t attributes);

#endif // SIMPLEOS_IDT_H