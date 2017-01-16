//uart.c

#include "uart.h"

void uart_init()
{
   //activation horologe UART0
   SIM_SOPT2 = SIM_SOPT2 |  0x04010000;
   SIM_SOPT2 = SIM_SOPT2 & ~0x08000000;
   SIM_SCGC4 = SIM_SCGC4 |  0x00000400;

   //config oversampling
   //OSR = 28
   UART0_C4 = UART0_C4 |  0x1c;
   UART0_C4 = UART0_C4 & ~0x03;
   //SBR = 7
   UART0_BDH = UART0_BDH & ~0x1f;
   UART0_BDL = 0x07;

   //mode 8N1
   UART0_C1  = UART0_C1  & ~0x10; //8bits de données
   UART0_C1  = UART0_C1  & ~0x02; //pas de parité
   UART0_BDH = UART0_BDH & ~0x20; //1bit de stop

   //broche RX et TX du portA en mode UART
   SIM_SCGC5 = SIM_SCGC5 | 0x00000200;
   //RX
   PORTA_PCR1 = PORTA_PCR1 |  0x00000200;
   PORTA_PCR1 = PORTA_PCR1 & ~0x00000500;
   //TX 
   PORTA_PCR2 = PORTA_PCR2 |  0x00000200;
   PORTA_PCR2 = PORTA_PCR2 & ~0x00000500;

   //activation transmetteur récepteur
   UART0_C2 = UART0_C2 | 0x0c;
}

void uart_putchar(char c)
{
   //attente buffer de transmission vide
   while((UART0_S1 & 0x80) == 0);

   //envoie du caractere c
   UART0_D = c;
}

unsigned char uart_getchar()
{
   while((UART0_S1 & 0x20) == 0);
   return UART0_D;
}

void uart_puts(const char *s)
{
   while(*s != '\0')
   {
      uart_putchar(*s);
      s++;
   }
}

void uart_gets(char *s, int size)
{
   for(int i = 0; i<size; i++)
   {
      *s = uart_getchar();
      s++;
   }
}
