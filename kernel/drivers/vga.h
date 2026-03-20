#ifndef _VGA_H
#define _VGA_H

#include <stdint.h>
#include <stddef.h>

#define VGA_TEXT_ADDR 0xb8000
#define VGA_GRAPHICS_ADDR 0xa0000
#define VGA_TEXT_WIDTH 80
#define VGA_TEXT_HEIGHT 25

typedef enum VGA_COLOR {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENDA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
  VGA_COLOR_LIGHT_YELLOW = 0xE,
  VGA_COLOR_YELLOW = 0x2C
};

void putchar(char c, uint8_t COLOR);

void write(char* data, size_t size, uint8_t COLOR);

void printf(char* data, uint8_t COLOR);

int puts(char* str, uint8_t color);

uint8_t vga_entry_color(enum VGA_COLOR fg, enum VGA_COLOR bg);

uint16_t vga_entry(unsigned char c, uint8_t color);

void move_tcursor(int x, int y);

void vga_clear(uint8_t color);

#endif
