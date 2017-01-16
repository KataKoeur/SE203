//main.c

#include "led.h"
#include "uart.h"

void clocks_init();

int sum = 0;

int main (void)
{
   clocks_init();
   led_init();
   uart_init();

   while(1)
   {
      sum = sum + uart_getchar();
   }
}
