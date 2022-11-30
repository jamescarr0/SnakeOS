/**
 * @file kernel.c
 * @author James Carr
 * @brief Kernel directory, main() called from kernel.asm
 * @version 0.1
 * @date 19/02/2002
 */

#include "stdio.h"
#include "idt.h"
#include "kheap.h"
#include "interrupts.h"

void plotBorder(int color)
{
    // Top and bottom
    plotLine(5, 5, 315, 5, color);
    plotLine(5, 195, 315, 5, color);
    // Left and right
    for (size_t i = 6; i < 195; i++)
    {
        plotLine(5, i, 6, 5, color);
        plotLine(314, i, 315, 5, color);
    }
    
}

void plotFilledSquare(int x, int y, int size, int color)
{
    for (size_t i = 0; i < size; i++)
    {
        plotLine(x, y+i, x+size, y+i, color);
    }
    
}

void plotLine(int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int D = (2 * dy) - dx;
    int y = y0;

    for (size_t x=x0; x!=x1; x++)
    {
        putpixel(x, y, color);
        if (D > 0)
        {
            y++;
            D = D - (2 * dx);
        }
        D = D + (2 * dy);
    }
}

int main()
{

    clear();

    plotBorder(100);
    plotFilledSquare(20, 20, 10, 118);
    
    // Initialise the heap.
    kheap_init();

    // Initialize the IDT.
    idt_init();

    // Enable interrupts.
    enable_interrupts();

    while (1)
        ;

    return 0;
}