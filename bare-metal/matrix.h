//matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

typedef struct
{
   uint8_t r;
   uint8_t g;
   uint8_t b;
}  rgb_color;

extern rgb_color screen[64];

void matrix_init();
void test_pixels();
void test_static_image();
void display_screen();
void display_screen_row_by_row();

#endif
