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

   //mode 8N1
   UART0_C1  = UART0_C1  & ~0x10; //8bits de données
   UART0_C1  = UART0_C1  & ~0x02; //pas de parité
   UART0_BDH = UART0_BDH & ~0x20; //1bit de stop

   //broche RX et TX du portA en mode UART
   SIM_SCGC5 = SIMSCGC5 | 0x00000200;
   
}
