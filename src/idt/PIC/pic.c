/**
 * @file pic.c
 * @author James Carr
 * @brief 
 * @version 0.1
 * @date 2022-03-07
 *
 * 
 */

#include "pic.h"
#include "io.h"

/*
 * Remap the PIC to avoid hardware/software interrupts.
 *
 * offset1 Vector offset for the master PIC
 * offset2  Vector offset for the slave PIC
 *
 * In protected mode, the IRQs 0 to 7 conflict with the CPU exception which are reserved
 * by Intel up until 0x1F (31 decimal).  0x20 should therefore be the offset for PIC1 (master).
 * Each chip (master and slave) has a command port and a data port (given in the table below).
 * When no command is issued, the data port allows us to access the interrupt mask of the 8259 PIC.
 *
 * Chip - Purpose	I/O port
 * Master PIC - Command	0x0020
 * Master PIC - Data	0x0021
 * Slave PIC - Command	0x00A0
 * Slave PIC - Data	0x00A1
 */
void _PIC_remap(int offset1, int offset2)
{
    unsigned char a1, a2;

    a1 = insb(PIC1_DATA); // save masks
    a2 = insb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // starts the initialization sequence (in cascade mode)
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
    io_wait();
    outb(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
    io_wait();
    outb(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_wait();
    outb(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1); // restore saved masks.
    outb(PIC2_DATA, a2);
}

// Issue an End of Interrupt command code
void PIC_send_EOI(uint8_t irq)
{
    if (irq >= 8)
    {
        outb(PIC2_COMMAND, PIC_EOI);
    }
    else
    {
        outb(PIC1_COMMAND, PIC_EOI);
    }
}