#include "commands.h"
#include "terminal/terminal.h"
#include "drivers/vga.h"

typedef struct {
    char *name;
    void (*func)(uint8_t color);
} Command;

static void cmd_help(uint8_t color);
static void cmd_hello(uint8_t color);
static void cmd_test(uint8_t color);
static void CMD_contributors(uint8_t);

// The command table
static Command commands[] = {
    { "help",  cmd_help  },
    { "hello", cmd_hello },
    { "contributors", cmd_contributors},
    { "test",  cmd_test  },
};

static int num_commands = sizeof(commands) / sizeof(commands[0]);

// ---- Command Functions ----

static void cmd_help(uint8_t color) {
    printf("\nhelp   - show this message\n", color);
    printf("hello  - say hello\n", color);
    printf("test   - placeholder", color);
}

static void cmd_hello(uint8_t color) {
    printf("\nHello, world!", color);
}

static void cmd_test(uint8_t color) {
    printf("\nTest command has run successfully", color);
}

static void cmd_contributors(uint8_t color) {
    printf("--- Contributors ---");
    printf("Ember2819");
    printf("Sifi11");
}

// ---- dispatcher ----
static int streq(char *a, char *b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++; b++;
    }
    return *a == *b;
}

void run_command(char *input, uint8_t color) {
    // Check the input against command table
    for (int i = 0; i < num_commands; i++) {
        if (streq(input, commands[i].name)) {
            commands[i].func(color);
            return;
        }
    }
    printf("\nUnknown command. Type 'help' for available commands", color);
}
