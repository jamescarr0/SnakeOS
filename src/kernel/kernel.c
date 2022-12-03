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
#include "game/game.h"

void sleep() { for (size_t i = 0; i < 10000000; i++){;}} // Todo: Look into/implement PIT.

int main()
{
    // Initialise the heap.
    kheap_init();

    // Initialize the IDT.
    idt_init();

    enable_interrupts();

    // Setup the console and initiliase the snake game.
    init_video();
    struct Snake *snake = init_snake();
    
    while(1) {
        draw_border(100);

        handle_events(snake);

        draw_snake(snake);

        // Bounce sqauare off walls and reverse direction
        if(snake->y > 184) { snake->direction=up; }
        if(snake->y < 6) { snake->direction=down; }
        if(snake->x < 6) { snake->direction=right; }
        if(snake->x > 304) { snake->direction=left; }

        blit();

        sleep();
    }
    
    return 0;
}
