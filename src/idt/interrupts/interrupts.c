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

#define KEY_PRESS_UP 0x48
#define KEY_PRESS_DOWN 0x50
#define KEY_PRESS_LEFT 0x4B
#define KEY_PRESS_RIGHT 0x4D

enum XYDir_t {up, down, left, right};
struct Game {
    enum XYDir_t snake_direction;
};
extern struct Game game;

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
    uint8_t key_code = insb(0x60);
    switch (key_code) {
        case KEY_PRESS_UP:
            game.snake_direction = up;
            break;
        case KEY_PRESS_DOWN:
            game.snake_direction = down;
            break;
        case KEY_PRESS_LEFT:
            game.snake_direction = left;
            break;
        case KEY_PRESS_RIGHT:
            game.snake_direction = right;
            break;
        default:
            ;
    }
    PIC_send_EOI(IRQ_KEYBOARD);
}
