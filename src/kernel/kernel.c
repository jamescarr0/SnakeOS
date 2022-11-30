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

void plotFilledSquare(int x, int y, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        plotLine(x, y+i, x+size, y+i);
    }
    
}

void plotLine(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int D = (2 * dy) - dx;
    int y = y0;

    for (size_t x=x0; x!=x1; x++)
    {
        putpixel(x, y, 118);
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
    plotLine(10, 10, 310, 10);
    plotFilledSquare(20, 20, 60);
    
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