//matrix.c

#include "matrix.h"

#define SIM_SCGC5   (*(volatile uint32_t *)0x40048038)
#define PORTB_PCR0  (*(volatile uint32_t *)0x4004a000)
#define PORTB_PCR1  (*(volatile uint32_t *)0x4004a004)
#define PORTB_PCR2  (*(volatile uint32_t *)0x4004a008)
#define PORTC_PCR8  (*(volatile uint32_t *)0x4004b020)
#define PORTC_PCR9  (*(volatile uint32_t *)0x4004b024)
#define PORTA_PCR13 (*(volatile uint32_t *)0x40049034)
#define PORTD_PCR2  (*(volatile uint32_t *)0x4004c008)
#define PORTD_PCR4  (*(volatile uint32_t *)0x4004c010)
#define PORTD_PCR6  (*(volatile uint32_t *)0x4004c018)
#define PORTD_PCR7  (*(volatile uint32_t *)0x4004c01c)
#define PORTD_PCR5  (*(volatile uint32_t *)0x4004c014)
#define PORTA_PCR12 (*(volatile uint32_t *)0x40049030)
#define PORTA_PCR4  (*(volatile uint32_t *)0x40049010)
#define GPIOA_PDDR  (*(volatile uint32_t *)0x400ff014)
#define GPIOB_PDDR  (*(volatile uint32_t *)0x400ff054)
#define GPIOC_PDDR  (*(volatile uint32_t *)0x400ff094)
#define GPIOD_PDDR  (*(volatile uint32_t *)0x400ff0d4)
#define GPIOA_PCOR  (*(volatile uint32_t *)0x400ff008)
#define GPIOA_PSOR  (*(volatile uint32_t *)0x400ff004)
#define GPIOB_PCOR  (*(volatile uint32_t *)0x400ff048)
#define GPIOB_PSOR  (*(volatile uint32_t *)0x400ff044)
#define GPIOC_PCOR  (*(volatile uint32_t *)0x400ff088)
#define GPIOC_PSOR  (*(volatile uint32_t *)0x400ff084)
#define GPIOD_PCOR  (*(volatile uint32_t *)0x400ff0c8)
#define GPIOD_PSOR  (*(volatile uint32_t *)0x400ff0c4)

#define SB(x)   {if(x) GPIOB_PSOR = 0x00000001; else GPIOB_PCOR = 0x00000001;}
#define LAT(x)  {if(x) GPIOB_PSOR = 0x00000002; else GPIOB_PCOR = 0x00000002;}
#define RST(x)  {if(x) GPIOB_PSOR = 0x00000004; else GPIOB_PCOR = 0x00000004;}
#define SCK(x)  {if(x) GPIOC_PSOR = 0x00000100; else GPIOC_PCOR = 0x00000100;}
#define SDA(x)  {if(x) GPIOC_PSOR = 0x00000200; else GPIOC_PCOR = 0x00000200;}
#define ROW0(x) {if(x) GPIOA_PSOR = 0x00002000; else GPIOA_PCOR = 0x00002000;}
#define ROW1(x) {if(x) GPIOD_PSOR = 0x00000004; else GPIOD_PCOR = 0x00000004;}
#define ROW2(x) {if(x) GPIOD_PSOR = 0x00000010; else GPIOD_PCOR = 0x00000010;}
#define ROW3(x) {if(x) GPIOD_PSOR = 0x00000040; else GPIOD_PCOR = 0x00000040;}
#define ROW4(x) {if(x) GPIOD_PSOR = 0x00000080; else GPIOD_PCOR = 0x00000080;}
#define ROW5(x) {if(x) GPIOD_PSOR = 0x00000020; else GPIOD_PCOR = 0x00000020;}
#define ROW6(x) {if(x) GPIOA_PSOR = 0x00001000; else GPIOA_PCOR = 0x00001000;}
#define ROW7(x) {if(x) GPIOA_PSOR = 0x00000010; else GPIOA_PCOR = 0x00000010;}

rgb_color screen[64];

extern char _binary_image_raw_start; 
extern char _binary_image_raw_end; 

static void init_bank0();
static void pulse_SCK();
static void pulse_LAT();

void matrix_init()
{
   //activation horloge port A B C et D
   SIM_SCGC5 |= 0x00001e00;

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
   GPIOA_PDDR |= 0x00003010;
   GPIOB_PDDR |= 0x00000007;
   GPIOC_PDDR |= 0x00000300;
   GPIOD_PDDR |= 0x000000f4;

   //valeurs acceptables
   RST (0)
   LAT (1)
   SB  (1)
   SCK (0)
   SDA (0)
   deactivate_rows();
   //100ms d'attente minimum
   for(int i=0; i<10000; i++) asm volatile("nop");
   RST(1)

   //initialisation du bank0
   init_bank0();
}

//pulsation positive
static void pulse_SCK()
{
   SCK(0)
   asm volatile("nop"); // >25ns
   asm volatile("nop");
   SCK(1)
   asm volatile("nop"); // >25ns
   asm volatile("nop");
   SCK(0)
}

//pulsation négative
static void pulse_LAT()
{
   LAT(1)
   asm volatile("nop"); // >25ns
   asm volatile("nop");
   LAT(0)
   asm volatile("nop"); // >7ns
   LAT(1)
}

void deactivate_rows()
{
   ROW0(0)
   ROW1(0)
   ROW2(0)
   ROW3(0)
   ROW4(0)
   ROW5(0)
   ROW6(0)
   ROW7(0)
}

void activate_row(int row)
{
   if(row == 0)      ROW0(1)
   else if(row == 1) ROW1(1)
   else if(row == 2) ROW2(1)
   else if(row == 3) ROW3(1)
   else if(row == 4) ROW4(1)
   else if(row == 5) ROW5(1)
   else if(row == 6) ROW6(1)
   else if(row == 7) ROW7(1)
}

void send_byte(uint8_t val, int bank)
{
   //selection registre à décalage
   SB(bank)

   int pix_bits = bank? 8 : 6;

   //envoie bit à bit sur SDA
   for(int i=pix_bits-1; i>=0; i--)
   {
      SDA(val & (1<<i))
      pulse_SCK();
   }
}

void mat_set_row(int row, const rgb_color *val)
{
   //activation LED par LED
   for(int i=0; i<8; i++)
   {
      send_byte(val[7-i].b, 1);
      send_byte(val[7-i].g, 1);
      send_byte(val[7-i].r, 1);
   }

   //désactivation de toutes les lignes
   deactivate_rows();

   //attente pour eviter le clignotement des LEDs
   for(int i=0; i<500; i++) asm volatile("nop");

   pulse_LAT();

   //activation d'une ligne
   activate_row(row);
}

static void init_bank0()
{
   for(int i=0; i<8; i++)
   {
      send_byte(0xff,0);
      send_byte(0xff,0);
      send_byte(0xff,0);
   }
   pulse_LAT();
}

void test_pixels()
{
   rgb_color val[8];

   //dégradé de rouge
   for(int i=0; i<8; i++)
   {
      val[i].r = 255 >> i;
      val[i].g = 0;
      val[i].b = 0;
   }

   mat_set_row(0, val);
   mat_set_row(1, val);
   mat_set_row(2, val);
   
   //dégradé de vert
   for(int i=0; i<8; i++)
   {
      val[i].r = 0;
      val[i].g = 255 >> i;
      val[i].b = 0;
   }

   mat_set_row(3, val);
   mat_set_row(4, val);
   mat_set_row(5, val);

   //dégradé de bleu
   for(int i=0; i<8; i++)
   {
      val[i].r = 0;
      val[i].g = 0;
      val[i].b = 255 >> i;
   }

   mat_set_row(6, val);
   mat_set_row(7, val);
}   

void test_static_image()
{
   rgb_color val[8];
   char *i = &_binary_image_raw_start;
   int row = 0;
   int led = 0;

   while(i < &_binary_image_raw_end)   
   {
      for(led = 0; led<8; led++)
      {
         val[led].r = *i++;
         val[led].g = *i++;
         val[led].b = *i++;
      }
      mat_set_row(row, val);
      row++;
   }
}

void display_screen()
{
   for(int row=0; row<8; row++)
   {
      mat_set_row(row, screen+(row*8));
   }
}
