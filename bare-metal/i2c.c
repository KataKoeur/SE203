//i2c.c

#include "i2c.h"

#define PORTE_PCR24 (*(volatile uint32_t *)0x4004d060)
#define PORTE_PCR25 (*(volatile uint32_t *)0x4004d064)
#define PORTC_PCR5  (*(volatile uint32_t *)0x4004b014)
#define PORTD_PCR1  (*(volatile uint32_t *)0x4004c004)
#define SIM_SCGC4   (*(volatile uint32_t *)0x40048034)
#define SIM_SCGC5   (*(volatile uint32_t *)0x40048038)
#define I2C0_A1     (*(volatile uint8_t  *)0x40066000)
#define I2C0_F      (*(volatile uint8_t  *)0x40066001)
#define I2C0_C1     (*(volatile uint8_t  *)0x40066002)
#define I2C0_S      (*(volatile uint8_t  *)0x40066003)
#define I2C0_D      (*(volatile uint8_t  *)0x40066004)
#define I2C0_C2     (*(volatile uint8_t  *)0x40066005)
#define I2C0_FLT    (*(volatile uint8_t  *)0x40066006)
#define I2C0_RA     (*(volatile uint8_t  *)0x40066007)
#define I2C0_SMR    (*(volatile uint8_t  *)0x40066008)
#define I2C0_A2     (*(volatile uint8_t  *)0x40066009)
#define I2C0_SLTH   (*(volatile uint8_t  *)0x4006600A)
#define I2C0_SLTL   (*(volatile uint8_t  *)0x4006600B)

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

   //Baud rate = 24MHz/(4*20) = 300kHz
   I2C0_F = 0x80;

   //adresse esclave
   I2C0_A1 = 0x1E;

   //mode master
   I2C0_C1 |= 1<<5;

   //activation i2c
   I2C0_C1 |= 1<<7;
}
