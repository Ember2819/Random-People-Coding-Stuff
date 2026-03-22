// bonk enjoyer (dorito girl)

// PS/2 keyboard driver

#ifndef KB_PS2
#define KB_PS2

#include <stdint.h>
#include "../ports.h"
#include <stdbool.h>

#define PS2_KB_BUFF_SIZE 512
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_COMMAND_PORT 0x64
#define KEYBOARD_STATUS_PORT 0x64

#define LEFT_SHIFT_SC 0x2A
#define RIGHT_SHIFT_SC 0x36
#define CAPS_LOCK_SC 0x3A
#define BACKSPACE_SC 0xE
#define ENTER_SC 0x1C

typedef struct {
    bool ShiftL;        // Is Left Shift pressed?
    bool ShiftR;        // Is Right Shift pressed?
    bool AltL;          // Is Left Alt pressed?
    bool AltR;          // Is Right Alt pressed?
    bool CtrlL;         // Is Left Ctrl pressed?
    bool CtrlR;         // is Right Ctrl pressed?
    bool CapsLock;      // Is CapsLock pressed?
} KeyState;

// A type for easier recognition of scancodes
typedef uint8_t scancode_t;

// Translate a scancode to ASCII according to the layout provided
unsigned char scancode_to_ascii(scancode_t scancode);
// Initialize PS/2 Keyboard
void ps2_kb_init();
// Process keypress
void process_keypress(scancode_t sc);
// Wait For Input
scancode_t ps2_kb_wfi();
// Set Layout
void set_layout(unsigned char* DOWNCASE, unsigned char* UPPERCASE);



#endif
