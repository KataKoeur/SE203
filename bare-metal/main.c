//main.c

#include "led.h"

int main (void)
{
   led_init();

   while(1)
   {
      led_g_toggle();
      led_r_toggle();

      for(int i=0; i<3; i++)
      {
         asm volatile("nop");
      }
   }
}
