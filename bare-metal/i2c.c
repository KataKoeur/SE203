//i2c.c

#include "i2c.h"

#define PORTE_PCR24 (*(volatile uint32_t *)0x4004d060)
#define PORTE_PCR25 (*(volatile uint32_t *)0x4004d064)
#define PORTC_PCR5  (*(volatile uint32_t *)0x4004b014)
#define PORTD_PCR1  (*(volatile uint32_t *)0x4004c004)
#define SIM_SCGC4   (*(volatile uint32_t *)0x40048034)
#define SIM_SCGC5   (*(volatile uint32_t *)0x40048038)

void i2c_init()
{
   //activation horloge
   SIM_SCGC4 |= 1<<6;
   SIM_SCGC5 |= 1<<11;
   SIM_SCGC5 |= 1<<12;
   SIM_SCGC5 |= 1<<13;

   //mode i2c
   PORTE_PCR24 = (PORTE_PCR24 | 0x00000500) & ~0x00000200; //SCL
   PORTE_PCR25 = (PORTE_PCR25 | 0x00000500) & ~0x00000200; //SDA
}
