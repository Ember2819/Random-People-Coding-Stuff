//#include "kernel.h"
#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "layouts/kb_layouts.h"
#include "mem.h"
#include "terminal/terminal.h"
#include "commands.h" // Included by Ember2819: Adds commands
#include "colors.h" // Added by MorganPG1 to centralise colors into one file

// Ember2819: Add command functionality
void process_input(unsigned char *buffer) {
    run_command(buffer, TERM_COLOR);
}

__attribute__((section(".text.entry"))) // Add section attribute so linker knows this should be at the start
void _entry()
{
    // Initialise display.
    vga_clear(TERM_COLOR);
    printf("----- COMMUNITY OS v0.5 -----\n", TERM_COLOR);
    printf("Built by random people on the internet.\n", TERM_COLOR);
    printf("Use help to see available commands.\n", TERM_COLOR);

    // Setup keyboard layouts
    set_layout(LAYOUTS[0]);
    
    while (1) {    // Shell loop
        // Prints shell prompt
        printf("> ", PROMPT_COLOR);
        
        //Obtains and processes the user input
        unsigned char buff[512];
        input(buff, 512, TERM_COLOR);
        process_input(buff);

        // Adds a new line and then restarts the loop
        putchar('\n', TERM_COLOR);
    }

    //asm volatile ("hlt");
}
