/**
 * @file io.h
 * @author James Carr
 * @brief Define input output functions for writing and reading data from ports.
 * @version 0.1
 * @date 2022-03-03
 *
 * Reading and writing declarations for transferring data to and from memory and disks.
 */

#ifndef SIMPLEOS_IO_H
#define SIMPLEOS_IO_H

#include <stdint.h>

/**
 * Read a byte of data.
 * @param port the port to read from.
 * @return byte read from port
 *
 * Calls an external function written in assembly to read a byte from the specified port.
 */
extern uint8_t insb(uint16_t port);

/**
 * Read a word of data
 * @param port the port to read from
 * @return word read from port
 *
 * Calls an external function written in assembly to read a word from the specified port.
 */
extern uint16_t insw(uint16_t port);

/**
 * Write a byte of data to a port.
 * @param port The port to send a byte to.
 * @param data The data to send.
 */
extern void outb(uint16_t port, uint8_t data);

/**
 * Write a word of data to a port.
 * @param port The port to send word to
 * @param data THe data to send
 */
extern void outw(uint16_t port, uint16_t data);

/**
 * Used to wait a small but imprecise amount of time after sending command to PIC.
 * This is probably completely unnecessary but for the sake of backward compatability and a lack of
 * thorough OS development and PIC knowledge, we shall continue to use the function while researching the history and
 * documentation around it.
 */
void io_wait(void);

#endif