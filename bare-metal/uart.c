//uart.c

#include "uart.h"

void uart_init()
{
   //activation horologe UART0
   SIM_SOPT2 = SIM_SOPT2 |  0x04000000;
   SIM_SOPT2 = SIM_SOPT2 & ~0x08000000;
   SIM_SCGC4 = SIM_SCGC4 |  0x00000400;

   //config oversampling
}
