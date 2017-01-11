//main.c

#include "led.h"

int main (void)
{
   led_init();

   while(1)
   {
      for(int i=0; i<10000; i++)
      {
         asm volatile("nop");
      }
   }
}
