/**
 * @file term.c
 * @author James Carr
 * @brief Function definitions for standard input output.
 * @version 0.1
 * @date 2022-23-02
 *
 * Definitions for standard input ouput.
 */

#include <stdint.h>
#include "strings.h"
#include "term.h"
#include "memory.h"
#include "kheap.h"


static struct Screen_s screen = {
    .framebuffer = (uint8_t *)0xA0000,
};

void init_video()
{
    memset(screen.framebuffer, 0, (64000));
    screen.backbuffer = kzalloc(64000);
}

void blit()
{
    for (size_t i = 0; i < (64000); i++)
    {
        screen.framebuffer[i] = screen.backbuffer[i];
        screen.backbuffer[i] = 0;
    }
}

void putpixel(int pos_x, int pos_y, unsigned char vga_color)
{
    screen.backbuffer[320 * pos_y + pos_x] = vga_color;
}