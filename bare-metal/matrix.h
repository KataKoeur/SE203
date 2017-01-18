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
#define GPIOA_PCOR  (*(volatile uint32_t *)0x400ff008)
#define GPIOB_PCOR  (*(volatile uint32_t *)0x400ff048)
#define GPIOB_PSOR  (*(volatile uint32_t *)0x400ff044)
#define GPIOC_PCOR  (*(volatile uint32_t *)0x400ff088)
#define GPIOD_PCOR  (*(volatile uint32_t *)0x400ff0c8)

void matrix_init();

void SB  (int x);
void LAT (int x);
void RST (int x);
void SCK (int x);
void SDA (int x);
void ROW0(int x);
void ROW1(int x);
void ROW2(int x);
void ROW3(int x);
void ROW4(int x);
void ROW5(int x);
void ROW6(int x);
void ROW7(int x);

void pulse_SCK();
void pulse_LAT();

void deactivate_rows();
void activate_row(int row);

void send_byte(uint8_t val, int bank);

#endif
