//matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

#define SIM_SCGC5   (*(volatile uint32_t *)0x40048038)
#define PORTB_PCR0  (*(volatile uint32_t *)0x4004a000)
#define PORTB_PCR1  (*(volatile uint32_t *)0x4004a004)
#define PORTB_PCR2  (*(volatile uint32_t *)0x4004a008)
#define PORTC_PCR8  (*(volatile uint32_t *)0x4004b020)
#define PORTC_PCR9  (*(volatile uint32_t *)0x4004b024)
#define PORTA_PCR13 (*(volatile uint32_t *)0x4004b034)
#define PORTD_PCR2  (*(volatile uint32_t *)0x4004c008)
#define PORTD_PCR4  (*(volatile uint32_t *)0x4004c010)
#define PORTD_PCR6  (*(volatile uint32_t *)0x4004c018)
#define PORTD_PCR7  (*(volatile uint32_t *)0x4004c01c)
#define PORTD_PCR5  (*(volatile uint32_t *)0x4004c014)
#define PORTA_PCR12 (*(volatile uint32_t *)0x40049030)
#define PORTA_PCR4  (*(volatile uint32_t *)0x40049010)
#define GPIOA_PDDR  (*(volatile uint32_t *)0x400ff014)
#define GPIOB_PDDR  (*(volatile uint32_t *)0x400ff054)
#define GPIOC_PDDR  (*(volatile uint32_t *)0x400ff094)
#define GPIOD_PDDR  (*(volatile uint32_t *)0x400ff0d4)

void matrix_init();

#endif
