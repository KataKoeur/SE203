//uart.h

#ifndef UART_H
#define UART_H

#include <stdint.h>

#define SIM_SOPT2  (*(volatile uint32_t *)0x40048004)
#define SIM_SCGC4  (*(volatile uint32_t *)0x40048034)
#define SIM_SCGC5  (*(volatile uint32_t *)0x40048038)
#define UART0_C1   (*(volatile uint8_t  *)0x4006a002)
#define UART0_C2   (*(volatile uint8_t  *)0x4006a003)
#define UART0_S1   (*(volatile uint8_t  *)0x4006a004)
#define UART0_D    (*(volatile uint8_t  *)0x4006a007)
#define UART0_C4   (*(volatile uint8_t  *)0x4006a00a)
#define UART0_BDH  (*(volatile uint8_t  *)0x4006a000)
#define UART0_BDL  (*(volatile uint8_t  *)0x4006a001)
#define PORTA_PCR1 (*(volatile uint32_t *)0x40049004)
#define PORTA_PCR2 (*(volatile uint32_t *)0x40049008)

void           uart_init();
void           uart_putchar(char c);
unsigned char  uart_getchar();
void           uart_puts(const char *s);

#endif
