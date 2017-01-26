//main.c

#include "led.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"

void clocks_init();
void button_init();

int main (void)
{
   //initialisation
   clocks_init();
   irq_init();
   led_init();
   uart_init();
   matrix_init();
   button_init();

   //code
   while(1) display_screen();
}
