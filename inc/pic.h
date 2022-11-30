/**
 * @file pic.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 * 
 * 
 */

#ifndef SIMPLEOS_PIC_H
#define SIMPLEOS_PIC_H

#include <stdint.h>

#define PIC_EOI 0x20 // End of interrupt command code.

/* PIC Remap */
#define PIC1		    0x20		/* IO base address for master PIC */
#define PIC2		    0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	    (PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	    (PIC2+1)
#define ICW1_ICW4	    0x01		/* reinitialize the PIC controllers, giving them specified vector offsets rather than 8h and 70h, as configured by default */
#define ICW1_INIT	    0x10		/* Initialization - required! */
#define ICW4_8086	    0x01		/* 8086/88 (MCS-80/85) mode */


/**
 * @brief Issue an End of Interrupt command code
 * 
 * @param irq Interrupt request number
 * 
 * The command code is issued to the PIC chips at the end of an IRQ-based interrupt routine.
 */
void PIC_send_EOI(uint8_t irq);

/**
 * @brief Remap the PIC to avoid hardware/software interrupts.
 *
 * @param offset1 Vector offset for the master PIC
 * @param offset2  Vector offset for the slave PIC
 *
 * In protected mode, the IRQs 0 to 7 conflict with the CPU exception which are reserved
 * by Intel up until 0x1F (31 decimal).  0x20 should therefore be the offset for PIC1 (master).
 * Each chip (master and slave) has a command port and a data port (given in the table below).
 * When no command is issued, the data port allows us to access the interrupt mask of the 8259 PIC.
 *
 *
 * Chip - Purpose	I/O port
 * Master PIC - Command	- 0x0020
 * Master PIC - Data	- 0x0021
 * Slave PIC - Command	- 0x00A0
 * Slave PIC - Data	- 0x00A1
 */
void _PIC_remap(int offset1, int offset2);

#endif