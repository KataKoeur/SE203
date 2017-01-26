//buttons.c

#include "led.h"
#include "irq.h"

#define SIM_SCGC5  (*(volatile uint32_t *)0x40048038)
#define PORTC_PCR3 (*(volatile uint32_t *)0x4004b00c)
#define GPIOC_PDDR (*(volatile uint32_t *)0x400ff094)

void button_init(void)
{
   //activation horloge port C
   SIM_SCGC5 |= 0x00000800;

   //config du port C3
   PORTC_PCR3 = (PORTC_PCR3 | 0x000a0103) & ~0x00050600;

   //config entrée
   GPIOC_PDDR &= ~0x00000008;

   //activation interrupttion port C
   irq_enable(31);
}

void PORTCD_IRQHandler(void)
{
   disable_irq() 
   led_r_toggle();
   PORTC_PCR3 |= 0x01000000; //flag
   enable_irq()
}
