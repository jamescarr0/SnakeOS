/**
 * @file interrupts.c
 * @author James Carr
 * @brief Interrupt Service Routine Definitions
 * @version 0.1
 * @date 2022-03-06
 *
 *
 * ISR 0    - Divide By Zero.
 * ISR 33   - IRQ[0x21] - remapped(irq1) Keyboard Interrupt 
 *
 */

#include "io.h"
#include "interrupts.h"
#include "pic.h"
#include "bool.h"
#include "game/events.h"
#include "game/game.h"

extern struct Event g_event;

// Default interrupt handler when no ISR is assigned to a IRQ
void no_interrupt_handler(void)
{
    outb(0x20, 0x20);
}

// ISR 0, Divide by zero definition
void isr_zero()
{
    // TODO: Do something with divide by zero error.
    while(1);
}

// 0x21 : Keyboard Interrupt handler
void int_handler_21(void)
{
    g_event.scancode = insb(0x60);
    g_event.key_pressed = true;

    PIC_send_EOI(IRQ_KEYBOARD);
}
