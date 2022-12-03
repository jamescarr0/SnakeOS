#include "game/events.h"
#include "bool.h"
#include "game/game.h"

#define KEY_PRESS_UP 0x48
#define KEY_PRESS_DOWN 0x50
#define KEY_PRESS_LEFT 0x4B
#define KEY_PRESS_RIGHT 0x4D

struct Event g_event;

void handle_events(struct Snake *snake)
{
    if (g_event.key_pressed)
    {
        switch (g_event.scancode)
        {
        case KEY_PRESS_UP:
            snake->direction=up;
            break;
        case KEY_PRESS_DOWN:
            snake->direction=down;
            break;
        case KEY_PRESS_LEFT:
            snake->direction=left;
            break;
        case KEY_PRESS_RIGHT:
            snake->direction=right;
            break;
        default:
            break;
        }
        g_event.key_pressed = false;
    }
}