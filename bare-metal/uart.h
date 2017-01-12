//uart.h

#ifndef UART_H
#define UART_H

#define SIM_SOPT2 (*(volatile int *)0x40048004)
#define SIM_SCGC4 (*(volatile int *)0x40048034)
#define UART0_C4  (*(volatile int *)0x4006a00a)
#define UART0_BDH (*(volatile int *)0x4006a000)
#define UART0_BDL (*(volatile int *)0x4006a001)

void uart_init();

#endif
