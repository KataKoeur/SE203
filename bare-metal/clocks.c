//clocks.c

#include "clocks.h"

#define MCG_C1      (*(volatile uint8_t  *)0x40064000)
#define MCG_C2      (*(volatile uint8_t  *)0x40064001)
#define MCG_C3      (*(volatile uint8_t  *)0x40064002)
#define MCG_C4      (*(volatile uint8_t  *)0x40064003)
#define MCG_C5      (*(volatile uint8_t  *)0x40064004)
#define MCG_C6      (*(volatile uint8_t  *)0x40064005)
#define MCG_S       (*(volatile uint8_t  *)0x40064006)
#define MCG_SC      (*(volatile uint8_t  *)0x40064008)
#define MCG_ATCVH   (*(volatile uint8_t  *)0x4006400a)
#define MCG_ATCVL   (*(volatile uint8_t  *)0x4006400b)
#define MCG_C7      (*(volatile uint8_t  *)0x4006400c)
#define MCG_C8      (*(volatile uint8_t  *)0x4006400d)
#define MCG_C9      (*(volatile uint8_t  *)0x4006400e)
#define MCG_C10     (*(volatile uint8_t  *)0x4006400f)
#define SIM_COPC    (*(volatile uint32_t *)0x40048100)
#define SIM_CLKDIV1 (*(volatile uint32_t *)0x40048044)

void clocks_init()
{
   int BLPE_mode = 0;

   //désactivation du watchdog
   SIM_COPC = 0x00;

   //FEI vers FBE

   //C2[RANGE0] set to 2'b01 because the frequency of 4 MHz is within the high frequency range.
   //C2[HGO0]   set to 1 to configure the crystal oscillator for high gain operation.
   //C2[EREFS0] set to 1, because a crystal is being used.
   MCG_C2 = 0x1c;

   //C1[CLKS]  set to 2'b10 to select external reference clock as system clock source
   //C1[FRDIV] set to 3'b011, or divide-by-256 because 8 MHz / 256 = 31.25 kHz which is in the 31.25 kHz to 39.0625 kHz range required by the FLL
   //C1[IREFS] cleared to 0, selecting the external reference clock and enabling the external oscillator.
   MCG_C1 = 0x98;

   //Loop until S[OSCINIT0] is 1, indicating the crystal selected by C2[EREFS0] has been initialized.
   while(!(MCG_S & (1<<1)));

   //Loop until S[IREFST] is 0, indicating the external reference is the current source for the reference clock.
   while(MCG_S & (1<<4));

   //Loop until S[CLKST] is 2'b10, indicating that the external reference clock is selected to feed MCGOUTCLK.
   while((MCG_S & 0x0c) != 0x08);

   //C5[PRDIV] set to 5'b00011, or divide-by-4 resulting in a pll reference frequency of 8MHz/4 = 2 MHz.
   MCG_C5 = 0x03;


   //FBE vers PBE

   //BLPE: If a transition through BLPE mode is desired, first set C2[LP] to 1.
   if(BLPE_mode) MCG_C2 |= (1<<1);

   //C6[PLLS] set to 1, selects the PLL. At this time, with a C5[PRDIV0] value of 2'b00011, the PLL reference divider is 4 (see PLL External Reference Divide Factor table), resulting in a reference frequency of 8 MHz/ 4 = 2 MHz. In BLPE mode, changing the C6[PLLS] bit only prepares the MCG for PLL usage in PBE mode.
   //C6[VDIV] set to 5'b00000, or multiply-by-24 because 2 MHz reference * 24 = 48 MHz. In BLPE mode, the configuration of the VDIV bits does not matter because the PLL is disabled. Changing them only sets up the multiply value for PLL usage in PBE mode.
   MCG_C6 = 0x40;

   //BLPE: If transitioning through BLPE mode, clear C2[LP] to 0 here to switch to PBE mode.
   if(BLPE_mode) MCG_C2 &= ~(1<<1);

   //PBE: Loop until S[PLLST] is set, indicating that the current source for the PLLS clock is the PLL.
   while(!(MCG_S & (1<<5)));

   //PBE: Then loop until S[LOCK0] is set, indicating that the PLL has acquired lock.
   while(!(MCG_S & (1<<6)));


   //PBE vers PEE

   //C1[CLKS] set to 2'b00 to select the output of the PLL as the system clock source.
   MCG_C1 &= ~0xc0;

   //Loop until S[CLKST] are 2'b11, indicating that the PLL output is selected to feed MCGOUTCLK in the current clock mode.
   while((MCG_S & 0x0c) != 0x0c);

   //config horloge périphériques
   SIM_CLKDIV1 = 1<<16;
}
