//#include "kernel.h"
#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "mem.h"
#include "terminal/terminal.h"
#include "commands.h" // Included by Ember2819: Adds commands
#include "colors.h" // Added by MorganPG1 to centralise colors into one file
// Ember2819: Add command functionality
void process_input(char *buffer) {
    run_command(buffer, TERM_COLOR);
}

__attribute__((section(".text.entry"))) // Add section attribute so linker knows this should be at the start
void _entry()
{
    vga_clear(TERM_COLOR);
    //vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    printf("----- COMMUNITY OS v0.4 -----\n", TERM_COLOR);
    printf("Built by random people on the internet.\n", TERM_COLOR);
    printf("Use help to see available commands.\n", TERM_COLOR);

    // AMERICAN US QWERTY KEYBOARD
    unsigned char DOWNCASE[128] = {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
        'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
        // Rest unprintable
    };
    unsigned char UPPERCASE[128] = {
        0, 27, '!', '@', '#', '$', '%','^','&','*','(',')','_','+','\b','\t',
        'Q','W','E','R','T','Y','U','I','O','P','{','}', '\n', 0,
        'A','S','D','F','G','H','J','K','L',':','"', '~', 0, '|',
        'Z','X','C','V','B','N','M','<','>','?', 0, '*', 0, ' '
        // Rest unprintable
    };
    set_layout(DOWNCASE, UPPERCASE);
    
    while (1) {    // Shell loop

        printf("> ", PROMPT_COLOR);
        
        //Obtains and processes the user input
        unsigned char buff[512];
        input(buff, 512, TERM_COLOR);
        process_input(buff);

        //Adds a new line and then restarts the loop
        putchar('\n', TERM_COLOR);
    }

    asm volatile ("hlt");
}
