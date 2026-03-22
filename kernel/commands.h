#ifndef COMMANDS_H
#define COMMANDS_H

// We need uint8_t for the color parameter
#include <stdint.h>

// MorganPG1 - Moved some declarations from commands.c to commands.h
typedef struct {
    char *name;
    void (*func)(uint8_t color);
} Command;

static void cmd_help(uint8_t color);
static void cmd_hello(uint8_t color);
static void cmd_test(uint8_t color);
static void cmd_contributors(uint8_t color);
static void cmd_setkeyswe(uint8_t color);
static void cmd_setkeyus(uint8_t color);

static int streq(unsigned char *a, char *b);
void run_command(unsigned char *input, uint8_t color);

#endif
