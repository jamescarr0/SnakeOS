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
#include "game/events.h"

void sleep() { for (size_t i = 0; i < 50000000; i++){;}} // Todo: Look into/implement PIT.

int main()
{
    // Initialize the IDT.
    idt_init();

    // Initialise the heap.
    kheap_init();

    enable_interrupts();

    // Setup the console and initiliase the snake game.
    init_video();
    struct Snake *snake = init_snake();

    while(1) {
        draw_border(BORDER_COLOR);
        handle_events(snake);
        update_snake(snake);
        blit();
        sleep();
    }
    
    return 0;
}
