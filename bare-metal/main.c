//main.c

#include "led.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"
#include "pit.h"
#include "clocks.h"

int main (void)
{
   //initialisation
   clocks_init();
   irq_init();
   led_init();
   uart_init();
   matrix_init();
   button_init();
   pit_init();

   //code
   while(1);
}
