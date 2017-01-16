//main.c

#include "led.h"
#include "uart.h"

void clocks_init();

int main (void)
{
   clocks_init();
   led_init();
   uart_init();

   while(1)
   {
      led_g_toggle();
      led_r_toggle();

      uart_putchar('G');

      for(int i=0; i<10000000; i++)
      {
         asm volatile("nop");
      }
   }
}
