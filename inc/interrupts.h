/**
 * @file interrupts.h
 * @author James Carr
 * @brief Interrupt service routine definitions.
 * @version 0.1
 * @date 2022-03-06
 *
 * 0 - Divide By Zero.
 * 33 - 0x21 : Keyboard interrupt
 *
 */

#define IRQ_TIMER 0
#define IRQ_KEYBOARD 1
#define IRQ_CASCADE_SLAVE_CONTROLLER 2
#define IRQ_SERIAL_PORT2 3
#define IRQ_SERIAL_PORT1 4
#define IRQ_AT_SYSTEMS_RES1 5
#define IRQ_DISKETTE_DRIVE 6
#define IRQ_PARALLEL_PORT1 7
#define IRQ_CMOS_CLOCK 8
#define IRQ_CGA_VERT_RETRACE 9
#define IRQ_RESERVED_1 10
#define IRQ_RESERVED_2 11
#define IRQ_AT_SYSTEMS_RES2 12
#define IRQ_FPU 13
#define IRQ_HARD_DISK_CONTROLLER 14
#define IRQ_RESERVED_3 15

/****************** ASM WRAPPERS ******************/

/**
 * @brief Interrupt 21 assembly wrapper
 *
 */
extern void int21_wrapper(void);

/**
 * @brief Assembly wrapper for calling the C no interrupt handler function.
 *
 * Assembly wrapper ensures an iret opcode is returned after interrupt returns from
 * C function.
 * 
 */
extern void no_interrupt(void);

/****************** END OF WRAPPERS ******************/

/* External ASM: Enable Disable Interrupts : idt.asm */

/**
 * @brief Enable interrupts
 * 
 * Executes the sti instruciton to enable interrupts.
 */
extern void enable_interrupts(void);

/**
 * @brief Disable interrupts.
 * 
 * Executes the cli instruction to disable interrupts. 
 */
extern void disable_interrupts(void);

/* External ASM : Enable Disable Interrupts END */


/**
 * @brief Default interrupt handler
 *
 * When no interrupt handler has been assigned to an IRQ the default
 * no interrupt handler is called.  We acknoledge the request and simply exit.
 */
void no_interrupt_handler(void);

/**
 * @brief Divide By Zero Interrupt Service Routine
 *
 */
void isr_zero();

/**
 * @brief Interrupt 33 (0x21) keyboard handler
 *
 */
void int_handler_21(void);