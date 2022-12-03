#include "kheap.h"
#include "game/game.h"
#include "term.h"

struct Snake *init_snake()
{
    struct Snake *snake = kmalloc(sizeof(struct Snake));
    snake->direction = up;
    snake->x = 155;
    snake->y = 90;
    return snake;
}

static void plotLine(int x0, int y0, int x1, int y1, int color)
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

static void plotBorder(int color)
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

static void plotFilledSquare(int x, int y, int size, int color)
{
    for (size_t i = 0; i < size; i++)
    {
        plotLine(x, y+i, x+size, y+i, color);
    }
}

void draw_border(int color)
{
    plotBorder(color);
}

void draw_snake(struct Snake *snake)
{
    // Basic movement of a square
    switch (snake->direction)
    {
    case up:
        plotFilledSquare(snake->x, snake->y--, 10, 118);
        break;
    case down:
        plotFilledSquare(snake->x, snake->y++, 10, 118);
        break;
    case left:
        plotFilledSquare(snake->x--, snake->y, 10, 118);
        break;
    case right:
        plotFilledSquare(snake->x++, snake->y, 10, 118);
        break;
    default:
        break;
    }
}
