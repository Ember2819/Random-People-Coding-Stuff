#include "vga.h"
#include "../ports.h"
#include <stdint.h>
#include <stddef.h>

uint8_t TERMINAL_COLOR;

size_t terminal_row = 0;
size_t terminal_column = 0;

void putentryat(char c, uint8_t color, size_t x, size_t y) {
	size_t index = y * VGA_TEXT_WIDTH + x;
	((uint16_t*)VGA_TEXT_ADDR)[index] = vga_entry(c, color);
}

uint8_t vga_entry_color(enum VGA_COLOR fg, enum VGA_COLOR bg) {
	return fg | bg << 4;
}

// I'm tired of commenting. - bonk enjoyer (dorito girl)

uint16_t vga_entry(unsigned char c, uint8_t color) {
	return (uint16_t) c | (uint16_t) color << 8;
}

void vga_clear(uint8_t color) {
	uint16_t off = 0;
	while (off < VGA_TEXT_WIDTH * VGA_TEXT_HEIGHT) {
		((uint16_t*)VGA_TEXT_ADDR)[off] = vga_entry(' ', color);
		off++;
	}
}

// Ember2819: Add a scroll so if the screen fills you can scroll down
void vga_scroll(uint8_t color) {
	volatile uint16_t* buf = (volatile uint16_t*)VGA_TEXT_ADDR;

	for (size_t row = 1; row < VGA_TEXT_HEIGHT; row++)
		for (size_t col = 0; col < VGA_TEXT_WIDTH; col++)
			buf[(row - 1) * VGA_TEXT_WIDTH + col] =
				buf[row * VGA_TEXT_WIDTH + col];

	for (size_t col = 0; col < VGA_TEXT_WIDTH; col++)
		buf[(VGA_TEXT_HEIGHT - 1) * VGA_TEXT_WIDTH + col] = vga_entry(' ', color);

	terminal_row = VGA_TEXT_HEIGHT - 1;
}

void move_tcursor(int x, int y) {
	uint16_t pos = y * VGA_TEXT_WIDTH + x;

	outb(0x3D4, 0xF);
	outb(0x3d5, (uint8_t) (pos & 0xFF));
	outb(0x3d4, 0xE);
	outb(0x3d5, (uint8_t) ((pos >> 8) & 0xFF));
}

void putchar(char c, uint8_t COLOR) {
	if (c == 0) return;
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
		if (terminal_row == VGA_TEXT_HEIGHT)
			vga_scroll(COLOR);
	}
	else if (c == '\t') {
		for (int j = 0; j < 4; j++) putchar(' ', COLOR);
	}
	else {
		putentryat(c, COLOR, terminal_column, terminal_row);
		terminal_column++;
	}
	if (terminal_column == VGA_TEXT_WIDTH) {
		terminal_column = 0;
		terminal_row++; // MorganPG - Fix implementation for wrapping onto a new line
	}
	if (terminal_row == VGA_TEXT_HEIGHT)
		terminal_row = 0;

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

void set_termcolor(enum VGA_COLOR FG, enum VGA_COLOR BG) {
	TERMINAL_COLOR = vga_entry_color(FG, BG);
}
