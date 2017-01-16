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
      uart_putchar(uart_getchar());
   }
}
