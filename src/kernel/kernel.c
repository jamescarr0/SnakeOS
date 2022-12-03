/**
 * @file kernel.c
 * @author James Carr
 * @brief Kernel directory, main() called from kernel.asm
 * @version 0.1
 * @date 19/02/2002
 */

#include "term.h"
#include "idt.h"
#include "kheap.h"
#include "interrupts.h"

void sleep() { for (size_t i = 0; i < 10000000; i++){;}} // Todo: Look into/implement PIT.

// Todo: Refactor pixel/drawing functions.
void plotBorder(int color);
void plotFilledSquare(int x, int y, int size, int color);
void plotLine(int x0, int y0, int x1, int y1, int color);

// Todo: Refactor Game.
enum XYDir_t {up, down, left, right};
struct Game {
    enum XYDir_t snake_direction;
};
struct Game game;

int main()
{
    // Initialise the heap.
    kheap_init();

    // Initialize the IDT.
    idt_init();

    // Enable interrupts.
    enable_interrupts();

    // Driver code testing animation.
    init_video();

    // Set starting direction and position.
    game.snake_direction = up;
    int x = 155;
    int y = 90;
    
    plotBorder(100);
    plotFilledSquare(155, y++, 10, 118);

    while(1) {
        plotBorder(100);

        // Basic movement of a square
        switch (game.snake_direction)
        {
        case up:
            plotFilledSquare(x, y--, 10, 118);
            break;
        case down:
            plotFilledSquare(x, y++, 10, 118);
            break;
        case left:
            plotFilledSquare(x--, y, 10, 118);
            break;
        case right:
            plotFilledSquare(x++, y, 10, 118);
            break;
        default:
            break;
        }

        // Bounce sqauare off walls and reverse direction
        if(y > 184) { game.snake_direction=up; }
        if(y < 6) { game.snake_direction=down; }
        if(x < 6) { game.snake_direction=right; }
        if(x > 304) { game.snake_direction=left; }

        blit();
        sleep();
    }
    
    return 0;
}

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