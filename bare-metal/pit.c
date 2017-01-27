//pit.c

#include "pit.h"

#define SIM_SCGC6  (*(volatile uint32_t *)0x4004803c)
#define PIT_MCR    (*(volatile uint32_t *)0x40037000)
#define PIT_LDVAL0 (*(volatile uint32_t *)0x40037100)
#define PIT_TCTRL0 (*(volatile uint32_t *)0x40037108)
#define PIT_TFLG0  (*(volatile uint32_t *)0x4003710c)

void pit_init()
{
   //activation horloge PIT
   SIM_SCGC6 |= 1<<23;
   PIT_MCR = 0x00000000;

   //fréquence des interruptions (70Hz)
   PIT_LDVAL0 = 0x00053b49;

   //abaissement du flag
   PIT_TFLG0 = 0x00000001;

   //activation timer et interruption
   irq_enable(22);
   PIT_TCTRL0 = 0x00000003;
}

void PIT_IRQHandler()
{
   display_screen();
   //abaissement du flag
   PIT_TFLG0 = 0x00000001;
}
