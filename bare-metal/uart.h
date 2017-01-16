//uart.h

#ifndef UART_H
#define UART_H

#define SIM_SOPT2  (*(volatile int *)0x40048004)
#define SIM_SCGC4  (*(volatile int *)0x40048034)
#define SIM_SCGC5  (*(volatile int *)0x40048038)
#define UART0_C1   (*(volatile int *)0x4006a002)
#define UART0_C2   (*(volatile int *)0x4006a003)
#define UART0_C4   (*(volatile int *)0x4006a00a)
#define UART0_BDH  (*(volatile int *)0x4006a000)
#define UART0_BDL  (*(volatile int *)0x4006a001)
#define PORTA_PCR1 (*(volatile int *)0x40049004)
#define PORTA_PCR2 (*(volatile int *)0x40049008)

void uart_init();

#endif
