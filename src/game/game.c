#include "kheap.h"
#include "game/game.h"
#include "term.h"

struct Snake *init_snake()
{
    struct Snake *snake = kmalloc(sizeof(struct Snake));
    snake->direction = right;
    snake->dx = SNAKE_SEGMENT_SIZE;
    snake->dy = 0;
    for (int i = 0; i < SNAKE_INITIAL_SIZE; i++)
    {
        snake->segment[i].x = 60 - (SNAKE_SEGMENT_SIZE * i);
        snake->segment[i].y = 90;
        snake->segment->size = SNAKE_SEGMENT_SIZE;
    }

    return snake;
}

static void plotLine(int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int D = (2 * dy) - dx;
    int y = y0;

    for (int x = x0; x != x1; x++)
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

void draw_border(int color)
{
    plotBorder(color);
}

static void plotFilledSquare(int x, int y, int size, int color)
{
    for (size_t i = 0; i < size; i++)
    {
        plotLine(x, y + i, x + size, y + i, color);
    }
}

void spawn_snake(struct Snake *snake)
{
    for (int i = 0; i < SNAKE_MAX_LENGTH; i++)
    {
        if (snake->segment[i].size > 0)
            plotFilledSquare(snake->segment[i].x, snake->segment[i].y, snake->segment->size, SNAKE_SEGMENT_COLOR);
    }
}

void update_snake(struct Snake *snake)
{
    switch (snake->direction)
    {
    case up:
        snake->dx = 0;
        snake->dy = -SNAKE_SEGMENT_SIZE;
        break;

    case down:
        snake->dx = 0;
        snake->dy = SNAKE_SEGMENT_SIZE;
        break;

    case left:
        snake->dx = -SNAKE_SEGMENT_SIZE;
        snake->dy = 0;
        break;

    case right:
        snake->dx = SNAKE_SEGMENT_SIZE;
        snake->dy = 0;
        break;

    default:
        break;
    }

    // Snake movement
    // Shift elements over by one, create a head and delete a tail to create 'movement'.
    // Shift snake segments over to leave space for a new head
    for (int i = SNAKE_MAX_LENGTH - 1; i >= 0; i--)
    {
        snake->segment[i] = snake->segment[i - 1];
    }

    // Create a new head.
    snake->segment[0].x = snake->segment[1].x + snake->dx;
    snake->segment[0].y = snake->segment[1].y + snake->dy;
    snake->segment[0].size = SNAKE_SEGMENT_SIZE;

    // Delete the tail.
    for (int i = SNAKE_INITIAL_SIZE; i < SNAKE_MAX_LENGTH; i++)
    {
        if (snake->segment[i].size == 0)
        {
            snake->segment[i - 1].x = 0;
            snake->segment[i - 1].y = 0;
            snake->segment[i - 1].size = 0;
        }
    }

    spawn_snake(snake);
}
