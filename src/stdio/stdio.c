/**
 * @file stdio.c
 * @author James Carr
 * @brief Function definitions for standard input output.
 * @version 0.1
 * @date 2022-23-02
 *
 * Definitions for standard input ouput.
 */

#include <stdint.h>
#include "strings.h"
#include "stdio.h"
#include "memory.h"

struct Screen_s
{
    volatile uint8_t *framebuffer;
    volatile uint8_t *backbuffer;
};

static struct Screen_s screen = {
    .framebuffer = (volatile uint8_t *)0xA0000,
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

void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR)
{
    screen.backbuffer[320 * pos_y + pos_x] = VGA_COLOR;
}