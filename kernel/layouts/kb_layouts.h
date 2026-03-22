#ifndef  KB_LAYOUTS_H
#define KB_LAYOUTS_H

typedef struct {
    unsigned char lower[128];
    unsigned char upper[128];
} KeyboardLayout;

extern KeyboardLayout LAYOUTS[];

#endif