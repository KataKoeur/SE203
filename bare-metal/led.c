//led.c

#include "led.h"

void led_init()
{
   //activation horloge port D et E
   SIM_SCGC5 = SIM_SCGC5 | 0x00003000;

   //config GPIO (MUX = 001)
   PORTD_PCR5  = PORTD_PCR5  |  0x00000100;
   PORTD_PCR5  = PORTD_PCR5  & ~0x00000600;
   PORTE_PCR29 = PORTE_PCR29 |  0x00000100;
   PORTE_PCR29 = PORTE_PCR29 & ~0x00000600;

   //config sortie
   GPIOD_PDDR = GPIOD_PDDR | 0x00000020;
   GPIOE_PDDR = GPIOE_PDDR | 0x20000000;

   //allumage des leds
   GPIOD_PCOR = GPIOD_PCOR & ~0x00000020;
   GPIOE_PCOR = GPIOE_PCOR & ~0x20000000;
}
