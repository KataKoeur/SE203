//main.c

#include "led.h"
#include "uart.h"

void clocks_init();

int main (void)
{
   clocks_init();
   led_init();
   uart_init();

   int sum = 0;

   while(1)
   {
      sum = sum + uart_getchar();
      uart_putchar(sum);
   }
}
