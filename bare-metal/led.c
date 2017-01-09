//led.c
#include led.h

void led_init()
{
   //activation horloge port D et E
   SIM_SCGC5 = SIM_SCGC5 | 0b11000000000000;

   //config GPIO (MUX = 001)
   PORTD_PCR5  = PORTD_PCR5  | 0b100000000;
   PORTD_PCR5  = PORTD_PCR5  & ~0b11000000000;
   PORTE_PCR29 = PORTE_PCR29 | 0b100000000;
   PORTE_PCR29 = PORTE_PCR29 & ~0b11000000000;

   //config sortie
   GPIOD_PDDR = 1;
   GPIOE_PDDR = 1;

   //allumage des leds
   GPIOD_PCOR = 0;
   GPIOE_PCOR = 0;
}
