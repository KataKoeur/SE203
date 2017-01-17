//matrix.c

#include "matrix.h"

void matrix_init()
{
   //activation horloge port A B C et D
   SIM_SCGC5 = SIM_SCGC5 | 0x00001e00;

   //mode GPIO
   PORTB_PCR0  = (PORTB_PCR0  | 0x00000100) & ~0x00000600;
   PORTB_PCR1  = (PORTB_PCR1  | 0x00000100) & ~0x00000600;
   PORTB_PCR2  = (PORTB_PCR2  | 0x00000100) & ~0x00000600;
   PORTC_PCR8  = (PORTC_PCR8  | 0x00000100) & ~0x00000600;
   PORTC_PCR9  = (PORTC_PCR9  | 0x00000100) & ~0x00000600;
   PORTA_PCR13 = (PORTA_PCR13 | 0x00000100) & ~0x00000600;
   PORTD_PCR2  = (PORTD_PCR2  | 0x00000100) & ~0x00000600;
   PORTD_PCR4  = (PORTD_PCR4  | 0x00000100) & ~0x00000600;
   PORTD_PCR6  = (PORTD_PCR6  | 0x00000100) & ~0x00000600;
   PORTD_PCR7  = (PORTD_PCR7  | 0x00000100) & ~0x00000600;
   PORTD_PCR5  = (PORTD_PCR5  | 0x00000100) & ~0x00000600;
   PORTA_PCR12 = (PORTA_PCR12 | 0x00000100) & ~0x00000600;
   PORTA_PCR4  = (PORTA_PCR4  | 0x00000100) & ~0x00000600;

   //mode sortie
   GPIOA_PDDR = GPIOA_PDDR | 0x00003010;
   GPIOB_PDDR = GPIOB_PDDR | 0x00000007;
   GPIOC_PDDR = GPIOC_PDDR | 0x00000180;
   GPIOD_PDDR = GPIOD_PDDR | 0x000000f4;

   //valeurs acceptables
   GPIOA_PCOR = 0x00003010;
   GPIOB_PCOR = 0x00000004;
   GPIOB_PSOR = 0x00000003;
   GPIOC_PCOR = 0x00000300;
   GPIOD_PCOR = 0x000000f4;
   //100ms d'attente minimum
   for(int i=0; i<10000; i++) asm volatile("nop");
   GPIOB_PSOR = 0x00000004;
}

void SB(int x)
{
   if(x) GPIOB_PSOR = 0x00000001;
   else  GPIOB_PCOR = 0x00000001;
}

void LAT(int x)
{
   if(x) GPIOB_PSOR = 0x00000002;
   else  GPIOB_PCOR = 0x00000002;
}

void RST(int x)
{
   if(x) GPIOB_PSOR = 0x00000004;
   else  GPIOB_PCOR = 0x00000004;
}

void SCK(int x)
{
   if(x) GPIOC_PSOR = 0x00000100;
   else  GPIOC_PCOR = 0x00000100;
}

void SDA(int x)
{
   if(x) GPIOC_PSOR = 0x00000200;
   else  GPIOC_PCOR = 0x00000200;
}

void ROW0(int x)
{
   if(x) GPIOA_PSOR = 0x00002000;
   else  GPIOA_PCOR = 0x00002000;
}

void ROW1(int x)
{
   if(x) GPIOD_PSOR = 0x00000004;
   else  GPIOD_PCOR = 0x00000004;
}

void ROW2(int x)
{
   if(x) GPIOD_PSOR = 0x00000010;
   else  GPIOD_PCOR = 0x00000010;
}

void ROW3(int x)
{
   if(x) GPIOD_PSOR = 0x00000040;
   else  GPIOD_PCOR = 0x00000040;
}

void ROW4(int x)
{
   if(x) GPIOD_PSOR = 0x00000080;
   else  GPIOD_PCOR = 0x00000080;
}

void ROW5(int x)
{
   if(x) GPIOD_PSOR = 0x00000020;
   else  GPIOD_PCOR = 0x00000020;
}

void ROW6(int x)
{
   if(x) GPIOA_PSOR = 0x00001000;
   else  GPIOA_PCOR = 0x00001000;
}

void ROW7(int x)
{
   if(x) GPIOA_PSOR = 0x00000010;
   else  GPIOA_PCOR = 0x00000010;
}

//pulsation positive
void pulse_SCK()
{
   SCK(0);
   for(int i=0; i<10000; i++) asm volatile("nop");
   SCK(1);
   for(int i=0; i<10000; i++) asm volatile("nop");
   SCK(0);
   for(int i=0; i<10000; i++) asm volatile("nop");
}

//pulsation négative
void pulse_LAT()
{
   LAT(1);
   for(int i=0; i<10000; i++) asm volatile("nop");
   LAT(0);
   for(int i=0; i<10000; i++) asm volatile("nop");
   LAT(1);
   for(int i=0; i<10000; i++) asm volatile("nop");
}
