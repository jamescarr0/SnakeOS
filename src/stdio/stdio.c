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

static Terminal terminal = {
        .col_pos = 0,
        .row_pos = 0,
        .framebuffer = (volatile uint16_t *)0xB8000 // Text video memory.
};

/* Text video memory requires two bytes per character.  An ASCII byte, and an attribute
byte, which is the colour of the character to be sent to video memory.
X86 is little endian so the bytes need to be converted (reversed) accordingly with
a bitshift left and biwide or
 */

static uint16_t create_video_char(const char character, const int color)
{
    return (color << 8) | character; // Convert to little endian. Swap bytes.
}

/* Inserts the 'two byte' text video character into video memory at location x, y */
static void send_to_framebuffer(const char character, const int color)
{
    terminal.framebuffer[(terminal.row_pos * VGA_WIDTH) + terminal.col_pos] = create_video_char(character, color);
}

/* Update the terminal cursor position and send the character to be inserted into video memory to the
video memory helper function 'send_to_framebuffer' */
static void putchar(const char character, const int color)
{
    if (character == '\n') // Increment the terminal row position when reading a newline.
    {
        terminal.row_pos++;
        terminal.col_pos = 0;
        return;
    }

    // Send the char to video memory.
    send_to_framebuffer(character, color);
    terminal.col_pos++;

    // Wrap text to a newline when the end of the terminal is reached.
    if (terminal.col_pos >= VGA_WIDTH)
    {
        terminal.row_pos++;
        terminal.col_pos = 0;
    }
}

/* Clears the terminal screen by iterating the video memory vector and inserting
 * white space
 */
void clear(void)
{
    terminal.framebuffer = (volatile uint16_t *)0xB8000;
    uint8_t *y = &terminal.row_pos;
    uint8_t *x = &terminal.col_pos;

    for (*y = 0; *y < VGA_HEIGHT; ++*y)
    {
        for (*x = 0; *x < VGA_WIDTH; ++*x)
            send_to_framebuffer(' ', 0);
    }

    terminal.col_pos = 0;
    terminal.row_pos = 0;
}

/* C Style print function for printing characters to the terminal */
void print(const char *const str, enum Font_fg color)
{
    for (size_t i = 0; i < strlen(str); ++i)
    {
        putchar(str[i], color);
    }
}


void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR)
{
    unsigned char* location = (unsigned char*)0xA0000 + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}