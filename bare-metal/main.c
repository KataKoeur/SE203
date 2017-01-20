//main.c

#include "led.h"
#include "uart.h"
#include "matrix.h"

void clocks_init();

int main (void)
{
   //initialisation
   clocks_init();
   led_init();
   uart_init();
   matrix_init();

   //code

   while(1) test_static_image();
}
