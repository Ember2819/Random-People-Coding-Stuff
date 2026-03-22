#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include "terminal.h"

uint16_t terminal_column = 0; 
uint16_t terminal_row = 0;

void putchar(char c, uint8_t color) {
	if (c == 0) return;
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
	}
	else if (c == '\t') {
		for (int j = 0; j < 4; j++) putchar(' ', color);
	}
	else {
		putentryat(c, color, terminal_column, terminal_row);
		terminal_column++;
	}
	if (terminal_column == VGA_TEXT_WIDTH) {
		terminal_column = 0;
		terminal_row++; // MorganPG - Fix implementation for wrapping onto a new line
	}
	if (terminal_row == VGA_TEXT_HEIGHT) {
        vga_scroll(color);
        terminal_column = 0;
        terminal_row = VGA_TEXT_HEIGHT - 1;
    }
	move_tcursor(terminal_column, terminal_row);
}

void write(char* data, size_t size, uint8_t COLOR) {
	for (int i = 0; i < size; i++)
		putchar(data[i], COLOR);
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


void input(unsigned char* buff, size_t buffer_size, uint8_t color) {
    size_t buff_count = 0; //Initialise the buffer count
    
    size_t x = terminal_column;
    size_t y = terminal_row;

    while (true) {
        scancode_t sc = ps2_kb_wfi();

        // Ignore release scancodes
        if (sc & 0x80) continue;
        unsigned char ascii = scancode_to_ascii(sc);
    
        if (ascii == '\n') break;

        if (ascii == '\b') {
            if (buff_count > 0) {
                if (x > 0) {
                    x--;
                }
                else if (y > 0) { //Handle deleting characters on the row above
                    x = VGA_TEXT_WIDTH - 1;
                    y--;
                }

                // Delete the character
                putentryat(' ', color, x, y);
                buff_count--;
                buff[buff_count] = 0;
                
                // Update cursor
                terminal_column = x;
                terminal_row = y;
                move_tcursor(x, y);
            }
            continue;
        }
        // If buffer is big enough, and ASCII is printable
        if (buff_count < buffer_size - 1 && ascii >= 0x20) {
            buff[buff_count] = ascii;
            
            putchar(ascii, color);

            y = terminal_row;
            x = terminal_column;
            buff_count++;
        }
    }

    buff[buff_count] = '\0';
}
