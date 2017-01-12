//uart.c

#include "uart.h"

void uart_init()
{
   //activation horologe UART0
   SIM_SOPT2 = SIM_SOPT2 |  0x04000000;
   SIM_SOPT2 = SIM_SOPT2 & ~0x08000000;
   SIM_SCGC4 = SIM_SCGC4 |  0x00000400;

   //config oversampling
   //OSR = 28
   UART0_C4 = UART0_C4 |  0x1c;
   UART0_C4 = UART0_C4 & ~0x02;
   //SBR = 7
   UART0_BDH = UART0_BDH & ~0x1f;
   UART0_BDL = 0x07;
}
