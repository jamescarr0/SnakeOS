#include <stdint.h>
#include "bool.h"

struct Event {
    bool key_pressed;
    uint8_t scancode;
};