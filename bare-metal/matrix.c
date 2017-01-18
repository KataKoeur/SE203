//matrix.c

#include "matrix.h"

void matrix_init()
{
   //activation horloge port A B C et D
   SIM_SCGC5 = SIM_SCGC5 | 0x00001e00;

   //mode GPIO
   PORTB_PCR0  = (PORTB_PCR0  | 0x00000100) & ~0x00000600;
   PORTB_PCR1  = (PORTB_PCR1  | 0x00000100) & ~0x00000600;
   PORTB_PCR2  = (PORTB_PCR2  | 0x00000100) & ~0x00000600;
   PORTC_PCR8  = (PORTC_PCR8  | 0x00000100) & ~0x00000600;
   PORTC_PCR9  = (PORTC_PCR9  | 0x00000100) & ~0x00000600;
   PORTA_PCR13 = (PORTA_PCR13 | 0x00000100) & ~0x00000600;
   PORTD_PCR2  = (PORTD_PCR2  | 0x00000100) & ~0x00000600;
   PORTD_PCR4  = (PORTD_PCR4  | 0x00000100) & ~0x00000600;
   PORTD_PCR6  = (PORTD_PCR6  | 0x00000100) & ~0x00000600;
   PORTD_PCR7  = (PORTD_PCR7  | 0x00000100) & ~0x00000600;
   PORTD_PCR5  = (PORTD_PCR5  | 0x00000100) & ~0x00000600;
   PORTA_PCR12 = (PORTA_PCR12 | 0x00000100) & ~0x00000600;
   PORTA_PCR4  = (PORTA_PCR4  | 0x00000100) & ~0x00000600;

   //mode sortie
   GPIOA_PDDR = GPIOA_PDDR | 0x00003010;
   GPIOB_PDDR = GPIOB_PDDR | 0x00000007;
   GPIOC_PDDR = GPIOC_PDDR | 0x00000180;
   GPIOD_PDDR = GPIOD_PDDR | 0x000000f4;

   //valeurs acceptables
   GPIOA_PCOR = 0x00003010;
   GPIOB_PCOR = 0x00000004;
   GPIOB_PSOR = 0x00000003;
   GPIOC_PCOR = 0x00000300;
   GPIOD_PCOR = 0x000000f4;
   //100ms d'attente minimum
   for(int i=0; i<10000; i++) asm volatile("nop");
   GPIOB_PSOR = 0x00000004;
}

void SB(int x)
{
   if(x) GPIOB_PSOR = 0x00000001;
   else  GPIOB_PCOR = 0x00000001;
}

void LAT(int x)
{
   if(x) GPIOB_PSOR = 0x00000002;
   else  GPIOB_PCOR = 0x00000002;
}

void RST(int x)
{
   if(x) GPIOB_PSOR = 0x00000004;
   else  GPIOB_PCOR = 0x00000004;
}

void SCK(int x)
{
   if(x) GPIOC_PSOR = 0x00000100;
   else  GPIOC_PCOR = 0x00000100;
}

void SDA(int x)
{
   if(x) GPIOC_PSOR = 0x00000200;
   else  GPIOC_PCOR = 0x00000200;
}

void ROW0(int x)
{
   if(x) GPIOA_PSOR = 0x00002000;
   else  GPIOA_PCOR = 0x00002000;
}

void ROW1(int x)
{
   if(x) GPIOD_PSOR = 0x00000004;
   else  GPIOD_PCOR = 0x00000004;
}

void ROW2(int x)
{
   if(x) GPIOD_PSOR = 0x00000010;
   else  GPIOD_PCOR = 0x00000010;
}

void ROW3(int x)
{
   if(x) GPIOD_PSOR = 0x00000040;
   else  GPIOD_PCOR = 0x00000040;
}

void ROW4(int x)
{
   if(x) GPIOD_PSOR = 0x00000080;
   else  GPIOD_PCOR = 0x00000080;
}

void ROW5(int x)
{
   if(x) GPIOD_PSOR = 0x00000020;
   else  GPIOD_PCOR = 0x00000020;
}

void ROW6(int x)
{
   if(x) GPIOA_PSOR = 0x00001000;
   else  GPIOA_PCOR = 0x00001000;
}

void ROW7(int x)
{
   if(x) GPIOA_PSOR = 0x00000010;
   else  GPIOA_PCOR = 0x00000010;
}

//pulsation positive
void pulse_SCK()
{
   SCK(0);
   asm volatile("nop"); // >25ns
   SCK(1);
   asm volatile("nop"); // >25ns
   SCK(0);
}

//pulsation négative
void pulse_LAT()
{
   LAT(1);
   asm volatile("nop"); // >25ns
   LAT(0);
   asm volatile("nop"); // >7ns
   LAT(1);
}

void deactivate_rows()
{
   ROW0(0);
   ROW1(0);
   ROW2(0);
   ROW3(0);
   ROW4(0);
   ROW5(0);
   ROW6(0);
   ROW7(0);
}

void activate_row(int row)
{
   if(row == 0)      ROW0(1);
   else if(row == 1) ROW1(1);
   else if(row == 2) ROW2(1);
   else if(row == 3) ROW3(1);
   else if(row == 4) ROW4(1);
   else if(row == 5) ROW5(1);
   else if(row == 6) ROW6(1);
   else if(row == 7) ROW7(1);
}

void send_byte(uint8_t val, int bank)
{
   //selection registre à décalage
   SB(bank);

   //envoie bit à bit sur SDA
   for(int i=7+(2*bank); i>=0; i++)
   {
      SDA(val & ~(1<<i));
      pulse_SCK();
   }
}

void mat_set_row(int row, const rgb_color *val)
{
   //envoie des 8 pixels sur le bank1
   for(int i=0; i<8; i++)
   {
      send_byte(val->b, 1);
      send_byte(val->g, 1);
      send_byte(val->r, 1);
      val++;
   }

   //activation d'une colonne
   activate_row(row);
   pulse_LAT();
}
