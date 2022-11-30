/**
 * @file stdio.h
 * @author James Carr
 * @brief Kernel declerations for standard input and output
 * @version 0.1
 * @date 2022-03-07
 * 
 * Kernel definitions for standard input and output.
 */

#ifndef SIMPLEOS_STDIO_H
#define SIMPLEOS_STDIO_H

#include <stdint.h>
#include <stddef.h>

/**
 * Setup the terminal
 */

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum Font_fg {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    brown,
    light_gray,
    dark_gray,
    light_blue,
    light_green,
    light_cyan,
    light_red,
    light_magenta,
    yellow,
    white
};

typedef struct Terminal_s{
    uint8_t col_pos;
    uint8_t row_pos;
    volatile uint16_t *framebuffer;
} Terminal;

/**
 * @brief Clear the terminal and reset the terminal cursor x and y position to 0, 0.
 * 
 */
void clear(void);

/**
 * @brief C Style print function.
 * @param str String to print to stdout (console)
 * @param color Font color.
 */
void print(const char *const str, enum Font_fg color);

#endif //SIMPLEOS_STDIO_H
