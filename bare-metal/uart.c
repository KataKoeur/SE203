//uart.c

#include "uart.h"

#define SIM_SOPT2  (*(volatile uint32_t *)0x40048004)
#define SIM_SCGC4  (*(volatile uint32_t *)0x40048034)
#define SIM_SCGC5  (*(volatile uint32_t *)0x40048038)
#define UART0_C1   (*(volatile uint8_t  *)0x4006a002)
#define UART0_C2   (*(volatile uint8_t  *)0x4006a003)
#define UART0_C4   (*(volatile uint8_t  *)0x4006a00a)
#define UART0_S1   (*(volatile uint8_t  *)0x4006a004)
#define UART0_D    (*(volatile uint8_t  *)0x4006a007)
#define UART0_BDH  (*(volatile uint8_t  *)0x4006a000)
#define UART0_BDL  (*(volatile uint8_t  *)0x4006a001)
#define PORTA_PCR1 (*(volatile uint32_t *)0x40049004)
#define PORTA_PCR2 (*(volatile uint32_t *)0x40049008)

extern rgb_color screen[64];

void uart_init()
{
   //activation horologe UART0
   SIM_SOPT2  = (SIM_SOPT2 | 0x04010000) & ~0x08000000;
   SIM_SCGC4 |= 0x00000400;

   //config oversampling
   //OSR = 24
   UART0_C4 = 0x18;
   //SBR = 25
   UART0_BDH = 0x00;
   UART0_BDL = 0x19;

   //mode 8N1
   UART0_C1 = 0x00;

   //activation interruption UART0
   UART0_C2 = 0x20;
   irq_enable(12);

   //broche RX et TX du portA en mode UART0
   SIM_SCGC5 |= 0x00000200;
   //RX
   PORTA_PCR1 = (PORTA_PCR1 | 0x00000200) & ~0x00000500;
   //TX 
   PORTA_PCR2 = (PORTA_PCR2 | 0x00000200) & ~0x00000500;

   //activation transmetteur récepteur
   UART0_C2 = 0x2c;
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
   while((UART0_S1 & 0x20) == 0) UART0_S1 = 0x1f;
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

void UART0_IRQHandler()
{
   char pix = uart_getchar();
   static int ptr_color  = 0;
   static int ptr_screen = 0;

   //OR
   if(UART0_S1 & 1<<3)
   {
      UART0_S1 = (1<<3);
   }

   //FE
   else if(UART0_S1 & 1<<1) 
   {
      UART0_S1 = (1<<1);
   }

   else if(pix == 0xff)
   {
      ptr_color  = 0;
      ptr_screen = 0;
   }

   else
   {
      if(ptr_color == 0)      screen[ptr_screen].r = pix;
      else if(ptr_color == 1) screen[ptr_screen].g = pix;
      else if(ptr_color == 2) screen[ptr_screen].b = pix;

      ptr_color++;
      if(ptr_color  == 3) {ptr_color  = 0; ptr_screen++;}
      if(ptr_screen == 64) ptr_screen = 0;
   }
}
