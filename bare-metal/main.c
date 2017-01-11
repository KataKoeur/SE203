//main.c

#include "led.h"

int main (void)
{
   led_init();

   while(1)
   {
      for(int i=0; i<3; i++)
      {
         asm volatile("nop");
      }

      led_g_on();
      led_r_off();

      for(int i=0; i<3; i++)
      {
         asm volatile("nop");
      }

      led_g_off();
      led_r_on();
   }
}
