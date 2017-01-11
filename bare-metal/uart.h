//uart.h

#ifndef UART_H
#define UART_H

#define SIM_SOPT2 (*(volatile int *)0x40048004)
#define SIM_SCGC4 (*(volatile int *)0x40048034)

void uart_init();

#endif
