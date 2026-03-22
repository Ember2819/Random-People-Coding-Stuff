#include "commands.h"
#include "colors.h"
#include "drivers/keyboard.h"
#include "layouts/kb_layouts.h"
#include "terminal/terminal.h"


// The command table
static Command commands[] = {
    { "help",  cmd_help  },
    { "hello", cmd_hello },
    { "contributors", cmd_contributors},
    { "setkeyswe", cmd_setkeyswe},
    { "setkeyus", cmd_setkeyus},
    { "test",  cmd_test  },
};

static int num_commands = sizeof(commands) / sizeof(commands[0]);

// ---- Command Functions ----

static void cmd_help(uint8_t color) {
    printf("\nhelp   - show this message\n", color);
    printf("hello  - say hello\n", color);
    printf("test   - placeholder\n", color);
    printf("contributors - Displays names of all contributors\n", color);
    printf("setkeyswe - Sets keyboard layout to Swedish QWERTY\n", color); // Zorx555 - Keyboard layout commands
    printf("setkeyus - Sets keyboard layout to US QWERTY", color);
}

static void cmd_hello(uint8_t color) {
    printf("\nHello, world!", color);
}

static void cmd_test(uint8_t color) {
    printf("\nTest command has run successfully", color);
}

static void cmd_contributors(uint8_t color) {
    printf("\n--- Contributors ---\n", color);
    printf("Ember2819 - Founder\n", BOLD_COLOR);
    printf("Sifi11\n", color);
    printf("Crim\n", color);
    printf("CheeseFunnel23\n", color);
    printf("bonk enjoyer/dorito girl\n", BOLD_COLOR);
    printf("KaleidoscopeOld5841\n", color);
    printf("WilliamMMM/billythemoon\n", color);
    printf("TheGirl790\n", color);
    printf("kotofyt\n", color);
    printf("xtn59\n", color);
    printf("c-bass\n", color);
    printf("u/EastConsequence3792\n", color);
    printf("MorganPG1\n", color);
    printf("Zorx555", color);
}

static void cmd_setkeyswe(uint8_t color) {
    set_layout(LAYOUTS[1]); // Changed to work with my layout system
    printf("\nKeyboard layout set to Swedish QWERTY", color);
}

static void cmd_setkeyus(uint8_t color) {
    set_layout(LAYOUTS[0]); // Changed to work with my layout system
    printf("\nKeyboard layout set to US QWERTY", color);
}

// ---- dispatcher ----
static int streq(unsigned char *a, char *b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++; b++;
    }
    return *a == *b;
}

void run_command(unsigned char *input, uint8_t color) {
    // Check the input against command table
    for (int i = 0; i < num_commands; i++) {
        if (streq(input, commands[i].name)) {
            commands[i].func(color);
            return;
        }
    }
    printf("\nUnknown command. Type 'help' for available commands", color);
}
