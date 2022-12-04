#pragma once

#include <stdint.h>
#include "bool.h"
#include "game/game.h"

#define KEY_PRESS_UP 0x48
#define KEY_PRESS_DOWN 0x50
#define KEY_PRESS_LEFT 0x4B
#define KEY_PRESS_RIGHT 0x4D

struct Event {
    bool key_pressed;
    uint8_t scancode;
};

void handle_events(struct Snake *snake);
