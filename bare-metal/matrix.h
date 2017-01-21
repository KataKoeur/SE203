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


void matrix_init();

void deactivate_rows();
void activate_row(int row);

void send_byte(uint8_t val, int bank);
void mat_set_row(int row, const rgb_color *val);

void test_pixels();
void test_static_image();

#endif
