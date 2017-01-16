//matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#define SIM_SCGC5 (*(volatile uint32_t *)0x40048038)

void matrix_init();

#endif
