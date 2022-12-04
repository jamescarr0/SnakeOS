/**
 * @file term.h
 * @author James Carr
 * @brief Kernel declerations for standard input and output
 * @version 0.1
 * @date 2022-03-07
 * 
 * Definitions for drawing pixels and flipping double buffer.
 */

#ifndef SIMPLEOS_STDIO_H
#define SIMPLEOS_STDIO_H

#include <stdint.h>
#include <stddef.h>

struct Screen_s
{
    uint8_t *framebuffer;
    uint8_t *backbuffer;
};

void init_video();

void blit();

void putpixel(int pos_x, int pos_y, unsigned char vga_color);

#endif //SIMPLEOS_STDIO_H
