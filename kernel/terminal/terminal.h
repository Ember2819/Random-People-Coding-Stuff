#ifndef TERMINAL_H
#define TERMINAL_H

#include "../drivers/keyboard.h"
#include "../drivers/vga.h"
#include <stdint.h>

void putchar(char c, uint8_t COLOR);
void write(char* data, size_t size, uint8_t COLOR);
void printf(char* data, uint8_t COLOR);

void vga_scroll(uint8_t color);

void input(unsigned char* buff, size_t buffer_size, uint8_t color);

#endif
