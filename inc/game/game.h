#pragma once

#define SNAKE_INITIAL_SIZE 5
#define SNAKE_SEGMENT_COLOR 118
#define SNAKE_SEGMENT_SIZE 10
#define SNAKE_MAX_LENGTH ((320 * 200) / SNAKE_SEGMENT_SIZE)
#define BORDER_COLOR 73

enum XYDir_t
{
    up,
    down,
    left,
    right
};

struct Snake_Segment
{
    int x;
    int y;
    int size;
};

struct Snake
{
    enum XYDir_t direction;
    int dx;
    int dy;
    struct Snake_Segment segment[SNAKE_MAX_LENGTH];
};

struct Snake *init_snake();

void update_snake(struct Snake *snake);
void draw_border(int color);
void draw_snake(struct Snake *snake);