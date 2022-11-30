/**
 * @file io.c
 * @author James Carr
 * @brief System Input Output Function Definitions
 * @version 0.1
 * @date 2022-03-03
 *
 * ASM code now replaced with inline assembly examples from
 * OS Dev.
 *
 * io.asm works; file kept as a backup incase gcc compilation emits bugs.
 *
 * " What follows is a collection of inline assembly functions so common
 * that they should be useful to most OS developers using GCC ""
 * https://wiki.osdev.org/Inline_Assembly/Examples
 *
 */

#include "io.h"

void io_wait(void)
{
    outb(0x80, 0);
}
