#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

//variable globale initialisé => .data
int32_t globale1 =34;
int32_t globale2 =34;

int main()
{
  //variable pointeur => .heap
  uint16_t *ptr1 = (uint16_t*) malloc(16);
  uint16_t *ptr2 = (uint16_t*) malloc(16);

  //variable locale non static initialisé => .stack
  uint16_t locale1 = 12;
  uint16_t locale2 = 12;
  uint16_t locale3 = 12;
  uint16_t locale4 = 12;

  printf("globale1  = %p\n", &globale1);
  printf("globale2  = %p\n", &globale2);
  printf("ptr1      = %p\n", ptr1);
  printf("ptr2      = %p\n", ptr2);
  printf("locale1   = %p\n", &locale1);
  printf("locale2   = %p\n", &locale2);
  printf("locale3   = %p\n", &locale3);
  printf("locale4   = %p\n", &locale4);

  return 0;
}
