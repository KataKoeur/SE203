//led.c

#include "led.h"

#define SIM_SCGC5   (*(volatile uint32_t *)0x40048038)
#define PORTD_PCR5  (*(volatile uint32_t *)0x4004c014)
#define PORTE_PCR29 (*(volatile uint32_t *)0x4004d074)
#define GPIOD_PDDR  (*(volatile uint32_t *)0x400ff0d4)
#define GPIOE_PDDR  (*(volatile uint32_t *)0x400ff114)
#define GPIOD_PCOR  (*(volatile uint32_t *)0x400ff0c8)
#define GPIOE_PCOR  (*(volatile uint32_t *)0x400ff108)
#define GPIOD_PSOR  (*(volatile uint32_t *)0x400ff0c4)
#define GPIOE_PSOR  (*(volatile uint32_t *)0x400ff104)
#define GPIOD_PTOR  (*(volatile uint32_t *)0x400ff0cc)
#define GPIOE_PTOR  (*(volatile uint32_t *)0x400ff10c)

void led_init()
{
   //activation horloge port D et E
   SIM_SCGC5 |= 0x00003000;

   //config GPIO (MUX = 001)
   PORTD_PCR5  = (PORTD_PCR5  | 0x00000100) & ~0x00000600;
   PORTE_PCR29 = (PORTE_PCR29 | 0x00000100) & ~0x00000600;

   //config sortie
   GPIOD_PDDR |= 0x00000020;
   GPIOE_PDDR |= 0x20000000;

   //extinction des LEDs par défaut
   led_g_off();
   led_r_off();
}

void led_g_on()
{
   GPIOD_PCOR = 0x00000020;
}

void led_r_on()
{
   GPIOE_PCOR = 0x20000000;
}

void led_g_off()
{
   GPIOD_PSOR = 0x00000020;
}

void led_r_off()
{
   GPIOE_PSOR = 0x20000000;
}

void led_g_toggle()
{
   GPIOD_PTOR = 0x00000020;
}

void led_r_toggle()
{
   GPIOE_PTOR = 0x20000000;
}
