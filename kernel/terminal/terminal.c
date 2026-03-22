#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include "terminal.h"

uint16_t terminal_column = 0; 
uint16_t terminal_row = 0;
static int history_count = 0;
static int history_head  = 0;

void putchar(char c, uint8_t color) {
	if (c == 0) {
        return; // Don't print null characters
    }
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
	}
	else if (c == '\t') {
		for (int j = 0; j < 4; j++) { 
            putchar(' ', color); // Print 4 spaces when tab is pressed
        }
	}
	else {
		putentryat(c, color, terminal_column, terminal_row); // Display the character if it is standard ASCII
		terminal_column++;
	}

    // Wrapping and scrolling
	if (terminal_column == VGA_TEXT_WIDTH) {
		terminal_column = 0;
		terminal_row++; // MorganPG1 - Fix implementation for wrapping onto a new line
	}
	if (terminal_row == VGA_TEXT_HEIGHT) {
        vga_scroll(color);
        terminal_column = 0;
        terminal_row = VGA_TEXT_HEIGHT - 1;
    }

    // Update VGA Cursor
	move_tcursor(terminal_column, terminal_row);
}

void write(char* data, size_t size, uint8_t COLOR) {
	for (int i = 0; i < size; i++) {
		putchar(data[i], COLOR);
    }
}

// just an alias
void printf(char* data, uint8_t COLOR) {
	for (size_t i = 0; data[i]; i++) {
		putchar(data[i], COLOR);
	}
}

// Ember2819: Add a scroll so if the screen fills you can scroll down
// bonk enjoyer(dorito girl) : make it work
void vga_scroll(uint8_t color) {
	size_t count = (VGA_TEXT_HEIGHT - 1) * VGA_TEXT_WIDTH;
	uint16_t* buff = (uint16_t*) VGA_TEXT_ADDR;
	// Move all lines up
	for (size_t i = 0; i < count; i++)
		buff[i] = buff[i + VGA_TEXT_WIDTH];
	// Clear the last line
	for (size_t i = 0; i < VGA_TEXT_WIDTH; i++)
		buff[count + i] = vga_entry(' ', color);
}

void terminal_clear(uint8_t color) {
    vga_clear(color);
    terminal_column = 0;
    terminal_row = 0;
    move_tcursor(0, 0);
}

static void history_push(unsigned char* buf) {
    if (buf[0] == '\0') return;
    size_t i;
    for (i = 0; buf[i] && i < 511; i++) {
        history_entries[history_head][i] = buf[i];
    }
    history_entries[history_head][i] = '\0';
    history_head = (history_head + 1) % HISTORY_SIZE;
    if (history_count < HISTORY_SIZE) history_count++;
}


void input(unsigned char* buff, size_t buffer_size, uint8_t color) {
    size_t buff_count = 0; //Initialise the buffer count
    size_t start_x = terminal_column;
    size_t start_y = terminal_row;

    // Ember2891: history
    int browse_idx = 0;
    unsigned char saved_input[512];
    //saved_input[0] = '\0';

    while (true) {
        scancode_t sc = ps2_kb_wfi();

        if (sc & 0x80) continue;
        if (sc == 0) continue;

        if (sc == KEY_UP || sc == KEY_DOWN) {
            if (sc == KEY_UP && browse_idx == 0) {
                size_t k;
                for (k = 0; k < buff_count; k++) {
                    saved_input[k] = buff[k];
                }
                saved_input[k] = '\0';
            }

            if (sc == KEY_UP   && browse_idx < history_count) browse_idx++;
            if (sc == KEY_DOWN && browse_idx > 0)             browse_idx--;

            // Pick the string to show: restored current input or a history slot.
            unsigned char* src;
            if (browse_idx == 0) {
                src = saved_input;
            } else {
                int slot = (history_head - browse_idx + HISTORY_SIZE) % HISTORY_SIZE;
                src = history_entries[slot];
            }

            for (size_t k = 0; k < terminal_column-start_x; k++) {
                size_t col = (start_x + k) % VGA_TEXT_WIDTH;
                size_t row = start_y + (start_x + k) / VGA_TEXT_WIDTH;
                putentryat(' ', color, col, row);
            }
            // Reset software and hardware cursor back to start of input.
            terminal_column = start_x;
            terminal_row    = start_y;
            move_tcursor(start_x, start_y);

            size_t k;
            for (k = 0; src[k] && k < buffer_size - 1; k++) {
                buff[k] = src[k];
                putchar(src[k], color);
            }
            buff_count = k;
            buff[buff_count] = '\0';
            continue;
        }
        unsigned char ascii = scancode_to_ascii(sc);
    
        if (ascii == '\n') break;

        if (ascii == '\b') {
            if (buff_count > 0) {
                if (terminal_column > 0) {
                    terminal_column--;
                }
                else if (terminal_row > 0) { 
                    terminal_row = VGA_TEXT_WIDTH - 1;
                    terminal_row--;
                }

                putentryat(' ', color, terminal_column, terminal_row);
                buff_count--;
                buff[buff_count] = 0;
                
                // Update cursor
                move_tcursor(terminal_column, terminal_row);
            }
            continue;
        }
        if (buff_count < buffer_size - 1 && ascii >= 0x20) {
            buff[buff_count] = ascii;
            
            putchar(ascii, color);
            buff_count++;
        }
    }

    buff[buff_count] = '\0';

    // Ember2819: arrow recal
    history_push(buff);
}
