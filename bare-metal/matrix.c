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

static void init_bank0();
static void SB  (int x);
static void LAT (int x);
static void RST (int x);
static void SCK (int x);
static void SDA (int x);
static void ROW0(int x);
static void ROW1(int x);
static void ROW2(int x);
static void ROW3(int x);
static void ROW4(int x);
static void ROW5(int x);
static void ROW6(int x);
static void ROW7(int x);
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
   RST (0);
   LAT (1);
   SB  (1);
   SCK (0);
   SDA (0);
   deactivate_rows();
   //100ms d'attente minimum
   for(int i=0; i<10000; i++) asm volatile("nop");
   RST(1);

   //initialisation du bank0  
   init_bank0();
}

static void SB(int x)
{
   if(x) GPIOB_PSOR = 0x00000001;
   else  GPIOB_PCOR = 0x00000001;
}

static void LAT(int x)
{
   if(x) GPIOB_PSOR = 0x00000002;
   else  GPIOB_PCOR = 0x00000002;
}

static void RST(int x)
{
   if(x) GPIOB_PSOR = 0x00000004;
   else  GPIOB_PCOR = 0x00000004;
}

static void SCK(int x)
{
   if(x) GPIOC_PSOR = 0x00000100;
   else  GPIOC_PCOR = 0x00000100;
}

static void SDA(int x)
{
   if(x) GPIOC_PSOR = 0x00000200;
   else  GPIOC_PCOR = 0x00000200;
}

static void ROW0(int x)
{
   if(x) GPIOA_PSOR = 0x00002000;
   else  GPIOA_PCOR = 0x00002000;
}

static void ROW1(int x)
{
   if(x) GPIOD_PSOR = 0x00000004;
   else  GPIOD_PCOR = 0x00000004;
}

static void ROW2(int x)
{
   if(x) GPIOD_PSOR = 0x00000010;
   else  GPIOD_PCOR = 0x00000010;
}

static void ROW3(int x)
{
   if(x) GPIOD_PSOR = 0x00000040;
   else  GPIOD_PCOR = 0x00000040;
}

static void ROW4(int x)
{
   if(x) GPIOD_PSOR = 0x00000080;
   else  GPIOD_PCOR = 0x00000080;
}

static void ROW5(int x)
{
   if(x) GPIOD_PSOR = 0x00000020;
   else  GPIOD_PCOR = 0x00000020;
}

static void ROW6(int x)
{
   if(x) GPIOA_PSOR = 0x00001000;
   else  GPIOA_PCOR = 0x00001000;
}

static void ROW7(int x)
{
   if(x) GPIOA_PSOR = 0x00000010;
   else  GPIOA_PCOR = 0x00000010;
}

//pulsation positive
static void pulse_SCK()
{
   SCK(0);
   asm volatile("nop"); // >25ns
   asm volatile("nop");
   SCK(1);
   asm volatile("nop"); // >25ns
   asm volatile("nop");
   SCK(0);
}

//pulsation négative
static void pulse_LAT()
{
   LAT(1);
   asm volatile("nop"); // >25ns
   asm volatile("nop");
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
   for(int i=5+(2*bank); i>=0; i--)
   {
      SDA(val & (1<<i));
      pulse_SCK();
   }
}

void mat_set_row(int row, const rgb_color *val)
{
   //activation d'une colonne
   for(int i=0; i<8; i++)
   {
      send_byte(val->b, 1);
      send_byte(val->g, 1);
      send_byte(val->r, 1);
      val++;
   }

   //activation d'une ligne
   activate_row(row);
   pulse_LAT();
}

static void init_bank0()
{
   for(int i=0; i<6; i++)
   {
      send_byte(0xff,0);
   }
   pulse_LAT();
}

void test_pixels()
{
   rgb_color val[8];

   //initialisation des pixels à 0
   for(int i=0; i<8; i++)
   {
      val[i].r=0;
      val[i].g=0;
      val[i].b=0;
   }

   //choix de pixels indépendants
   val[0].r=0xff;
   val[1].r=0xf0;
   val[2].r=0xf0;

   val[2].g=0xf0;
   val[3].g=0xf0;
   val[4].g=0xff;
   val[5].g=0xf0;
   val[6].g=0xf0;

   val[6].b=0xf0;
   val[7].b=0xf0;

   for(int i=0; i<8; i++)
   {
      mat_set_row(i, val);
   }
}
