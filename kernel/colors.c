// Added by MorganPG1 to centralise colors
#include "colors.h"
#include "drivers/vga.h"
#include <stdint.h>

const uint8_t BG_COLOR = VGA_COLOR_BLUE;
const uint8_t TERM_COLOR = VGA_COLOR_WHITE | BG_COLOR << 4;
const uint8_t PROMPT_COLOR = VGA_COLOR_LIGHT_GREEN | BG_COLOR << 4;
const uint8_t BOLD_COLOR = VGA_COLOR_LIGHT_GREY | BG_COLOR << 4;