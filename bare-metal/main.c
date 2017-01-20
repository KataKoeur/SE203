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
   test_pixels();
   
   while(1);
}
