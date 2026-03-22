// bonk enjoyer (dorito girl)

// PS/2 keyboard driver

#include "keyboard.h"
#include "../layouts/kb_layouts.h"
#include "../ports.h"
// Layout map by scancodes.
// Add layout via set_layout()
char ScASCII[128];
char ScASCII_UPPER[128];

// Key State (what control keys are pressed currently)
KeyState KEYSTATE;

unsigned char scancode_to_ascii(scancode_t scancode) {
    bool shift = KEYSTATE.ShiftL || KEYSTATE.ShiftR; // Is either Left Shift or Right Shift pressed
    // If shift is pressed and CapsLock isn't, and vice versa
    if (KEYSTATE.CapsLock ^ shift)
        return ScASCII_UPPER[(uint8_t) scancode];
    else
        return ScASCII[(uint8_t) scancode];
}

void process_keypress(scancode_t sc) {
    // Dark magic
    bool released = sc & 0x80;
    sc &= 0x7F;

    switch (sc) {
        case LEFT_SHIFT_SC:
            KEYSTATE.ShiftL = !released;
            break;
        case RIGHT_SHIFT_SC:
            KEYSTATE.ShiftR = !released;
            break;
        case CAPS_LOCK_SC:
            if (!released) KEYSTATE.CapsLock = !KEYSTATE.CapsLock;
        default:
            break;
    }
}

scancode_t ps2_kb_wfi() {
    scancode_t scancode;
    // Waiting for input.
    while (!(inb(KEYBOARD_STATUS_PORT) & 1)) {
        asm volatile("pause");
    }
    scancode = inb(KEYBOARD_DATA_PORT);
    
    // Ember2819: arrow key history
    if (scancode == 0xE0) {
        while (!(inb(KEYBOARD_STATUS_PORT) & 1)) {
            asm volatile("pause");
        }
        scancode_t ext = inb(KEYBOARD_DATA_PORT);
        if (ext & 0x80) return 0;        // ignore extended key releases
        if (ext == 0x48) return KEY_UP;
        if (ext == 0x50) return KEY_DOWN;
        return 0;
    }

    process_keypress(scancode);

    return scancode;
}

void ps2_kb_init() {
    KEYSTATE = (KeyState) {false, false, false, false, false, false, false};
}

// Im getting tired of writing these dumb comments that nobody reads.

void set_layout(KeyboardLayout layout) {
    unsigned char* lowercase = layout.lower;
    unsigned char* uppercase = layout.upper;

    for (int j = 0; j < 128; j++) ScASCII[j] = lowercase[j];
    for (int j = 0; j < 128; j++) ScASCII_UPPER[j] = uppercase[j];
}
